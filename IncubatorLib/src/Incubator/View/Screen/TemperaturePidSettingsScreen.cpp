#include "Incubator/View/Screen/TemperaturePidSettingsScreen.h"
#include <cassert>

namespace Incubator
{

    void TemperaturePidSettingsScreen::HandleScreenLineP(const JoystickEvent &event)
    {
        if (event.bIsLeftPressed)
        {
            SetNextScreen(SCREEN_TYPE_ADMINISTRATOR_SETTINGS);
        }
        else if (event.bIsDownPressed)
        {
            m_SelectedLine = TEMPERATURE_PID_SETTINGS_SCREEN_LINE_I;
            m_Lcd->MoveCursor(1U, 0U);
            m_Lcd->Print(TC2004::String80(" "));
            m_Lcd->MoveCursor(2U, 0U);
            m_Lcd->Print(TC2004::TC2004_CHAR_ARROW_SYMBOL);
        }
        else if (event.bIsRightPressed || event.bIsButtonPressed)
        {
            SetNextScreen(SCREEN_TYPE_DATA_SET_P);
        }
        else
        {
            // intentionally left blank
        }
    }

    void TemperaturePidSettingsScreen::HandleScreenLineI(const JoystickEvent &event)
    {
        if (event.bIsLeftPressed)
        {
            SetNextScreen(SCREEN_TYPE_ADMINISTRATOR_SETTINGS);
        }
        else if(event.bIsUpPressed)
        {
            m_SelectedLine = TEMPERATURE_PID_SETTINGS_SCREEN_LINE_P;
            m_Lcd->MoveCursor(1U, 0U);
            m_Lcd->Print(TC2004::TC2004_CHAR_ARROW_SYMBOL);
            m_Lcd->MoveCursor(2U, 0U);
            m_Lcd->Print(TC2004::String80(" "));
        }
        else if (event.bIsDownPressed)
        {
            m_SelectedLine = TEMPERATURE_PID_SETTINGS_SCREEN_LINE_D;
            m_Lcd->MoveCursor(2U, 0U);
            m_Lcd->Print(TC2004::String80(" "));
            m_Lcd->MoveCursor(3U, 0U);
            m_Lcd->Print(TC2004::TC2004_CHAR_ARROW_SYMBOL);
        }
        else if (event.bIsRightPressed || event.bIsButtonPressed)
        {
            SetNextScreen(SCREEN_TYPE_DATA_SET_I);
        }
        else
        {
            // intentionally left blank
        }
    }

    void TemperaturePidSettingsScreen::HandleScreenLineD(const JoystickEvent &event)
    {
        if (event.bIsLeftPressed)
        {
            SetNextScreen(SCREEN_TYPE_ADMINISTRATOR_SETTINGS);
        }
        else if(event.bIsUpPressed)
        {
            m_SelectedLine = TEMPERATURE_PID_SETTINGS_SCREEN_LINE_I;
            m_Lcd->MoveCursor(2U, 0U);
            m_Lcd->Print(TC2004::TC2004_CHAR_ARROW_SYMBOL);
            m_Lcd->MoveCursor(3U, 0U);
            m_Lcd->Print(TC2004::String80(" "));
        }
        else if (event.bIsRightPressed || event.bIsButtonPressed)
        {
            SetNextScreen(SCREEN_TYPE_DATA_SET_D);
        }
        else
        {
            // intentionally left blank
        }
    }


    TemperaturePidSettingsScreen::TemperaturePidSettingsScreen() : 
        AScreen { SCREEN_TYPE_TEMPERATURE_PID },
        m_Lcd { nullptr },
        m_SelectedLine { TEMPERATURE_PID_SETTINGS_SCREEN_LINE_P }
    {
    }

    TemperaturePidSettingsScreen::~TemperaturePidSettingsScreen()
    {
    }

    void TemperaturePidSettingsScreen::Initialize(TC2004::Lcd *tc2004Lcd)
    {
        m_Lcd = tc2004Lcd;
    }

    void TemperaturePidSettingsScreen::OnInitial()
    {
        Reset();
        m_Lcd->Clear();
        m_Lcd->MoveCursor(0U, 0U);
        m_Lcd->Print(TC2004::String80("[S"));
        m_Lcd->Print(TC2004::TC2004_CHAR_LOWER_I);
        m_Lcd->Print(TC2004::String80("cakl"));
        m_Lcd->Print(TC2004::TC2004_CHAR_LOWER_I);
        m_Lcd->Print(TC2004::String80("k Pid]"));
        m_Lcd->MoveCursor(1U, 0U);
        if (TEMPERATURE_PID_SETTINGS_SCREEN_LINE_P == m_SelectedLine)
        {
            m_Lcd->Print(TC2004::TC2004_CHAR_ARROW_SYMBOL);
        }
        else
        {
            m_Lcd->Print(TC2004::String80(" "));
        }
        m_Lcd->Print(TC2004::String80("P"));

        m_Lcd->MoveCursor(2U, 0U);
        if (TEMPERATURE_PID_SETTINGS_SCREEN_LINE_I == m_SelectedLine)
        {
            m_Lcd->Print(TC2004::TC2004_CHAR_ARROW_SYMBOL);
        }
        else
        {
            m_Lcd->Print(TC2004::String80(" "));
        }
        m_Lcd->Print(TC2004::String80("I"));

        m_Lcd->MoveCursor(3U, 0U);
        if (TEMPERATURE_PID_SETTINGS_SCREEN_LINE_D == m_SelectedLine)
        {
            m_Lcd->Print(TC2004::TC2004_CHAR_ARROW_SYMBOL);
        }
        else
        {
            m_Lcd->Print(TC2004::String80(" "));
        }
        m_Lcd->Print(TC2004::String80("D"));
    }

    void TemperaturePidSettingsScreen::Run()
    {
        // intentionally left blank
    }

    void TemperaturePidSettingsScreen::OnUserAction(const JoystickEvent &event)
    {
        switch (m_SelectedLine)
        {
        case TEMPERATURE_PID_SETTINGS_SCREEN_LINE_P:
        {
            HandleScreenLineP(event);
            break;
        }

        case TEMPERATURE_PID_SETTINGS_SCREEN_LINE_I:
        {
            HandleScreenLineI(event);
            break;
        }

        case TEMPERATURE_PID_SETTINGS_SCREEN_LINE_D:
        {
            HandleScreenLineD(event);
            break;
        }
        
        default:
            break;
        }
        // intentionally left blank
    }


} // namespace Incubator
