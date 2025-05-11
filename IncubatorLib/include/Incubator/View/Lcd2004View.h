#ifndef INCUBATOR_LCD2004VIEW_H
#define INCUBATOR_LCD2004VIEW_H
#include "TC2004/Lcd.h"
#include "IView.h"
#include "Joystick/JoystickSensor.h"
#include "Incubator/Time/TimerTask.h"
#include "Incubator/View/JoystickEvent.h"
#include "Screen/ScreenFacade.h"


namespace Incubator
{
    class Lcd2004View : public IView
    {
    public:
        Lcd2004View();
        ~Lcd2004View();
        virtual bool Initialize(const DataChangedEventHandlers *eventHandlers) override;
        virtual void UpdateTemperature(const double temperatureInCelcius) override;
        virtual void OnTemperatureFailure() override;
        
        virtual void UpdateHumidity(const uint8_t humidityInPercentage) override;
        virtual void OnHumidityFailure() override;

        virtual void UpdatePidData(const PidData &data) override;
        virtual void UpdateSettingsData(const SettingsData &data) override;
        virtual void UpdateTimeInformationData(const TimeInformationData &data) override;
        virtual void OnModelFailure()override;
        virtual void UpdateSensorsStatus(const SensorsStatusData &data) override;

        void Run();

    private:
        TC2004::Lcd m_TC2004Lcd;
        bool m_bIsInitialized;
        Joystick::JoystickSensor m_JoystickSensor;
        bool m_bLastStateWasHorizontal;
        bool m_bUpShifted;
        bool m_bDownShifted;
        bool m_bRightShifted;
        bool m_bLeftShifted;
        bool m_bSwitchPressed;
        Time::TimerTask m_JoystickSensorTimerTask;
        ScreenFacade m_ScreenFacade;

    private:
        void ReadJoystick();
        void OnUserAction(const JoystickEvent event);
    };
} // namespace Incubator

#endif // INCUBATOR_LCD2004VIEW_H