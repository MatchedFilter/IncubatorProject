#ifndef INCUBATOR_ASCREEN_H
#define INCUBATOR_ASCREEN_H
#include "Incubator/View/JoystickEvent.h"
#include "EnumScreenType.h"
namespace Incubator
{
    class AScreen
    {
    public:
        inline AScreen(const EnumScreenType screenType) : m_ScreenType { screenType } { }
        inline virtual ~AScreen() { }
        inline EnumScreenType GetScreenType()const  { return m_ScreenType; }
        virtual void OnUserAction(const JoystickEvent event) = 0;
        virtual void Run() = 0;

    private:
        EnumScreenType m_ScreenType;
    };
} // namespace Incubator

#endif // INCUBATOR_ASCREEN_H