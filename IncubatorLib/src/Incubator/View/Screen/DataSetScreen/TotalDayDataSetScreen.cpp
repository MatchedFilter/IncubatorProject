#include "Incubator/View/Screen/DataSetScreen/TotalDayDataSetScreen.h"
#include "TC2004/String80.h"
#include <cassert>

namespace Incubator
{

    void TotalDayDataSetScreen::SetSecondFromDayCount(const uint8_t &dayCount)
    {
        m_ChangedIncubatorInformationData->m_SettingsData.m_TotalIncubationDayCount = dayCount;
    }

    TotalDayDataSetScreen::TotalDayDataSetScreen() :
        ADataSetScreen( SCREEN_TYPE_DATA_SET_TOTAL_DAY_COUNT )
    {
    }

    TotalDayDataSetScreen::~TotalDayDataSetScreen()
    {
    }

    void TotalDayDataSetScreen::PrintCurrentData() const
    {
        const uint8_t currentTotalDayCount = m_CurrentIncubatorInformationData->m_SettingsData.m_TotalIncubationDayCount;
        TC2004::String80 currentTotalDayCountString;
        currentTotalDayCountString.Clear();
        currentTotalDayCountString += static_cast<int32_t>(currentTotalDayCount);
        m_Lcd->Print(currentTotalDayCountString);
        m_Lcd->Print(TC2004::String80(" G"));
        m_Lcd->Print(TC2004::TC2004_CHAR_LOWER_U);
        m_Lcd->Print(TC2004::String80("n  "));
    }

    void TotalDayDataSetScreen::PrintNewData() const
    {
        const uint8_t totalDayCount = m_ChangedIncubatorInformationData->m_SettingsData.m_TotalIncubationDayCount;
        TC2004::String80 changedTotalDayCountString;
        changedTotalDayCountString.Clear();
        changedTotalDayCountString += static_cast<int32_t>(totalDayCount);
        m_Lcd->Print(changedTotalDayCountString);
        m_Lcd->Print(TC2004::String80(" G"));
        m_Lcd->Print(TC2004::TC2004_CHAR_LOWER_U);
        m_Lcd->Print(TC2004::String80("n  "));
    }

    void TotalDayDataSetScreen::OnIncrementHighEvent()
    {
        const uint8_t nextTotalDayCount = m_ChangedIncubatorInformationData->m_SettingsData.m_TotalIncubationDayCount + HIGH_INCREMENT_COUNT;
        uint8_t resultTotalDayCount = MAX_ALLOWED_DAY_COUNT;
        if (nextTotalDayCount < MAX_ALLOWED_DAY_COUNT)
        {
            resultTotalDayCount = nextTotalDayCount;
        }
        SetSecondFromDayCount(resultTotalDayCount);
    }

    void TotalDayDataSetScreen::OnIncrementLowEvent()
    {
        const uint8_t nextTotalDayCount = m_ChangedIncubatorInformationData->m_SettingsData.m_TotalIncubationDayCount + LOW_INCREMENT_COUNT;
        uint8_t resultTotalDayCount = MAX_ALLOWED_DAY_COUNT;
        if (nextTotalDayCount < MAX_ALLOWED_DAY_COUNT)
        {
            resultTotalDayCount = nextTotalDayCount;
        }
        SetSecondFromDayCount(resultTotalDayCount);
    }

    void TotalDayDataSetScreen::OnDecrementHighEvent()
    {
        const uint8_t changedTotalDayCount = m_ChangedIncubatorInformationData->m_SettingsData.m_TotalIncubationDayCount;
        uint8_t resultTotalDayCount = MIN_ALLOWED_DAY_COUNT;
        if (changedTotalDayCount > HIGH_INCREMENT_COUNT)
        {
            const uint8_t nextTotalDayCount = changedTotalDayCount - HIGH_INCREMENT_COUNT;
            if (nextTotalDayCount > MIN_ALLOWED_DAY_COUNT)
            {
                resultTotalDayCount = nextTotalDayCount;
            }
        }
        SetSecondFromDayCount(resultTotalDayCount);
    }

    void TotalDayDataSetScreen::OnDecrementLowEvent()
    {
        const uint8_t changedTotalDayCount = m_ChangedIncubatorInformationData->m_SettingsData.m_TotalIncubationDayCount;;
        uint8_t resultTotalDayCount = MIN_ALLOWED_DAY_COUNT;
        if (changedTotalDayCount > LOW_INCREMENT_COUNT)
        {
            const uint8_t nextTotalDayCount = changedTotalDayCount - LOW_INCREMENT_COUNT;
            if (nextTotalDayCount > MIN_ALLOWED_DAY_COUNT)
            {
                resultTotalDayCount = nextTotalDayCount;
            }
        }
        SetSecondFromDayCount(resultTotalDayCount);
    }

    void TotalDayDataSetScreen::NotifyChangedData()
    {
        m_DataChangedEventHandlers->m_SettingsDataChangedEventHandler->OnUpdate(m_ChangedIncubatorInformationData->m_SettingsData);
    }

    EnumScreenType TotalDayDataSetScreen::GetNextScreenForNoSelection() const
    {
        return SCREEN_TYPE_INCUBATOR_TIME_SETTINGS;
    }

} // namespace Incubator
