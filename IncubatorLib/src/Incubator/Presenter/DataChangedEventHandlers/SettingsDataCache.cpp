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
            m_View->UpdateSettingsData(data);
        }
    }
} // namespace Incubator
