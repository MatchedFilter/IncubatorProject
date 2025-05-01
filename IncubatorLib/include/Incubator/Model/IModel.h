#ifndef INCUBATOR_IMODEL_H
#define INCUBATOR_IMODEL_H
#include <cinttypes>
#include "Incubator/IncubatorData/PidData.h"
#include "Incubator/IncubatorData/SettingsData.h"
#include "Incubator/IncubatorData/TimeInformationData.h"
namespace Incubator
{
    class IModel
    {
    public:
        inline virtual ~IModel() { }
        virtual bool Update(const PidData &data) = 0;
        virtual bool Update(const SettingsData &data) = 0;
        virtual bool Update(const TimeInformationData &data) = 0;
        virtual bool Get(PidData &data) = 0;
        virtual bool Get(SettingsData &data) = 0;
        virtual bool Get(TimeInformationData &data) = 0;
    };
} // namespace Incubator

#endif // INCUBATOR_IMODEL_H