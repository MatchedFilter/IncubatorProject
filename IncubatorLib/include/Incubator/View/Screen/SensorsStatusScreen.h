#ifndef INCUBATOR_SENSORSSTATUSSCREEN_H
#define INCUBATOR_SENSORSSTATUSSCREEN_H
#include "TC2004/Lcd.h"
#include "AScreen.h"
#include "Incubator/Time/TimerTask.h"
#include "Incubator/IncubatorData/SensorsStatusData.h"
namespace Incubator
{
    enum EnumSensorsStatusScreenLine : uint8_t
    {
        SENSOR_STATUS_SCREEN_LINE_SHT31,
        SENSOR_STATUS_SCREEN_LINE_NTC,
        SENSOR_STATUS_SCREEN_LINE_DHT11
    };

    class SensorsStatusScreen : public AScreen
    {
    public:
        SensorsStatusScreen();
        ~SensorsStatusScreen();
        void Initialize(TC2004::Lcd *tc2004Lcd);
        void OnInitial() override;

        virtual void Run() override;

        void OnUserAction(const JoystickEvent &event) override;
        void UpdateSensorsStatus(const SensorsStatusData &data);

    private:
        TC2004::Lcd *m_Lcd;
        EnumSensorsStatusScreenLine m_SelectedLine;
        Time::TimerTask m_SensorStatusScreenUpdateTimerTask;
        SensorsStatusData m_SensorsStatusData;

    private:
        void PrintSensorStatus(const EnumSensorStatus &sensorStatus);
    };
} // namespace Incubator

#endif // INCUBATOR_SENSORSSTATUSSCREEN_H