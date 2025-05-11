#include "Incubator/View/Lcd2004View.h"
#include "Incubator/View/JoystickEvent.h"
#include "Incubator/IncubatorDependencies.h"

namespace Incubator
{
    void Lcd2004View::ReadJoystick()
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
                        const JoystickEvent event = {
                            .bIsUpPressed = true,
                            .bIsDownPressed = false,
                            .bIsRightPressed = false,
                            .bIsLeftPressed = false,
                            .bIsButtonPressed = false
                        };
                        OnUserAction(event);
                    }
                    else if (m_bDownShifted)
                    {
                        const JoystickEvent event = {
                            .bIsUpPressed = false,
                            .bIsDownPressed = true,
                            .bIsRightPressed = false,
                            .bIsLeftPressed = false,
                            .bIsButtonPressed = false
                        };
                        OnUserAction(event);
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
                        const JoystickEvent event = {
                            .bIsUpPressed = false,
                            .bIsDownPressed = false,
                            .bIsRightPressed = false,
                            .bIsLeftPressed = true,
                            .bIsButtonPressed = false
                        };
                        OnUserAction(event);
                    }
                }
                else if (horizontalValue < LOWER_THRESHOLD)
                {
                    m_bLeftShifted = true;
                    if (m_bRightShifted)
                    {
                        const JoystickEvent event = {
                            .bIsUpPressed = false,
                            .bIsDownPressed = false,
                            .bIsRightPressed = true,
                            .bIsLeftPressed = false,
                            .bIsButtonPressed = false
                        };
                        OnUserAction(event);
                    }
                }
                else
                {
                    if (m_bRightShifted)
                    {
                        const JoystickEvent event = {
                            .bIsUpPressed = false,
                            .bIsDownPressed = false,
                            .bIsRightPressed = true,
                            .bIsLeftPressed = false,
                            .bIsButtonPressed = false
                        };
                        OnUserAction(event);
                    }
                    else if (m_bLeftShifted)
                    {
                        const JoystickEvent event = {
                            .bIsUpPressed = false,
                            .bIsDownPressed = false,
                            .bIsRightPressed = false,
                            .bIsLeftPressed = true,
                            .bIsButtonPressed = false
                        };
                        OnUserAction(event);
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
                    const JoystickEvent event = {
                        .bIsUpPressed = false,
                        .bIsDownPressed = false,
                        .bIsRightPressed = false,
                        .bIsLeftPressed = false,
                        .bIsButtonPressed = true
                    };
                    OnUserAction(event);
                }
            }
            m_bSwitchPressed = bIsSwitchPressed;
            m_JoystickSensorTimerTask.Start();
        }
    }

    void Lcd2004View::OnUserAction(const JoystickEvent event)
    {
        m_ScreenFacade.OnUserAction(event);
    }

    Lcd2004View::Lcd2004View() : 
        m_TC2004Lcd { static_cast<uint8_t>(0U) },
        m_bIsInitialized { false },
        m_JoystickSensor { 0x00U },
        m_bLastStateWasHorizontal { false },
        m_bUpShifted { false },
        m_bDownShifted { false },
        m_bRightShifted { false },
        m_bLeftShifted { false },
        m_bSwitchPressed { false }
    {
    }

    Lcd2004View::~Lcd2004View()
    {
    }

    bool Lcd2004View::Initialize(const DataChangedEventHandlers *eventHandlers)
    {
        bool bResult = false;
        m_JoystickSensorTimerTask.SetDurationInMillisecond(static_cast<uint32_t>(20UL));
        constexpr uint32_t MAX_TRY_COUNT = static_cast<uint32_t>(5UL);
        
        for (uint32_t i = static_cast<uint32_t>(0UL); i < MAX_TRY_COUNT; i++ )
        {
            if(m_TC2004Lcd.Initialize(true))
            {
                bResult = true;
                m_bIsInitialized = true;
                DelayInMillisecond(static_cast<uint32_t>(5UL));
                m_TC2004Lcd.Clear();
                m_TC2004Lcd.MoveCursor(0U, 0U);
                m_ScreenFacade.Initialize(&m_TC2004Lcd, eventHandlers);
                m_JoystickSensorTimerTask.Start();
                break;
            }
        }
        return bResult;
    }

    void Lcd2004View::UpdateTemperature(const double temperatureInCelcius)
    {
        if (m_bIsInitialized)
        {
            m_ScreenFacade.UpdateTemperature(temperatureInCelcius);
        }
    }

    void Lcd2004View::OnTemperatureFailure()
    {
        m_ScreenFacade.OnTemperatureFailure();
    }

    void Lcd2004View::UpdateHumidity(const uint8_t humidityInPercentage)
    {
        m_ScreenFacade.UpdateHumidity(humidityInPercentage);
    }

    void Lcd2004View::OnHumidityFailure()
    {
        m_ScreenFacade.OnHumidityFailure();
    }

    void Lcd2004View::UpdateAdminData(const AdminData &data)
    {
        m_ScreenFacade.UpdateAdminData(data);
    }

    void Lcd2004View::UpdateSettingsData(const SettingsData &data)
    {
        m_ScreenFacade.UpdateSettingsData(data);
    }

    void Lcd2004View::UpdateTimeInformationData(const TimeInformationData &data)
    {
        m_ScreenFacade.UpdateTimeInformationData(data);
    }

    void Lcd2004View::OnModelFailure()
    {
        m_ScreenFacade.OnModelFailure();
    }

    void Lcd2004View::UpdateSensorsStatus(const SensorsStatusData &data)
    {
        m_ScreenFacade.UpdateSensorsStatus(data);
    }

    void Lcd2004View::Run()
    {
        if (m_bIsInitialized)
        {
            ReadJoystick();
            m_ScreenFacade.Run();
        }
    }

} // namespace Incubator
