#include "MessageHandlerMap.h"
#include "Message.h"

#include <unordered_map>
#include <typeindex>

namespace Ceres
{
	class MessageSystem
	{
		public:
			static void RegisterComponent(std::type_index componentType);

			static void RegisterHandler(std::string messageType, std::type_index componentType, std::function<void(IComponent*, Message&)> handler);

			static const MessageHandlerMap& GetHandler(std::type_index componentType);

			static std::unordered_map<std::type_index, MessageHandlerMap> _componentClassHandlers;
	};
}