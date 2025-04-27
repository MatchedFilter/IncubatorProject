#include "Incubator/Presenter.h"
#include "Incubator/IncubatorData/IncubatorInformationData.h"

namespace Incubator
{
    void DelayInMillisecond(uint32_t durationInMillisecond);

    Presenter::Presenter() :
        m_View ( nullptr ),
        m_Model ( nullptr ),
        m_DHT11Sensor ( 0x00U ),
        m_SHT31Sensor ( 0x00U ),
        m_TemperatureSensor ( 0x00U )
    {
    }

    Presenter::~Presenter()
    {
    }

    void Presenter::Initialize(IView *view, IModel *model, IModel* spareModel)
    {
        m_View = view;
        m_Model = model;
        m_SpareModel = spareModel;
        m_TemperatureSensor.Initialize(100.0);
        m_SHT31Sensor.Initialize();

        IncubatorInformationData data;
        data.Reset();
        (void) m_Model->Update(data.m_SettingsData);
        (void) m_Model->Update(data.m_TimeInformationData);
        // (void) m_SpareModel->Update(data.m_SettingsData);
        (void) m_SpareModel->Update(data.m_TimeInformationData);
    }

    void Presenter::Run(void)
    {
        static uint32_t counter = 0UL;
        if (m_View != nullptr)
        {
            double sht11TemperatureInCelcius = 0.0;
            double sht11HumidityInPercentage = 0.0;
            if (m_SHT31Sensor.Read(sht11TemperatureInCelcius, sht11HumidityInPercentage))
            {
                m_View->UpdateTemperature(sht11TemperatureInCelcius);
                m_View->UpdateHumidity(sht11HumidityInPercentage);
            }
            else
            {
                m_View->OnTemperatureFailure(0x00U);
                m_View->OnHumidityFailure(0x00U);
            }
            DelayInMillisecond(1000UL);
            /**
            float dht11TemperatureInCelcius, humidityInPercentage;
            const uint8_t dht11Result = m_DHT11Sensor.Read(dht11TemperatureInCelcius, humidityInPercentage);
            if (0x00U == dht11Result)
            {
                m_Dht11FailureCount = static_cast<uint32_t>(0UL);
                m_View->UpdateHumidity(humidityInPercentage);
            }
            else
            {
                m_Dht11FailureCount++;
                m_View->OnHumidityFailure(dht11Result);
            }
            float temperatureInCelcius;
            if (DetermineTemperature(temperatureInCelcius, dht11TemperatureInCelcius))
            {
                m_View->UpdateTemperature(temperatureInCelcius);
            }
            else
            {
                m_View->OnTemperatureFailure(dht11Result);
            }
            SettingsData sData;
            m_SpareModel->Get(sData);
            m_View->UpdateSettingsData(sData);

            DelayInMillisecond(1000UL);
            counter++;
            if (counter == 15UL)
            {
                sData.m_TemperatureInMilliCelcius = 41700UL;
                (void) m_SpareModel->Update(sData);
                counter = 0UL;  
            }
            */
        }
    }

    bool Presenter::DetermineTemperature(float &resultInCelcius, const float &dht11TemperatureInCelcius)
    {
        bool bResult = false;
        double ntcTemperatureInCelcius;
        const bool bNtcWorking = m_TemperatureSensor.Read(ntcTemperatureInCelcius);
        if (bNtcWorking)
        {
            bResult = true;
            if (m_Dht11FailureCount < MAX_DHT11_FAILURE_COUNT)
            {
                const float tempDifference = (static_cast<float>(ntcTemperatureInCelcius) - dht11TemperatureInCelcius < 0) ? (dht11TemperatureInCelcius - static_cast<float>(ntcTemperatureInCelcius)) : (static_cast<float>(ntcTemperatureInCelcius) - dht11TemperatureInCelcius);
                if (tempDifference < 10.0F)
                {
                    resultInCelcius = static_cast<float>(ntcTemperatureInCelcius);
                }
                else
                {
                    resultInCelcius = dht11TemperatureInCelcius;
                }
            }
            else
            {
                resultInCelcius = static_cast<float>(ntcTemperatureInCelcius);
            }
        }
        else
        {
            if (m_Dht11FailureCount < MAX_DHT11_FAILURE_COUNT)
            {
                resultInCelcius = dht11TemperatureInCelcius;
                bResult = true;
            }
        }
        return bResult;
    }


} // namespace Incubator
