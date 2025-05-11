#ifndef INCUBATOR_HYSTERISISHUMIDITYSETTINGSSCREEN_H
#define INCUBATOR_HYSTERISISHUMIDITYSETTINGSSCREEN_H
#include "TC2004/Lcd.h"
#include "AScreen.h"
namespace Incubator
{

    enum EnumHysterisisHumiditySettingsScreenLine : uint8_t
    {
        HYSTERISIS_HUMIDITY_SETTINGS_SCREEN_LINE_UPPER,
        HYSTERISIS_HUMIDITY_SETTINGS_SCREEN_LINE_LOWER
    };

    class HysterisisHumiditySettingsScreen : public AScreen
    {
    public:
        HysterisisHumiditySettingsScreen();
        ~HysterisisHumiditySettingsScreen();
        void Initialize(TC2004::Lcd *tc2004Lcd);
        void OnInitial() override;

        virtual void Run() override;

        void OnUserAction(const JoystickEvent &event) override;

    private:
        TC2004::Lcd *m_Lcd;
        EnumHysterisisHumiditySettingsScreenLine m_SelectedLine;

    private:
        void HandleScreenLineUpper(const JoystickEvent &event);
        void HandleScreenLineLower(const JoystickEvent &event);
    };
} // namespace Incubator

#endif // INCUBATOR_HYSTERISISHUMIDITYSETTINGSSCREEN_H