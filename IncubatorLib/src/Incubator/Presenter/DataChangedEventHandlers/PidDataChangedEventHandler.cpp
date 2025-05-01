#include "Incubator/Presenter/DataChangedEventHandlers/PidDataChangedEventHandler.h"

namespace Incubator
{
    PidDataChangedEventHandler::PidDataChangedEventHandler() : 
        m_Model { nullptr },
        m_SpareModel { nullptr }
    {
    }

    PidDataChangedEventHandler::~PidDataChangedEventHandler()
    {
    }

    void PidDataChangedEventHandler::OnUpdate(const PidData &data)
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
