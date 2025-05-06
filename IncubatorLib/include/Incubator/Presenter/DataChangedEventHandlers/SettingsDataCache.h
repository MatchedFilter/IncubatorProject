#ifndef INCUBATOR_SETTINGSDATACACHE_H
#define INCUBATOR_SETTINGSDATACACHE_H
#include "Incubator/View/DataChangedEventHandler/ISettingsDataChangedEventHandler.h"
#include "Incubator/Model/IModel.h"
#include "Incubator/View/IView.h"

namespace Incubator
{
    class SettingsDataCache : public ISettingsDataChangedEventHandler
    {
    public:
        SettingsDataCache();
        virtual ~SettingsDataCache();
        inline void Initialize(IModel *model, IModel* spareModel, IView *view) { m_Model = model; m_SpareModel = spareModel; m_View = view; }
        virtual void OnUpdate(const SettingsData &data) override;
        inline SettingsData GetData() { return m_Data; }

    private:
        IModel *m_Model;
        IModel *m_SpareModel;
        IView *m_View;
        SettingsData m_Data;
    };
} // namespace Incubator

#endif // INCUBATOR_SETTINGSDATACACHE_H