#include "Incubator/View/Screen/DataSetScreen/LastDayDataSetScreen.h"
#include "TC2004/String80.h"
#include <cassert>

namespace Incubator
{

    void LastDayDataSetScreen::SetSecondFromDayCount(const uint8_t &dayCount)
    {
        m_ChangedIncubatorInformationData->m_SettingsData.m_LastDaysCount = dayCount;
    }

    LastDayDataSetScreen::LastDayDataSetScreen() :
        ADataSetScreen( SCREEN_TYPE_DATA_SET_LAST_DAY_COUNT )
    {
    }

    LastDayDataSetScreen::~LastDayDataSetScreen()
    {
    }

    void LastDayDataSetScreen::PrintCurrentData() const
    {
        const uint8_t currentLastDayCount = m_CurrentIncubatorInformationData->m_SettingsData.m_LastDaysCount;
        TC2004::String80 currentLastDayCountString;
        currentLastDayCountString.Clear();
        currentLastDayCountString += static_cast<int32_t>(currentLastDayCount);
        m_Lcd->Print(currentLastDayCountString);
        m_Lcd->Print(TC2004::String80(" G"));
        m_Lcd->Print(TC2004::TC2004_CHAR_LOWER_U);
        m_Lcd->Print(TC2004::String80("n  "));
    }

    void LastDayDataSetScreen::PrintNewData() const
    {
        const uint8_t lastDayCount = m_ChangedIncubatorInformationData->m_SettingsData.m_LastDaysCount;
        TC2004::String80 changedLastDayCountString;
        changedLastDayCountString.Clear();
        changedLastDayCountString += static_cast<int32_t>(lastDayCount);
        m_Lcd->Print(changedLastDayCountString);
        m_Lcd->Print(TC2004::String80(" G"));
        m_Lcd->Print(TC2004::TC2004_CHAR_LOWER_U);
        m_Lcd->Print(TC2004::String80("n  "));
    }

    void LastDayDataSetScreen::OnIncrementHighEvent()
    {
        const uint8_t nextLastDayCount = m_ChangedIncubatorInformationData->m_SettingsData.m_LastDaysCount + HIGH_INCREMENT_COUNT;
        uint8_t maxAllowedDayCount = m_CurrentIncubatorInformationData->m_SettingsData.m_TotalIncubationDayCount;
        uint8_t resultLastDayCount = 0U;
        if (maxAllowedDayCount > 0U)
        {
            resultLastDayCount = maxAllowedDayCount - 1U;
            if (nextLastDayCount < maxAllowedDayCount)
            {
                resultLastDayCount = nextLastDayCount;
            }
        }

        SetSecondFromDayCount(resultLastDayCount);
    }

    void LastDayDataSetScreen::OnIncrementLowEvent()
    {
        const uint8_t nextLastDayCount = m_ChangedIncubatorInformationData->m_SettingsData.m_LastDaysCount + LOW_INCREMENT_COUNT;
        uint8_t maxAllowedDayCount = m_CurrentIncubatorInformationData->m_SettingsData.m_TotalIncubationDayCount;
        uint8_t resultLastDayCount = 0U;
        if (maxAllowedDayCount > 0U)
        {
            resultLastDayCount = maxAllowedDayCount - 1U;
            if (nextLastDayCount < maxAllowedDayCount)
            {
                resultLastDayCount = nextLastDayCount;
            }
        }

        SetSecondFromDayCount(resultLastDayCount);
    }

    void LastDayDataSetScreen::OnDecrementHighEvent()
    {
        const uint8_t changedLastDayCount = m_ChangedIncubatorInformationData->m_SettingsData.m_LastDaysCount;
        uint8_t resultLastDayCount = MIN_ALLOWED_DAY_COUNT;
        if (changedLastDayCount > HIGH_INCREMENT_COUNT)
        {
            const uint8_t nextLastDayCount = changedLastDayCount - HIGH_INCREMENT_COUNT;
            if (nextLastDayCount > MIN_ALLOWED_DAY_COUNT)
            {
                resultLastDayCount = nextLastDayCount;
            }
        }
        SetSecondFromDayCount(resultLastDayCount);
    }

    void LastDayDataSetScreen::OnDecrementLowEvent()
    {
        const uint8_t changedLastDayCount = m_ChangedIncubatorInformationData->m_SettingsData.m_LastDaysCount;;
        uint8_t resultLastDayCount = MIN_ALLOWED_DAY_COUNT;
        if (changedLastDayCount > LOW_INCREMENT_COUNT)
        {
            const uint8_t nextLastDayCount = changedLastDayCount - LOW_INCREMENT_COUNT;
            if (nextLastDayCount > MIN_ALLOWED_DAY_COUNT)
            {
                resultLastDayCount = nextLastDayCount;
            }
        }
        SetSecondFromDayCount(resultLastDayCount);
    }

    void LastDayDataSetScreen::NotifyChangedData()
    {
        m_DataChangedEventHandlers->m_SettingsDataChangedEventHandler->OnUpdate(m_ChangedIncubatorInformationData->m_SettingsData);
    }

    EnumScreenType LastDayDataSetScreen::GetNextScreenForNoSelection() const
    {
        return SCREEN_TYPE_INCUBATOR_TIME_SETTINGS;
    }

} // namespace Incubator
