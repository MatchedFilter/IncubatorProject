#ifndef INCUBATOR_DEFAULTSSETTINGSSCREEN_H
#define INCUBATOR_DEFAULTSSETTINGSSCREEN_H
#include "TC2004/Lcd.h"
#include "AScreen.h"
#include "Incubator/Time/TimerTask.h"
#include "Incubator/IncubatorData/SettingsData.h"
#include "Incubator/IncubatorData/TimeInformationData.h"
namespace Incubator
{

    enum EnumDefaultsSettingsScreenLine : uint8_t
    {
        DEFAULTS_SETTINGS_SCREEN_LINE_CHICKEN,
        DEFAULTS_SETTINGS_SCREEN_LINE_GOOSE,
        DEFAULTS_SETTINGS_SCREEN_LINE_DUCK,
        DEFAULTS_SETTINGS_SCREEN_LINE_QUAIL

    };

    class DefaultsSettingsScreen : public AScreen
    {
    public:
        DefaultsSettingsScreen();
        ~DefaultsSettingsScreen();
        void Initialize(TC2004::Lcd *tc2004Lcd, SettingsData *changedSettingsData);
        void OnInitial() override;

        virtual void Run() override;

        void OnUserAction(const JoystickEvent &event) override;

    private:
        TC2004::Lcd *m_Lcd;
        EnumDefaultsSettingsScreenLine m_SelectedLine;
        SettingsData *m_ChangedSettingsData;

    private:
        void HandleChickenLineEvent(const JoystickEvent &event);
        void HandleGooseLineEvent(const JoystickEvent &event);
        void HandleDuckLineEvent(const JoystickEvent &event);
        void HandleQuailLineEvent(const JoystickEvent &event);
    };
} // namespace Incubator

#endif // INCUBATOR_DEFAULTSSETTINGSSCREEN_H