#include "Incubator/View/Screen/QuestionScreen/TimeResetQuestionScreen.h"
#include "TC2004/String80.h"
#include <cassert>

namespace Incubator
{

    TimeResetQuestionScreen::TimeResetQuestionScreen() : 
        AQuestionScreen { SCREEN_TYPE_QUESTION_TIME_RESET },
        m_ChangedTimeInformationData { nullptr }
    {
    }

    TimeResetQuestionScreen::~TimeResetQuestionScreen()
    {
    }

    void TimeResetQuestionScreen::OnInitial()
    {
        Reset();
        m_Lcd->Clear();
        m_Lcd->MoveCursor(0U, 0U);
        m_Lcd->Print(TC2004::String80("G"));
        m_Lcd->Print(TC2004::TC2004_CHAR_LOWER_U);
        m_Lcd->Print(TC2004::String80("ncel zaman"));
        m_Lcd->MoveCursor(1U, 0U);
        m_Lcd->Print(TC2004::String80("s"));
        m_Lcd->Print(TC2004::TC2004_CHAR_LOWER_I);
        m_Lcd->Print(TC2004::String80("f"));
        m_Lcd->Print(TC2004::TC2004_CHAR_LOWER_I);
        m_Lcd->Print(TC2004::String80("rlans"));
        m_Lcd->Print(TC2004::TC2004_CHAR_LOWER_I);
        m_Lcd->Print(TC2004::String80("n m"));
        m_Lcd->Print(TC2004::TC2004_CHAR_LOWER_I);
        m_Lcd->Print(TC2004::String80("?"));
        AQuestionScreen::OnInitial();
    }


    void TimeResetQuestionScreen::Initialize(TC2004::Lcd *tc2004Lcd,
        DataChangedEventHandlers *eventHandlers,
        TimeInformationData *changedTimeInformationData)
    {
        AQuestionScreen::Initialize(tc2004Lcd, eventHandlers);
        m_ChangedTimeInformationData = changedTimeInformationData;

        assert(nullptr != m_ChangedTimeInformationData);
    }

    void TimeResetQuestionScreen::NotifyChangedData()
    {
        m_DataChangedEventHandlers->m_TimeInformationDataChangedEventHandler->OnUpdate(*m_ChangedTimeInformationData);
    }


} // namespace Incubator
