#ifndef INCUBATOR_AdministratorResetQuestionScreen_H
#define INCUBATOR_AdministratorResetQuestionScreen_H
#include "AQuestionScreen.h"
#include "Incubator/IncubatorData/PidData.h"
namespace Incubator
{
    class AdministratorResetQuestionScreen : public AQuestionScreen
    {
    public:
        AdministratorResetQuestionScreen();
        ~AdministratorResetQuestionScreen();

        void OnInitial();
        
        void Initialize(TC2004::Lcd *tc2004Lcd,
            DataChangedEventHandlers *eventHandlers,
            PidData *changedPidData);

    protected:
        virtual void NotifyChangedData() override;
        virtual EnumScreenType GetNextScreenWhenYesSelected() const;

    private:
    PidData *m_PidData;
    };
} // namespace Incubator

#endif // INCUBATOR_AdministratorResetQuestionScreen_H