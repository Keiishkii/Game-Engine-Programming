#include <map>
#include <string>

namespace Engine
{
	namespace Components { struct Component; }

	struct Entity;

	struct SystemIndexer
	{
		enum Type { E_COMPONENT, E_ENTITY };

		friend Entity;
		friend Components::Component;

	private:
		std::map<unsigned int, Type> _activeIndexes;
	public:


	private:
		unsigned int GetIndex(Type type);
		void ReturnIndex(unsigned int index);

		std::string TypeToString(Type type);
	public:
	};
}