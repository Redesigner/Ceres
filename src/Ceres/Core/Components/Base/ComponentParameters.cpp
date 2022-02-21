#include "ComponentParameters.h"

#include <fmt/core.h>

namespace Ceres
{
	ComponentParams::ComponentParams(size_t size)
	{
		// fmt::print("Component Params created with size {}\n", size);
		_rawData = new char[size];
		memset(_rawData, 'x', size);
		_size = size;
	}

	ComponentParams::~ComponentParams()
	{
		// fmt::print("Component Params deleted with size {}\n", _size);
		delete[] _rawData;
	}

	int ComponentParams::Count() const
	{
		return _paramLocations.size();
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