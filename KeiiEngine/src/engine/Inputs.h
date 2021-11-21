#include <glm/glm.hpp>

namespace Engine
{
	struct InputManager;
	struct Inputs
	{
		friend InputManager;

	public:
		enum Keys { W, A, S, D, SPACE, LSHIFT, ESCAPE };

	private:
	// Events
		bool _SDLQuit;
	// Mouse Input
		float _relativeXPosition;
		float _relativeYPosition;
		float _scrollWheelDelta;
	// Keyboard Input
		bool _wDown, _wHeld, _wReleased;
		bool _aDown, _aHeld, _aReleased;
		bool _sDown, _sHeld, _sReleased;
		bool _dDown, _dHeld, _dReleased;
		bool _escapeDown, _escapeHeld, _escapeReleased;
		bool _spaceDown, _spaceHeld, _spaceReleased;
		bool _lshiftDown, _lshiftHeld, _lshiftReleased;
	public:


	private:
		void RefreshAtStartOfNewFrame();
	public:
		bool KeyDown(Keys key);
		bool KeyHeld(Keys key);
		bool KeyReleased(Keys key);

		glm::vec2 MousePosition();
		float MouseScrollDelta();

		bool QuitEvent();
	};
}