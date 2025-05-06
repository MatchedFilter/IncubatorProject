#include "Incubator/View/Screen/DefaultsSettingsScreen.h"

namespace Incubator
{

    DefaultsSettingsScreen::DefaultsSettingsScreen() : 
        AScreen { SCREEN_TYPE_DEFAULTS_SETTINGS },
        m_Lcd { nullptr },
        m_SelectedLine { DEFAULTS_SETTINGS_SCREEN_LINE_CHICKEN }
    {
    }

    DefaultsSettingsScreen::~DefaultsSettingsScreen()
    {
    }

    void DefaultsSettingsScreen::Initialize(TC2004::Lcd *tc2004Lcd)
    {
        m_Lcd = tc2004Lcd;
    }

    void DefaultsSettingsScreen::OnInitial()
    {
        m_Lcd->Clear();
        m_Lcd->MoveCursor(0U, 0U);
        m_Lcd->Print(TC2004::String80("[Varsay"));
        m_Lcd->Print(TC2004::TC2004_CHAR_LOWER_I);
        m_Lcd->Print(TC2004::String80("lanlar]"));
        m_Lcd->MoveCursor(1U, 0U);
        if (DEFAULTS_SETTINGS_SCREEN_LINE_CHICKEN == m_SelectedLine)
        {
            m_Lcd->Print(TC2004::TC2004_CHAR_ARROW_SYMBOL);
        }
        else
        {
            m_Lcd->Print(TC2004::String80(" "));
        }
        m_Lcd->Print(TC2004::String80("Tavuk"));

        m_Lcd->MoveCursor(2U, 0U);
        if (DEFAULTS_SETTINGS_SCREEN_LINE_GOOSE == m_SelectedLine)
        {
            m_Lcd->Print(TC2004::TC2004_CHAR_ARROW_SYMBOL);
        }
        else
        {
            m_Lcd->Print(TC2004::String80(" "));
        }
        m_Lcd->Print(TC2004::String80("Kaz"));

        m_Lcd->MoveCursor(3U, 0U);
        if (DEFAULTS_SETTINGS_SCREEN_LINE_DUCK == m_SelectedLine)
        {
            m_Lcd->Print(TC2004::TC2004_CHAR_ARROW_SYMBOL);
        }
        else
        {
            m_Lcd->Print(TC2004::String80(" "));
        }
        m_Lcd->Print(TC2004::TC2004_CHAR_UPPER_O);
        m_Lcd->Print(TC2004::String80("rdek"));

    }

    void DefaultsSettingsScreen::Run()
    {
        // intentionally left blank
    }

    void DefaultsSettingsScreen::OnUserAction(const JoystickEvent &event)
    {
        switch (m_SelectedLine)
        {
        case DEFAULTS_SETTINGS_SCREEN_LINE_CHICKEN:
        {
            if(event.bIsDownPressed)
            {
                m_SelectedLine = DEFAULTS_SETTINGS_SCREEN_LINE_GOOSE;
                m_Lcd->MoveCursor(1U, 0U);
                m_Lcd->Print(TC2004::String80(" "));
                m_Lcd->MoveCursor(2U, 0U);
                m_Lcd->Print(TC2004::TC2004_CHAR_ARROW_SYMBOL);
            }
            break;
        }

        case DEFAULTS_SETTINGS_SCREEN_LINE_GOOSE:
        {
            if(event.bIsUpPressed)
            {
                m_SelectedLine = DEFAULTS_SETTINGS_SCREEN_LINE_CHICKEN;
                m_Lcd->MoveCursor(1U, 0U);
                m_Lcd->Print(TC2004::TC2004_CHAR_ARROW_SYMBOL);
                m_Lcd->MoveCursor(2U, 0U);
                m_Lcd->Print(TC2004::String80(" "));
            }
            else if (event.bIsDownPressed)
            {
                m_SelectedLine = DEFAULTS_SETTINGS_SCREEN_LINE_DUCK;
                m_Lcd->MoveCursor(2U, 0U);
                m_Lcd->Print(TC2004::String80(" "));
                m_Lcd->MoveCursor(3U, 0U);
                m_Lcd->Print(TC2004::TC2004_CHAR_ARROW_SYMBOL);
            }
            else
            {
                // intentionally left blank
            }
            break;
        }

        case DEFAULTS_SETTINGS_SCREEN_LINE_DUCK:
        {
            if(event.bIsUpPressed)
            {
                m_SelectedLine = DEFAULTS_SETTINGS_SCREEN_LINE_GOOSE;
                m_Lcd->MoveCursor(2U, 0U);
                m_Lcd->Print(TC2004::TC2004_CHAR_ARROW_SYMBOL);
                m_Lcd->MoveCursor(3U, 0U);
                m_Lcd->Print(TC2004::String80(" "));
            }
            break;
        }
        
        default:
            break;
        }
        // intentionally left blank
    }


} // namespace Incubator
