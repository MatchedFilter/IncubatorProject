#include "Incubator/View/Screen/TimeSettingsScreen.h"

namespace Incubator
{

    void TimeSettingsScreen::HandleScreenLineTotalDay(const JoystickEvent &event)
    {
        if (event.bIsLeftPressed)
        {
            SetNextScreen(SCREEN_TYPE_SETTINGS);
        }
        else if (event.bIsDownPressed)
        {
            m_SelectedLine = TIME_SETTINGS_SCREEN_LINE_DAY;
            m_Lcd->MoveCursor(1U, 0U);
            m_Lcd->Print(TC2004::String80(" "));
            m_Lcd->MoveCursor(2U, 0U);
            m_Lcd->Print(TC2004::TC2004_CHAR_ARROW_SYMBOL);
        }
        else if (event.bIsRightPressed || event.bIsButtonPressed)
        {
            // SetNextScreen(SCREEN_TYPE_TIME_SET_TOTAL_DAYS);
        }
        else
        {
            // intentionally left blank
        }
    }

    void TimeSettingsScreen::HandleScreenLineDay(const JoystickEvent &event)
    {
        if (event.bIsLeftPressed)
        {
            SetNextScreen(SCREEN_TYPE_SETTINGS);
        }
        else if(event.bIsUpPressed)
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
        else if (event.bIsRightPressed || event.bIsButtonPressed)
        {
            // SetNextScreen(SCREEN_TYPE_TIME_SET_LAST_DAYS);
            // TODO: Create Day Set Screen
        }
        else
        {
            // intentionally left blank
        }
    }

    void TimeSettingsScreen::HandleScreenLineHour(const JoystickEvent &event)
    {
        if (event.bIsLeftPressed)
        {
            SetNextScreen(SCREEN_TYPE_SETTINGS);
        }
        else if(event.bIsUpPressed)
        {
            m_SelectedLine = TIME_SETTINGS_SCREEN_LINE_DAY;
            m_Lcd->MoveCursor(2U, 0U);
            m_Lcd->Print(TC2004::TC2004_CHAR_ARROW_SYMBOL);
            m_Lcd->MoveCursor(3U, 0U);
            m_Lcd->Print(TC2004::String80(" "));
        }
        else if (event.bIsRightPressed || event.bIsButtonPressed)
        {
            // TODO: Create Day Set Screen
        }
        else
        {
            // intentionally left blank
        }
    }


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
        Reset();
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
            HandleScreenLineTotalDay(event);
            break;
        }

        case TIME_SETTINGS_SCREEN_LINE_DAY:
        {
            HandleScreenLineDay(event);
            break;
        }

        case TIME_SETTINGS_SCREEN_LINE_HOUR:
        {
            HandleScreenLineHour(event);
            break;
        }
        
        default:
            break;
        }
        // intentionally left blank
    }


} // namespace Incubator
