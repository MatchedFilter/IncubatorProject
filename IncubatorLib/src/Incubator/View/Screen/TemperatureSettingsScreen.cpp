#include "Incubator/View/Screen/TemperatureSettingsScreen.h"

namespace Incubator
{

    void TemperatureSettingsScreen::HandlerTemperatureLine(const JoystickEvent &event)
    {
        if (event.bIsLeftPressed)
        {
            SetNextScreen(SCREEN_TYPE_INCUBATOR_SETTINGS);
        }
        else if(event.bIsDownPressed)
        {
            m_SelectedLine = TEMPERATURE_SETTINGS_SCREEN_LINE_LAST_DAYS_TEMPERATURE;
            m_Lcd->MoveCursor(1U, 0U);
            m_Lcd->Print(TC2004::String80(" "));
            m_Lcd->MoveCursor(2U, 0U);
            m_Lcd->Print(TC2004::TC2004_CHAR_ARROW_SYMBOL);
        }
        else if (event.bIsRightPressed || event.bIsButtonPressed)
        {
            SetNextScreen(SCREEN_TYPE_DATA_SET_TEMPERATURE);
        }
        else
        {
            // intentionally left blank
        }
    }

    void TemperatureSettingsScreen::HandleTemperatureLastDaysTemperatureLine(const JoystickEvent &event)
    {
        if (event.bIsLeftPressed)
        {
            SetNextScreen(SCREEN_TYPE_INCUBATOR_SETTINGS);
        }
        else if(event.bIsUpPressed)
        {
            m_SelectedLine = TEMPERATURE_SETTINGS_SCREEN_LINE_TEMPERATURE;
            m_Lcd->MoveCursor(1U, 0U);
            m_Lcd->Print(TC2004::TC2004_CHAR_ARROW_SYMBOL);
            m_Lcd->MoveCursor(2U, 0U);
            m_Lcd->Print(TC2004::String80(" "));
        }

        else if (event.bIsRightPressed || event.bIsButtonPressed)
        {
            SetNextScreen(SCREEN_TYPE_DATA_SET_TEMPERATURE_LAST_DAYS);
        }
        else
        {
            // intentionally left blank
        }
    }

    TemperatureSettingsScreen::TemperatureSettingsScreen() : 
        AScreen { SCREEN_TYPE_TEMPERATURE_SETTINGS },
        m_Lcd { nullptr },
        m_SelectedLine { TEMPERATURE_SETTINGS_SCREEN_LINE_TEMPERATURE }
    {
    }

    TemperatureSettingsScreen::~TemperatureSettingsScreen()
    {
    }

    void TemperatureSettingsScreen::Initialize(TC2004::Lcd *tc2004Lcd)
    {
        m_Lcd = tc2004Lcd;
    }

    void TemperatureSettingsScreen::OnInitial()
    {
        Reset();
        m_Lcd->Clear();
        m_Lcd->MoveCursor(0U, 0U);
        m_Lcd->Print(TC2004::String80("[S"));
        m_Lcd->Print(TC2004::TC2004_CHAR_LOWER_I);
        m_Lcd->Print(TC2004::String80("cakl"));
        m_Lcd->Print(TC2004::TC2004_CHAR_LOWER_I);
        m_Lcd->Print(TC2004::String80("k Ayarlar"));
        m_Lcd->Print(TC2004::TC2004_CHAR_LOWER_I);
        m_Lcd->Print(TC2004::String80("]"));
        m_Lcd->MoveCursor(1U, 0U);
        if (TEMPERATURE_SETTINGS_SCREEN_LINE_TEMPERATURE == m_SelectedLine)
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
        m_Lcd->Print(TC2004::String80("k"));

        m_Lcd->MoveCursor(2U, 0U);
        if (TEMPERATURE_SETTINGS_SCREEN_LINE_LAST_DAYS_TEMPERATURE == m_SelectedLine)
        {
            m_Lcd->Print(TC2004::TC2004_CHAR_ARROW_SYMBOL);
        }
        else
        {
            m_Lcd->Print(TC2004::String80(" "));
        }
        m_Lcd->Print(TC2004::String80("Son s"));
        m_Lcd->Print(TC2004::TC2004_CHAR_LOWER_I);
        m_Lcd->Print(TC2004::String80("cakl"));
        m_Lcd->Print(TC2004::TC2004_CHAR_LOWER_I);
        m_Lcd->Print(TC2004::String80("k"));
    }

    void TemperatureSettingsScreen::Run()
    {
        // intentionally left blank
    }

    void TemperatureSettingsScreen::OnUserAction(const JoystickEvent &event)
    {
        switch (m_SelectedLine)
        {
        case TEMPERATURE_SETTINGS_SCREEN_LINE_TEMPERATURE:
        {
            HandlerTemperatureLine(event);
            break;
        }

        case TEMPERATURE_SETTINGS_SCREEN_LINE_LAST_DAYS_TEMPERATURE:
        {
            HandleTemperatureLastDaysTemperatureLine(event);
            break;
        }
        
        default:
            break;
        }
    }


} // namespace Incubator
