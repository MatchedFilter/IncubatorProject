#ifndef INCUBATOR_SCREENFACADE_H
#define INCUBATOR_SCREENFACADE_H
#include "TC2004/Lcd.h"
#include "MenuScreen.h"
#include "SettingsScreen.h"
#include "Incubator/View/DataChangedEventHandler/DataChangedEventHandlers.h"

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
        AScreen *m_CurrentScreen;
        MenuScreen m_MenuScreen;
        SettingsScreen m_SettingsScreen;
        DataChangedEventHandlers m_DataChangedEventHandlers;
        IPidDataChangedEventHandler *m_PidDataChangedEventHandler;
        ISettingsDataChangedEventHandler *m_SettingsDataChangedEventHandler;
        ITimeInformationDataChangedEventHandler *m_TimeInformationDataChangedEventHandler;

    };
} // namespace Incubator

#endif // INCUBATOR_SCREENFACADE_H