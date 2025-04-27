#ifndef INCUBATOR_TIME_TIMEUTILS_H
#define INCUBATOR_TIME_TIMEUTILS_H
#include <cinttypes>
namespace Incubator
{
    namespace Time
    {
        class TimeUtils
        {
        public:
            static uint64_t GetStartTimestampInMillisecond();
            static uint32_t GetIncubatorTimestampInSecond();
            static void SetIncubatorTimestampInSecond(const uint32_t timestampInSecond);

        private:
            static uint32_t s_IncubatorTimeStampInSecond;
        };
    } // namespace Time
    
} // namespace Incubator

#endif // INCUBATOR_TIME_TIMEUTILS_H