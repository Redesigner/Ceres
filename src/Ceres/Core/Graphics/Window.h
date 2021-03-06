#pragma once

#include "../Common/Vector2.h"

struct SDL_Window;

namespace Ceres
{
    class Window
    {
        public:
            Window();
            ~Window();

            SDL_Window* Get() const;

            void Lock();
            void Unlock();

            void Resize(const int width, const int height);
            void SwapBuffer() const;
            void ToggleFullscreen();
            void Maximize();
            void ResizeViewport();
            
            Vector2 GetViewportSize() const; 

        private:
            SDL_Window* _sdlWindow = nullptr;
            unsigned int _width = 1280;
            unsigned int _height = 720;

            unsigned int _restoreWidth = 1280;
            unsigned int _restoreHeight = 720;
    };
}