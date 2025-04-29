#ifndef INCUBATOR_PRESENTER_H
#define INCUBATOR_PRESENTER_H
#include "Incubator/View/IView.h"
#include "Incubator/Model/IModel.h"

namespace Incubator
{
    class Presenter
    {
    public:
        Presenter();
        ~Presenter();
        void Initialize(IView *view, IModel *model, IModel* spareModel = nullptr);
        void Run(void);

    private:
        IView *m_View;
        IModel *m_Model;
        IModel *m_SpareModel;

    };
} // namespace Incubator

#endif // INCUBATOR_PRESENTER_H