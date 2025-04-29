#ifndef INCUBATOR_INCUBATORDEPENDENCIES_H
#define INCUBATOR_INCUBATORDEPENDENCIES_H
#include <cinttypes>
#include "Incubator/Model/FlashBuffer.h"

namespace Incubator
{
    void DelayInMillisecond(uint32_t durationInMillisecond);
    bool WriteToFlash(const uint32_t address, const FlashBuffer &buffer );
    bool ReadFromFlash(const uint32_t address, FlashBuffer &buffer, const uint32_t size);
    uint64_t GetTimestampInMillisecond();
} // namespace Incubator

#endif // INCUBATOR_INCUBATORDEPENDENCIES_H