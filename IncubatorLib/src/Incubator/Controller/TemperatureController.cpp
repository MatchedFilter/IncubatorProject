#include "Incubator/Controller/TemperatureController.h"


namespace Incubator
{
    TemperatureController::TemperatureController() : 
        m_bIsTemperatureValid ( false ),
        m_DesiredTemperatureInCelcius ( 0.0 ),
        m_PreviousTemperatureInCelcius ( 0.0 ),
        m_PConstant ( 0.0 ),
        m_IConstant ( 0.0 ),
        m_DConstant ( 0.0 )
    {
    }

    TemperatureController::~TemperatureController()
    {
    }

    void TemperatureController::SetDesiredTemperature(const double &desiredTemperatureInCelcius)
    {
        m_DesiredTemperatureInCelcius = desiredTemperatureInCelcius;
    }

    double TemperatureController::Control(const double &temperatureInCelcius, const uint32_t &timeDifferenceInMillisecond)
    {
        if (false == m_bIsTemperatureValid)
        {
            m_PreviousTemperatureInCelcius = temperatureInCelcius;
            m_bIsTemperatureValid = true;
        }

        const double error = m_DesiredTemperatureInCelcius - temperatureInCelcius;
        const double previousError = m_DesiredTemperatureInCelcius - m_PreviousTemperatureInCelcius;
        const double result  = 
            (m_PConstant * error) +
            (m_IConstant * error * timeDifferenceInMillisecond) +
            (m_DConstant * ((error - previousError) / timeDifferenceInMillisecond));

        return result;
    }

    void TemperatureController::OnTemperatureFailure()
    {
        m_bIsTemperatureValid = false;
        m_PreviousTemperatureInCelcius = 0.0;
    }

} // namespace Incubator
