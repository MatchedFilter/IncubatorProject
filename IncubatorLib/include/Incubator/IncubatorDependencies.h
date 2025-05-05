#ifndef INCUBATOR_INCUBATORDEPENDENCIES_H
#define INCUBATOR_INCUBATORDEPENDENCIES_H
#include <cinttypes>
#include "Incubator/Model/FlashBuffer.h"

namespace Incubator
{
    void DelayInMillisecond(uint32_t durationInMillisecond);
    bool WriteToFlash(const uint32_t flashBaseAddress, const uint32_t offset, const FlashBuffer &buffer);
    bool ReadFromFlash(const uint32_t baseAddress, const uint32_t offset, FlashBuffer &buffer, const uint32_t size);
    uint64_t GetTimestampInMillisecond();
    void TurnOnHeater();
    void TurnOffHeater();
    void TurnOnHumidityGenerator();
    void TurnOffHumidityGenerator();
} // namespace Incubator

#endif // INCUBATOR_INCUBATORDEPENDENCIES_H