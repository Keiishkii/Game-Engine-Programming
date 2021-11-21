#include "Inputs.h"
#include "InputManager.h"

namespace Engine
{
	void Inputs::RefreshAtStartOfNewFrame()
	{
		// - [Events] -
		_SDLQuit = false;

		// - [Mouse Input] -
		_relativeXPosition = 0;
		_relativeYPosition = 0;
		_scrollWheelDelta = 0;

		// - [Keyboard Input] - 
		_wDown = false, _wReleased = false;
		_aDown = false, _aReleased = false;
		_sDown = false, _sReleased = false;
		_dDown = false, _dReleased = false;
		_escapeDown = false, _escapeReleased = false;
		_spaceDown = false, _spaceReleased = false;
		_lshiftDown = false, _lshiftReleased = false;	
	}

	bool Inputs::KeyDown(Keys key)
	{
		bool result = false;
		switch (key)
		{
			case W:
			{
				result = _wDown;
			} break;
			case A:
			{
				result = _aDown;
			} break;
			case S:
			{
				result = _sDown;
			} break;
			case D:
			{
				result = _dDown;
			} break;
			case ESCAPE:
			{
				result = _escapeDown;
			} break;
			case SPACE:
			{
				result = _spaceDown;
			} break;
			case LSHIFT:
			{
				result = _lshiftDown;
			} break;
		}

		return result;
	}

	bool Inputs::KeyHeld(Keys key)
	{		
		bool result = false;
		switch (key)
		{
			case W:
			{
				result = _wHeld;
			} break;
			case A:
			{
				result = _aHeld;
			} break;
			case S:
			{
				result = _sHeld;
			} break;
			case D:
			{
				result = _dHeld;
			} break;
			case ESCAPE:
			{
				result = _escapeHeld;
			} break;
			case SPACE:
			{
				result = _spaceHeld;
			} break;
			case LSHIFT:
			{
				result = _lshiftHeld;
			} break;
		}

		return result;
	}

	bool Inputs::KeyReleased(Keys key)
	{
		bool result = false;
		switch (key)
		{
			case W:
			{
				result = _wReleased;
			} break;
			case A:
			{
				result = _aReleased;
			} break;
			case S:
			{
				result = _sReleased;
			} break;
			case D:
			{
				result = _dReleased;
			} break;
			case ESCAPE:
			{
				result = _escapeReleased;
			} break;
			case SPACE:
			{
				result = _spaceReleased;
			} break;
			case LSHIFT:
			{
				result = _lshiftReleased;
			} break;
		}

		return result;
	}

	glm::vec2 Inputs::MousePosition() { return glm::vec2(_relativeXPosition, _relativeYPosition); }
	float Inputs::MouseScrollDelta() { return _scrollWheelDelta; }
	bool Inputs::QuitEvent() { return _SDLQuit; }
}