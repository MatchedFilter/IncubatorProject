#include "Incubator/Time/TimeUtils.h"

namespace Incubator
{
    uint64_t GetTimestampInMillisecond();
    
    namespace Time
    {
        uint32_t TimeUtils::s_IncubatorTimeStampInSecond = static_cast<uint32_t>(0UL);
        static uint64_t s_IncubatorTimestampOffsetInMillisecond = static_cast<uint32_t>(0UL);

        uint64_t TimeUtils::GetStartTimestampInMillisecond()
        {
            return GetTimestampInMillisecond();
        }

        uint32_t TimeUtils::GetIncubatorTimestampInSecond()
        {
            const uint32_t result = s_IncubatorTimeStampInSecond + static_cast<uint32_t>(GetTimestampInMillisecond() -  s_IncubatorTimestampOffsetInMillisecond) / static_cast<uint32_t>(1000UL);
            return result;
        }

        void TimeUtils::SetIncubatorTimestampInSecond(const uint32_t timestampInSecond)
        {
            s_IncubatorTimeStampInSecond = timestampInSecond;
            s_IncubatorTimestampOffsetInMillisecond = GetTimestampInMillisecond();
        }


    } // namespace Time
    
} // namespace Incubator
