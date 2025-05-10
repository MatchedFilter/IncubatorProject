#ifndef INCUBATOR_ADATASETSCREEN_H
#define INCUBATOR_ADATASETSCREEN_H
#include "TC2004/Lcd.h"
#include "Incubator/View/Screen/AScreen.h"
#include "Incubator/Time/TimerTask.h"
#include "Incubator/IncubatorData/IncubatorInformationData.h"
#include "Incubator/IncubatorData/PidData.h"
#include "Incubator/IncubatorData/TimeInformationData.h"
#include "Incubator/View/DataChangedEventHandler/DataChangedEventHandlers.h"
#include "Incubator/View/Screen/EnumScreenType.h"
#include "Incubator/View/Screen/QuestionScreen/EnumQuestionSelection.h"

namespace Incubator
{
    class ADataSetScreen : public AScreen
    {
    public:
        ADataSetScreen(const EnumScreenType screenType);
        ~ADataSetScreen();
        void Initialize(TC2004::Lcd *tc2004Lcd,
            DataChangedEventHandlers * const eventHandlers,
            const IncubatorInformationData *const currentIncubatorInformationData,
            IncubatorInformationData *const changedIncubatorInformationData);

        void OnInitial() final override;
        virtual void Reset() final override;
        virtual void Run() final override;
        void OnUserAction(const JoystickEvent &event) final override;


    protected:
        virtual void PrintCurrentData() const = 0;
        virtual void PrintNewData() const = 0;
        virtual void OnIncrementHighEvent() = 0;
        virtual void OnIncrementLowEvent() = 0;
        virtual void OnDecrementHighEvent() = 0;
        virtual void OnDecrementLowEvent() = 0;
        virtual void NotifyChangedData() = 0;
        virtual EnumScreenType GetNextScreenForNoSelection() const = 0;

    protected:
        TC2004::Lcd *m_Lcd;
        const IncubatorInformationData * m_CurrentIncubatorInformationData;
        IncubatorInformationData * m_ChangedIncubatorInformationData;
        DataChangedEventHandlers *m_DataChangedEventHandlers;

    private:
        EnumQuestionSelection m_QuestionSelection;
        bool m_bIsInSaveState;


    private:
        void OnSaveStateEnter();
        void HandleForSaveState(const JoystickEvent &event);
        void HandleForSetState(const JoystickEvent &event);
    };
} // namespace Incubator

#endif // INCUBATOR_ADATASETSCREEN_H