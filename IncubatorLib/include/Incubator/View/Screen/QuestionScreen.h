#ifndef INCUBATOR_QUESTIONSCREEN_H
#define INCUBATOR_QUESTIONSCREEN_H
#include "TC2004/Lcd.h"
#include "AScreen.h"
#include "Incubator/Time/TimerTask.h"
#include "Incubator/IncubatorData/SettingsData.h"
#include "Incubator/IncubatorData/TimeInformationData.h"
#include "Incubator/View/DataChangedEventHandler/DataChangedEventHandlers.h"
#include "EnumScreenType.h"
#include "EnumQuestionSelection.h"
namespace Incubator
{
    class QuestionScreen : public AScreen
    {
    public:
        QuestionScreen();
        ~QuestionScreen();
        void Initialize(TC2004::Lcd *tc2004Lcd,
            DataChangedEventHandlers *eventHandlers,
            SettingsData *changedSettingsData
        );
        void OnInitial() override;

        virtual void Reset() override;
        virtual void Run() override;
        void OnUserAction(const JoystickEvent &event) override;

    private:
        TC2004::Lcd *m_Lcd;
        EnumQuestionSelection m_QuestionSelection;
        DataChangedEventHandlers *m_DataChangedEventHandlers;
        SettingsData *m_ChangedSettingsData;
    };
} // namespace Incubator

#endif // INCUBATOR_QUESTIONSCREEN_H