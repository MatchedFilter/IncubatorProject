#ifndef INCUBATOR_AdministatorSettingsScreen_H
#define INCUBATOR_AdministatorSettingsScreen_H
#include "TC2004/Lcd.h"
#include "AScreen.h"
namespace Incubator
{

    enum EnumAdministatorSettingsScreenLine : uint8_t
    {
        ADMINISTRATOR_SETTINGS_SCREEN_LINE_TEMPERATURE_PID,
        ADMINISTRATOR_SETTINGS_SCREEN_LINE_HUMIDITY_HYSTERISIS,
        ADMINISTRATOR_SETTINGS_SCREEN_LINE_RESET
    };

    class AdministatorSettingsScreen : public AScreen
    {
    public:
        AdministatorSettingsScreen();
        ~AdministatorSettingsScreen();
        void Initialize(TC2004::Lcd *tc2004Lcd);
        void OnInitial() override;

        virtual void Run() override;

        void OnUserAction(const JoystickEvent &event) override;

    private:
        TC2004::Lcd *m_Lcd;
        EnumAdministatorSettingsScreenLine m_SelectedLine;

    private:
        void HandleScreenLineTemperaturePid(const JoystickEvent &event);
        void HandleScreenLineHumidityHysterisis(const JoystickEvent &event);
        void HandleScreenLineReset(const JoystickEvent &event);
    };
} // namespace Incubator

#endif // INCUBATOR_AdministatorSettingsScreen_H