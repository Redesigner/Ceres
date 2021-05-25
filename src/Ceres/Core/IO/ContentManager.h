#include <string>

namespace Ceres
{
    class ContentManager
    {
        public:
            ContentManager();
            ~ContentManager();
            static const std::string LoadString(const char* filename);
        private:            
    };
}