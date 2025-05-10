#ifndef INCUBATOR_SCREENFACADE_H
#define INCUBATOR_SCREENFACADE_H
#include "TC2004/Lcd.h"
#include "MenuScreen.h"
#include "SettingsScreen.h"
#include "IncubatorSettingsScreen.h"
#include "TimeSettingsScreen.h"
#include "DefaultsSettingsScreen.h"
#include "TemperatureSettingsScreen.h"
#include "HumiditySettingsScreen.h"
#include "DataSetScreen/TemperatureDataSetScreen.h"
#include "DataSetScreen/TemperatureLastDaysDataSetScreen.h"
#include "DataSetScreen/HumidityDataSetScreen.h"
#include "DataSetScreen/HumidityLastDaysDataSetScreen.h"
#include "QuestionScreen/SaveQuestionScreen.h"
#include "QuestionScreen/TimeResetQuestionScreen.h"
#include "CurrentTimeSettingsScreen.h"
#include "DataSetScreen/CurrentDayDataSetScreen.h"
#include "DataSetScreen/CurrentHourDataSetScreen.h"
#include "DataSetScreen/CurrentMinuteDataSetScreen.h"

#include "Incubator/View/DataChangedEventHandler/DataChangedEventHandlers.h"
#include "Incubator/IncubatorData/IncubatorInformationData.h"

namespace Incubator
{
    class ScreenFacade
    {
    public:
        ScreenFacade();
        ~ScreenFacade();
        void Initialize(TC2004::Lcd * tc2004Lcd, const DataChangedEventHandlers *eventHandlers);

        void UpdatePidData(const PidData &data);
        void UpdateSettingsData(const SettingsData &data);
        void UpdateTimeInformationData(const TimeInformationData &data);
        void UpdateTemperature(const double &temperatureInCelcius);
        void OnTemperatureFailure();
        void UpdateHumidity(const uint8_t &humidityInPrecentage);
        void OnHumidityFailure();
        void UpdateTime(const uint32_t timestampInSeconds);

        void OnModelFailure();
        void OnUserAction(const JoystickEvent &event);
        void Run();

    private:
        TC2004::Lcd *m_Lcd;
        AScreen *m_ScreenList[SCREEN_TYPE_SIZE];
        AScreen *m_CurrentScreen;
        MenuScreen m_MenuScreen;
        SettingsScreen m_SettingsScreen;
        TimeSettingsScreen m_TimeSettingsScreen;
        IncubatorSettingsScreen m_IncubatorSettingsScreen;
        TemperatureSettingsScreen m_TemperatureSettingsScreen;
        HumiditySettingsScreen m_HumiditySettingsScreen;
        TemperatureDataSetScreen m_TemperatureDataSetScreen;
        TemperatureLastDaysDataSetScreen m_TemperatureLastDaysDataSetScreen;
        HumidityDataSetScreen m_HumidityDataSetScreen;
        HumidityLastDaysDataSetScreen m_HumidityLastDaysDataSetScreen;
        DefaultsSettingsScreen m_DefaultsSettingsScreen;
        SaveQuestionScreen m_SaveQuestionScreen;
        TimeResetQuestionScreen m_TimeResetQuestionScreen;
        CurrentTimeSettingsScreen m_CurrentTimeSettingsScreen;
        CurrentDayDataSetScreen m_CurrentDayDataSetScreen;
        CurrentHourDataSetScreen m_CurrentHourDataSetScreen;
        CurrentMinuteDataSetScreen m_CurrentMinuteDataSetScreen;
        
        DataChangedEventHandlers m_DataChangedEventHandlers;

        IncubatorInformationData m_CurrentIncubatorInformationData;
        IncubatorInformationData m_ChangedIncubatorInformationData;
    private:
        EnumScreenType DetermineNextScreen(const JoystickEvent event);

    };
} // namespace Incubator

#endif // INCUBATOR_SCREENFACADE_H