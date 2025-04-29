#include "TC2004/TC2004Dependencies.h"
#include "Stm32Peripherals.h"

namespace TC2004
{

    static constexpr uint16_t SLAVE_ADDR_RAW = 0x27U;
    static constexpr uint16_t SLAVE_ADDRESS_1 = static_cast<uint16_t>(SLAVE_ADDR_RAW << static_cast<uint16_t>(1U));
    
	void DelayInMillisecond(const uint32_t durationInMillisecond)
	{
		HAL_Delay(durationInMillisecond);
	}

	bool SendCommand(const uint8_t id, const uint8_t command)
	{
        bool bResult = false;
        if (id == 0x00U)
        {


            const uint8_t upperData = command & static_cast<uint8_t>(0xF0U);
            const uint8_t lowerData = static_cast<uint8_t>( command << static_cast<uint8_t>(4U)) & static_cast<uint8_t>(0xF0U);
            uint8_t buffer[4] = {
                static_cast<uint8_t>(upperData | static_cast<uint8_t>(0x0CU)),  // en=1, rs=0 -> bxxxx1100
                static_cast<uint8_t>(upperData | static_cast<uint8_t>(0x08U)),  // en=0, rs=0 -> bxxxx1000
                static_cast<uint8_t>(lowerData | static_cast<uint8_t>(0x0CU)),  // en=1, rs=0 -> bxxxx1100
                static_cast<uint8_t>(lowerData | static_cast<uint8_t>(0x08U))   // en=0, rs=0 -> bxxxx1000
            }; // not constant due to HAL_I2C_Master_Tranmit function signature
            const uint8_t result = HAL_I2C_Master_Transmit (&hi2c1, SLAVE_ADDRESS_1, buffer, static_cast<uint16_t>(4U), static_cast<uint32_t>(100U));
            if (result == HAL_OK)
            {
                bResult = true;
            }
        }
        return bResult;
	}
	bool SendData(const uint8_t id, const uint8_t data)
    {
        bool bResult = false;
        if (id == 0x00U)
        {
            const uint8_t upperData = data & static_cast<uint8_t>(0xF0U);
            const uint8_t lowerData = static_cast<uint8_t>( data << static_cast<uint8_t>(4U)) & static_cast<uint8_t>(0xF0U);
            uint8_t buffer[4] = {
                static_cast<uint8_t>(upperData | static_cast<uint8_t>(0x0DU)),  // en=1, rs=0 -> bxxxx1100
                static_cast<uint8_t>(upperData | static_cast<uint8_t>(0x09U)),  // en=0, rs=0 -> bxxxx1000
                static_cast<uint8_t>(lowerData | static_cast<uint8_t>(0x0DU)),  // en=1, rs=0 -> bxxxx1100
                static_cast<uint8_t>(lowerData | static_cast<uint8_t>(0x09U))   // en=0, rs=0 -> bxxxx1000
            }; // not constant due to HAL_I2C_Master_Tranmit function signature
            const uint8_t result = HAL_I2C_Master_Transmit (&hi2c1, SLAVE_ADDRESS_1, buffer, static_cast<uint16_t>(4U), static_cast<uint32_t>(100U));
            if (result == HAL_OK)
            {
                bResult = true;
            }
        }
        return bResult;
    }

} // namespace TC2004