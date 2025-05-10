#include "Incubator/View/Screen/HumiditySettingsScreen.h"

namespace Incubator
{

    void HumiditySettingsScreen::HandlerHumidityLine(const JoystickEvent &event)
    {
        if (event.bIsLeftPressed)
        {
            SetNextScreen(SCREEN_TYPE_INCUBATOR_SETTINGS);
        }
        else if(event.bIsDownPressed)
        {
            m_SelectedLine = HUMIDITY_SETTINGS_SCREEN_LINE_LAST_DAYS_HUMIDITY;
            m_Lcd->MoveCursor(1U, 0U);
            m_Lcd->Print(TC2004::String80(" "));
            m_Lcd->MoveCursor(2U, 0U);
            m_Lcd->Print(TC2004::TC2004_CHAR_ARROW_SYMBOL);
        }
        else if (event.bIsRightPressed || event.bIsButtonPressed)
        {
            SetNextScreen(SCREEN_TYPE_DATA_SET_HUMIDITY);
        }
        else
        {
            // intentionally left blank
        }
    }

    void HumiditySettingsScreen::HandleHumidityLastDaysHumidityLine(const JoystickEvent &event)
    {
        if (event.bIsLeftPressed)
        {
            SetNextScreen(SCREEN_TYPE_INCUBATOR_SETTINGS);
        }
        else if(event.bIsUpPressed)
        {
            m_SelectedLine = HUMIDITY_SETTINGS_SCREEN_LINE_HUMIDITY;
            m_Lcd->MoveCursor(1U, 0U);
            m_Lcd->Print(TC2004::TC2004_CHAR_ARROW_SYMBOL);
            m_Lcd->MoveCursor(2U, 0U);
            m_Lcd->Print(TC2004::String80(" "));
        }

        else if (event.bIsRightPressed || event.bIsButtonPressed)
        {
            SetNextScreen(SCREEN_TYPE_DATA_SET_HUMIDITY_LAST_DAYS);
        }
        else
        {
            // intentionally left blank
        }
    }

    HumiditySettingsScreen::HumiditySettingsScreen() : 
        AScreen { SCREEN_TYPE_HUMIDITY_SETTINGS },
        m_Lcd { nullptr },
        m_SelectedLine { HUMIDITY_SETTINGS_SCREEN_LINE_HUMIDITY }
    {
    }

    HumiditySettingsScreen::~HumiditySettingsScreen()
    {
    }

    void HumiditySettingsScreen::Initialize(TC2004::Lcd *tc2004Lcd)
    {
        m_Lcd = tc2004Lcd;
    }

    void HumiditySettingsScreen::OnInitial()
    {
        Reset();
        m_Lcd->Clear();
        m_Lcd->MoveCursor(0U, 0U);
        m_Lcd->Print(TC2004::String80("[Nem Ayarlar"));
        m_Lcd->Print(TC2004::TC2004_CHAR_LOWER_I);
        m_Lcd->Print(TC2004::String80("]"));
        m_Lcd->MoveCursor(1U, 0U);
        if (HUMIDITY_SETTINGS_SCREEN_LINE_HUMIDITY == m_SelectedLine)
        {
            m_Lcd->Print(TC2004::TC2004_CHAR_ARROW_SYMBOL);
        }
        else
        {
            m_Lcd->Print(TC2004::String80(" "));
        }
        m_Lcd->Print(TC2004::String80("Nem"));

        m_Lcd->MoveCursor(2U, 0U);
        if (HUMIDITY_SETTINGS_SCREEN_LINE_LAST_DAYS_HUMIDITY == m_SelectedLine)
        {
            m_Lcd->Print(TC2004::TC2004_CHAR_ARROW_SYMBOL);
        }
        else
        {
            m_Lcd->Print(TC2004::String80(" "));
        }
        m_Lcd->Print(TC2004::String80("Son nem"));
    }

    void HumiditySettingsScreen::Run()
    {
        // intentionally left blank
    }

    void HumiditySettingsScreen::OnUserAction(const JoystickEvent &event)
    {
        switch (m_SelectedLine)
        {
        case HUMIDITY_SETTINGS_SCREEN_LINE_HUMIDITY:
        {
            HandlerHumidityLine(event);
            break;
        }

        case HUMIDITY_SETTINGS_SCREEN_LINE_LAST_DAYS_HUMIDITY:
        {
            HandleHumidityLastDaysHumidityLine(event);
            break;
        }
        
        default:
            break;
        }
    }


} // namespace Incubator
