#include "Incubator/Time/TimerTask.h"
#include "Incubator/Time/TimeUtils.h"

namespace Incubator
{
    namespace Time
    {
        TimerTask::TimerTask() : 
            m_bIsRunning ( false ),
            m_DurationInMillisecond ( static_cast<uint32_t>(1000UL) ),
            m_StartTimestampInMillisecond ( static_cast<uint64_t>(0UL))
        {
        }

        TimerTask::~TimerTask()
        {
        }

        void TimerTask::SetDurationInMillisecond(uint32_t millisecond)
        {
            m_DurationInMillisecond = millisecond;
        }
        
        void TimerTask::Start()
        {
            m_bIsRunning = true;
            m_StartTimestampInMillisecond = TimeUtils::GetStartTimestampInMillisecond();
        }
        
        void TimerTask::Stop()
        {
            m_bIsRunning = false;
        }
        
        bool TimerTask::IsFinished() const
        {
            bool bResult = false;
            if (m_bIsRunning)
            {
                const uint64_t passedTimeInMillisecond = GetTimeDifferenceFromStartInMillisecond();
                if (false == (passedTimeInMillisecond < m_DurationInMillisecond))
                {
                    bResult = true;
                }
            }
            return bResult;
        }

        bool TimerTask::IsRunning() const
        {
            return m_bIsRunning;
        }


        uint64_t TimerTask::GetTimeDifferenceFromStartInMillisecond() const
        {
            const uint64_t result = TimeUtils::GetStartTimestampInMillisecond() -  m_StartTimestampInMillisecond;
            return result;
        }

        
    } // namespace Time
    
} // namespace Incubator
