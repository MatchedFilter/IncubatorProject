#include "main.h"
#include "stm32f1xx.h"
#include <cinttypes>
#include "Eeprom24C/EepromI2CBuffer.h"
#include "Incubator/InternalFlashModel.h"
#include "SHT3X/ShtBuffer.h"

extern I2C_HandleTypeDef hi2c1;
extern I2C_HandleTypeDef hi2c2;
extern TIM_HandleTypeDef htim4;
extern ADC_HandleTypeDef hadc1;
extern ADC_HandleTypeDef hadc2;

namespace TC2004
{

    static constexpr uint16_t SLAVE_ADDR_RAW = 0x27U;
    static constexpr uint16_t SLAVE_ADDRESS_1 = static_cast<uint16_t>(SLAVE_ADDR_RAW << static_cast<uint16_t>(1U));
	void DelayInMillisecond(const uint32_t durationInMillisecond);
	bool SendCommand(const uint8_t id, const uint8_t command);
	bool SendData(const uint8_t id, const uint8_t data);

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

namespace DHT11
{
    void StartTimer(const uint8_t id)
    {
        if (id == 0x00U)
        {
            __HAL_TIM_SET_COUNTER(&htim4, 0);
            HAL_TIM_Base_Start(&htim4);
        }
    }

    void ResetTimer(const uint8_t id)
    {
        if (id == 0x00U)
        {
	        __HAL_TIM_SET_COUNTER(&htim4, 0);
        }
    }

    void StopTimer(const uint8_t id)
    {
        if (id == 0x00U)
        {
	        HAL_TIM_Base_Stop(&htim4);
        }
    }

    uint32_t GetTimestampInMicrosecondFromTimer(const uint8_t id)
    {
    	uint32_t result = static_cast<uint32_t>(0UL);
        if (id == 0x00U)
        {
        	result = static_cast<uint32_t>(__HAL_TIM_GET_COUNTER(&htim4));
        }
        return result;
    }

    void SetDataPinAsOutput(const uint8_t id)
    {
        if (id == 0x00U)
        {
            GPIO_InitTypeDef GPIO_InitStruct = {0};
            GPIO_InitStruct.Pin = GPIO_PIN_8;
            GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
            GPIO_InitStruct.Pull = GPIO_NOPULL;
            GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
            HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
        }
}

    void SetDataPinAsHigh(const uint8_t id)
    {
        if (id == 0x00U)
        {
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET);
        }
    }

    void SetDataPinAsLow(const uint8_t id)
    {
        if (id == 0x00U)
        {
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET);
        }
    }

    void DelayInMillisecond(const uint32_t durationInMillisecond)
    {
	    HAL_Delay(durationInMillisecond);
    }

    void SetDataPinAsInput(const uint8_t id)
    {
        if (id == 0x00U)
        {
            GPIO_InitTypeDef GPIO_InitStruct = {0};
            GPIO_InitStruct.Pin = GPIO_PIN_8;
            GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
            GPIO_InitStruct.Pull = GPIO_NOPULL;
            GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
            HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
        }
    }

    uint8_t ReadDataPin(const uint8_t id)
    {
        uint8_t result = 0x02U;
        if (id == 0x00U)
        {
            result = static_cast<uint8_t>(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8));
        }
        return result;
    }

} // namespace DHT11


namespace Incubator
{
    void DelayInMillisecond(const uint32_t durationInMillisecond)
    {
	    HAL_Delay(durationInMillisecond);
    }
} // namespace Incubator


namespace NTC
{
    void StartAdc(const uint8_t id);
    uint32_t ReadAdc(const uint8_t id);

    void StartAdc(const uint8_t id)
    {
        if (id == 0x00U)
        {
            HAL_ADC_Start(&hadc1);
        }
    }

    uint32_t ReadAdc(const uint8_t id)
    {
        uint32_t result = static_cast<uint32_t>(0UL);
        if (id == 0x00U)
        {
            result =  HAL_ADC_GetValue(&hadc1);
        }
        return result;
    }
} // namespace NTC

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



namespace Incubator
{
	static uint64_t s_ApplicationRunningTimeInMillisecond = static_cast<uint64_t>(0UL);
    bool WriteToFlash(const uint32_t address, const FlashBuffer &buffer );
    bool ReadFromFlash(const uint32_t address, FlashBuffer &buffer, const uint32_t size);
    uint64_t GetTimestampInMillisecond();

    bool WriteToFlash(const uint32_t address, const FlashBuffer &buffer )
    {
        bool bResult = false;
        if ((buffer.m_Size < FlashBuffer::MAX_WORD_SIZE) && (buffer.m_Size > static_cast<uint32_t>(0UL)))
        {
            HAL_FLASH_Unlock();
            bool bValid = true;
            for (uint32_t i  = static_cast<uint32_t>(0UL); i < buffer.m_Size; i++)
            {
                const uint32_t writeAddress = address + (i * static_cast<uint32_t>(sizeof(uint32_t)));
                if (HAL_OK != HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, writeAddress, buffer.m_Words[i]))
                {
                    bValid = false;
                    break;
                }
            }
            bResult = bValid;
            HAL_FLASH_Lock();
        }
        return bResult;
    }


    bool ReadFromFlash(const uint32_t address, FlashBuffer &buffer, const uint32_t size)
    {
        bool bResult = false;
        if ((size < FlashBuffer::MAX_WORD_SIZE) && (size > static_cast<uint32_t>(0UL)))
        {
            bResult = true;
            for (uint32_t i = static_cast<uint32_t>(0UL); i < size; i++)
            {
                volatile uint32_t *readAddress = reinterpret_cast<volatile uint32_t*>(address + (i * static_cast<uint32_t>(sizeof(uint32_t))));
                buffer.m_Words[i] = *readAddress;
            }
            buffer.m_Size = size;
        }
        return bResult;
    }

    uint64_t GetTimestampInMillisecond()
    {
    	return s_ApplicationRunningTimeInMillisecond;
    }

} // namespace Incubator

void SysTick_Handler(void)
{
	Incubator::s_ApplicationRunningTimeInMillisecond++;
}


namespace SHT3X
{
    bool ReadFromI2C(const uint8_t id, const uint16_t deviceAddress, const uint16_t addressToRead, ShtBuffer &buffer, const uint16_t size);
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


namespace Joystick
{
    void StartHorizontalAdc(const uint8_t id);
    void StartVertialAdc(const uint8_t id);
    void DelayInMillisecond(const uint32_t durationInMillisecond);
    uint32_t ReadAdc(const uint8_t id);
    uint8_t ReadSwitchState(const uint8_t id);

    void StartHorizontalAdc(const uint8_t id)
    {
        if (0x00U == id)
        {
            ADC_ChannelConfTypeDef sConfig = {0};
            sConfig.Channel = ADC_CHANNEL_2;
            sConfig.Rank = ADC_REGULAR_RANK_1;
            sConfig.SamplingTime = ADC_SAMPLETIME_13CYCLES_5;
            HAL_ADC_ConfigChannel(&hadc2, &sConfig);
            HAL_ADC_Start(&hadc2);
        }
    }

    void StartVertialAdc(const uint8_t id)
    {
        if (0x00U == id)
        {
            ADC_ChannelConfTypeDef sConfig = {0};
            sConfig.Channel = ADC_CHANNEL_3;
            sConfig.Rank = ADC_REGULAR_RANK_1;
            sConfig.SamplingTime = ADC_SAMPLETIME_13CYCLES_5;
            HAL_ADC_ConfigChannel(&hadc2, &sConfig);
            HAL_ADC_Start(&hadc2);
        }
    }

    void DelayInMillisecond(const uint32_t durationInMillisecond)
    {
		HAL_Delay(durationInMillisecond);
    }

    uint32_t ReadAdc(const uint8_t id)
    {
        uint32_t result = static_cast<uint32_t>(0x00U);
        if (0x00U == id)
        {
            result = HAL_ADC_GetValue(&hadc2);
        }
        return result;
    }

    uint8_t ReadSwitchState(const uint8_t id)
    {
        uint8_t result = 0x00U;
        if (0x00U == id)
        {
            result = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4) == GPIO_PIN_RESET;
        }
        return result;
    }

} // namespace Joystick
