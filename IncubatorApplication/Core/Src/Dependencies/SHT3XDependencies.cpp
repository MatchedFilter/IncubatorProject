#include "SHT3X/SHT3XDependencies.h"
#include "Stm32Peripherals.h"

namespace SHT3X
{
    bool ReadFromI2C(const uint8_t id, const uint16_t deviceAddress, const uint16_t addressToRead, ShtBuffer &buffer, const uint16_t size)
    {
        bool bResult = false;
        if (0x00U == id)
        {
        	if (size <= ShtBuffer::MAX_SHT_BUFFER_SIZE)
        	{
				if (HAL_OK == HAL_I2C_Mem_Read(&hi2c2,
						deviceAddress, addressToRead,
						static_cast<uint16_t>(sizeof(uint16_t)),
						buffer.m_Buffer,
						size, static_cast<uint32_t>(1000UL)))
				{

                    buffer.m_Size = size;
					bResult = true;
				}
        	}
        }
        return bResult;
    }
} // namespace SHT3X

