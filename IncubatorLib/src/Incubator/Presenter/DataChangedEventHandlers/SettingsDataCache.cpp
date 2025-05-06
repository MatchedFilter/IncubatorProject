#include "Incubator/Presenter/DataChangedEventHandlers/SettingsDataCache.h"

namespace Incubator
{
    SettingsDataCache::SettingsDataCache() : 
        m_Model { nullptr },
        m_SpareModel { nullptr },
        m_View { nullptr }
    {
    }

    SettingsDataCache::~SettingsDataCache()
    {
    }

    void SettingsDataCache::OnUpdate(const SettingsData &data)
    {
        if (m_Model != nullptr)
        {
            m_Model->Update(data);
        }
        if (m_SpareModel != nullptr)
        {
            m_SpareModel->Update(data);
        }
        if (m_View != nullptr)
        {
            m_View->UpdateSettingsData(data);
        }
    }
} // namespace Incubator
