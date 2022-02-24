#include "ComponentParameters.h"

#include <fmt/core.h>

namespace Ceres
{
	ComponentParams::ComponentParams()
	{
		_size = 0;
	}
	ComponentParams::ComponentParams(size_t size)
	{
		_rawData = new char[size];
		memset(_rawData, 'x', size);
		_size = size;
	}

	ComponentParams::~ComponentParams()
	{
		if (_rawData)
		{
			delete[] _rawData;
		}
	}

	int ComponentParams::Count() const
	{
		return _paramLocations.size();
	}

	std::unique_ptr<ComponentParams> ComponentParams::Empty()
	{
		return std::unique_ptr<ComponentParams>(new ComponentParams());
	}

	std::string ComponentParams::ToString() const
	{
		std::string string = "";
		for(int i = 0; i < _paramTypes.size(); i++)
		{
			string.append(fmt::format("{} | {}, ", _paramLocations[i], _paramTypes[i].name()));
		}
		return string;
	}
}