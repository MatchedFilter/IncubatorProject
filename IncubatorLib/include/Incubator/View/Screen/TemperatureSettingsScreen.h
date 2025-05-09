#ifndef INCUBATOR_TEMPERATURESETTINGSSCREEN_H
#define INCUBATOR_TEMPERATURESETTINGSSCREEN_H
#include "TC2004/Lcd.h"
#include "AScreen.h"
#include "Incubator/Time/TimerTask.h"
#include "Incubator/IncubatorData/SettingsData.h"
#include "Incubator/IncubatorData/TimeInformationData.h"
namespace Incubator
{

    enum EnumTemperatureSettingsScreenLine : uint8_t
    {
        TEMPERATURE_SETTINGS_SCREEN_LINE_TEMPERATURE,
        TEMPERATURE_SETTINGS_SCREEN_LINE_LAST_DAYS_TEMPERATURE,
    };

    class TemperatureSettingsScreen : public AScreen
    {
    public:
        TemperatureSettingsScreen();
        ~TemperatureSettingsScreen();
        void Initialize(TC2004::Lcd *tc2004Lcd);
        void OnInitial() override;
        virtual void Run() override;
        void OnUserAction(const JoystickEvent &event) override;

    private:
        TC2004::Lcd *m_Lcd;
        EnumTemperatureSettingsScreenLine m_SelectedLine;

    private:
        void HandlerTemperatureLine(const JoystickEvent &event);
        void HandleTemperatureLastDaysTemperatureLine(const JoystickEvent &event);
    };
} // namespace Incubator

#endif // INCUBATOR_TEMPERATURESETTINGSSCREEN_H