#pragma once

#include <memory>
#include <vector>

#include "Mesh.h"
#include "VertexTypes/IVertexType.h"
#include "../Common/Matrix.h"

struct SDL_Window;
struct SDL_Surface;

namespace Ceres
{
    class Context;
    class Effect;

    struct Vector3;

    using EffectPtr = std::shared_ptr<Effect>;
    using MeshPtr = std::shared_ptr<Mesh>;

    class GraphicsDevice
    {
        public:

            GraphicsDevice();
            ~GraphicsDevice();

            void Render();

            EffectPtr LoadEffect(const char* vertexShaderName, const char* fragmentShaderName);
            MeshPtr LoadMesh(IVertexType vertexData[], const IVertexLayout& vertexLayout, int vertexCount, unsigned int indices[], int indexCount);
            
        private:
            void beginRender();
            void endRender();
            void printError();

            void unloadEffects();
            void unloadMeshes();

            SDL_Window* createWindow();
            
            SDL_Window* _window;
            SDL_Surface* _screenSurface;

            Context* _currentContext;
            EffectPtr _currentEffect;
            Matrix _defaultModelMatrix;

            std::vector<EffectPtr> _loadedEffects;
            std::vector<MeshPtr> _loadedMeshes;
    };
}