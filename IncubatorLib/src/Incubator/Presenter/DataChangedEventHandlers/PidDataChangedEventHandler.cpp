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
            m_View->UpdatePidData(data);
        }
    }
} // namespace Incubator
