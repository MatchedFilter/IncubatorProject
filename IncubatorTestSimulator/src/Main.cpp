#include "IncubatorTestSimulator.h"
#include "Incubator/IncubatorApp.h"
#include <SDL2/SDL.h>
#include <thread>

#ifndef INCUBATOR_SOFTWARE_VERSION
#define INCUBATOR_SOFTWARE_VERSION "Hata"
#endif // INCUBATOR_SOFTWARE_VERSION

const char *INCUBATOR_VERSION = INCUBATOR_SOFTWARE_VERSION;

namespace IncubatorSim
{
    IncubatorTestSimulator g_IncubatorTestSimulator;
    static Incubator::IncubatorApp s_IncubatorApp;
    static bool s_bApplicationRunning = true;

    static void RunIncubatorApp();

    static void RunIncubatorApp()
    {
        while (s_bApplicationRunning)
        {
            s_IncubatorApp.Run();
        }
    }
} // namespace IncubatorSim

int main(int argc, char *argv[])
{
    IncubatorSim::g_IncubatorTestSimulator.Initialize();
    IncubatorSim::s_IncubatorApp.Initialize();
    std::thread incubatorThread = std::thread(IncubatorSim::RunIncubatorApp);
    while (IncubatorSim::s_bApplicationRunning)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                IncubatorSim::s_bApplicationRunning = false;
            }
            else
            {
                IncubatorSim::g_IncubatorTestSimulator.HandleEvents(event);
            }
        }
        IncubatorSim::g_IncubatorTestSimulator.Run();
    }
    incubatorThread.join();
    return 0;
}