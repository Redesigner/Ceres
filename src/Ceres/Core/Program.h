namespace Ceres
{
    class Game;
    class Program
    {
        public:
            Program::Program(Game* game);
            Program::~Program();

            void Program::Loop();

        private:
            bool _exit;
            Game* _game;
            void Program::handleEvents();
    };
}