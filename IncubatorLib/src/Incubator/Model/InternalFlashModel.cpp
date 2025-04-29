#include "Incubator/Model/InternalFlashModel.h"
#include "Incubator/IncubatorData/IncubatorDataConstants.h"
#include "MF/MFBuffer.h"
#include "Incubator/Model/FlashBuffer.h"
#include "Incubator/IncubatorDependencies.h"

namespace Incubator
{


    static constexpr uint32_t SETTINGS_DATA_START_MEMORY_ADDRESS_OFFSET = static_cast<uint32_t>(0x0UL);
    static constexpr uint32_t TIME_INFORMATION_DATA_START_MEMORY_ADDRESS_OFFSET = SettingsData::DATA_SIZE +
        (((SettingsData::DATA_SIZE % static_cast<uint32_t>(sizeof(uint32_t))) != static_cast<uint32_t>(0UL)) * static_cast<uint32_t>(4UL));



    InternalFlashModel::InternalFlashModel(const uint32_t flashBaseAddress) : 
        m_FlashBaseAddress ( flashBaseAddress )
    {
    }

    InternalFlashModel::~InternalFlashModel()
    {
    }

    bool InternalFlashModel::Update(const SettingsData &data)
    {
        bool bResult = false;
        MF::MFBuffer<INCUBATOR_BUFFER_SIZE> buffer;
        static constexpr uint32_t WORD_SIZE = (SettingsData::DATA_SIZE / static_cast<uint32_t>(sizeof(uint32_t))) 
            + ((SettingsData::DATA_SIZE % static_cast<uint32_t>(4UL)) != static_cast<uint32_t>(0UL));

        static constexpr uint32_t BUFFER_TOTAL_SIZE = WORD_SIZE * static_cast<uint32_t>(sizeof(uint32_t));
        for (uint32_t i = static_cast<uint32_t>(0UL); i < BUFFER_TOTAL_SIZE; i++)
        {
            buffer.m_Buffer[i] = 0x00U;
        }
        buffer.m_Size = SettingsData::DATA_SIZE;
        MF::ByteStreamWriter<INCUBATOR_BUFFER_SIZE> writer(buffer);
        if (data.Serialize(writer))
        {

            FlashBuffer flashBuffer;
            flashBuffer.Reset();
            flashBuffer.m_Size = WORD_SIZE;
            for (uint32_t i = static_cast<uint32_t>(0UL); i < WORD_SIZE; i++)
            {
                flashBuffer.m_Words[i] = reinterpret_cast<uint32_t&>(buffer.m_Buffer[i * static_cast<uint32_t>(sizeof(uint32_t))]);
            }
            if (WriteToFlash(m_FlashBaseAddress + SETTINGS_DATA_START_MEMORY_ADDRESS_OFFSET, flashBuffer))
            {
                bResult = true;
            }
        }
        return bResult;
    }

    bool InternalFlashModel::Update(const TimeInformationData &data)
    {
        bool bResult = false;
        MF::MFBuffer<INCUBATOR_BUFFER_SIZE> buffer;
        static constexpr uint32_t WORD_SIZE = (TimeInformationData::DATA_SIZE / static_cast<uint32_t>(sizeof(uint32_t))) 
            + ((TimeInformationData::DATA_SIZE % static_cast<uint32_t>(4UL)) != static_cast<uint32_t>(0UL));
        
        static constexpr uint32_t BUFFER_TOTAL_SIZE = WORD_SIZE * static_cast<uint32_t>(sizeof(uint32_t));
        for (uint32_t i = static_cast<uint32_t>(0UL); i < BUFFER_TOTAL_SIZE; i++)
        {
            buffer.m_Buffer[i] = 0x00U;
        }
        buffer.m_Size = TimeInformationData::DATA_SIZE;
        MF::ByteStreamWriter<INCUBATOR_BUFFER_SIZE> writer(buffer);
        if (data.Serialize(writer))
        {

            FlashBuffer flashBuffer;
            flashBuffer.Reset();
            flashBuffer.m_Size = WORD_SIZE;
            for (uint32_t i = static_cast<uint32_t>(0UL); i < WORD_SIZE; i++)
            {
                flashBuffer.m_Words[i] = reinterpret_cast<uint32_t&>(buffer.m_Buffer[i * static_cast<uint32_t>(sizeof(uint32_t))]);
            }
            if (WriteToFlash(m_FlashBaseAddress + TIME_INFORMATION_DATA_START_MEMORY_ADDRESS_OFFSET, flashBuffer))
            {
                bResult = true;
            }
        }
        return bResult;
    }

    bool InternalFlashModel::Get(SettingsData &data)
    {
        bool bResult = false;
        FlashBuffer flashBuffer;
        flashBuffer.Reset();
        static constexpr uint32_t WORD_SIZE = (SettingsData::DATA_SIZE / static_cast<uint32_t>(sizeof(uint32_t))) 
            + ((SettingsData::DATA_SIZE % static_cast<uint32_t>(4UL)) != static_cast<uint32_t>(0UL));
        if (ReadFromFlash(m_FlashBaseAddress + SETTINGS_DATA_START_MEMORY_ADDRESS_OFFSET, flashBuffer, WORD_SIZE))
        {
            static constexpr uint32_t BUFFER_TOTAL_SIZE = WORD_SIZE * static_cast<uint32_t>(sizeof(uint32_t));

            MF::MFBuffer<INCUBATOR_BUFFER_SIZE> buffer;
            buffer.Reset();
            
            const uint8_t * flashPtr = reinterpret_cast<const uint8_t*>(flashBuffer.m_Words);
            for (uint32_t i = static_cast<uint32_t>(0UL); i < BUFFER_TOTAL_SIZE; i++)
            {
                buffer.m_Buffer[i] = flashPtr[i];
            }
            buffer.m_Size = SettingsData::DATA_SIZE;
            MF::ByteStreamReader<INCUBATOR_BUFFER_SIZE> reader(buffer);
            if (data.Deserialize(reader))
            {
                bResult = true;
            }

        }
        return bResult;
    }

    bool InternalFlashModel::Get(TimeInformationData &data)
    {
        bool bResult = false;
        FlashBuffer flashBuffer;
        flashBuffer.Reset();
        static constexpr uint32_t WORD_SIZE = (TimeInformationData::DATA_SIZE / static_cast<uint32_t>(sizeof(uint32_t))) 
            + ((TimeInformationData::DATA_SIZE % static_cast<uint32_t>(4UL)) != static_cast<uint32_t>(0UL));
        if (ReadFromFlash(m_FlashBaseAddress + SETTINGS_DATA_START_MEMORY_ADDRESS_OFFSET, flashBuffer, WORD_SIZE))
        {
            static constexpr uint32_t BUFFER_TOTAL_SIZE = WORD_SIZE * static_cast<uint32_t>(sizeof(uint32_t));
            
            MF::MFBuffer<INCUBATOR_BUFFER_SIZE> buffer;
            buffer.Reset();
            
            const uint8_t * flashPtr = reinterpret_cast<const uint8_t*>(flashBuffer.m_Words);
            for (uint32_t i = static_cast<uint32_t>(0UL); i < BUFFER_TOTAL_SIZE; i++)
            {
                buffer.m_Buffer[i] = flashPtr[i];
            }
            buffer.m_Size = TimeInformationData::DATA_SIZE;
            MF::ByteStreamReader<INCUBATOR_BUFFER_SIZE> reader(buffer);
            if (data.Deserialize(reader))
            {
                bResult = true;
            }

        }
        return bResult;
    }

    
} // namespace Incubator
