#include <memory>
#include <vector>


namespace Engine
{
	struct Component;
	struct Entity
	{
	private:
		std::vector<std::shared_ptr<Component>> componentList;

	public:
		std::shared_ptr<Component> AddComponent();
	};
}