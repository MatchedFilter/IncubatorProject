#include "Incubator/Presenter/DataChangedEventHandlers/TimeInformationDataChangedEventHandler.h"
#include "Incubator/Time/TimeUtils.h"

namespace Incubator
{
    TimeInformationDataChangedEventHandler::TimeInformationDataChangedEventHandler() : 
        m_Model { nullptr },
        m_SpareModel { nullptr },
        m_View { nullptr }
    {
    }

    TimeInformationDataChangedEventHandler::~TimeInformationDataChangedEventHandler()
    {
    }

    void TimeInformationDataChangedEventHandler::OnUpdate(const TimeInformationData &data)
    {
        Time::TimeUtils::SetIncubatorTimestampInSecond(data.m_CurrentTimestampInSecond);
        if (nullptr != m_Model)
        {
            m_Model->Update(data);
        }
        if (nullptr != m_SpareModel)
        {
            m_SpareModel->Update(data);
        }
        if (nullptr != m_View)
        {
            m_View->UpdateTimeInformationData(data);
        }
    }
} // namespace Incubator
