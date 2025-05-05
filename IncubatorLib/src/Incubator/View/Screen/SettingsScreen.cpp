#include "Incubator/View/Screen/SettingsScreen.h"

namespace Incubator
{

    SettingsScreen::SettingsScreen() : 
        AScreen { SCREEN_TYPE_SETTINGS },
        m_Lcd { nullptr },
        m_SelectedLine { 0U }
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
        m_Lcd->Clear();
        m_Lcd->MoveCursor(0U, 0U);
        m_Lcd->Print(TC2004::String80("--AYARLAR--"));
        m_Lcd->MoveCursor(1U, 0U);
        if (0U == m_SelectedLine)
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
        if (1U == m_SelectedLine)
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
        case 0U:
        {
            if(event.bIsDownPressed)
            {
                m_SelectedLine = 1U;
                m_Lcd->MoveCursor(1U, 0U);
                m_Lcd->Print(TC2004::String80(" "));
                m_Lcd->MoveCursor(2U, 0U);
                m_Lcd->Print(TC2004::TC2004_CHAR_ARROW_SYMBOL);
            }
            break;
        }

        case 1U:
        {
            if(event.bIsUpPressed)
            {
                m_SelectedLine = 0U;
                m_Lcd->MoveCursor(1U, 0U);
                m_Lcd->Print(TC2004::TC2004_CHAR_ARROW_SYMBOL);
                m_Lcd->MoveCursor(2U, 0U);
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
