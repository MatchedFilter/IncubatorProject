#include "Incubator/View/Screen/ScreenFacade.h"


namespace Incubator
{
    ScreenFacade::ScreenFacade() :
        m_Lcd { nullptr },
        m_CurrentScreen { nullptr }
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
        m_IncubatorSettingsScreen.Initialize(tc2004Lcd);
        m_TimeSettingsScreen.Initialize(tc2004Lcd);
        m_DefaultsSettingsScreen.Initialize(tc2004Lcd);
        m_QuestionScreen.Initialize(tc2004Lcd);
        m_CurrentScreen = &m_MenuScreen;
        m_DataChangedEventHandlers.Reset();
        m_DataChangedEventHandlers.Copy(*eventHandlers);
    }

    void ScreenFacade::UpdatePidData(const PidData &data)
    {
        m_CurrentPidData.Copy(data);
    }

    void ScreenFacade::UpdateSettingsData(const SettingsData &data)
    {
        m_CurrentSettingsData.Copy(data);
        m_MenuScreen.UpdateSettingsData(data);
    }

    void ScreenFacade::UpdateTimeInformationData(const TimeInformationData &data)
    {
        m_CurrentTimeInformationData.Copy(data);
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

        switch (m_CurrentScreen->GetScreenType())
        {
        case SCREEN_TYPE_MENU:
        {
            if (event.bIsButtonPressed)
            {
                m_CurrentScreen = &m_SettingsScreen;
                m_SettingsScreen.OnInitial();
            }
            else
            {
                m_CurrentScreen->OnUserAction(event);
            }
            break;
        }
        case SCREEN_TYPE_SETTINGS:
        {
            if (event.bIsLeftPressed)
            {
                m_CurrentScreen = &m_MenuScreen;
                m_MenuScreen.OnInitial();
            }
            else if (event.bIsRightPressed)
            {
                if (SETTINGS_SCREEN_LINE_INCUBATOR == m_SettingsScreen.GetSettingsScreenLine())
                {
                    m_IncubatorSettingsScreen.OnInitial();
                    m_CurrentScreen = &m_IncubatorSettingsScreen;
                }
                else if (SETTINGS_SCREEN_LINE_TIME == m_SettingsScreen.GetSettingsScreenLine())
                {
                    m_TimeSettingsScreen.OnInitial();
                    m_CurrentScreen = &m_TimeSettingsScreen;
                }
                else
                {
                    // intentionally left blank
                }
            }
            else
            {
                m_SettingsScreen.OnUserAction(event);
            }
            break;
        }
        case SCREEN_TYPE_INCUBATOR_SETTINGS:
        {
            if (event.bIsLeftPressed)
            {
                m_CurrentScreen = &m_SettingsScreen;
                m_SettingsScreen.OnInitial();
            }
            else if (event.bIsRightPressed)
            {
                if (INCUBATOR_SETTINGS_SCREEN_LINE_DEFAULT == m_IncubatorSettingsScreen.GetLine())
                {
                    m_CurrentScreen = &m_DefaultsSettingsScreen;
                    m_DefaultsSettingsScreen.OnInitial();
                }
            }
            else
            {
                m_IncubatorSettingsScreen.OnUserAction(event);
            }
            break;
        }
        case SCREEN_TYPE_TIME_SETTINGS:
        {
            if (event.bIsLeftPressed)
            {
                m_CurrentScreen = &m_SettingsScreen;
                m_SettingsScreen.OnInitial();
            }
            else if (event.bIsRightPressed)
            {
            }
            else
            {
                m_TimeSettingsScreen.OnUserAction(event);
            }
            break;
        }
        case SCREEN_TYPE_DEFAULTS_SETTINGS:
        {
            if (event.bIsLeftPressed)
            {
                m_CurrentScreen = &m_IncubatorSettingsScreen;
                m_IncubatorSettingsScreen.OnInitial();
            }
            else if (event.bIsRightPressed)
            {
                m_CurrentScreen = &m_QuestionScreen;
                m_ChangedSettingsData.Copy(m_CurrentSettingsData);
                switch (m_DefaultsSettingsScreen.GetLine())
                {
                case DEFAULTS_SETTINGS_SCREEN_LINE_CHICKEN:
                {
                    m_QuestionScreen.OnInitial();
                    m_Lcd->MoveCursor(1U, 0U);
                    m_Lcd->Print(TC2004::String80("Se"));
                    m_Lcd->Print(TC2004::TC2004_CHAR_LOWER_C);
                    m_Lcd->Print(TC2004::String80("ilen: Tavuk"));
                    m_ChangedSettingsData.Reset();
                    break;
                }

                case DEFAULTS_SETTINGS_SCREEN_LINE_GOOSE:
                {
                    m_QuestionScreen.OnInitial();
                    m_Lcd->MoveCursor(1U, 0U);
                    m_Lcd->Print(TC2004::String80("Se"));
                    m_Lcd->Print(TC2004::TC2004_CHAR_LOWER_C);
                    m_Lcd->Print(TC2004::String80("ilen: Kaz"));
                    m_ChangedSettingsData.m_TemperatureInMilliCelcius = static_cast<uint32_t>(37700UL);
                    m_ChangedSettingsData.m_LastDaysTemperatureInMilliCelcius = static_cast<uint32_t>(37000UL);
                    m_ChangedSettingsData.m_HumidityInPercentage = 60U;
                    m_ChangedSettingsData.m_LastDaysHumidityInPercentage = 70U;
                    m_ChangedSettingsData.m_TotalIncubationDayCount = 28U;
                    m_ChangedSettingsData.m_LastDaysCount = 3U;

                    break;
                }

                case DEFAULTS_SETTINGS_SCREEN_LINE_DUCK:
                {
                    m_QuestionScreen.OnInitial();
                    m_Lcd->MoveCursor(1U, 0U);
                    m_Lcd->Print(TC2004::String80("Se"));
                    m_Lcd->Print(TC2004::TC2004_CHAR_LOWER_C);
                    m_Lcd->Print(TC2004::String80("ilen: "));
                    m_Lcd->Print(TC2004::TC2004_CHAR_UPPER_O);
                    m_Lcd->Print(TC2004::String80("rdek"));

                    m_ChangedSettingsData.m_TemperatureInMilliCelcius = static_cast<uint32_t>(37800UL);
                    m_ChangedSettingsData.m_LastDaysTemperatureInMilliCelcius = static_cast<uint32_t>(37200UL);
                    m_ChangedSettingsData.m_HumidityInPercentage = 65U;
                    m_ChangedSettingsData.m_LastDaysHumidityInPercentage = 80U;
                    m_ChangedSettingsData.m_TotalIncubationDayCount = 24U;
                    m_ChangedSettingsData.m_LastDaysCount = 4U;
                    break;
                }
                
                default:
                    break;
                }
            }
            else
            {
                m_DefaultsSettingsScreen.OnUserAction(event);
            }
            break;
        }

        case SCREEN_TYPE_QUESTION:
        {
            m_QuestionScreen.OnUserAction(event);
            if (event.bIsButtonPressed)
            {
                if (QUESTION_SELECTION_YES == m_QuestionScreen.GetQuestionSelection())
                {
                    m_DataChangedEventHandlers.m_SettingsDataChangedEventHandler->OnUpdate(m_ChangedSettingsData);
                }
                m_QuestionScreen.Reset();
                m_CurrentScreen = &m_DefaultsSettingsScreen; // TODO: will be updated
                m_DefaultsSettingsScreen.OnInitial();
            }
            break;
        }

        
        default:
            break;
        }
    }

    void ScreenFacade::Run()
    {
        m_CurrentScreen->Run();
    }


} // namespace Incubator
