#include "Incubator/View/Screen/QuestionScreen/SaveQuestionScreen.h"
#include "TC2004/String80.h"
#include <cassert>

namespace Incubator
{

    SaveQuestionScreen::SaveQuestionScreen() : 
        AQuestionScreen { SCREEN_TYPE_QUESTION_SAVE },
        m_ChangedSettingsData { nullptr }
    {
    }

    SaveQuestionScreen::~SaveQuestionScreen()
    {
    }

    void SaveQuestionScreen::OnInitial()
    {
        Reset();
        m_Lcd->MoveCursor(0U, 0U);
        m_Lcd->Print(TC2004::String80("Kaydedilsin mi?"));
        AQuestionScreen::OnInitial();
    }


    void SaveQuestionScreen::Initialize(TC2004::Lcd *tc2004Lcd,
        DataChangedEventHandlers *eventHandlers,
        SettingsData *changedSettingsData
    )
    {
        AQuestionScreen::Initialize(tc2004Lcd, eventHandlers);
        m_ChangedSettingsData = changedSettingsData;

        assert(nullptr != m_ChangedSettingsData);
    }

    void SaveQuestionScreen::NotifyChangedData()
    {
        m_DataChangedEventHandlers->m_SettingsDataChangedEventHandler->OnUpdate(*m_ChangedSettingsData);
    }


} // namespace Incubator
