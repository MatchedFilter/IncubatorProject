#ifndef INCUBATOR_FLASHBUFFER_H
#define INCUBATOR_FLASHBUFFER_H
#include <cinttypes>

namespace Incubator
{
    struct FlashBuffer
    {
        static constexpr uint32_t MAX_WORD_SIZE = static_cast<uint32_t>(32UL);
        uint32_t m_Words[MAX_WORD_SIZE];
        uint32_t m_Size;
        void Reset();
    }; 
} // namespace Incubator

#endif // INCUBATOR_FLASHBUFFER_H