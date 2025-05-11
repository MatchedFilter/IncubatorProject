#include "Incubator/View/Screen/DataSetScreen/ADataSetScreen.h"
#include "TC2004/String80.h"
#include <cassert>

namespace Incubator
{

    void ADataSetScreen::OnSaveStateEnter()
    {
        m_Lcd->MoveCursor(2U, 0U);
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

    void ADataSetScreen::HandleForSaveState(const JoystickEvent &event)
    {
        if (event.bIsButtonPressed)
        {
            if (QUESTION_SELECTION_YES == m_QuestionSelection)
            {
                SetNextScreen(SCREEN_TYPE_MAIN);
                NotifyChangedData();
            }
            else
            {
                GetNextScreenForNoSelection();
                SetNextScreen(GetNextScreenForNoSelection());
            }
        }
        else
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
        }   
    }

    void ADataSetScreen::HandleForSetState(const JoystickEvent &event)
    {
        if (event.bIsButtonPressed)
        {
            m_bIsInSaveState = true;
            OnSaveStateEnter();
        }
        else
        {
            if (event.bIsUpPressed)
            {
                OnIncrementHighEvent();
            }
            else if (event.bIsDownPressed)
            {
                OnDecrementHighEvent();
            }
            else if (event.bIsRightPressed)
            {
                OnIncrementLowEvent();
            }
            else if (event.bIsLeftPressed)
            {
                OnDecrementLowEvent();
            }
            else
            {
                // intentionally left blank
            }
            m_Lcd->MoveCursor(1U, 6U);
            PrintNewData();
        }
    }

    ADataSetScreen::ADataSetScreen(const EnumScreenType screenType) : 
        AScreen { screenType },
        m_Lcd { nullptr },
        m_CurrentIncubatorInformationData { nullptr },
        m_ChangedIncubatorInformationData { nullptr },
        m_DataChangedEventHandlers { nullptr },
        m_QuestionSelection { QUESTION_SELECTION_NO },
        m_bIsInSaveState { false }
    {
    }

    ADataSetScreen::~ADataSetScreen()
    {
    }

    void ADataSetScreen::Initialize(TC2004::Lcd *tc2004Lcd,
        DataChangedEventHandlers * const eventHandlers,
        const IncubatorInformationData *const currentIncubatorInformationData,
        IncubatorInformationData *const changedIncubatorInformationData)
    {
        m_Lcd = tc2004Lcd;
        m_DataChangedEventHandlers = eventHandlers;
        m_CurrentIncubatorInformationData = currentIncubatorInformationData;
        m_ChangedIncubatorInformationData = changedIncubatorInformationData;

        assert(nullptr != m_DataChangedEventHandlers);
        assert(nullptr != m_CurrentIncubatorInformationData);
        assert(nullptr != m_ChangedIncubatorInformationData);
    }

    void ADataSetScreen::OnInitial()
    {
        Reset();
        m_bIsInSaveState = false;

        assert(nullptr != m_CurrentIncubatorInformationData);
        assert(nullptr != m_ChangedIncubatorInformationData);

        m_ChangedIncubatorInformationData->Copy(*m_CurrentIncubatorInformationData);

        m_Lcd->Clear();
        m_Lcd->MoveCursor(0U, 0U);
        m_Lcd->Print(TC2004::String80("Eski: "));
        PrintCurrentData();
        m_Lcd->MoveCursor(1U, 0U);
        m_Lcd->Print(TC2004::String80("Yeni: "));
        PrintNewData();
    }

    void ADataSetScreen::Reset()
    {
        AScreen::Reset();
        m_QuestionSelection = QUESTION_SELECTION_NO;
    }

    void ADataSetScreen::Run()
    {
        // intentionally left blank
    }

    void ADataSetScreen::OnUserAction(const JoystickEvent &event)
    {
        if (m_bIsInSaveState)
        {
            HandleForSaveState(event);
        }
        else
        {
            HandleForSetState(event);
        }
    }


} // namespace Incubator
