#ifndef INCUBATOR_QUESTIONSCREEN_H
#define INCUBATOR_QUESTIONSCREEN_H
#include "TC2004/Lcd.h"
#include "AScreen.h"
#include "Incubator/Time/TimerTask.h"
#include "Incubator/IncubatorData/SettingsData.h"
#include "Incubator/IncubatorData/TimeInformationData.h"
namespace Incubator
{

    enum EnumQuestionSelection : uint8_t
    {
        QUESTION_SELECTION_NO,
        QUESTION_SELECTION_YES
    };

    class QuestionScreen : public AScreen
    {
    public:
        QuestionScreen();
        ~QuestionScreen();
        void Initialize(TC2004::Lcd *tc2004Lcd);
        void OnInitial();
        inline EnumQuestionSelection GetQuestionSelection() { return m_QuestionSelection; }
        void Reset();

        virtual void Run() override;

        void OnUserAction(const JoystickEvent &event) override;

    private:
        TC2004::Lcd *m_Lcd;
        EnumQuestionSelection m_QuestionSelection;

    };
} // namespace Incubator

#endif // INCUBATOR_QUESTIONSCREEN_H