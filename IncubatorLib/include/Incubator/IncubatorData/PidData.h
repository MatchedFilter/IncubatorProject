#ifndef INCUBATOR_INCUBATORDATA_PIDDATA_H
#define INCUBATOR_INCUBATORDATA_PIDDATA_H
#include "MF/ByteStreamReader.h"
#include "MF/ByteStreamWriter.h"
#include "IncubatorDataConstants.h"
namespace Incubator
{
    struct PidData
    {
    public:
        double m_P;
        double m_I;
        double m_D;

        static constexpr uint32_t DATA_SIZE = 
            static_cast<uint32_t>(sizeof(m_P)) +
            static_cast<uint32_t>(sizeof(m_I)) +
            static_cast<uint32_t>(sizeof(m_D));

    public:
        void Reset();
        void Copy(const PidData &other);
        bool Serialize(MF::ByteStreamWriter<INCUBATOR_BUFFER_SIZE> &writer) const;
        bool Deserialize(MF::ByteStreamReader<INCUBATOR_BUFFER_SIZE> &reader);
    };
    
} // namespace Incubator

#endif // INCUBATOR_INCUBATORDATA_PIDDATA_H