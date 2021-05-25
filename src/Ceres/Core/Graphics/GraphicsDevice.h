#pragma once

#include <vector>

struct SDL_Window;
struct SDL_Surface;

namespace Ceres
{
    class Context;
    class Effect;
    class VertexBufferObject;

    struct Vector3;

    class GraphicsDevice
    {
        public:

            GraphicsDevice();
            ~GraphicsDevice();

            void LoadVertices(std::vector<Vector3> vertices);
            void Render();
            
        private:
            void printError();
            SDL_Window* createWindow();
            
            SDL_Window* _window;
            SDL_Surface* _screenSurface;

            Context* _currentContext;
            VertexBufferObject* _currentVBO;
            Effect* _currentEffect;
    };
}