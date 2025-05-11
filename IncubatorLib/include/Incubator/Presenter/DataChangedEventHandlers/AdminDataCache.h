#ifndef INCUBATOR_ADMINDATACACHE_H
#define INCUBATOR_ADMINDATACACHE_H
#include "Incubator/View/DataChangedEventHandler/IAdminDataChangedEventHandler.h"
#include "Incubator/Model/IModel.h"
#include "Incubator/View/IView.h"

namespace Incubator
{
    class AdminDataCache : public IAdminDataChangedEventHandler
    {
    public:
        AdminDataCache();
        virtual ~AdminDataCache();
        inline void Initialize(IModel *model, IModel* spareModel, IView *view) { m_Model = model; m_SpareModel = spareModel; m_View = view; }
        virtual void OnUpdate(const AdminData &data) override;
        bool GetPid(double &p, double &i, double &d) const;
        bool GetHumidityHysterisisDiff(uint8_t &upperDiff, uint8_t &lowerDiff) const;

    private:
        IModel *m_Model;
        IModel *m_SpareModel;
        IView *m_View;
        bool m_bUpdated;
        AdminData m_AdminData;
    };
} // namespace Incubator

#endif // INCUBATOR_ADMINDATACACHE_H