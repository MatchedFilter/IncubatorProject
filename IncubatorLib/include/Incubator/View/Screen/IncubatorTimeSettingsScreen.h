#ifndef INCUBATOR_INCUBATORTIMESETTINGSSCREEN_H
#define INCUBATOR_INCUBATORTIMESETTINGSSCREEN_H
#include "TC2004/Lcd.h"
#include "AScreen.h"
#include "Incubator/Time/TimerTask.h"
namespace Incubator
{

    enum EnumIncubatorTimeSettingsScreenLine : uint8_t
    {
        INCUBATOR_TIME_SETTINGS_SCREEN_LINE_TOTAL_DAYS,
        INCUBATOR_TIME_SETTINGS_SCREEN_LINE_LAST_DAYS
    };

    class IncubatorTimeSettingsScreen : public AScreen
    {
    public:
        IncubatorTimeSettingsScreen();
        ~IncubatorTimeSettingsScreen();
        void Initialize(TC2004::Lcd *tc2004Lcd);
        void OnInitial() override;

        virtual void Run() override;

        void OnUserAction(const JoystickEvent &event) override;

    private:
        TC2004::Lcd *m_Lcd;
        EnumIncubatorTimeSettingsScreenLine m_SelectedLine;

    private:
        void HandleScreenLineTotalDays(const JoystickEvent &event);
        void HandleScreenLineLastDays(const JoystickEvent &event);
    };
} // namespace Incubator

#endif // INCUBATOR_INCUBATORTIMESETTINGSSCREEN_H