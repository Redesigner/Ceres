namespace Ceres
{
    class Game;
    class MainHandler
    {
        public:
            MainHandler::MainHandler(Game* game);
            MainHandler::~MainHandler();

            void MainHandler::Loop();

        private:
            bool _exit;
            Game* _game;
            void MainHandler::handleEvents();
    };
}