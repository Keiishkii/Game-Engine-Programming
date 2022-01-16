#include <map>
#include <string>

namespace Engine
{
	namespace Components { struct Component; }

	struct Entity;

	/**	The SystemIndexer class is used to give each entity and component there own unique ID's, these are used to keep track of loaded memory and also aid in fast access and destruction of each object.  	*/
	struct SystemIndexer
	{
		/**	The Type enum is used to what class type has take up a given index, this can allow for debugging memory issues if indexes arn't cleaned up.  	*/
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