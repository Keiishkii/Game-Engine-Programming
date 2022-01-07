#include <vector>

namespace Engine
{
	namespace Components { struct Component; }

	struct Entity;

	struct SystemIndexer
	{
		friend Entity;
		friend Components::Component;

	private:
		std::vector<unsigned int> _activeIndexes;
		std::vector<unsigned int>::iterator _indexIterator;
	public:


	private:
		unsigned int GetIndex();
		void ReturnIndex(unsigned int index);
	public:
		SystemIndexer();
	};
}