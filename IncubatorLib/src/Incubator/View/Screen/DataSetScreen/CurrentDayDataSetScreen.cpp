#include "Incubator/View/Screen/DataSetScreen/CurrentDayDataSetScreen.h"
#include "TC2004/String80.h"
#include <cassert>
#include "DateUtils.h"

namespace Incubator
{

    void CurrentDayDataSetScreen::SetSecondFromDayCount(const uint8_t &dayCount)
    {
        const uint8_t hour = DateUtils::GetHourFromTimestamp(m_CurrentIncubatorInformationData->m_TimeInformationData.m_CurrentTimestampInSecond);
        const uint8_t minute = DateUtils::GetMinuteFromTimestamp(m_CurrentIncubatorInformationData->m_TimeInformationData.m_CurrentTimestampInSecond);
        const uint8_t second = DateUtils::GetSecondFromTimestamp(m_CurrentIncubatorInformationData->m_TimeInformationData.m_CurrentTimestampInSecond);
        m_ChangedIncubatorInformationData->m_TimeInformationData.m_CurrentTimestampInSecond = DateUtils::GetTimestapmInSecondFromDate(dayCount, hour, minute, second);
    }


    CurrentDayDataSetScreen::CurrentDayDataSetScreen() :
        ADataSetScreen( SCREEN_TYPE_DATA_SET_CURRENT_MINUTE )
    {
    }

    CurrentDayDataSetScreen::~CurrentDayDataSetScreen()
    {
    }


    void CurrentDayDataSetScreen::PrintCurrentData() const
    {
        const uint8_t currentDay = DateUtils::GetDayFromTimestamp(m_CurrentIncubatorInformationData->m_TimeInformationData.m_CurrentTimestampInSecond);
        TC2004::String80 currentDayString;
        currentDayString.Clear();
        currentDayString += static_cast<int32_t>(currentDay);
        m_Lcd->Print(currentDayString);
        m_Lcd->Print(TC2004::String80(". G"));
        m_Lcd->Print(TC2004::TC2004_CHAR_LOWER_U);
        m_Lcd->Print(TC2004::String80("n  "));
    }

    void CurrentDayDataSetScreen::PrintNewData() const
    {
        const uint8_t currentDay = DateUtils::GetDayFromTimestamp(m_ChangedIncubatorInformationData->m_TimeInformationData.m_CurrentTimestampInSecond);
        TC2004::String80 currentDayString;
        currentDayString.Clear();
        currentDayString += static_cast<int32_t>(currentDay);
        m_Lcd->Print(currentDayString);
        m_Lcd->Print(TC2004::String80(". G"));
        m_Lcd->Print(TC2004::TC2004_CHAR_LOWER_U);
        m_Lcd->Print(TC2004::String80("n  "));
    }

    void CurrentDayDataSetScreen::OnIncrementHighEvent()
    {
        const uint8_t nextDayCount = DateUtils::GetDayFromTimestamp(m_ChangedIncubatorInformationData->m_TimeInformationData.m_CurrentTimestampInSecond) + HIGH_INCREMENT_COUNT;
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

    void CurrentDayDataSetScreen::OnIncrementLowEvent()
    {
        const uint8_t nextDayCount = DateUtils::GetDayFromTimestamp(m_ChangedIncubatorInformationData->m_TimeInformationData.m_CurrentTimestampInSecond) + LOW_INCREMENT_COUNT;
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

    void CurrentDayDataSetScreen::OnDecrementHighEvent()
    {
        const uint8_t changedDayCount = DateUtils::GetDayFromTimestamp(m_ChangedIncubatorInformationData->m_TimeInformationData.m_CurrentTimestampInSecond);
        uint8_t resultDayCount = MIN_ALLOWED_DAY_COUNT;
        if (changedDayCount > HIGH_INCREMENT_COUNT)
        {
            const uint8_t nextDayCount = changedDayCount - HIGH_INCREMENT_COUNT;
            if (nextDayCount > MIN_ALLOWED_DAY_COUNT)
            {
                resultDayCount = nextDayCount;
            }
        }
        SetSecondFromDayCount(resultDayCount);
    }

    void CurrentDayDataSetScreen::OnDecrementLowEvent()
    {
        const uint8_t changedDayCount = DateUtils::GetDayFromTimestamp(m_ChangedIncubatorInformationData->m_TimeInformationData.m_CurrentTimestampInSecond);
        uint8_t resultDayCount = MIN_ALLOWED_DAY_COUNT;
        if (changedDayCount > LOW_INCREMENT_COUNT)
        {
            const uint8_t nextDayCount = changedDayCount - LOW_INCREMENT_COUNT;
            if (nextDayCount > MIN_ALLOWED_DAY_COUNT)
            {
                resultDayCount = nextDayCount;
            }
        }
        SetSecondFromDayCount(resultDayCount);
    }

    void CurrentDayDataSetScreen::NotifyChangedData()
    {
        m_DataChangedEventHandlers->m_TimeInformationDataChangedEventHandler->OnUpdate(m_ChangedIncubatorInformationData->m_TimeInformationData);
    }

    EnumScreenType CurrentDayDataSetScreen::GetNextScreenForNoSelection() const
    {
        return SCREEN_TYPE_CURRENT_TIME_SETTINGS;
    }

} // namespace Incubator
