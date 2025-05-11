#include "Incubator/View/Screen/AdministatorSettingsScreen.h"
#include <cassert>

namespace Incubator
{

    void AdministatorSettingsScreen::HandleScreenLineTemperaturePid(const JoystickEvent &event)
    {
        if (event.bIsLeftPressed)
        {
            SetNextScreen(SCREEN_TYPE_SETTINGS);
        }
        else if (event.bIsDownPressed)
        {
            m_SelectedLine = ADMINISTRATOR_SETTINGS_SCREEN_LINE_HUMIDITY_HYSTERISIS;
            m_Lcd->MoveCursor(1U, 0U);
            m_Lcd->Print(TC2004::String80(" "));
            m_Lcd->MoveCursor(2U, 0U);
            m_Lcd->Print(TC2004::TC2004_CHAR_ARROW_SYMBOL);
        }
        else if (event.bIsRightPressed || event.bIsButtonPressed)
        {
            SetNextScreen(SCREEN_TYPE_TEMPERATURE_PID);
        }
        else
        {
            // intentionally left blank
        }
    }

    void AdministatorSettingsScreen::HandleScreenLineHumidityHysterisis(const JoystickEvent &event)
    {
        if (event.bIsLeftPressed)
        {
            SetNextScreen(SCREEN_TYPE_SETTINGS);
        }
        else if(event.bIsUpPressed)
        {
            m_SelectedLine = ADMINISTRATOR_SETTINGS_SCREEN_LINE_TEMPERATURE_PID;
            m_Lcd->MoveCursor(1U, 0U);
            m_Lcd->Print(TC2004::TC2004_CHAR_ARROW_SYMBOL);
            m_Lcd->MoveCursor(2U, 0U);
            m_Lcd->Print(TC2004::String80(" "));
        }
        else if (event.bIsDownPressed)
        {
            m_SelectedLine = ADMINISTRATOR_SETTINGS_SCREEN_LINE_RESET;
            m_Lcd->MoveCursor(2U, 0U);
            m_Lcd->Print(TC2004::String80(" "));
            m_Lcd->MoveCursor(3U, 0U);
            m_Lcd->Print(TC2004::TC2004_CHAR_ARROW_SYMBOL);
        }
        else if (event.bIsRightPressed || event.bIsButtonPressed)
        {
            SetNextScreen(SCREEN_TYPE_HYSTERISIS_HUMIDITY);
        }
        else
        {
            // intentionally left blank
        }
    }

    void AdministatorSettingsScreen::HandleScreenLineReset(const JoystickEvent &event)
    {
        if (event.bIsLeftPressed)
        {
            SetNextScreen(SCREEN_TYPE_SETTINGS);
        }
        else if(event.bIsUpPressed)
        {
            m_SelectedLine = ADMINISTRATOR_SETTINGS_SCREEN_LINE_HUMIDITY_HYSTERISIS;
            m_Lcd->MoveCursor(2U, 0U);
            m_Lcd->Print(TC2004::TC2004_CHAR_ARROW_SYMBOL);
            m_Lcd->MoveCursor(3U, 0U);
            m_Lcd->Print(TC2004::String80(" "));
        }
        else if (event.bIsRightPressed || event.bIsButtonPressed)
        {
            SetNextScreen(SCREEN_TYPE_QUESTION_ADMIN_RESET);
        }
        else
        {
            // intentionally left blank
        }
    }


    AdministatorSettingsScreen::AdministatorSettingsScreen() : 
        AScreen { SCREEN_TYPE_ADMINISTRATOR_SETTINGS },
        m_Lcd { nullptr },
        m_SelectedLine { ADMINISTRATOR_SETTINGS_SCREEN_LINE_TEMPERATURE_PID }
    {
    }

    AdministatorSettingsScreen::~AdministatorSettingsScreen()
    {
    }

    void AdministatorSettingsScreen::Initialize(TC2004::Lcd *tc2004Lcd)
    {
        m_Lcd = tc2004Lcd;
    }

    void AdministatorSettingsScreen::OnInitial()
    {
        Reset();
        m_Lcd->Clear();
        m_Lcd->MoveCursor(0U, 0U);
        m_Lcd->Print(TC2004::String80("[Y"));
        m_Lcd->Print(TC2004::TC2004_CHAR_LOWER_O);
        m_Lcd->Print(TC2004::String80("netici Ayarlar"));
        m_Lcd->Print(TC2004::TC2004_CHAR_LOWER_I);
        m_Lcd->Print(TC2004::String80("]"));
        m_Lcd->MoveCursor(1U, 0U);
        if (ADMINISTRATOR_SETTINGS_SCREEN_LINE_TEMPERATURE_PID == m_SelectedLine)
        {
            m_Lcd->Print(TC2004::TC2004_CHAR_ARROW_SYMBOL);
        }
        else
        {
            m_Lcd->Print(TC2004::String80(" "));
        }
        m_Lcd->Print(TC2004::String80("S"));
        m_Lcd->Print(TC2004::TC2004_CHAR_LOWER_I);
        m_Lcd->Print(TC2004::String80("cakl"));
        m_Lcd->Print(TC2004::TC2004_CHAR_LOWER_I);
        m_Lcd->Print(TC2004::String80("k Pid"));

        m_Lcd->MoveCursor(2U, 0U);
        if (ADMINISTRATOR_SETTINGS_SCREEN_LINE_HUMIDITY_HYSTERISIS == m_SelectedLine)
        {
            m_Lcd->Print(TC2004::TC2004_CHAR_ARROW_SYMBOL);
        }
        else
        {
            m_Lcd->Print(TC2004::String80(" "));
        }
        m_Lcd->Print(TC2004::String80("Nem Histerisis"));

        m_Lcd->MoveCursor(3U, 0U);
        if (ADMINISTRATOR_SETTINGS_SCREEN_LINE_RESET == m_SelectedLine)
        {
            m_Lcd->Print(TC2004::TC2004_CHAR_ARROW_SYMBOL);
        }
        else
        {
            m_Lcd->Print(TC2004::String80(" "));
        }
        m_Lcd->Print(TC2004::String80("S"));
        m_Lcd->Print(TC2004::TC2004_CHAR_LOWER_I);
        m_Lcd->Print(TC2004::String80("f"));
        m_Lcd->Print(TC2004::TC2004_CHAR_LOWER_I);
        m_Lcd->Print(TC2004::String80("rla"));
    }

    void AdministatorSettingsScreen::Run()
    {
        // intentionally left blank
    }

    void AdministatorSettingsScreen::OnUserAction(const JoystickEvent &event)
    {
        switch (m_SelectedLine)
        {
        case ADMINISTRATOR_SETTINGS_SCREEN_LINE_TEMPERATURE_PID:
        {
            HandleScreenLineTemperaturePid(event);
            break;
        }

        case ADMINISTRATOR_SETTINGS_SCREEN_LINE_HUMIDITY_HYSTERISIS:
        {
            HandleScreenLineHumidityHysterisis(event);
            break;
        }

        case ADMINISTRATOR_SETTINGS_SCREEN_LINE_RESET:
        {
            HandleScreenLineReset(event);
            break;
        }
        
        default:
            break;
        }
        // intentionally left blank
    }


} // namespace Incubator
