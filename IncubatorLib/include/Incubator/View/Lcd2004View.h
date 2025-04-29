#ifndef INCUBATOR_LCD2004VIEW_H
#define INCUBATOR_LCD2004VIEW_H
#include "TC2004/Lcd.h"
#include "IView.h"
#include "Incubator/IncubatorData/IncubatorInformationData.h"
#include "Joystick/JoystickSensor.h"
#include "Incubator/Time/TimerTask.h"
namespace Incubator
{
    class Lcd2004View : public IView
    {
    public:
        Lcd2004View();
        ~Lcd2004View();
        virtual void Initialize(void) override;
        virtual void UpdateTemperature(const double temperatureInCelcius) override;
        virtual void OnTemperatureFailure(const uint8_t errorCode) override;
        
        virtual void UpdateHumidity(const double humidityInPercentage) override;
        virtual void OnHumidityFailure(const uint8_t errorCode) override;

        virtual void UpdateSettingsData(const SettingsData &data) override;
        virtual void UpdateTimeInformationData(const TimeInformationData &data) override;

        void Run();

    private:
        TC2004::Lcd m_TC2004Lcd;
        bool m_bTemperatureValid;
        bool m_bHumidityValid;
        float m_TemperatureInCelcius;
        float m_HumidityInPercentage;
        IncubatorInformationData m_IncubatorInformationData;
        Joystick::JoystickSensor m_JoystickSensor;
        bool m_bLastStateWasHorizontal;
        bool m_bUpShifted;
        bool m_bDownShifted;
        bool m_bRightShifted;
        bool m_bLeftShifted;
        bool m_bSwitchPressed;
        Time::TimerTask m_JoystickSensorTimerTask;


    private:
        void OnUserAction(const bool bUpKeyPressed, const bool bDownKeyPressed, const bool bRightKeyPressed, const bool bLeftKeyPressed, const bool bSwitchClicked);
    };
} // namespace Incubator

#endif // INCUBATOR_LCD2004VIEW_H