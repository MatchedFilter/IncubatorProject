#include "Incubator/Model/FlashBuffer.h"

namespace Incubator
{
    void FlashBuffer::Reset()
    {
        for (uint32_t i = static_cast<uint32_t>(0UL); i < MAX_WORD_SIZE; i++)
        {
            m_Words[i] = static_cast<uint32_t>(0UL);
        }
        m_Size = static_cast<uint32_t>(0UL);
    }
} // namespace Incubator
