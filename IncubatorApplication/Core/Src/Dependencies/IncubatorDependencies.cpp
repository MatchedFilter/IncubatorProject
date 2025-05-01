#include "Incubator/IncubatorDependencies.h"
#include "Stm32Peripherals.h"

namespace Incubator
{
    void DelayInMillisecond(const uint32_t durationInMillisecond)
    {
	    HAL_Delay(durationInMillisecond);
    }

    static uint64_t s_ApplicationRunningTimeInMillisecond = static_cast<uint64_t>(0UL);

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

    void TurnOnHeater()
    {
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
    }

    void TurnOffHeater()
    {
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
    }

    void TurnOnHumidityGenerator()
    {
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_SET);
    }

    void TurnOffHumidityGenerator()
    {
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET);
    }


} // namespace Incubator

void SysTick_Handler(void)
{
	Incubator::s_ApplicationRunningTimeInMillisecond++;
}
