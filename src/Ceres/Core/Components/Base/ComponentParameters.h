#pragma once

#include <memory>
#include <numeric>
#include <vector>
#include <string>
#include <exception>
#include <typeindex>
#include <typeinfo>

namespace Ceres
{
    struct ComponentParams
    {
        public:
			ComponentParams();
            ComponentParams(size_t count);
            ~ComponentParams();

            template <typename... Ts>
            static std::unique_ptr<ComponentParams> WriteParams(Ts... args)
			{
				size_t data[] = {sizeof(Ts)...};
        		size_t size = std::accumulate(std::begin(data), std::end(data), size_t(0));
				std::unique_ptr<ComponentParams> params = std::unique_ptr<ComponentParams>(new ComponentParams(size));
				params->WriteParam(0, args...);
				return params;
			}

			static std::unique_ptr<ComponentParams> Empty();

			template <typename T, typename... Ts>
			void WriteParam(int offset, T first, Ts&... args)
			{
				memcpy(_rawData + offset, &first, sizeof(T));
				_paramLocations.push_back(offset);
				_paramTypes.push_back(std::type_index(typeid(T)) );
				WriteParam(offset + sizeof(T), args...);
			}

			void WriteParam(int offset)
			{
			}

			template <typename T>
			T& Get(int index) const
			{
				if (_paramTypes.at(index) == std::type_index(typeid(T)) )
				{
					return *reinterpret_cast<T*>(_rawData + _paramLocations.at(index));
				}
				throw std::invalid_argument("The type of the requested parameter does not match the supplied type.");
			}

			int Count() const;

			std::string ToString() const;

        private:
			unsigned int _size;
            char* _rawData = nullptr;
            std::vector<std::type_index> _paramTypes;
            std::vector<int> _paramLocations;
    };
}