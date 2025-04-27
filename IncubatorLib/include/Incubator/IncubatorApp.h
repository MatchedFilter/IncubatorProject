#ifndef INCUBATOR_INCUBATORAPP_H
#define INCUBATOR_INCUBATORAPP_H
#include "TC2004/Lcd.h"
#include "Presenter.h"
#include "Lcd2004View.h"
#include "EepromModel.h"
#include "InternalFlashModel.h"
namespace Incubator
{
    class IncubatorApp
    {
    public:
        IncubatorApp();
        ~IncubatorApp();
        void Initialize(void);
        void Run(void);

    private:
        Presenter m_Presenter;
        Lcd2004View m_Lcd2004View;
        EepromModel m_EepromModel;
        InternalFlashModel m_InternalFlashModel;
    };
} // namespace Incubator

#endif // INCUBATOR_INCUBATORAPP_H