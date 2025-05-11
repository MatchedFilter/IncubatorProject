#ifndef INCUBATOR_AQUESTIONSCREEN_H
#define INCUBATOR_AQUESTIONSCREEN_H
#include "TC2004/Lcd.h"
#include "Incubator/View/Screen/AScreen.h"
#include "Incubator/Time/TimerTask.h"
#include "Incubator/View/DataChangedEventHandler/DataChangedEventHandlers.h"
#include "Incubator/View/Screen/EnumScreenType.h"
#include "EnumQuestionSelection.h"

namespace Incubator
{
    class AQuestionScreen : public AScreen
    {
    public:
        AQuestionScreen(const EnumScreenType screenType);
        ~AQuestionScreen();

        void OnInitial() override;

        virtual void Reset() override final;
        virtual void Run() override final;
        void OnUserAction(const JoystickEvent &event) override final;


    protected:
        void Initialize(TC2004::Lcd *tc2004Lcd,
            DataChangedEventHandlers *eventHandlers
        );
        virtual void NotifyChangedData() = 0;
        virtual EnumScreenType GetNextScreenWhenYesSelected() const;

    protected:
        TC2004::Lcd *m_Lcd;
        EnumQuestionSelection m_QuestionSelection;
        DataChangedEventHandlers *m_DataChangedEventHandlers;

    private:
    };
} // namespace Incubator

#endif // INCUBATOR_AQUESTIONSCREEN_H