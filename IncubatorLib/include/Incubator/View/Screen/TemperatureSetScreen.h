#ifndef INCUBATOR_TEMPERATURESETSCREEN_H
#define INCUBATOR_TEMPERATURESETSCREEN_H
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
    class TemperatureSetScreen : public AScreen
    {
    public:
        TemperatureSetScreen(DataChangedEventHandlers &eventHandlers,
            SettingsData &changedSettingsData,
            const SettingsData &currentSettingsData,
            bool bIsForLastDays);
        ~TemperatureSetScreen();
        void Initialize(TC2004::Lcd *tc2004Lcd);
        void OnInitial() override;

        virtual void Reset() override;
        virtual void Run() override;
        void OnUserAction(const JoystickEvent &event) override;

    private:
        TC2004::Lcd *m_Lcd;
        DataChangedEventHandlers &m_DataChangedEventHandlers;
        EnumQuestionSelection m_QuestionSelection;
        SettingsData &m_ChangedSettingsData;
        const SettingsData &m_CurrentSettingsData;
        const bool m_bIsForLastDays;
        bool m_bIsInSaveState;

    private:
        static TC2004::String80 GetTemperatureString(const uint32_t temperatureInMillicelcius);
        void OnSaveStateEnter();
        void HandleForSaveState(const JoystickEvent &event);
        void HandleForSetState(const JoystickEvent &event);
    };
} // namespace Incubator

#endif // INCUBATOR_TEMPERATURESETSCREEN_H