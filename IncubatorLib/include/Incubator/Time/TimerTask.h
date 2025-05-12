#ifndef INCUBATOR_TIME_TIMERTASK_H
#define INCUBATOR_TIME_TIMERTASK_H
#include <cinttypes>
namespace Incubator
{
    namespace Time
    {
        class TimerTask
        {
        public:
            TimerTask();
            ~TimerTask();
            void SetDurationInMillisecond(uint32_t millisecond); // default is 1000
            void Start();
            void Stop();
            bool IsFinished() const;
            bool IsRunning() const;
            uint64_t GetTimeDifferenceFromStartInMillisecond() const;
            
        private:
            bool m_bIsRunning;
            uint32_t m_DurationInMillisecond;
            uint64_t m_StartTimestampInMillisecond;
        };
    } // namespace Time
    
} // namespace Incubator

#endif // INCUBATOR_TIME_TIMERTASK_H