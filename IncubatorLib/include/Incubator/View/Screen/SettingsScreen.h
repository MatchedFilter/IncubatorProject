#ifndef INCUBATOR_SETTINGSSCREEN_H
#define INCUBATOR_SETTINGSSCREEN_H
#include "TC2004/Lcd.h"
#include "AScreen.h"
#include "Incubator/Time/TimerTask.h"
#include "Incubator/IncubatorData/SettingsData.h"
#include "Incubator/IncubatorData/TimeInformationData.h"
namespace Incubator
{
    class SettingsScreen : public AScreen
    {
    public:
        SettingsScreen();
        ~SettingsScreen();
        void Initialize(TC2004::Lcd *tc2004Lcd);
        void OnInitial();

        virtual void Run() override;

        void OnUserAction(const JoystickEvent &event) override;

    private:
        TC2004::Lcd *m_Lcd;
        uint8_t m_SelectedLine;

    };
} // namespace Incubator

#endif // INCUBATOR_SETTINGSSCREEN_H