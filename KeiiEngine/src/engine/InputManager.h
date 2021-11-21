#include <memory>

namespace Engine
{
	struct Core;
	struct Inputs;
	struct InputManager
	{
		friend Core;

	private:
		std::shared_ptr<Inputs> _inputs;
	public:


	private:
		void ProcessFrameInput();
	public:
		InputManager();
		std::shared_ptr<Inputs> Input();
	};
}