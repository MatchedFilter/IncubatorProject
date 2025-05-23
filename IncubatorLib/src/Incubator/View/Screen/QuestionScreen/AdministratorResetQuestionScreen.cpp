#include "Incubator/View/Screen/QuestionScreen/AdministratorResetQuestionScreen.h"
#include "TC2004/String80.h"
#include <cassert>

namespace Incubator
{

    AdministratorResetQuestionScreen::AdministratorResetQuestionScreen() : 
        AQuestionScreen { SCREEN_TYPE_QUESTION_ADMIN_RESET },
        m_AdminData { nullptr }
    {
    }

    AdministratorResetQuestionScreen::~AdministratorResetQuestionScreen()
    {
    }

    void AdministratorResetQuestionScreen::OnInitial()
    {
        Reset();
        m_Lcd->Clear();
        m_Lcd->MoveCursor(0U, 0U);
        m_Lcd->Print(TC2004::String80("Y"));
        m_Lcd->Print(TC2004::TC2004_CHAR_LOWER_O);
        m_Lcd->Print(TC2004::String80("netici ayarlar"));
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


    void AdministratorResetQuestionScreen::Initialize(TC2004::Lcd *tc2004Lcd,
        DataChangedEventHandlers *eventHandlers,
        AdminData *changedAdminData)
    {
        AQuestionScreen::Initialize(tc2004Lcd, eventHandlers);
        m_AdminData = changedAdminData;

        assert(nullptr != m_AdminData);
    }

    void AdministratorResetQuestionScreen::NotifyChangedData()
    {
        m_AdminData->Reset();
        m_DataChangedEventHandlers->m_AdminDataChangedEventHandler->OnUpdate(*m_AdminData);
    }

    EnumScreenType AdministratorResetQuestionScreen::GetNextScreenWhenYesSelected() const
    {
        return SCREEN_TYPE_ADMINISTRATOR_SETTINGS;
    }



} // namespace Incubator
