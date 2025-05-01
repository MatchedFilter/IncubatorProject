#include "Incubator/Presenter/DataChangedEventHandlers/TimeInformationDataChangedEventHandler.h"

namespace Incubator
{
    TimeInformationDataChangedEventHandler::TimeInformationDataChangedEventHandler() : 
        m_Model { nullptr },
        m_SpareModel { nullptr }
    {
    }

    TimeInformationDataChangedEventHandler::~TimeInformationDataChangedEventHandler()
    {
    }

    void TimeInformationDataChangedEventHandler::OnUpdate(const TimeInformationData &data)
    {
        if (m_Model != nullptr)
        {
            m_Model->Update(data);
        }
        if (m_SpareModel != nullptr)
        {
            m_SpareModel->Update(data);
        }
    }
} // namespace Incubator
