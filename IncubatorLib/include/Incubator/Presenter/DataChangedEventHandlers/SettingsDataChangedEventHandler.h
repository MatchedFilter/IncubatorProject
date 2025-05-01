#ifndef INCUBATOR_SETTINGSDATACHANGEDEVENTHANDLER_H
#define INCUBATOR_SETTINGSDATACHANGEDEVENTHANDLER_H
#include "Incubator/View/ISettingsDataChangedEventHandler.h"
#include "Incubator/Model/IModel.h"

namespace Incubator
{
    class SettingsDataChangedEventHandler : public ISettingsDataChangedEventHandler
    {
    public:
        SettingsDataChangedEventHandler();
        virtual ~SettingsDataChangedEventHandler();
        inline void Initialize(IModel *model, IModel* spareModel) { m_Model = model; m_SpareModel = spareModel; }
        virtual void OnUpdate(const SettingsData &data) override;

    private:
        IModel *m_Model;
        IModel *m_SpareModel;
    };
} // namespace Incubator

#endif // INCUBATOR_SETTINGSDATACHANGEDEVENTHANDLER_H