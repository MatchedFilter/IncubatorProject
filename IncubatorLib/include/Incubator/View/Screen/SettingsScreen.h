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
        SETTINGS_SCREEN_LINE_TIME,
        SETTINGS_SCREEN_LINE_ADMINISTRATOR,

    };

    enum EnumAdministratorEnterLevel: uint8_t
    {
        ADMINISTRATOR_ENTER_LEVEL_0,
        ADMINISTRATOR_ENTER_LEVEL_1,
        ADMINISTRATOR_ENTER_LEVEL_2,
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
        static constexpr uint32_t ADMINISTRATOR_CLICK_TIMEOUT_IN_MILLISECOND = static_cast<uint32_t>(500UL);
        Time::TimerTask m_AdministratorClickTimerTask;
        EnumAdministratorEnterLevel m_AdministratorEnterLevel;

    private:
        void HandleScreenLineIncubator(const JoystickEvent &event);
        void HandleScreenLineTime(const JoystickEvent &event);
        void HandleScreenLineAdministrator(const JoystickEvent &event);

    };
} // namespace Incubator

#endif // INCUBATOR_SETTINGSSCREEN_H