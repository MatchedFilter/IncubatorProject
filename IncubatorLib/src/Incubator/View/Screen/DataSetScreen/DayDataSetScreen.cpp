#include "Incubator/View/Screen/DataSetScreen/DayDataSetScreen.h"
#include "TC2004/String80.h"
#include <cassert>

namespace Incubator
{


    uint8_t DayDataSetScreen::GetDayFromSecond(const uint32_t &second)
    {
        return static_cast<uint8_t>(((second / static_cast<uint32_t>(60UL) )/ static_cast<uint32_t>(60UL)) / static_cast<uint32_t>(24UL));
    }

    void DayDataSetScreen::SetSecondFromDayCount(const uint8_t &dayCount)
    {
        const uint32_t dayDurationInSecond = static_cast<uint32_t>(dayCount) * static_cast<uint32_t>(60UL) * static_cast<uint32_t>(60UL) * static_cast<uint32_t>(24UL);
        const uint32_t remainderSeconds = m_CurrentIncubatorInformationData->m_TimeInformationData.m_CurrentTimestampInSecond % (static_cast<uint32_t>(24UL) * static_cast<uint32_t>(60UL) * static_cast<uint32_t>(60UL));
        m_ChangedIncubatorInformationData->m_TimeInformationData.m_CurrentTimestampInSecond = (dayDurationInSecond + remainderSeconds);
    }


    DayDataSetScreen::DayDataSetScreen() :
        ADataSetScreen( SCREEN_TYPE_DATA_SET_CURRENT_DAY )
    {
    }

    DayDataSetScreen::~DayDataSetScreen()
    {
    }


    void DayDataSetScreen::PrintCurrentData() const
    {
        const uint8_t currentDay = GetDayFromSecond(m_CurrentIncubatorInformationData->m_TimeInformationData.m_CurrentTimestampInSecond);
        TC2004::String80 currentDayString;
        currentDayString.Clear();
        currentDayString += static_cast<int32_t>(currentDay);
        m_Lcd->Print(currentDayString);
        m_Lcd->Print(TC2004::String80(". G"));
        m_Lcd->Print(TC2004::TC2004_CHAR_LOWER_U);
        m_Lcd->Print(TC2004::String80("n  "));
    }

    void DayDataSetScreen::PrintNewData() const
    {
        const uint8_t currentDay = GetDayFromSecond(m_ChangedIncubatorInformationData->m_TimeInformationData.m_CurrentTimestampInSecond);
        TC2004::String80 currentDayString;
        currentDayString.Clear();
        currentDayString += static_cast<int32_t>(currentDay);
        m_Lcd->Print(currentDayString);
        m_Lcd->Print(TC2004::String80(". G"));
        m_Lcd->Print(TC2004::TC2004_CHAR_LOWER_U);
        m_Lcd->Print(TC2004::String80("n  "));
    }

    void DayDataSetScreen::OnIncrementHighEvent()
    {
        const uint8_t nextDayCount = GetDayFromSecond(m_ChangedIncubatorInformationData->m_TimeInformationData.m_CurrentTimestampInSecond) + HIGH_INCREMENT_COUNT;
        uint8_t maxAllowedDayCount = 0U;
        if (m_CurrentIncubatorInformationData->m_SettingsData.m_TotalIncubationDayCount > 0U)
        {
            maxAllowedDayCount = m_CurrentIncubatorInformationData->m_SettingsData.m_TotalIncubationDayCount - 1U;
        }
        uint8_t resultDayCount = maxAllowedDayCount;
        if (nextDayCount < maxAllowedDayCount)
        {
            resultDayCount = nextDayCount;
        }
        SetSecondFromDayCount(resultDayCount);
    }

    void DayDataSetScreen::OnIncrementLowEvent()
    {
        const uint8_t nextDayCount = GetDayFromSecond(m_ChangedIncubatorInformationData->m_TimeInformationData.m_CurrentTimestampInSecond) + LOW_INCREMENT_COUNT;
        uint8_t maxAllowedDayCount = 0U;
        if (m_CurrentIncubatorInformationData->m_SettingsData.m_TotalIncubationDayCount > 0U)
        {
            maxAllowedDayCount = m_CurrentIncubatorInformationData->m_SettingsData.m_TotalIncubationDayCount - 1U;
        }
        uint8_t resultDayCount = maxAllowedDayCount;
        if (nextDayCount < maxAllowedDayCount)
        {
            resultDayCount = nextDayCount;
        }
        SetSecondFromDayCount(resultDayCount);
    }

    void DayDataSetScreen::OnDecrementHighEvent()
    {
        const uint32_t changedDayCount = GetDayFromSecond(m_ChangedIncubatorInformationData->m_TimeInformationData.m_CurrentTimestampInSecond);
        uint32_t resultDayCount = MIN_ALLOWED_DAY_COUNT;
        if (changedDayCount > HIGH_INCREMENT_COUNT)
        {
            const uint32_t nextDayCount = changedDayCount - HIGH_INCREMENT_COUNT;
            if (nextDayCount > MIN_ALLOWED_DAY_COUNT)
            {
                resultDayCount = nextDayCount;
            }
        }
        SetSecondFromDayCount(resultDayCount);
    }

    void DayDataSetScreen::OnDecrementLowEvent()
    {
        const uint32_t changedDayCount = GetDayFromSecond(m_ChangedIncubatorInformationData->m_TimeInformationData.m_CurrentTimestampInSecond);
        uint32_t resultDayCount = MIN_ALLOWED_DAY_COUNT;
        if (changedDayCount > LOW_INCREMENT_COUNT)
        {
            const uint32_t nextDayCount = changedDayCount - LOW_INCREMENT_COUNT;
            if (nextDayCount > MIN_ALLOWED_DAY_COUNT)
            {
                resultDayCount = nextDayCount;
            }
        }
        SetSecondFromDayCount(resultDayCount);
    }

    void DayDataSetScreen::NotifyChangedData()
    {
        m_DataChangedEventHandlers->m_TimeInformationDataChangedEventHandler->OnUpdate(m_ChangedIncubatorInformationData->m_TimeInformationData);
    }

    EnumScreenType DayDataSetScreen::GetNextScreenForNoSelection() const
    {
        return SCREEN_TYPE_CURRENT_TIME_SETTINGS;
    }

} // namespace Incubator
