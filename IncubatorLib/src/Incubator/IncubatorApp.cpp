#include "Incubator/IncubatorApp.h"
#include "Incubator/IncubatorDependencies.h"
#include "Incubator/Time/TimeUtils.h"

namespace Incubator
{

    bool IncubatorApp::ReadSht31(double &temperatureInCelcius, double &humidityInPercent)
    {
        bool bResult = false;
        if (m_Sht31FailureReadTimerTask.IsFinished())
        {
            bResult = true;
            if (false == m_SHT31Sensor.Read(temperatureInCelcius, humidityInPercent))
            {
                constexpr uint8_t ALLOWED_SHT31_FAIL_COUNT = 5U;
                if (m_Sht31FailCount > ALLOWED_SHT31_FAIL_COUNT)
                {
                    bResult = false;
                    m_Sht31FailureReadTimerTask.Start();
                }
                else
                {
                    m_Sht31FailCount++;
                    temperatureInCelcius = m_PrevSht31Temp;
                    humidityInPercent = m_PrevSht31Humidity;
                }
            }
            else
            {
                m_Sht31FailCount = 0U;
                m_PrevSht31Temp = temperatureInCelcius;
                m_PrevSht31Humidity = humidityInPercent;
            }
        }
        m_SensorsStatusData.m_Sht31Status = SENSOR_STATUS_ERROR;
        if (bResult)
        {
            m_SensorsStatusData.m_Sht31Status = SENSOR_STATUS_NO_ERROR;
        }

        return bResult;
    }

    bool IncubatorApp::ReadDht11(double &temperatureInCelcius, double &humidityInPercent)
    {
        bool bResult = false;
        if (m_Dht11FailureReadTimerTask.IsFinished())
        {
            bResult = true;
            if (false == m_DHT11Sensor.Read(temperatureInCelcius, humidityInPercent))
            {
                constexpr uint8_t ALLOWED_DHT11_FAIL_COUNT = 15U;
                if (m_Dht11FailCount > ALLOWED_DHT11_FAIL_COUNT)
                {
                    bResult = false;
                    m_Dht11FailureReadTimerTask.Start();
                }
                else
                {
                    m_Dht11FailCount++;
                    temperatureInCelcius = m_PrevDht11Temp;
                    humidityInPercent = m_PrevDht11Humidity;
                }
            }
            else
            {
                m_Dht11FailCount = 0U;
                m_PrevDht11Temp = temperatureInCelcius;
                m_PrevDht11Humidity = humidityInPercent;
            }
        }
        m_SensorsStatusData.m_Dht11Status = SENSOR_STATUS_ERROR;
        if (bResult)
        {
            m_SensorsStatusData.m_Dht11Status = SENSOR_STATUS_NO_ERROR;
        }
        return bResult;
    }

    bool IncubatorApp::ReadNtc(double &temperatureInCelcius, const double &sht31Temp, const double &dht11Temp)
    {
        bool bResult = false;
        if (m_TemperatureSensor.Read(temperatureInCelcius))
        {
            constexpr double TOLERANCE = 7.0;
            constexpr uint8_t ALLOWED_DHT11_FAILURE_COUNT_FOR_NTC_COMPARISION = 15U;
            if (0U == m_Sht31FailCount)
            {
                bResult = ((sht31Temp - temperatureInCelcius) < TOLERANCE) && ((sht31Temp - temperatureInCelcius) > -TOLERANCE);
            }
            else if (ALLOWED_DHT11_FAILURE_COUNT_FOR_NTC_COMPARISION > m_Dht11FailCount)
            {
                bResult = ((dht11Temp - temperatureInCelcius) < TOLERANCE) && ((dht11Temp - temperatureInCelcius) > -TOLERANCE);
            }
            else
            {
                bResult = true;
            }
        }
        if (bResult)
        {
            m_PrevNtc = temperatureInCelcius;
            m_SensorsStatusData.m_NtcStatus = SENSOR_STATUS_NO_ERROR;
        }
        else
        {
            m_SensorsStatusData.m_NtcStatus = SENSOR_STATUS_ERROR;
        }
        return bResult;
    }

    void IncubatorApp::ReadSensors(bool &bTemperatureValid, double &temperatureInCelcius, bool &bHumidityValid, uint8_t &humidityInPercent)
    {
        double sht31Temp = 0.0;
        double sht31Humidity = 0.0;
        const bool bSht31Working = ReadSht31(sht31Temp, sht31Humidity);

        double dht11Temp = 0.0;
        double dht11Humidity = 0.0;
        const bool bDht11Working = ReadDht11(dht11Temp, dht11Humidity);

        double ntcTemp;
        const bool bNtcWorking = ReadNtc(ntcTemp, sht31Temp, dht11Temp);

        if (bSht31Working)
        {
            bHumidityValid = true;
            bTemperatureValid = true;
            humidityInPercent = static_cast<uint8_t>(sht31Humidity);
            temperatureInCelcius = sht31Temp;
        }
        else if (bDht11Working)
        {
            bHumidityValid = true;
            bTemperatureValid = true;
            humidityInPercent = static_cast<uint8_t>(dht11Humidity);
            temperatureInCelcius = bNtcWorking ? ntcTemp : dht11Temp;
        }
        else if (bNtcWorking)
        {
            bHumidityValid = false;
            bTemperatureValid = true;
            temperatureInCelcius = ntcTemp;
        }
        else
        {
            bHumidityValid = false;
            bTemperatureValid = false;
        }
    }

    void IncubatorApp::UpdatePresenter(const bool &bTemperatureValid, const double &temperatureInCelcius, const bool &bHumidityValid, const double &humidityInPercent)
    {
        m_Presenter.UpdateSensorsStatus(m_SensorsStatusData);
        if (bTemperatureValid)
        {
            m_Presenter.UpdateTemperature(temperatureInCelcius);
        }
        else
        {
            m_Presenter.OnTemperatureFailure();
        }

        if (bHumidityValid)
        {
            m_Presenter.UpdateHumidity(static_cast<uint8_t>(humidityInPercent));
        }
        else
        {
            m_Presenter.OnHumidityFailure();
        }
    }

    bool IncubatorApp::CalculateTemperatureOutput(const bool &bTemperatureValid, const double &temperatureInCelcius)
    {
        bool bResult = false;
        double desiredTemperatureInCelcius;
        if (bTemperatureValid)
        {
            if (GetDesiredTemperature(desiredTemperatureInCelcius))
            {
                const double temperatureDifference = desiredTemperatureInCelcius - temperatureInCelcius;
                constexpr double THRESHOLD_TEMPERATURE_LOW_DIFFERENCE_IN_MILLICELCIUS = 5.0;
                constexpr double THRESHOLD_TEMPERATURE_HIGH_DIFFERENCE_IN_MILLICELCIUS = -1.0;

                if (temperatureDifference > THRESHOLD_TEMPERATURE_LOW_DIFFERENCE_IN_MILLICELCIUS)
                {
                    bResult = true;
                    m_TemperatureOutputValue = MAX_TEMPERATURE_OUTPUT_CONTROL_VALUE;
                }
                else if (temperatureDifference < THRESHOLD_TEMPERATURE_HIGH_DIFFERENCE_IN_MILLICELCIUS)
                {
                    bResult = true;
                    m_TemperatureOutputValue = static_cast<uint16_t>(0UL);
                }
                else
                {
                    m_TemperatureController.SetDesiredTemperature(desiredTemperatureInCelcius);
                    double p,i,d;
                    if (m_Presenter.GetPidData(p,i,d))
                    {
                        bResult = true;
                        m_TemperatureController.SetPid(p,i,d);
                        m_TemperatureOutputValue = m_TemperatureController.Control(temperatureInCelcius, SENSOR_READ_TIMEOUT_IN_MILLISECOND);
                    }
                }
            }
        }
        return bResult;
    }

    void IncubatorApp::ControlTemperature()
    {
        if (m_TemperatureOutputTimeoutTask.IsFinished())
        {
            m_TemperatureOutputValue = static_cast<uint16_t>(0UL);
        }
        if (m_TemperatureOutputTimerTask.IsFinished())
        {
            m_TemperatureOutputTimerTask.Start();
            m_TemperatureOutputControlCounter += static_cast<uint16_t>(2UL);

            if (m_TemperatureOutputValue > m_TemperatureOutputControlCounter)
            {
                TurnOnHeater();
            }
            else
            {
                TurnOffHeater();
            }
            if (MAX_TEMPERATURE_OUTPUT_CONTROL_VALUE <= m_TemperatureOutputControlCounter)
            {
                m_TemperatureOutputControlCounter = static_cast<uint16_t>(0UL);
            }
        }
    }

    void IncubatorApp::ControlHumidity(uint8_t &humidityInPercentage, bool bHumidityValid)
    {
        EnumState state = STATE_OFF;
        if (bHumidityValid)
        {
            m_HumidityController.UpdateHumidityFailStatus(false);
            uint8_t desiredHumidityInPercentage;
            if (GetDesiredHumidity(desiredHumidityInPercentage))
            {
                uint8_t upperDiff, lowerDiff;
                if (m_Presenter.GetHumidityHysterisisDiff(upperDiff, lowerDiff))
                {
                    const uint8_t upperThresholdInPercentage = ((desiredHumidityInPercentage + upperDiff) > 100U) ? 100U : desiredHumidityInPercentage + upperDiff;
                    const uint8_t lowerThresholdInPercentage = (lowerDiff > desiredHumidityInPercentage) ? 0U : desiredHumidityInPercentage - lowerDiff;
                    m_HumidityController.SetHumidityThresholds(upperThresholdInPercentage, lowerThresholdInPercentage);
                    state = m_HumidityController.Control(humidityInPercentage);
                }

            }
        }
        else
        {
            m_HumidityController.UpdateHumidityFailStatus(true);
            state = m_HumidityController.Control(humidityInPercentage);
        }
        if (STATE_OFF == state)
        {
            TurnOffHumidityGenerator();
        }
        else
        {
            TurnOnHumidityGenerator();
        }

    }


    bool IncubatorApp::GetDesiredTemperature(double &desiredTemperatureInCelcius)
    {
        bool bResult = false;
        SettingsData settings;
        if (m_Presenter.GetSettingsData(settings))
        {
            bResult = true;
            const uint8_t dayCount = static_cast<uint8_t>(Time::TimeUtils::GetIncubatorTimestampInSecond() / (static_cast<uint32_t>(60UL) * static_cast<uint32_t>(60UL) * static_cast<uint32_t>(24UL)));
            if (dayCount >= (settings.m_TotalIncubationDayCount - settings.m_LastDaysCount))
            {
                desiredTemperatureInCelcius = static_cast<double>(settings.m_LastDaysTemperatureInMilliCelcius) / 1000.0;
            }
            else
            {
                desiredTemperatureInCelcius = static_cast<double>(settings.m_TemperatureInMilliCelcius) / 1000.0;
            }
        }

        return bResult;
    }

    bool IncubatorApp::GetDesiredHumidity(uint8_t &desiredHumidityInPercent)
    {
        bool bResult = false;
        SettingsData settings;
        if (m_Presenter.GetSettingsData(settings))
        {
            bResult = true;
            const uint8_t dayCount = static_cast<uint8_t>(Time::TimeUtils::GetIncubatorTimestampInSecond() / (static_cast<uint32_t>(60UL) * static_cast<uint32_t>(60UL) * static_cast<uint32_t>(24UL)));
            if (dayCount >= (settings.m_TotalIncubationDayCount - settings.m_LastDaysCount))
            {
                desiredHumidityInPercent = settings.m_LastDaysHumidityInPercentage;
            }
            else
            {
                desiredHumidityInPercent = settings.m_HumidityInPercentage;
            }
        }
        return bResult;
    }


    IncubatorApp::IncubatorApp() :
        m_InternalFlashModel { static_cast<uint32_t>(0x0801F000UL) },
        m_DHT11Sensor { 0x00U },
        m_TemperatureSensor { 0x00U },
        m_SHT31Sensor { 0x00U },
        m_Dht11FailCount { 0U },
        m_Sht31FailCount { 0U },
        m_NtcFailCount { 0U },
        m_PrevDht11Temp { 0.0 },
        m_PrevDht11Humidity { 0.0 },
        m_PrevSht31Temp { 0.0 },
        m_PrevSht31Humidity { 0.0 },
        m_PrevNtc { 0.0 },
        m_SensorsStatusData { .m_Sht31Status = SENSOR_STATUS_ERROR, .m_NtcStatus = SENSOR_STATUS_ERROR, .m_Dht11Status = SENSOR_STATUS_ERROR },
        m_TemperatureOutputValue { static_cast<uint16_t>(0U)},
        m_TemperatureOutputControlCounter { static_cast<uint16_t>(0U)}
    {
    }

    IncubatorApp::~IncubatorApp()
    {
    }

    void IncubatorApp::Initialize(void)
    {
        DelayInMillisecond(static_cast<uint32_t>(100UL));
        m_TemperatureSensor.Initialize(100.0);
        m_SHT31Sensor.Initialize();

        m_EepromModel.Initialize();
        m_Presenter.Initialize(&m_Lcd2004View, &m_EepromModel, &m_InternalFlashModel);

        m_SensorReadTimerTask.SetDurationInMillisecond(SENSOR_READ_TIMEOUT_IN_MILLISECOND);
        m_SensorReadTimerTask.Start();

        m_Sht31FailureReadTimerTask.SetDurationInMillisecond(SENSOR_FAIL_RETRY_TIMEOUT_IN_MILLISECOND);
        m_Sht31FailureReadTimerTask.Start();
        m_Dht11FailureReadTimerTask.SetDurationInMillisecond(SENSOR_FAIL_RETRY_TIMEOUT_IN_MILLISECOND);
        m_Dht11FailureReadTimerTask.Start();

        constexpr uint32_t TEMPERATURE_OUTPUT_VALUE_SET_TIMEOUT_IN_MILLISECOND = static_cast<uint32_t>(5000UL);
        m_TemperatureOutputTimeoutTask.SetDurationInMillisecond(TEMPERATURE_OUTPUT_VALUE_SET_TIMEOUT_IN_MILLISECOND);
        
        constexpr uint32_t TEMPERATURE_OUTPUT_CONTROL_DURATION_IN_MILLISECOND = static_cast<uint32_t>(2UL);
        m_TemperatureOutputTimerTask.SetDurationInMillisecond(TEMPERATURE_OUTPUT_CONTROL_DURATION_IN_MILLISECOND);
        m_TemperatureOutputTimerTask.Start();
    }

    void IncubatorApp::Run(void)
    {
        m_Presenter.Run();
        m_Lcd2004View.Run();
        
        if (m_SensorReadTimerTask.IsFinished())
        {
            m_SensorReadTimerTask.Start();
            double temperatureInCelcius;
            uint8_t humidityInPercent;
            bool bTemperatureIsValid, bHumidityIsValid;
            ReadSensors(bTemperatureIsValid, temperatureInCelcius, bHumidityIsValid, humidityInPercent);
            UpdatePresenter(bTemperatureIsValid, temperatureInCelcius, bHumidityIsValid, humidityInPercent);
            if (CalculateTemperatureOutput(bTemperatureIsValid, temperatureInCelcius))
            {
                m_TemperatureOutputTimeoutTask.Start();
            }
            ControlHumidity(humidityInPercent, bHumidityIsValid);
        }
        ControlTemperature();
    }

} // namespace Incubator
