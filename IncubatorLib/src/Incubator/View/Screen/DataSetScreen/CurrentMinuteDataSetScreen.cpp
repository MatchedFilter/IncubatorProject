#include "Incubator/View/Screen/DataSetScreen/CurrentMinuteDataSetScreen.h"
#include "TC2004/String80.h"
#include "DateUtils.h"
#include <cassert>

namespace Incubator
{

    void CurrentMinuteDataSetScreen::SetSecondFromMinute(const uint8_t &minute)
    {
        const uint8_t day = DateUtils::GetDayFromTimestamp(m_CurrentIncubatorInformationData->m_TimeInformationData.m_CurrentTimestampInSecond);
        const uint8_t hour = DateUtils::GetHourFromTimestamp(m_CurrentIncubatorInformationData->m_TimeInformationData.m_CurrentTimestampInSecond);
        const uint8_t second = DateUtils::GetSecondFromTimestamp(m_CurrentIncubatorInformationData->m_TimeInformationData.m_CurrentTimestampInSecond);
        m_ChangedIncubatorInformationData->m_TimeInformationData.m_CurrentTimestampInSecond = DateUtils::GetTimestapmInSecondFromDate(day, hour, minute, second);
    }

    CurrentMinuteDataSetScreen::CurrentMinuteDataSetScreen() :
        ADataSetScreen( SCREEN_TYPE_DATA_SET_CURRENT_MINUTE )
    {
    }

    CurrentMinuteDataSetScreen::~CurrentMinuteDataSetScreen()
    {
    }


    void CurrentMinuteDataSetScreen::PrintCurrentData() const
    {
        const uint8_t currentMinute = DateUtils::GetMinuteFromTimestamp(m_CurrentIncubatorInformationData->m_TimeInformationData.m_CurrentTimestampInSecond);
        TC2004::String80 currentMinuteString;
        currentMinuteString.Clear();
        currentMinuteString += static_cast<int32_t>(currentMinute);
        m_Lcd->Print(currentMinuteString);
        m_Lcd->Print(TC2004::String80(". Dakika  "));
    }

    void CurrentMinuteDataSetScreen::PrintNewData() const
    {
        const uint8_t currentMinute = DateUtils::GetMinuteFromTimestamp(m_ChangedIncubatorInformationData->m_TimeInformationData.m_CurrentTimestampInSecond);
        TC2004::String80 currentMinuteString;
        currentMinuteString.Clear();
        currentMinuteString += static_cast<int32_t>(currentMinute);
        m_Lcd->Print(currentMinuteString);
        m_Lcd->Print(TC2004::String80(". Dakika  "));
    }

    void CurrentMinuteDataSetScreen::OnIncrementHighEvent()
    {
        const uint8_t nextMinute = DateUtils::GetMinuteFromTimestamp(m_ChangedIncubatorInformationData->m_TimeInformationData.m_CurrentTimestampInSecond) + HIGH_INCREMENT_COUNT;
        uint8_t resultMinute = MAX_ALLOWED_MINUTE_COUNT;
        if (nextMinute < MAX_ALLOWED_MINUTE_COUNT)
        {
            resultMinute = nextMinute;
        }
        SetSecondFromMinute(resultMinute);
    }

    void CurrentMinuteDataSetScreen::OnIncrementLowEvent()
    {
        const uint8_t nextMinute = DateUtils::GetMinuteFromTimestamp(m_ChangedIncubatorInformationData->m_TimeInformationData.m_CurrentTimestampInSecond) + LOW_INCREMENT_COUNT;
        uint8_t resultMinute = MAX_ALLOWED_MINUTE_COUNT;
        if (nextMinute < MAX_ALLOWED_MINUTE_COUNT)
        {
            resultMinute = nextMinute;
        }
        SetSecondFromMinute(resultMinute);
    }

    void CurrentMinuteDataSetScreen::OnDecrementHighEvent()
    {
        const uint8_t changedMinute = DateUtils::GetMinuteFromTimestamp(m_ChangedIncubatorInformationData->m_TimeInformationData.m_CurrentTimestampInSecond);
        uint8_t resultMinute = MIN_ALLOWED_MINUTE_COUNT;
        if (changedMinute > HIGH_INCREMENT_COUNT)
        {
            const uint32_t nextMinute = changedMinute - HIGH_INCREMENT_COUNT;
            if (nextMinute > MIN_ALLOWED_MINUTE_COUNT)
            {
                resultMinute = nextMinute;
            }
        }
        SetSecondFromMinute(resultMinute);
    }

    void CurrentMinuteDataSetScreen::OnDecrementLowEvent()
    {
        const uint8_t changedMinute = DateUtils::GetMinuteFromTimestamp(m_ChangedIncubatorInformationData->m_TimeInformationData.m_CurrentTimestampInSecond);
        uint8_t resultMinute = MIN_ALLOWED_MINUTE_COUNT;
        if (changedMinute > LOW_INCREMENT_COUNT)
        {
            const uint8_t nextMinute = changedMinute - LOW_INCREMENT_COUNT;
            if (nextMinute > MIN_ALLOWED_MINUTE_COUNT)
            {
                resultMinute = nextMinute;
            }
        }
        SetSecondFromMinute(resultMinute);
    }

    void CurrentMinuteDataSetScreen::NotifyChangedData()
    {
        m_DataChangedEventHandlers->m_TimeInformationDataChangedEventHandler->OnUpdate(m_ChangedIncubatorInformationData->m_TimeInformationData);
    }

    EnumScreenType CurrentMinuteDataSetScreen::GetNextScreenForNoSelection() const
    {
        return SCREEN_TYPE_CURRENT_TIME_SETTINGS;
    }

} // namespace Incubator
