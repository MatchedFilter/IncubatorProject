#ifndef INCUBATOR_IPIDDATACHANGEDEVENTHANDLER_H
#define INCUBATOR_IPIDDATACHANGEDEVENTHANDLER_H
#include "Incubator/IncubatorData/PidData.h"
namespace Incubator
{
    class IPidDataChangedEventHandler
    {
    public:
        inline virtual ~IPidDataChangedEventHandler() { }
        virtual void OnUpdate(const PidData &data) = 0;
    };
} // namespace Incubator

#endif // INCUBATOR_IPIDDATACHANGEDEVENTHANDLER_H