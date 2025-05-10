#include "Incubator/View/Screen/DataSetScreen/CurrentHourDataSetScreen.h"
#include "TC2004/String80.h"
#include "DateUtils.h"
#include <cassert>

namespace Incubator
{

    void CurrentHourDataSetScreen::SetSecondFromHour(const uint8_t &hour)
    {
        const uint8_t day = DateUtils::GetDayFromTimestamp(m_CurrentIncubatorInformationData->m_TimeInformationData.m_CurrentTimestampInSecond);
        const uint8_t minute = DateUtils::GetMinuteFromTimestamp(m_CurrentIncubatorInformationData->m_TimeInformationData.m_CurrentTimestampInSecond);
        const uint8_t second = DateUtils::GetSecondFromTimestamp(m_CurrentIncubatorInformationData->m_TimeInformationData.m_CurrentTimestampInSecond);
        m_ChangedIncubatorInformationData->m_TimeInformationData.m_CurrentTimestampInSecond = DateUtils::GetTimestapmInSecondFromDate(day, hour, minute, second);
    }

    CurrentHourDataSetScreen::CurrentHourDataSetScreen() :
        ADataSetScreen( SCREEN_TYPE_DATA_SET_CURRENT_DAY )
    {
    }

    CurrentHourDataSetScreen::~CurrentHourDataSetScreen()
    {
    }


    void CurrentHourDataSetScreen::PrintCurrentData() const
    {
        const uint8_t currentHour = DateUtils::GetHourFromTimestamp(m_CurrentIncubatorInformationData->m_TimeInformationData.m_CurrentTimestampInSecond);
        TC2004::String80 currentHourString;
        currentHourString.Clear();
        currentHourString += static_cast<int32_t>(currentHour);
        m_Lcd->Print(currentHourString);
        m_Lcd->Print(TC2004::String80(". Saat  "));
    }

    void CurrentHourDataSetScreen::PrintNewData() const
    {
        const uint8_t currentHour = DateUtils::GetHourFromTimestamp(m_ChangedIncubatorInformationData->m_TimeInformationData.m_CurrentTimestampInSecond);
        TC2004::String80 currentHourString;
        currentHourString.Clear();
        currentHourString += static_cast<int32_t>(currentHour);
        m_Lcd->Print(currentHourString);
        m_Lcd->Print(TC2004::String80(". Saat  "));
    }

    void CurrentHourDataSetScreen::OnIncrementHighEvent()
    {
        const uint8_t nextHour = DateUtils::GetHourFromTimestamp(m_ChangedIncubatorInformationData->m_TimeInformationData.m_CurrentTimestampInSecond) + HIGH_INCREMENT_COUNT;
        uint8_t resultHour = MAX_ALLOWED_HOUR_COUNT;
        if (nextHour < MAX_ALLOWED_HOUR_COUNT)
        {
            resultHour = nextHour;
        }
        SetSecondFromHour(resultHour);
    }

    void CurrentHourDataSetScreen::OnIncrementLowEvent()
    {
        const uint8_t nextHour = DateUtils::GetHourFromTimestamp(m_ChangedIncubatorInformationData->m_TimeInformationData.m_CurrentTimestampInSecond) + LOW_INCREMENT_COUNT;
        uint8_t resultHour = MAX_ALLOWED_HOUR_COUNT;
        if (nextHour < MAX_ALLOWED_HOUR_COUNT)
        {
            resultHour = nextHour;
        }
        SetSecondFromHour(resultHour);
    }

    void CurrentHourDataSetScreen::OnDecrementHighEvent()
    {
        const uint8_t changedHour = DateUtils::GetHourFromTimestamp(m_ChangedIncubatorInformationData->m_TimeInformationData.m_CurrentTimestampInSecond);
        uint8_t resultHour = MIN_ALLOWED_HOUR_COUNT;
        if (changedHour > HIGH_INCREMENT_COUNT)
        {
            const uint32_t nextHour = changedHour - HIGH_INCREMENT_COUNT;
            if (nextHour > MIN_ALLOWED_HOUR_COUNT)
            {
                resultHour = nextHour;
            }
        }
        SetSecondFromHour(resultHour);
    }

    void CurrentHourDataSetScreen::OnDecrementLowEvent()
    {
        const uint8_t changedHour = DateUtils::GetHourFromTimestamp(m_ChangedIncubatorInformationData->m_TimeInformationData.m_CurrentTimestampInSecond);
        uint8_t resultHour = MIN_ALLOWED_HOUR_COUNT;
        if (changedHour > LOW_INCREMENT_COUNT)
        {
            const uint8_t nextHour = changedHour - LOW_INCREMENT_COUNT;
            if (nextHour > MIN_ALLOWED_HOUR_COUNT)
            {
                resultHour = nextHour;
            }
        }
        SetSecondFromHour(resultHour);
    }

    void CurrentHourDataSetScreen::NotifyChangedData()
    {
        m_DataChangedEventHandlers->m_TimeInformationDataChangedEventHandler->OnUpdate(m_ChangedIncubatorInformationData->m_TimeInformationData);
    }

    EnumScreenType CurrentHourDataSetScreen::GetNextScreenForNoSelection() const
    {
        return SCREEN_TYPE_CURRENT_TIME_SETTINGS;
    }

} // namespace Incubator
