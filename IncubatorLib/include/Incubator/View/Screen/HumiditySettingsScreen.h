#ifndef INCUBATOR_HUMIDITYSETTINGSSCREEN_H
#define INCUBATOR_HUMIDITYSETTINGSSCREEN_H
#include "TC2004/Lcd.h"
#include "AScreen.h"
#include "Incubator/Time/TimerTask.h"
#include "Incubator/IncubatorData/SettingsData.h"
#include "Incubator/IncubatorData/TimeInformationData.h"
namespace Incubator
{

    enum EnumHumiditySettingsScreenLine : uint8_t
    {
        HUMIDITY_SETTINGS_SCREEN_LINE_HUMIDITY,
        HUMIDITY_SETTINGS_SCREEN_LINE_LAST_DAYS_HUMIDITY,
    };

    class HumiditySettingsScreen : public AScreen
    {
    public:
        HumiditySettingsScreen();
        ~HumiditySettingsScreen();
        void Initialize(TC2004::Lcd *tc2004Lcd);
        void OnInitial() override;
        virtual void Run() override;
        void OnUserAction(const JoystickEvent &event) override;

    private:
        TC2004::Lcd *m_Lcd;
        EnumHumiditySettingsScreenLine m_SelectedLine;

    private:
        void HandlerHumidityLine(const JoystickEvent &event);
        void HandleHumidityLastDaysHumidityLine(const JoystickEvent &event);
    };
} // namespace Incubator

#endif // INCUBATOR_HUMIDITYSETTINGSSCREEN_H