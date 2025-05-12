#ifndef INCUBATOR_DISPLAYOFFSCREEN_H
#define INCUBATOR_DISPLAYOFFSCREEN_H
#include "TC2004/Lcd.h"
#include "AScreen.h"
namespace Incubator
{

    class DisplayOffScreen : public AScreen
    {
    public:
        DisplayOffScreen();
        ~DisplayOffScreen();
        void Initialize(TC2004::Lcd *tc2004Lcd);
        void OnInitial() override;
        virtual void Run() override;
        void OnUserAction(const JoystickEvent& event) override;

    private:
        TC2004::Lcd *m_Lcd;
    };
} // namespace Incubator

#endif // INCUBATOR_DISPLAYOFFSCREEN_H