#include "Incubator/View/Screen/DisplayOffScreen.h"

namespace Incubator
{
    DisplayOffScreen::DisplayOffScreen() : 
        AScreen { SCREEN_TYPE_DISPLAY_OFF },
        m_Lcd { nullptr }
    {
    }

    DisplayOffScreen::~DisplayOffScreen()
    {
    }

    void DisplayOffScreen::Initialize(TC2004::Lcd *tc2004Lcd)
    {
        m_Lcd = tc2004Lcd;
    }

    void DisplayOffScreen::OnInitial()
    {
        Reset();
        m_Lcd->TurnOff();
    }

    void DisplayOffScreen::Run()
    {
        // intentionally left blank
    }

    void DisplayOffScreen::OnUserAction(const JoystickEvent & event)
    {
        if (event.bIsButtonPressed)
        {
            constexpr uint8_t MAX_TRY_COUNT = 5U;
            for (uint8_t i = 0U; i < MAX_TRY_COUNT; i++)
            {
                if (m_Lcd->Initialize(true))
                {
                    SetNextScreen(SCREEN_TYPE_MAIN);
                    break;
                }
            }
        }
    }


} // namespace Incubator
