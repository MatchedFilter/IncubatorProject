#ifndef INCUBATOR_SETTINGSSCREEN_H
#define INCUBATOR_SETTINGSSCREEN_H
#include "TC2004/Lcd.h"
#include "AScreen.h"
#include "Incubator/Time/TimerTask.h"
#include "Incubator/IncubatorData/SettingsData.h"
#include "Incubator/IncubatorData/TimeInformationData.h"
namespace Incubator
{

    enum EnumSettingsScreenLine : uint8_t
    {
        SETTINGS_SCREEN_LINE_INCUBATOR,
        SETTINGS_SCREEN_LINE_TIME
    };

    class SettingsScreen : public AScreen
    {
    public:
        SettingsScreen();
        ~SettingsScreen();
        void Initialize(TC2004::Lcd *tc2004Lcd);
        void OnInitial() override;
        inline EnumSettingsScreenLine GetSettingsScreenLine() const { return m_SelectedLine; }

        virtual void Run() override;

        void OnUserAction(const JoystickEvent &event) override;

    private:
        TC2004::Lcd *m_Lcd;
        EnumSettingsScreenLine m_SelectedLine;

    private:
        void HandleScreenLineIncubator(const JoystickEvent &event);
        void HandleScreenLineTime(const JoystickEvent &event);

    };
} // namespace Incubator

#endif // INCUBATOR_SETTINGSSCREEN_H