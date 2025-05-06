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
        DEFAULTS_SETTINGS_SCREEN_LINE_DUCK
    };

    class DefaultsSettingsScreen : public AScreen
    {
    public:
        DefaultsSettingsScreen();
        ~DefaultsSettingsScreen();
        void Initialize(TC2004::Lcd *tc2004Lcd);
        void OnInitial();
        inline EnumDefaultsSettingsScreenLine GetLine() const { return m_SelectedLine; }

        virtual void Run() override;

        void OnUserAction(const JoystickEvent &event) override;

    private:
        TC2004::Lcd *m_Lcd;
        EnumDefaultsSettingsScreenLine m_SelectedLine;
    };
} // namespace Incubator

#endif // INCUBATOR_DEFAULTSSETTINGSSCREEN_H