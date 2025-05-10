#include "Incubator/View/Screen/ScreenFacade.h"

namespace Incubator
{
    ScreenFacade::ScreenFacade() :
        m_Lcd { nullptr },
        m_ScreenList { nullptr },
        m_CurrentScreen { nullptr }
    {
    }

    ScreenFacade::~ScreenFacade()
    {
    }

    void ScreenFacade::Initialize(TC2004::Lcd * tc2004Lcd, const DataChangedEventHandlers *eventHandlers)
    {
        m_Lcd = tc2004Lcd;
        m_DataChangedEventHandlers.Reset();
        m_DataChangedEventHandlers.Copy(*eventHandlers);

        m_MenuScreen.Initialize(tc2004Lcd);
        m_SettingsScreen.Initialize(tc2004Lcd);
        m_IncubatorSettingsScreen.Initialize(tc2004Lcd);
        m_TimeSettingsScreen.Initialize(tc2004Lcd);
        m_TemperatureSettingsScreen.Initialize(tc2004Lcd);
        m_TemperatureDataSetScreen.Initialize(tc2004Lcd,
                &m_DataChangedEventHandlers,
                &m_CurrentIncubatorInformationData,
                &m_ChangedIncubatorInformationData);

        m_TemperatureLastDaysDataSetScreen.Initialize(tc2004Lcd,
            &m_DataChangedEventHandlers,
            &m_CurrentIncubatorInformationData,
            &m_ChangedIncubatorInformationData);
        
        m_DefaultsSettingsScreen.Initialize(tc2004Lcd, &m_ChangedIncubatorInformationData.m_SettingsData);
        m_QuestionScreen.Initialize(tc2004Lcd, &m_DataChangedEventHandlers, &m_ChangedIncubatorInformationData.m_SettingsData);

        m_ScreenList[SCREEN_TYPE_MENU]                              = &m_MenuScreen;
        m_ScreenList[SCREEN_TYPE_SETTINGS]                          = &m_SettingsScreen;
        m_ScreenList[SCREEN_TYPE_INCUBATOR_SETTINGS]                = &m_IncubatorSettingsScreen;
        m_ScreenList[SCREEN_TYPE_TIME_SETTINGS]                     = &m_TimeSettingsScreen;
        m_ScreenList[SCREEN_TYPE_TEMPERATURE_SETTINGS]              = &m_TemperatureSettingsScreen;
        m_ScreenList[SCREEN_TYPE_DATA_SET_TEMPERATURE]              = &m_TemperatureDataSetScreen;
        m_ScreenList[SCREEN_TYPE_DATA_SET_TEMPERATURE_LAST_DAYS]    = &m_TemperatureLastDaysDataSetScreen;
        m_ScreenList[SCREEN_TYPE_DEFAULTS_SETTINGS]                 = &m_DefaultsSettingsScreen;
        m_ScreenList[SCREEN_TYPE_QUESTION]                          = &m_QuestionScreen;

        m_CurrentScreen = &m_MenuScreen;

    }

    void ScreenFacade::UpdatePidData(const PidData &data)
    {
        m_CurrentIncubatorInformationData.m_PidData.Copy(data);
    }

    void ScreenFacade::UpdateSettingsData(const SettingsData &data)
    {
        m_CurrentIncubatorInformationData.m_SettingsData.Copy(data);
        m_MenuScreen.UpdateSettingsData(data);
    }

    void ScreenFacade::UpdateTimeInformationData(const TimeInformationData &data)
    {
        m_CurrentIncubatorInformationData.m_TimeInformationData.Copy(data);
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
        const EnumScreenType screenType =  m_CurrentScreen->GetScreenType();
        m_CurrentScreen->OnUserAction(event);
        const EnumScreenType nextScreenType = m_CurrentScreen->GetNextScreen();
        if (screenType != nextScreenType)
        {
            const EnumScreenType nextValidScreenType = (static_cast<uint32_t>(nextScreenType) < static_cast<uint32_t>(SCREEN_TYPE_SIZE)) ? nextScreenType : SCREEN_TYPE_MENU;
            m_CurrentScreen = m_ScreenList[nextValidScreenType];
            m_CurrentScreen->SetPreviousScreen(screenType);
            m_CurrentScreen->OnInitial();
        }
    }

    void ScreenFacade::Run()
    {
        m_CurrentScreen->Run();
    }


} // namespace Incubator
