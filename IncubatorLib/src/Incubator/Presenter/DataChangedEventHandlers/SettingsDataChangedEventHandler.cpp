#include "Incubator/Presenter/DataChangedEventHandlers/SettingsDataChangedEventHandler.h"

namespace Incubator
{
    SettingsDataChangedEventHandler::SettingsDataChangedEventHandler() : 
        m_Model { nullptr },
        m_SpareModel { nullptr }
    {
    }

    SettingsDataChangedEventHandler::~SettingsDataChangedEventHandler()
    {
    }

    void SettingsDataChangedEventHandler::OnUpdate(const SettingsData &data)
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
