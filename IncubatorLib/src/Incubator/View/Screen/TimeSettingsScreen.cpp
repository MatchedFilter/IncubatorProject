#include "Incubator/View/Screen/TimeSettingsScreen.h"

namespace Incubator
{

    TimeSettingsScreen::TimeSettingsScreen() : 
        AScreen { SCREEN_TYPE_TIME_SETTINGS },
        m_Lcd { nullptr },
        m_SelectedLine { TIME_SETTINGS_SCREEN_LINE_TOTAL_DAY }
    {
    }

    TimeSettingsScreen::~TimeSettingsScreen()
    {
    }

    void TimeSettingsScreen::Initialize(TC2004::Lcd *tc2004Lcd)
    {
        m_Lcd = tc2004Lcd;
    }

    void TimeSettingsScreen::OnInitial()
    {
        m_Lcd->Clear();
        m_Lcd->MoveCursor(0U, 0U);
        m_Lcd->Print(TC2004::String80("[Zaman Ayarlar"));
        m_Lcd->Print(TC2004::TC2004_CHAR_LOWER_I);
        m_Lcd->Print(TC2004::String80("]"));
        m_Lcd->MoveCursor(1U, 0U);
        if (TIME_SETTINGS_SCREEN_LINE_TOTAL_DAY == m_SelectedLine)
        {
            m_Lcd->Print(TC2004::TC2004_CHAR_ARROW_SYMBOL);
        }
        else
        {
            m_Lcd->Print(TC2004::String80(" "));
        }
        m_Lcd->Print(TC2004::String80("Toplam G"));
        m_Lcd->Print(TC2004::TC2004_CHAR_LOWER_U);
        m_Lcd->Print(TC2004::String80("n"));

        m_Lcd->MoveCursor(2U, 0U);
        if (TIME_SETTINGS_SCREEN_LINE_DAY == m_SelectedLine)
        {
            m_Lcd->Print(TC2004::TC2004_CHAR_ARROW_SYMBOL);
        }
        else
        {
            m_Lcd->Print(TC2004::String80(" "));
        }
        m_Lcd->Print(TC2004::String80("G"));
        m_Lcd->Print(TC2004::TC2004_CHAR_LOWER_U);
        m_Lcd->Print(TC2004::String80("n"));

        m_Lcd->MoveCursor(3U, 0U);
        if (TIME_SETTINGS_SCREEN_LINE_HOUR == m_SelectedLine)
        {
            m_Lcd->Print(TC2004::TC2004_CHAR_ARROW_SYMBOL);
        }
        else
        {
            m_Lcd->Print(TC2004::String80(" "));
        }
        m_Lcd->Print(TC2004::String80("Saat"));

    }

    void TimeSettingsScreen::Run()
    {
        // intentionally left blank
    }

    void TimeSettingsScreen::OnUserAction(const JoystickEvent &event)
    {
        switch (m_SelectedLine)
        {
        case TIME_SETTINGS_SCREEN_LINE_TOTAL_DAY:
        {
            if(event.bIsDownPressed)
            {
                m_SelectedLine = TIME_SETTINGS_SCREEN_LINE_DAY;
                m_Lcd->MoveCursor(1U, 0U);
                m_Lcd->Print(TC2004::String80(" "));
                m_Lcd->MoveCursor(2U, 0U);
                m_Lcd->Print(TC2004::TC2004_CHAR_ARROW_SYMBOL);
            }
            break;
        }

        case TIME_SETTINGS_SCREEN_LINE_DAY:
        {
            if(event.bIsUpPressed)
            {
                m_SelectedLine = TIME_SETTINGS_SCREEN_LINE_TOTAL_DAY;
                m_Lcd->MoveCursor(1U, 0U);
                m_Lcd->Print(TC2004::TC2004_CHAR_ARROW_SYMBOL);
                m_Lcd->MoveCursor(2U, 0U);
                m_Lcd->Print(TC2004::String80(" "));
            }
            else if (event.bIsDownPressed)
            {
                m_SelectedLine = TIME_SETTINGS_SCREEN_LINE_HOUR;
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

        case TIME_SETTINGS_SCREEN_LINE_HOUR:
        {
            if(event.bIsUpPressed)
            {
                m_SelectedLine = TIME_SETTINGS_SCREEN_LINE_DAY;
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
