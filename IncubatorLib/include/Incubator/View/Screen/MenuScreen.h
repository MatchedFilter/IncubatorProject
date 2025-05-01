#ifndef INCUBATOR_MENUSCREEN_H
#define INCUBATOR_MENUSCREEN_H
#include "TC2004/Lcd.h"
#include "AScreen.h"
#include "Incubator/Time/TimerTask.h"
#include "Incubator/IncubatorData/SettingsData.h"
#include "Incubator/IncubatorData/TimeInformationData.h"
namespace Incubator
{
    class MenuScreen : public AScreen
    {
    public:
        MenuScreen();
        ~MenuScreen();
        void Initialize(TC2004::Lcd *tc2004Lcd);

        void UpdateSettingsData(const SettingsData &data);
        void UpdateTimeInformationData(const TimeInformationData &data);
        void UpdateTemperature(const double &temperatureInCelcius);
        void UpdateHumidity(const uint8_t &humidityInPercent);
        void OnTemperatureFailure();
        void OnHumidityFailure();
        void OnModelFailure();
        virtual void Run() override;

        void OnUserAction(const JoystickEvent) override;

    private:
        TC2004::Lcd *m_Lcd;
        bool m_bIsTemperatureSet;
        double m_TemperatureInCelcius;
        bool m_bIsHumiditySet;
        uint8_t m_HumidityInPercent;
        bool m_bIsIncubatorDataProvided;
        bool m_bIsSettingsProvided;
        bool m_TimeInformationProvided;
        SettingsData m_SettingsData;
        TimeInformationData m_TimeInformationData;
        Time::TimerTask m_ScreenInformationUpdateTimerTask;

    private:
        TC2004::String80 GetTemperature() const;
        TC2004::String80 GetTargetTemperature() const;
        TC2004::String80 GetTargetHumidity() const;
        void DisplayTemperatureInformation();
        void DisplayHumidityInformation();

    };
} // namespace Incubator

#endif // INCUBATOR_MENUSCREEN_H