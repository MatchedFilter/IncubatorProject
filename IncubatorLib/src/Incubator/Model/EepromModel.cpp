#include "Incubator/Model/EepromModel.h"

namespace Incubator
{

    static constexpr uint32_t SETTINGS_DATA_START_MEMORY_ADDRESS = static_cast<uint32_t>(0x0UL);
    static constexpr uint32_t TIME_INFORMATION_DATA_START_MEMORY_ADDRESS = SettingsData::DATA_SIZE;

    EepromModel::EepromModel() : 
        m_Eeprom24C32 ( 0x00U )
    {
    }

    EepromModel::~EepromModel()
    {
    }

    void EepromModel::Initialize()
    {
        m_Eeprom24C32.Initialize();
    }

    bool EepromModel::Update(const SettingsData &data)
    {
        bool bResult = false;
        MF::MFBuffer<INCUBATOR_BUFFER_SIZE> buffer;
        buffer.m_Size = SettingsData::DATA_SIZE;
        MF::ByteStreamWriter<INCUBATOR_BUFFER_SIZE> writer(buffer);
        if (data.Serialize(writer))
        {
            Eeprom24C::EepromBuffer eBuffer;
            if (buffer.m_Size < Eeprom24C::EepromBuffer::MAX_EEPROMBUFFER_SIZE)
            {
                for (uint32_t i = static_cast<uint32_t>(0UL); i < buffer.m_Size; i++)
                {
                    eBuffer.m_Buffer[i] = buffer.m_Buffer[i];
                }
                eBuffer.m_Size = buffer.m_Size;
                bResult = m_Eeprom24C32.Write(SETTINGS_DATA_START_MEMORY_ADDRESS, eBuffer); 
            }
        }
        return bResult;
    }

    bool EepromModel::Update(const TimeInformationData &data)
    {
        bool bResult = false;
        MF::MFBuffer<INCUBATOR_BUFFER_SIZE> buffer;
        buffer.m_Size = TimeInformationData::DATA_SIZE;
        MF::ByteStreamWriter<INCUBATOR_BUFFER_SIZE> writer(buffer);
        if (data.Serialize(writer))
        {
            Eeprom24C::EepromBuffer eBuffer;
            if (buffer.m_Size < Eeprom24C::EepromBuffer::MAX_EEPROMBUFFER_SIZE)
            {
                for (uint32_t i = static_cast<uint32_t>(0UL); i < buffer.m_Size; i++)
                {
                    eBuffer.m_Buffer[i] = buffer.m_Buffer[i];
                }
                eBuffer.m_Size = buffer.m_Size;
                bResult = m_Eeprom24C32.Write(TIME_INFORMATION_DATA_START_MEMORY_ADDRESS, eBuffer); 
            }
        }
        return bResult;
    }

    bool EepromModel::Get(SettingsData &data)
    {
        bool bResult = false;
        Eeprom24C::EepromBuffer eBuffer;
        eBuffer.m_Size = static_cast<uint32_t>(0UL);
        if (m_Eeprom24C32.Read(SETTINGS_DATA_START_MEMORY_ADDRESS, eBuffer, SettingsData::DATA_SIZE))
        {
            if (eBuffer.m_Size == SettingsData::DATA_SIZE)
            {
                MF::MFBuffer<INCUBATOR_BUFFER_SIZE> buffer;
                for (uint32_t i = static_cast<uint32_t>(0UL); i < eBuffer.m_Size; i++)
                {
                    buffer.m_Buffer[i] = eBuffer.m_Buffer[i];
                }
                buffer.m_Size = eBuffer.m_Size;
                MF::ByteStreamReader<INCUBATOR_BUFFER_SIZE> reader(buffer);
                if (data.Deserialize(reader))
                {
                    bResult = true;
                }
            }
        }
        return bResult;
    }

    bool EepromModel::Get(TimeInformationData &data)
    {
        bool bResult = false;
        Eeprom24C::EepromBuffer eBuffer;
        eBuffer.m_Size = static_cast<uint32_t>(0UL);
        if (m_Eeprom24C32.Read(TIME_INFORMATION_DATA_START_MEMORY_ADDRESS, eBuffer, TimeInformationData::DATA_SIZE))
        {
            if (eBuffer.m_Size == TimeInformationData::DATA_SIZE)
            {
                MF::MFBuffer<INCUBATOR_BUFFER_SIZE> buffer;
                for (uint32_t i = static_cast<uint32_t>(0UL); i < eBuffer.m_Size; i++)
                {
                    buffer.m_Buffer[i] = eBuffer.m_Buffer[i];
                }
                buffer.m_Size = eBuffer.m_Size;
                MF::ByteStreamReader<INCUBATOR_BUFFER_SIZE> reader(buffer);
                if (data.Deserialize(reader))
                {
                    bResult = true;
                }
            }
        }
        return bResult;
    }

    
} // namespace Incubator
