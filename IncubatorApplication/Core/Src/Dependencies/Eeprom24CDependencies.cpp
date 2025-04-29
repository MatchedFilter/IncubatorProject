#include "Eeprom24C/Eeprom24CDependencies.h"
#include "Stm32Peripherals.h"


namespace Eeprom24C
{
    bool WriteToI2C(const uint8_t id, const uint16_t deviceAddress, const uint16_t addressToWrite, const EepromI2CBuffer &i2cBuffer);
    bool ReadFromI2C(const uint8_t id, const uint16_t deviceAddress, const uint16_t addressToRead, EepromI2CBuffer &i2cBuffer, const uint16_t size);
    void DelayInMillisecond(const uint32_t durationInMillisecond);

    bool WriteToI2C(const uint8_t id, const uint16_t deviceAddress, const uint16_t addressToWrite, const EepromI2CBuffer &i2cBuffer)
    {
        bool bResult = false;
        if (0x00U == id)
        {
        	if (i2cBuffer.m_Size <= EepromI2CBuffer::MAX_EEPROMI2CBUFFER_SIZE)
        	{
        		EepromI2CBuffer writeBuffer;
        		for (uint32_t i = static_cast<uint32_t>(0UL); i < i2cBuffer.m_Size; i++)
        		{
        			writeBuffer.m_Buffer[i] = i2cBuffer.m_Buffer[i];
        		}
        		writeBuffer.m_Size = i2cBuffer.m_Size;

				if (HAL_OK == HAL_I2C_Mem_Write(&hi2c1,
						deviceAddress,
						addressToWrite,
						static_cast<uint16_t>(sizeof(uint16_t)),
						writeBuffer.m_Buffer,
						static_cast<uint16_t>(i2cBuffer.m_Size),
						static_cast<uint32_t>(100UL)) )
				{
					bResult = true;
				}
        	}
        }
        return bResult;
    }

    bool ReadFromI2C(const uint8_t id, const uint16_t deviceAddress, const uint16_t addressToRead, EepromI2CBuffer &i2cBuffer, const uint16_t size)
    {
        bool bResult = false;
        if (0x00U == id)
        {
        	if (size <= EepromI2CBuffer::MAX_EEPROMI2CBUFFER_SIZE)
        	{
				if (HAL_OK == HAL_I2C_Mem_Read(&hi2c1,
						deviceAddress, addressToRead,
						static_cast<uint16_t>(sizeof(uint16_t)),
						i2cBuffer.m_Buffer,
						size, static_cast<uint32_t>(1000UL)))
				{
                    i2cBuffer.m_Size = size;
					bResult = true;
				}
        	}
        }
        return bResult;
    }

    void DelayInMillisecond(const uint32_t durationInMillisecond)
    {
	    HAL_Delay(durationInMillisecond);
    }

} // namespace Eeprom24C
