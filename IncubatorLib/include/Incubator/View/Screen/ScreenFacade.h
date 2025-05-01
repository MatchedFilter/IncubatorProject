#ifndef INCUBATOR_SCREENFACADE_H
#define INCUBATOR_SCREENFACADE_H
#include "TC2004/Lcd.h"
#include "MenuScreen.h"
#include "Incubator/View/IPidDataChangedEventHandler.h"
#include "Incubator/View/ISettingsDataChangedEventHandler.h"
#include "Incubator/View/ITimeInformationDataChangedEventHandler.h"

namespace Incubator
{
    class ScreenFacade
    {
    public:
        ScreenFacade();
        ~ScreenFacade();
        void Initialize(TC2004::Lcd * tc2004Lcd, IPidDataChangedEventHandler *pidDataChangedEventHandler,
            ISettingsDataChangedEventHandler *settingsDataChangedEventHandler,
            ITimeInformationDataChangedEventHandler *timeInformationDataChangedEventHandler);

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
        IPidDataChangedEventHandler *m_PidDataChangedEventHandler;
        ISettingsDataChangedEventHandler *m_SettingsDataChangedEventHandler;
        ITimeInformationDataChangedEventHandler *m_TimeInformationDataChangedEventHandler;

    };
} // namespace Incubator

#endif // INCUBATOR_SCREENFACADE_H