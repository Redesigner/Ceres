#pragma once

struct SDL_Window;

namespace Ceres
{
    class Window
    {
        public:
            Window();
            ~Window();

            SDL_Window* Get() const;

            void Resize(const int width, const int height);
            void SwapBuffer() const;
            void ToggleFullscreen();
            void Maximize();
            void ResizeViewport();

        private:
            SDL_Window* _sdlWindow;

            unsigned int _width = 1280;
            unsigned int _height = 720;
    };
}