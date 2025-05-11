#include "Incubator/Presenter/DataChangedEventHandlers/PidDataCache.h"

namespace Incubator
{
    PidDataCache::PidDataCache() : 
        m_Model { nullptr },
        m_SpareModel { nullptr },
        m_bUpdated { false }
    {
    }

    PidDataCache::~PidDataCache()
    {
    }

    void PidDataCache::OnUpdate(const PidData &data)
    {
        if (false == m_bUpdated)
        {
            m_bUpdated = true;
        }
        m_PidData.Copy(data);

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
    
    bool PidDataCache::GetPid(double &p, double &i, double &d)const 
    {
        bool bResult = false;
        if (m_bUpdated)
        {
            bResult = true;
            p = static_cast<double>(m_PidData.m_P) / 10.0;
            i = static_cast<double>(m_PidData.m_I) / 10.0;
            d = static_cast<double>(m_PidData.m_D) / 10.0;
        }
        return bResult;
    }

    bool PidDataCache::GetHumidityHysterisisDiff(uint8_t &upperDiff, uint8_t &lowerDiff) const
    {
        bool bResult = false;
        if (m_bUpdated)
        {
            bResult = true;
            upperDiff = m_PidData.m_UpperHumidityDifference;
            lowerDiff = m_PidData.m_LowerHumidityDifference;
        }
        return bResult; 
    }



} // namespace Incubator
