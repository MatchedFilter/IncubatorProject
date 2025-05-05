#ifndef INCUBATOR_PIDDATACHANGEDEVENTHANDLER_H
#define INCUBATOR_PIDDATACHANGEDEVENTHANDLER_H
#include "Incubator/View/DataChangedEventHandler/IPidDataChangedEventHandler.h"
#include "Incubator/Model/IModel.h"

namespace Incubator
{
    class PidDataChangedEventHandler : public IPidDataChangedEventHandler
    {
    public:
        PidDataChangedEventHandler();
        virtual ~PidDataChangedEventHandler();
        inline void Initialize(IModel *model, IModel* spareModel) { m_Model = model; m_SpareModel = spareModel; }
        virtual void OnUpdate(const PidData &data) override;

    private:
        IModel *m_Model;
        IModel *m_SpareModel;
    };
} // namespace Incubator

#endif // INCUBATOR_PIDDATACHANGEDEVENTHANDLER_H