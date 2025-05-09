#ifndef INCUBATOR_INCUBATORSETTINGSSCREEN_H
#define INCUBATOR_INCUBATORSETTINGSSCREEN_H
#include "TC2004/Lcd.h"
#include "AScreen.h"
#include "Incubator/Time/TimerTask.h"
#include "Incubator/IncubatorData/SettingsData.h"
#include "Incubator/IncubatorData/TimeInformationData.h"
namespace Incubator
{

    enum EnumIncubatorSettingsScreenLine : uint8_t
    {
        INCUBATOR_SETTINGS_SCREEN_LINE_DEFAULT,
        INCUBATOR_SETTINGS_SCREEN_LINE_TEMPERATURE,
        INCUBATOR_SETTINGS_SCREEN_LINE_HUMIDITY
    };

    class IncubatorSettingsScreen : public AScreen
    {
    public:
        IncubatorSettingsScreen();
        ~IncubatorSettingsScreen();
        void Initialize(TC2004::Lcd *tc2004Lcd);
        void OnInitial() override;
        virtual void Run() override;
        void OnUserAction(const JoystickEvent &event) override;

    private:
        TC2004::Lcd *m_Lcd;
        EnumIncubatorSettingsScreenLine m_SelectedLine;

    private:
        void HandleIncubatorSettingsLine(const JoystickEvent &event);
        void HandleTemperatureSettingsLine(const JoystickEvent &event);
        void HandleHumiditySettingsLine(const JoystickEvent &event);
    };
} // namespace Incubator

#endif // INCUBATOR_INCUBATORSETTINGSSCREEN_H