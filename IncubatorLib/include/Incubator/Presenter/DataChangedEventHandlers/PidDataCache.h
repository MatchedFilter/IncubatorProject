#ifndef INCUBATOR_PIDDATACACHE_H
#define INCUBATOR_PIDDATACACHE_H
#include "Incubator/View/DataChangedEventHandler/IPidDataChangedEventHandler.h"
#include "Incubator/Model/IModel.h"
#include "Incubator/View/IView.h"

namespace Incubator
{
    class PidDataCache : public IPidDataChangedEventHandler
    {
    public:
        PidDataCache();
        virtual ~PidDataCache();
        inline void Initialize(IModel *model, IModel* spareModel, IView *view) { m_Model = model; m_SpareModel = spareModel; m_View = view; }
        virtual void OnUpdate(const PidData &data) override;
        bool GetPid(double &p, double &i, double &d) const;
        bool GetHumidityHysterisisDiff(uint8_t &upperDiff, uint8_t &lowerDiff) const;

    private:
        IModel *m_Model;
        IModel *m_SpareModel;
        IView *m_View;
        bool m_bUpdated;
        PidData m_PidData;
    };
} // namespace Incubator

#endif // INCUBATOR_PIDDATACACHE_H