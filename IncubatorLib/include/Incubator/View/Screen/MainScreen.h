#ifndef INCUBATOR_MAINSCREEN_H
#define INCUBATOR_MAINSCREEN_H
#include "TC2004/Lcd.h"
#include "AScreen.h"
#include "Incubator/Time/TimerTask.h"
#include "Incubator/IncubatorData/SettingsData.h"
#include "Incubator/IncubatorData/TimeInformationData.h"
namespace Incubator
{

    enum EnumUpdateStatus : uint8_t
    {
        UPDATE_STATUS_INVALID,
        UPDATE_STATUS_VALID,
        UPDATE_STATUS_SCREEN_UPDATED
    };

    class MainScreen : public AScreen
    {
    public:
        MainScreen();
        ~MainScreen();
        void Initialize(TC2004::Lcd *tc2004Lcd);
        void OnInitial() override;

        void UpdateSettingsData(const SettingsData &data);
        void UpdateTimeInformationData(const TimeInformationData &data);
        void UpdateTemperature(const double &temperatureInCelcius);
        void UpdateHumidity(const uint8_t &humidityInPercent);
        void OnTemperatureFailure();
        void OnHumidityFailure();
        void OnModelFailure();
        virtual void Run() override;

        void OnUserAction(const JoystickEvent& event) override;

    private:
        TC2004::Lcd *m_Lcd;
        bool m_bIsTemperatureSet;
        double m_TemperatureInCelcius;
        bool m_bIsHumiditySet;
        uint8_t m_HumidityInPercent;
        bool m_bIsIncubatorDataProvided;
        bool m_bIsSettingsProvided;
        bool m_bTimeInformationProvided;
        SettingsData m_SettingsData;
        TimeInformationData m_TimeInformationData;
        Time::TimerTask m_ScreenInformationUpdateTimerTask;
        bool m_bModelValid;
        EnumUpdateStatus m_TemperatureUpdateStatus;
        EnumUpdateStatus m_HumidityUpdateStatus;

    private:
        TC2004::String80 GetTemperature() const;
        TC2004::String80 GetTargetTemperature() const;
        TC2004::String80 GetTargetHumidity() const;
        void DisplayTemperatureInformation();
        void StartToDisplayTemperatureInformation();
        void DisplayTemperatureFailure();
        void DisplayHumidityInformation();
        void StartToDisplayHumidityInformation();
        void DisplayHumidityFailure();
        void DisplayTimeInformation();
        void DisplayDay();
        void DisplayHour();
        void DisplayMinute();
        void DisplaySecond();

    };
} // namespace Incubator

#endif // INCUBATOR_MAINSCREEN_H