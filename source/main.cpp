#include "SDL2TK/Window.hpp"
#include "SDL2TK/Network/Port.hpp"
#include "SDL2TK/Network/Address128.hpp"
#include "TestModule.hpp"
#include "Rectangle.hpp"
#include <SDL_image.h>
#include <vector>
using namespace std;

void TestNetwork()
{
    auto port = SDL2TK::Port::FromHostValue(12621);

    cout << "port: " << port << endl;
    cout << "port network value: " << port.networkValue << endl;

    SDL2TK::Address128 address = {};

    cout << "address 128: " << address << endl;
}

void MyCallback(
    GLenum source,
    GLenum type,
    GLuint id,
    GLenum severity,
    GLsizei length,
    const GLchar *msg,
    const void *data)
{
    cerr << "debug call: " << msg << endl;
}

int main(int argc, char** argv)
{
    //TestNetwork();
    TestRationals();
    TestLines();
    //return 0;

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER);
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF);

    {
        /* Open the first available controller. */
        SDL_GameController *controller = NULL;
        for (int i = 0; i < SDL_NumJoysticks(); ++i)
        {
            if (SDL_IsGameController(i))
            {
                controller = SDL_GameControllerOpen(i);
                if (controller)
                {
                    break;
                }
                else
                {
                    fprintf(
                        stderr,
                        "Could not open gamecontroller %i: %s\n",
                        i,
                        SDL_GetError());
                }
            }
        }

        SDL2TK::WindowSettings settings;
        settings.Title("Wombat Cheerios");
        settings.Width(1024);
        settings.Height(768);

        SDL2TK::Window window(move(settings));
        SDL_GL_SetSwapInterval(1);

        glDebugMessageCallback(MyCallback, nullptr);

        GLint v;
        glGetIntegerv(GL_CONTEXT_FLAGS, &v);
        if (v & GL_CONTEXT_FLAG_DEBUG_BIT)
            cerr << "DEBUG MODE\n";

        TestModule module;
        window.Run(module);

        for (int i = 0; i < SDL_NumJoysticks(); ++i)
        {
            if (SDL_IsGameController(i))
            {
                SDL_GameController *controller = SDL_GameControllerOpen(i);
                if (controller)
                {
                    SDL_GameControllerClose(controller);
                }
                else
                {
                    fprintf(
                        stderr,
                        "Could not open gamecontroller %i: %s\n",
                        i,
                        SDL_GetError());
                }
            }
        }
    }

    IMG_Quit();
    SDL_Quit();
    return 0;
}
