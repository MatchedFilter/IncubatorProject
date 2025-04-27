#include "Incubator/IncubatorApp.h"


namespace Incubator
{
    
    IncubatorApp::IncubatorApp() :
        m_InternalFlashModel ( static_cast<uint32_t>(0x0800C000UL) )
    {
    }

    IncubatorApp::~IncubatorApp()
    {
    }

    void IncubatorApp::Initialize(void)
    {
        m_Lcd2004View.Initialize();
        m_EepromModel.Initialize();
        m_Presenter.Initialize(&m_Lcd2004View, &m_EepromModel, &m_InternalFlashModel);
    }

    void IncubatorApp::Run(void)
    {
        m_Presenter.Run();
    }

} // namespace Incubator
