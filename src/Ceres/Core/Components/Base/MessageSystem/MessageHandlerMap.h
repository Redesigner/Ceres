#pragma once

#include "Message.h"

#include <functional>
#include <string>
#include <typeindex>
#include <unordered_map>

namespace Ceres
{
	class IComponent;
	class MessageHandlerMap
	{
		public:
			void Register(std::string message, std::function<void(IComponent*, Message&)> handler)
			{
				// Only need one lambda per component
				if (_internalMap.count(message) == 0)
				{
					_internalMap.insert(std::pair<std::string, std::function<void(IComponent*, Message&)>>(message, handler));
				}
			}

			bool Invoke(IComponent* component, Message& message) const
			{
				// Find the function associated with this message type
				auto messageHandlerFunction = _internalMap.find(message.Type);
				if (messageHandlerFunction != _internalMap.end())
				{
					messageHandlerFunction->second(component, message);
					return true;
				}
				return false;
			}
		private:
			std::unordered_map<std::string, std::function<void(IComponent*, Message&)>> _internalMap;
	};
}