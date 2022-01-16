#include <memory>

namespace Engine
{
	struct Core;
	struct Inputs;

	/**	The InputManager is used to update the current frames input from SDL2's input events.  	*/
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