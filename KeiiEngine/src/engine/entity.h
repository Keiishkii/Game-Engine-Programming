#include <vector>
#include <memory>

#include "Entity.cpp"



namespace Engine
{
	class Entity
	{
	private:
		std::vector<std::shared_ptr<Entity>> _entityList;
	public:

	};
}