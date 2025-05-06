#ifndef INCUBATOR_TIMESETTINGSSCREEN_H
#define INCUBATOR_TIMESETTINGSSCREEN_H
#include "TC2004/Lcd.h"
#include "AScreen.h"
#include "Incubator/Time/TimerTask.h"
namespace Incubator
{

    enum EnumTimeSettingsScreenLine : uint8_t
    {
        TIME_SETTINGS_SCREEN_LINE_TOTAL_DAY,
        TIME_SETTINGS_SCREEN_LINE_DAY,
        TIME_SETTINGS_SCREEN_LINE_HOUR
    };

    class TimeSettingsScreen : public AScreen
    {
    public:
        TimeSettingsScreen();
        ~TimeSettingsScreen();
        void Initialize(TC2004::Lcd *tc2004Lcd);
        void OnInitial();

        virtual void Run() override;

        void OnUserAction(const JoystickEvent &event) override;

    private:
        TC2004::Lcd *m_Lcd;
        EnumTimeSettingsScreenLine m_SelectedLine;
    };
} // namespace Incubator

#endif // INCUBATOR_TIMESETTINGSSCREEN_H