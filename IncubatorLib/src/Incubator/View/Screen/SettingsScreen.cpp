#include "Incubator/View/Screen/SettingsScreen.h"

namespace Incubator
{

    void SettingsScreen::HandleScreenLineIncubator(const JoystickEvent &event)
    {
        if (event.bIsLeftPressed)
        {
            SetNextScreen(SCREEN_TYPE_MENU);
        }
        else if(event.bIsDownPressed)
        {
            m_SelectedLine = SETTINGS_SCREEN_LINE_TIME;
            m_Lcd->MoveCursor(1U, 0U);
            m_Lcd->Print(TC2004::String80(" "));
            m_Lcd->MoveCursor(2U, 0U);
            m_Lcd->Print(TC2004::TC2004_CHAR_ARROW_SYMBOL);
        }
        else if (event.bIsRightPressed || event.bIsButtonPressed)
        {
            SetNextScreen(SCREEN_TYPE_INCUBATOR_SETTINGS);
        }
        else
        {
            // intentionally left blank
        }
    }

    void SettingsScreen::HandleScreenLineTime(const JoystickEvent &event)
    {
        if (event.bIsLeftPressed)
        {
            SetNextScreen(SCREEN_TYPE_MENU);
        }
        else if(event.bIsUpPressed)
        {
            m_SelectedLine = SETTINGS_SCREEN_LINE_INCUBATOR;
            m_Lcd->MoveCursor(1U, 0U);
            m_Lcd->Print(TC2004::TC2004_CHAR_ARROW_SYMBOL);
            m_Lcd->MoveCursor(2U, 0U);
            m_Lcd->Print(TC2004::String80(" "));
        }
        else if (event.bIsRightPressed || event.bIsButtonPressed)
        {
            SetNextScreen(SCREEN_TYPE_TIME_SETTINGS);
        }
        else
        {
            // intentionally left blank
        }
    }

    SettingsScreen::SettingsScreen() : 
        AScreen { SCREEN_TYPE_SETTINGS },
        m_Lcd { nullptr },
        m_SelectedLine { SETTINGS_SCREEN_LINE_INCUBATOR }
    {
    }

    SettingsScreen::~SettingsScreen()
    {
    }

    void SettingsScreen::Initialize(TC2004::Lcd *tc2004Lcd)
    {
        m_Lcd = tc2004Lcd;
    }

    void SettingsScreen::OnInitial()
    {
        Reset();
        m_Lcd->Clear();
        m_Lcd->MoveCursor(0U, 0U);
        m_Lcd->Print(TC2004::String80("[Ayarlar]"));
        m_Lcd->MoveCursor(1U, 0U);
        if (SETTINGS_SCREEN_LINE_INCUBATOR == m_SelectedLine)
        {
            m_Lcd->Print(TC2004::TC2004_CHAR_ARROW_SYMBOL);
        }
        else
        {
            m_Lcd->Print(TC2004::String80(" "));
        }
        m_Lcd->Print(TC2004::String80("Kulu"));
        m_Lcd->Print(TC2004::TC2004_CHAR_LOWER_C);
        m_Lcd->Print(TC2004::String80("ka"));

        m_Lcd->MoveCursor(2U, 0U);
        if (SETTINGS_SCREEN_LINE_TIME == m_SelectedLine)
        {
            m_Lcd->Print(TC2004::TC2004_CHAR_ARROW_SYMBOL);
        }
        else
        {
            m_Lcd->Print(TC2004::String80(" "));
        }
        m_Lcd->Print(TC2004::String80("Zaman"));
    }

    void SettingsScreen::Run()
    {
        // intentionally left blank
    }

    void SettingsScreen::OnUserAction(const JoystickEvent &event)
    {
        switch (m_SelectedLine)
        {
        case SETTINGS_SCREEN_LINE_INCUBATOR:
        {
            HandleScreenLineIncubator(event);
            break;
        }

        case SETTINGS_SCREEN_LINE_TIME:
        {
            HandleScreenLineTime(event);
            break;
        }
        
        default:
            break;
        }
    }


} // namespace Incubator
