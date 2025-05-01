#ifndef INCUBATOR_TIMEINFORMATIONDATACHANGEDEVENTHANDLER_H
#define INCUBATOR_TIMEINFORMATIONDATACHANGEDEVENTHANDLER_H
#include "Incubator/View/ITimeInformationDataChangedEventHandler.h"
#include "Incubator/Model/IModel.h"

namespace Incubator
{
    class TimeInformationDataChangedEventHandler : public ITimeInformationDataChangedEventHandler
    {
    public:
        TimeInformationDataChangedEventHandler();
        virtual ~TimeInformationDataChangedEventHandler();
        inline void Initialize(IModel *model, IModel* spareModel) { m_Model = model; m_SpareModel = spareModel; }
        virtual void OnUpdate(const TimeInformationData &data) override;

    private:
        IModel *m_Model;
        IModel *m_SpareModel;
    };
} // namespace Incubator

#endif // INCUBATOR_TIMEINFORMATIONDATACHANGEDEVENTHANDLER_H