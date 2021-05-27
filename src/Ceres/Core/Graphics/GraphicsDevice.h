#pragma once

#include <vector>

#include "VertexCollection.h"
#include "../Common/Matrix.h"
#include "VertexTypes/IVertexType.h"
#include "VertexTypes/VertexPosition.h"

struct SDL_Window;
struct SDL_Surface;

namespace Ceres
{
    class Context;
    class Effect;

    struct Vector3;

    class GraphicsDevice
    {
        public:

            GraphicsDevice();
            ~GraphicsDevice();

            template <typename V>
            void LoadCollection(VertexCollection<V> *collection)
            {
                _vertexCollections.push_back( (VertexCollection<IVertexType>*) collection);
            } 
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

            std::vector<VertexCollection<IVertexType>*> _vertexCollections;
    };
}