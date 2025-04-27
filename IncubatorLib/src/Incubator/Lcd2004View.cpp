#include "Incubator/Lcd2004View.h"

namespace Incubator
{
        
    Lcd2004View::Lcd2004View() : 
        m_TC2004Lcd ( static_cast<uint8_t>(0U) ),
        m_bTemperatureValid ( true ),
        m_bHumidityValid ( true ),
        m_TemperatureInCelcius ( static_cast<int16_t>(0)),
        m_HumidityInPercentage ( static_cast<int16_t>(0)),
        m_JoystickSensor ( 0x00U ),
        m_bLastStateWasHorizontal ( false ),
        m_bUpShifted ( false ),
        m_bDownShifted ( false ),
        m_bRightShifted ( false ),
        m_bLeftShifted ( false ),
        m_bSwitchPressed ( false )
    {
    }

    Lcd2004View::~Lcd2004View()
    {
    }

    void Lcd2004View::Initialize(void)
    {
        m_IncubatorInformationData.Reset();
        m_JoystickSensorTimerTask.SetDurationInMillisecond(static_cast<uint32_t>(20UL));
        if (m_TC2004Lcd.Initialize(true))
        {
            m_TC2004Lcd.Clear();
            m_TC2004Lcd.MoveCursor(0U, 0U);
            m_TC2004Lcd.Print(TC2004::String80("S"));
            m_TC2004Lcd.Print(TC2004::TC2004_CHAR_LOWER_I);
            m_TC2004Lcd.Print(TC2004::String80("cakl"));
            m_TC2004Lcd.Print(TC2004::TC2004_CHAR_LOWER_I);
            m_TC2004Lcd.Print(TC2004::String80("k: -"));

            m_TC2004Lcd.MoveCursor(1U, 0U);
            m_TC2004Lcd.Print(TC2004::String80("Nem: -"));

            m_TC2004Lcd.MoveCursor(2U, 0U);
            m_TC2004Lcd.Print(TC2004::String80("T: -"));
        }
    }

    void Lcd2004View::UpdateTemperature(const double temperatureInCelcius)
    {
        m_TemperatureInCelcius = temperatureInCelcius;
        m_TC2004Lcd.MoveCursor(0U, 10U);

        const int32_t temperatureLeftPart = static_cast<int32_t>(m_TemperatureInCelcius);
        const int32_t temperatureRightPart = static_cast<int32_t>((m_TemperatureInCelcius - static_cast<float>(temperatureLeftPart)) * 10.0F);
        TC2004::String80 temperatureString;
        temperatureString += temperatureLeftPart;
        temperatureString += TC2004::String80(".");
        temperatureString += temperatureRightPart;
        temperatureString += TC2004::String80("  ");
        m_TC2004Lcd.Print(temperatureString);
    }

    void Lcd2004View::OnTemperatureFailure(const uint8_t errorCode)
    {
        m_bTemperatureValid = false;
        m_TC2004Lcd.MoveCursor(0U, 11U);
        TC2004::String80 errorString ("E");
        errorString += static_cast<int32_t>(errorCode);
        errorString += TC2004::String80("   ");
        m_TC2004Lcd.Print(errorString);
        m_TC2004Lcd.MoveCursor(1U, 11U);
        m_TC2004Lcd.Print(errorString);
        m_TC2004Lcd.MoveCursor(2U, 11U);
        m_TC2004Lcd.Print(errorString);
    }

    void Lcd2004View::UpdateHumidity(const double humidityInPercentage)
    {
        m_HumidityInPercentage = humidityInPercentage;
        m_TC2004Lcd.MoveCursor(1U, 5U);

        const int32_t humidityLeftPart = static_cast<int32_t>(m_HumidityInPercentage);
        const int32_t humidityRightPart = static_cast<int32_t>((m_HumidityInPercentage - static_cast<float>(humidityLeftPart)) * 10.0F);
        TC2004::String80 humidityString;
        humidityString += humidityLeftPart;
        humidityString += TC2004::String80(".");
        humidityString += humidityRightPart;
        humidityString += TC2004::String80("  ");
        m_TC2004Lcd.Print(humidityString);
    }

    void Lcd2004View::OnHumidityFailure(const uint8_t errorCode)
    {
        m_bHumidityValid = false;
        TC2004::String80 errorString ("E");
        errorString += static_cast<int32_t>(errorCode);
        errorString += TC2004::String80("   ");
        m_TC2004Lcd.MoveCursor(1U, 5U);
        m_TC2004Lcd.Print(errorString);
    }

    void Lcd2004View::UpdateSettingsData(const SettingsData &data)
    {

        m_IncubatorInformationData.m_SettingsData.Copy(data);
        TC2004::String80 settingsString;
        settingsString.Clear();
        settingsString += static_cast<int32_t>(data.m_TemperatureInMilliCelcius / static_cast<uint32_t>(1000UL));
        settingsString += ".";
        settingsString += static_cast<int32_t>((data.m_TemperatureInMilliCelcius / static_cast<uint32_t>(100UL)) % static_cast<uint32_t>(10UL));
        m_TC2004Lcd.MoveCursor(2U, 3U);
        m_TC2004Lcd.Print(settingsString);
    }

    void Lcd2004View::UpdateTimeInformationData(const TimeInformationData &data)
    {
        m_IncubatorInformationData.m_TimeInformationData.Copy(data);
    }

    void Lcd2004View::Run()
    {
        if (m_JoystickSensorTimerTask.IsFinished())
        {
            constexpr uint32_t UPPER_THRESHOLD = static_cast<uint32_t>(2900UL);
            constexpr uint32_t LOWER_THRESHOLD = static_cast<uint32_t>(1100UL);
            if (m_bLastStateWasHorizontal)
            {
                m_bLastStateWasHorizontal = false;
                const uint32_t verticalValue = m_JoystickSensor.ReadVerticalValue();

                if (verticalValue > UPPER_THRESHOLD)
                {
                    m_bUpShifted = true;
                }
                else if (verticalValue < LOWER_THRESHOLD)
                {
                    m_bDownShifted = true;
                }
                else
                {
                    if (m_bUpShifted)
                    {
                        OnUserAction(true, false, false, false, false);
                    }
                    else if (m_bDownShifted)
                    {
                        OnUserAction(false, true, false, false, false);
                    }
                    else
                    {
                    }
                    m_bUpShifted = false;
                    m_bDownShifted = false;
                }
            }
            else
            {
                m_bLastStateWasHorizontal = true;
                const uint32_t horizontalValue = m_JoystickSensor.ReadHorizontalValue();

                if (horizontalValue > UPPER_THRESHOLD)
                {
                    m_bRightShifted = true;
                    if (m_bLeftShifted)
                    {
                        m_bLeftShifted = false;
                        OnUserAction(false, false, false, true, false);
                    }
                }
                else if (horizontalValue < LOWER_THRESHOLD)
                {
                    m_bLeftShifted = true;
                    if (m_bRightShifted)
                    {
                        m_bRightShifted = false;
                        OnUserAction(false, false, true, false, false);
                    }
                }
                else
                {
                    if (m_bRightShifted)
                    {
                        OnUserAction(false, false, true, false, false);
                    }
                    else if (m_bLeftShifted)
                    {
                        OnUserAction(false, false, false, true, false);
                    }
                    else
                    {
                    }
                    m_bRightShifted = false;
                    m_bLeftShifted = false;
                }
            }
            
            const bool bIsSwitchPressed = m_JoystickSensor.IsSwitchPressed();
            if (false == bIsSwitchPressed)
            {
                if (m_bSwitchPressed)
                {
                    OnUserAction(false, false, false, false, true);
                }
            }
            m_bSwitchPressed = bIsSwitchPressed;
            m_JoystickSensorTimerTask.Start();
        }
        
        uint32_t horizontalValue = m_JoystickSensor.ReadHorizontalValue();
    }


    void Lcd2004View::OnUserAction(const bool bUpKeyPressed, const bool bDownKeyPressed, const bool bRightKeyPressed, const bool bLeftKeyPressed, const bool bSwitchClicked)
    {
    }




} // namespace Incubator
