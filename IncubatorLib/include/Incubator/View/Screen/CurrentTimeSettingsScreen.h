#ifndef INCUBATOR_CURRENTTIMESETTINGSSCREEN_H
#define INCUBATOR_CURRENTTIMESETTINGSSCREEN_H
#include "TC2004/Lcd.h"
#include "AScreen.h"
#include "Incubator/Time/TimerTask.h"
namespace Incubator
{

    enum EnumCurrentTimeSettingsScreenLine : uint8_t
    {
        CURRENT_TIME_SETTINGS_SCREEN_LINE_DAY,
        CURRENT_TIME_SETTINGS_SCREEN_LINE_HOUR,
        CURRENT_TIME_SETTINGS_SCREEN_LINE_MINUTE
    };

    class CurrentTimeSettingsScreen : public AScreen
    {
    public:
        CurrentTimeSettingsScreen();
        ~CurrentTimeSettingsScreen();
        void Initialize(TC2004::Lcd *tc2004Lcd);
        void OnInitial() override;

        virtual void Run() override;

        void OnUserAction(const JoystickEvent &event) override;

    private:
        TC2004::Lcd *m_Lcd;
        EnumCurrentTimeSettingsScreenLine m_SelectedLine;

    private:
        void HandleScreenLineDay(const JoystickEvent &event);
        void HandleScreenLineHour(const JoystickEvent &event);
        void HandleScreenLineMinute(const JoystickEvent &event);
    };
} // namespace Incubator

#endif // INCUBATOR_CURRENTTIMESETTINGSSCREEN_H