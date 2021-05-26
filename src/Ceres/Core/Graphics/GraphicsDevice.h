#pragma once

#include <vector>

#include "../Common/Matrix.h"

struct SDL_Window;
struct SDL_Surface;

namespace Ceres
{
    class Context;
    class Effect;
    class VertexCollection;

    struct Vector3;

    class GraphicsDevice
    {
        public:

            GraphicsDevice();
            ~GraphicsDevice();

            void LoadCollection(VertexCollection* collection);
            void Render();
            
        private:
            void beginRender();
            void printError();
            void endRender();

            SDL_Window* createWindow();
            
            SDL_Window* _window;
            SDL_Surface* _screenSurface;

            Context* _currentContext;
            Effect* _currentEffect;

            std::vector<VertexCollection*> _vertexCollections;
    };
}