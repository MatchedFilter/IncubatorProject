#include "Incubator/View/Screen/ScreenFacade.h"

namespace Incubator
{
    ScreenFacade::ScreenFacade() :
        m_Lcd { nullptr },
        m_CurrentScreen { nullptr },
        m_PidDataChangedEventHandler { nullptr },
        m_SettingsDataChangedEventHandler { nullptr },
        m_TimeInformationDataChangedEventHandler { nullptr }

    {
    }

    ScreenFacade::~ScreenFacade()
    {
    }

    void ScreenFacade::Initialize(TC2004::Lcd * tc2004Lcd, const DataChangedEventHandlers *eventHandlers)
    {
        m_Lcd = tc2004Lcd;
        m_MenuScreen.Initialize(tc2004Lcd);
        m_SettingsScreen.Initialize(tc2004Lcd);
        m_CurrentScreen = &m_MenuScreen;
        m_DataChangedEventHandlers.Reset();
        m_DataChangedEventHandlers.Copy(*eventHandlers);
    }

    void ScreenFacade::UpdatePidData(const PidData &data)
    {
    }

    void ScreenFacade::UpdateSettingsData(const SettingsData &data)
    {
        m_MenuScreen.UpdateSettingsData(data);
    }

    void ScreenFacade::UpdateTimeInformationData(const TimeInformationData &data)
    {
        m_MenuScreen.UpdateTimeInformationData(data);
    }

    void ScreenFacade::UpdateTemperature(const double &temperatureInCelcius)
    {
        m_MenuScreen.UpdateTemperature(temperatureInCelcius);
    }

    void ScreenFacade::OnTemperatureFailure()
    {
        m_CurrentScreen = &m_MenuScreen;
        m_MenuScreen.OnTemperatureFailure();
    }

    void ScreenFacade::UpdateHumidity(const uint8_t &humidityInPrecentage)
    {
        m_MenuScreen.UpdateHumidity(humidityInPrecentage);
    }

    void ScreenFacade::OnHumidityFailure()
    {
        m_MenuScreen.OnHumidityFailure();
    }

    void ScreenFacade::OnModelFailure()
    {
        m_CurrentScreen = &m_MenuScreen;
        m_MenuScreen.OnModelFailure();
    }

    void ScreenFacade::OnUserAction(const JoystickEvent &event)
    {
        if (SCREEN_TYPE_MENU == m_CurrentScreen->GetScreenType())
        {
            if (event.bIsButtonPressed)
            {
                m_CurrentScreen = &m_SettingsScreen;
                m_SettingsScreen.OnInitial();
            }
        }
        else
        {
            if (event.bIsLeftPressed)
            {
                switch (m_CurrentScreen->GetScreenType())
                {   
                case SCREEN_TYPE_SETTINGS:
                    m_MenuScreen.OnInitial();
                    m_CurrentScreen = &m_MenuScreen;
                    break;
                
                default:
                    break;
                }
            }
            else
            {
                m_CurrentScreen->OnUserAction(event);
            }
        }
    }

    void ScreenFacade::Run()
    {
        m_CurrentScreen->Run();
    }



} // namespace Incubator
