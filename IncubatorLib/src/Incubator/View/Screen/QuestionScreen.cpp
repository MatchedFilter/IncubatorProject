#include "Incubator/View/Screen/QuestionScreen.h"
#include "TC2004/String80.h"

namespace Incubator
{

    QuestionScreen::QuestionScreen() : 
        AScreen { SCREEN_TYPE_QUESTION },
        m_Lcd { nullptr },
        m_QuestionSelection { QUESTION_SELECTION_NO }
    {
    }

    QuestionScreen::~QuestionScreen()
    {
    }

    void QuestionScreen::Initialize(TC2004::Lcd *tc2004Lcd)
    {
        m_Lcd = tc2004Lcd;
    }

    void QuestionScreen::OnInitial()
    {
        m_Lcd->Clear();
        m_Lcd->MoveCursor(0U, 0U);
        m_Lcd->Print(TC2004::String80("Kaydedilsin mi?"));

        m_Lcd->MoveCursor(3U, 0U);
        if (QUESTION_SELECTION_NO == m_QuestionSelection)
        {
            m_Lcd->Print(TC2004::String80(" Evet        [Hay"));
            m_Lcd->Print(TC2004::TC2004_CHAR_LOWER_I);
            m_Lcd->Print(TC2004::String80("r]"));
        }
        else if (QUESTION_SELECTION_YES == m_QuestionSelection)
        {
            m_Lcd->Print(TC2004::String80("[Evet]        Hay"));
            m_Lcd->Print(TC2004::TC2004_CHAR_LOWER_I);
            m_Lcd->Print(TC2004::String80("r "));
        }
        else
        {
            // intentionally left blank
        }
    }


    void QuestionScreen::Reset()
    {
        m_QuestionSelection = QUESTION_SELECTION_NO;
    }

    void QuestionScreen::Run()
    {
        // intentionally left blank
    }

    void QuestionScreen::OnUserAction(const JoystickEvent &event)
    {
        if (QUESTION_SELECTION_NO == m_QuestionSelection)
        {
            if (event.bIsLeftPressed)
            {
                m_QuestionSelection = QUESTION_SELECTION_YES;
                m_Lcd->MoveCursor(3U, 0U);
                m_Lcd->Print(TC2004::String80("["));
                m_Lcd->MoveCursor(3U, 5U);
                m_Lcd->Print(TC2004::String80("]"));
                m_Lcd->MoveCursor(3U, 13U);
                m_Lcd->Print(TC2004::String80(" "));
                m_Lcd->MoveCursor(3U, 19U);
                m_Lcd->Print(TC2004::String80(" "));
            }
        }
        else
        {
            if (event.bIsRightPressed)
            {
                m_QuestionSelection = QUESTION_SELECTION_NO;
                m_Lcd->MoveCursor(3U, 0U);
                m_Lcd->Print(TC2004::String80(" "));
                m_Lcd->MoveCursor(3U, 5U);
                m_Lcd->Print(TC2004::String80(" "));
                m_Lcd->MoveCursor(3U, 13U);
                m_Lcd->Print(TC2004::String80("["));
                m_Lcd->MoveCursor(3U, 19U);
                m_Lcd->Print(TC2004::String80("]"));
            }
        }
        // intentionally left blank
    }


} // namespace Incubator
