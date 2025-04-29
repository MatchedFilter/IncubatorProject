#include "Incubator/Presenter/Presenter.h"
#include "Incubator/IncubatorData/IncubatorInformationData.h"

namespace Incubator
{
    void DelayInMillisecond(uint32_t durationInMillisecond);

    Presenter::Presenter() :
        m_View ( nullptr ),
        m_Model ( nullptr )
    {
    }

    Presenter::~Presenter()
    {
    }

    void Presenter::Initialize(IView *view, IModel *model, IModel* spareModel)
    {
        m_View = view;
        m_Model = model;
        m_SpareModel = spareModel;


        IncubatorInformationData data;
        data.Reset();
        (void) m_Model->Update(data.m_SettingsData);
        (void) m_Model->Update(data.m_TimeInformationData);
        // (void) m_SpareModel->Update(data.m_SettingsData);
        (void) m_SpareModel->Update(data.m_TimeInformationData);
    }

    void Presenter::Run(void)
    {
        static uint32_t counter = 0UL;
        if (m_View != nullptr)
        {
        }
    }

} // namespace Incubator
