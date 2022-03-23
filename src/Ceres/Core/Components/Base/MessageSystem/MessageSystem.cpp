#include "MessageSystem.h"

namespace Ceres
{
	using MapType = std::unordered_map<std::type_index, MessageHandlerMap>;
	MapType MessageSystem::_componentClassHandlers = MapType();

	void MessageSystem::RegisterComponent(std::type_index componentType)
	{
		if (_componentClassHandlers.count(componentType) == 0)
		{
			_componentClassHandlers.insert(std::pair<std::type_index, MessageHandlerMap>(componentType, MessageHandlerMap()) );
		}
	}

	void MessageSystem::RegisterHandler(std::string messageType, std::type_index componentType, std::function<void(IComponent*, Message&)> handler)
	{
		auto handlerMap = _componentClassHandlers.find(componentType);
		if (handlerMap != _componentClassHandlers.end())
		{
			handlerMap->second.Register(messageType, handler);
		}
	}

	const MessageHandlerMap& MessageSystem::GetHandler(std::type_index componentType)
	{
		return _componentClassHandlers.find(componentType)->second;
	}

}