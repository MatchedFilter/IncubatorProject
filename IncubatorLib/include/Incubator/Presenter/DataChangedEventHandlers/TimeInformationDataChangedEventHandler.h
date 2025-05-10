#ifndef INCUBATOR_TIMEINFORMATIONDATACHANGEDEVENTHANDLER_H
#define INCUBATOR_TIMEINFORMATIONDATACHANGEDEVENTHANDLER_H
#include "Incubator/View/DataChangedEventHandler/ITimeInformationDataChangedEventHandler.h"
#include "Incubator/Model/IModel.h"
#include "Incubator/View/IView.h"

namespace Incubator
{
    class TimeInformationDataChangedEventHandler : public ITimeInformationDataChangedEventHandler
    {
    public:
        TimeInformationDataChangedEventHandler();
        virtual ~TimeInformationDataChangedEventHandler();
        inline void Initialize(IModel *model, IModel* spareModel, IView *view) { m_Model = model; m_SpareModel = spareModel; m_View = view; }
        virtual void OnUpdate(const TimeInformationData &data) override;

    private:
        IModel *m_Model;
        IModel *m_SpareModel;
        IView *m_View;
    };
} // namespace Incubator

#endif // INCUBATOR_TIMEINFORMATIONDATACHANGEDEVENTHANDLER_H