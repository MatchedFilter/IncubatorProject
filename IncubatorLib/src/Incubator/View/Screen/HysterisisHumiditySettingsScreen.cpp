#include "Incubator/View/Screen/HysterisisHumiditySettingsScreen.h"
#include <cassert>

namespace Incubator
{

    void HysterisisHumiditySettingsScreen::HandleScreenLineUpper(const JoystickEvent &event)
    {
        if (event.bIsLeftPressed)
        {
            SetNextScreen(SCREEN_TYPE_ADMINISTRATOR_SETTINGS);
        }
        else if (event.bIsDownPressed)
        {
            m_SelectedLine = HYSTERISIS_HUMIDITY_SETTINGS_SCREEN_LINE_LOWER;
            m_Lcd->MoveCursor(1U, 0U);
            m_Lcd->Print(TC2004::String80(" "));
            m_Lcd->MoveCursor(2U, 0U);
            m_Lcd->Print(TC2004::TC2004_CHAR_ARROW_SYMBOL);
        }
        else if (event.bIsRightPressed || event.bIsButtonPressed)
        {
            SetNextScreen(SCREEN_TYPE_DATA_SET_UPPER_HYSTERISIS);
        }
        else
        {
            // intentionally left blank
        }
    }

    void HysterisisHumiditySettingsScreen::HandleScreenLineLower(const JoystickEvent &event)
    {
        if (event.bIsLeftPressed)
        {
            SetNextScreen(SCREEN_TYPE_ADMINISTRATOR_SETTINGS);
        }
        else if(event.bIsUpPressed)
        {
            m_SelectedLine = HYSTERISIS_HUMIDITY_SETTINGS_SCREEN_LINE_UPPER;
            m_Lcd->MoveCursor(1U, 0U);
            m_Lcd->Print(TC2004::TC2004_CHAR_ARROW_SYMBOL);
            m_Lcd->MoveCursor(2U, 0U);
            m_Lcd->Print(TC2004::String80(" "));
        }
        else if (event.bIsRightPressed || event.bIsButtonPressed)
        {
            SetNextScreen(SCREEN_TYPE_DATA_SET_LOWER_HYSTERISIS);
        }
        else
        {
            // intentionally left blank
        }
    }



    HysterisisHumiditySettingsScreen::HysterisisHumiditySettingsScreen() : 
        AScreen { SCREEN_TYPE_HYSTERISIS_HUMIDITY },
        m_Lcd { nullptr },
        m_SelectedLine { HYSTERISIS_HUMIDITY_SETTINGS_SCREEN_LINE_UPPER }
    {
    }

    HysterisisHumiditySettingsScreen::~HysterisisHumiditySettingsScreen()
    {
    }

    void HysterisisHumiditySettingsScreen::Initialize(TC2004::Lcd *tc2004Lcd)
    {
        m_Lcd = tc2004Lcd;
    }

    void HysterisisHumiditySettingsScreen::OnInitial()
    {
        Reset();
        m_Lcd->Clear();
        m_Lcd->MoveCursor(0U, 0U);
        m_Lcd->Print(TC2004::String80("[Nem Histerisis]"));
        m_Lcd->MoveCursor(1U, 0U);
        if (HYSTERISIS_HUMIDITY_SETTINGS_SCREEN_LINE_UPPER == m_SelectedLine)
        {
            m_Lcd->Print(TC2004::TC2004_CHAR_ARROW_SYMBOL);
        }
        else
        {
            m_Lcd->Print(TC2004::String80(" "));
        }
        m_Lcd->Print(TC2004::String80("Nem "));
        m_Lcd->Print(TC2004::TC2004_CHAR_LOWER_U);
        m_Lcd->Print(TC2004::String80("st fark"));

        m_Lcd->MoveCursor(2U, 0U);
        if (HYSTERISIS_HUMIDITY_SETTINGS_SCREEN_LINE_LOWER == m_SelectedLine)
        {
            m_Lcd->Print(TC2004::TC2004_CHAR_ARROW_SYMBOL);
        }
        else
        {
            m_Lcd->Print(TC2004::String80(" "));
        }
        m_Lcd->Print(TC2004::String80("Nem alt fark"));
    }

    void HysterisisHumiditySettingsScreen::Run()
    {
        // intentionally left blank
    }

    void HysterisisHumiditySettingsScreen::OnUserAction(const JoystickEvent &event)
    {
        switch (m_SelectedLine)
        {
        case HYSTERISIS_HUMIDITY_SETTINGS_SCREEN_LINE_UPPER:
        {
            HandleScreenLineUpper(event);
            break;
        }

        case HYSTERISIS_HUMIDITY_SETTINGS_SCREEN_LINE_LOWER:
        {
            HandleScreenLineLower(event);
            break;
        }
        
        default:
            break;
        }
        // intentionally left blank
    }


} // namespace Incubator
