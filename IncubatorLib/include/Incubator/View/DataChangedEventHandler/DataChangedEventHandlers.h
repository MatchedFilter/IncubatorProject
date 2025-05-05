#ifndef INCUBATOR_DATACHANGEDEVENTHANDLERS_H
#define INCUBATOR_DATACHANGEDEVENTHANDLERS_H
#include "IPidDataChangedEventHandler.h"
#include "ISettingsDataChangedEventHandler.h"
#include "ITimeInformationDataChangedEventHandler.h"

namespace Incubator
{
    struct DataChangedEventHandlers
    {
        IPidDataChangedEventHandler *m_PidDataChangedEventHandler;
        ISettingsDataChangedEventHandler *m_SettingsDataChangedEventHandler;
        ITimeInformationDataChangedEventHandler *m_TimeInformationDataChangedEventHandler;
        inline void Reset()
        {
            m_PidDataChangedEventHandler = nullptr;
            m_SettingsDataChangedEventHandler = nullptr;
            m_TimeInformationDataChangedEventHandler = nullptr;
        }

        inline void Copy(const DataChangedEventHandlers &other)
        {
            m_PidDataChangedEventHandler = other.m_PidDataChangedEventHandler;
            m_SettingsDataChangedEventHandler = other.m_SettingsDataChangedEventHandler;
            m_TimeInformationDataChangedEventHandler = other.m_TimeInformationDataChangedEventHandler;
        }
    };

} // namespace Incubator

#endif // INCUBATOR_DATACHANGEDEVENTHANDLERS_H