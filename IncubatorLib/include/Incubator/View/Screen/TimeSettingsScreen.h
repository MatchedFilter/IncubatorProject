#ifndef INCUBATOR_TIMESETTINGSSCREEN_H
#define INCUBATOR_TIMESETTINGSSCREEN_H
#include "TC2004/Lcd.h"
#include "AScreen.h"
#include "Incubator/Time/TimerTask.h"
#include "Incubator/IncubatorData/TimeInformationData.h"
namespace Incubator
{

    enum EnumTimeSettingsScreenLine : uint8_t
    {
        TIME_SETTINGS_SCREEN_LINE_RESET,
        TIME_SETTINGS_SCREEN_LINE_CURRENT_TIME,
        TIME_SETTINGS_SCREEN_LINE_INCUBATOR_TIME
    };

    class TimeSettingsScreen : public AScreen
    {
    public:
        TimeSettingsScreen();
        ~TimeSettingsScreen();
        void Initialize(TC2004::Lcd *tc2004Lcd,
            TimeInformationData *changedTimeInformationData);
        void OnInitial() override;

        virtual void Run() override;

        void OnUserAction(const JoystickEvent &event) override;

    private:
        TC2004::Lcd *m_Lcd;
        EnumTimeSettingsScreenLine m_SelectedLine;
        TimeInformationData *m_ChangedTimeInformationData;

    private:
        void HandleScreenLineReset(const JoystickEvent &event);
        void HandleScreenLineCurrentTime(const JoystickEvent &event);
        void HandleScreenLineIncubatorTime(const JoystickEvent &event);
    };
} // namespace Incubator

#endif // INCUBATOR_TIMESETTINGSSCREEN_H