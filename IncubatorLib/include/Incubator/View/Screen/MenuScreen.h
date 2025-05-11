#ifndef INCUBATOR_MENUSCREEN_H
#define INCUBATOR_MENUSCREEN_H
#include "TC2004/Lcd.h"
#include "AScreen.h"
#include "Incubator/Time/TimerTask.h"
#include "Incubator/IncubatorData/TimeInformationData.h"
namespace Incubator
{

    enum EnumMenuScreenLine : uint8_t
    {
        MENU_SCREEN_LINE_SETTINGS,
        MENU_SCREEN_LINE_SENSORS_STATUS
    };

    class MenuScreen : public AScreen
    {
    public:
        MenuScreen();
        ~MenuScreen();
        void Initialize(TC2004::Lcd *tc2004Lcd);
        void OnInitial() override;
        inline EnumMenuScreenLine GetMenuScreenLine() const { return m_SelectedLine; }

        virtual void Run() override;

        void OnUserAction(const JoystickEvent &event) override;

    private:
        TC2004::Lcd *m_Lcd;
        EnumMenuScreenLine m_SelectedLine;

    private:
        void HandleScreenLineSettings(const JoystickEvent &event);
        void HandleScreenLineSensorsStatus(const JoystickEvent &event);

    };
} // namespace Incubator

#endif // INCUBATOR_MENUSCREEN_H