#include <SDL.h>

#include "InputManager.h"
#include "Inputs.h"

namespace Engine
{
	InputManager::InputManager()
	{
		_inputs = std::make_shared<Inputs>();
	}

	void InputManager::ProcessFrameInput()
	{
		SDL_Event event = { 0 };

		_inputs->RefreshAtStartOfNewFrame();
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_MOUSEMOTION:
				_inputs->_relativeXPosition = event.motion.xrel;
				_inputs->_relativeYPosition = event.motion.yrel;
				break;
			case SDL_MOUSEWHEEL:
				_inputs->_scrollWheelDelta = event.wheel.y;
				break;
			case SDL_QUIT:
				_inputs->_SDLQuit = true;
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
				case SDLK_w:
					_inputs->_wDown = true;
					_inputs->_wHeld = true;
					break;
				case SDLK_a:
					_inputs->_aDown = true;
					_inputs->_aHeld = true;
					break;
				case SDLK_s:
					_inputs->_sDown = true;
					_inputs->_sHeld = true;
					break;
				case SDLK_d:
					_inputs->_dDown = true;
					_inputs->_dHeld = true;
					break;
				case SDLK_ESCAPE:
					_inputs->_escapeDown = true;
					_inputs->_escapeHeld = true;
					break;
				case SDLK_SPACE:
					_inputs->_spaceDown = true;
					_inputs->_spaceHeld = true;
					break;
				case SDLK_LSHIFT:
					_inputs->_lshiftDown = true;
					_inputs->_lshiftHeld = true;
					break;
				}
				break;
			case SDL_KEYUP:
				switch (event.key.keysym.sym)
				{
				case SDLK_w:
					_inputs->_wReleased = true;
					_inputs->_wHeld = false;
					break;
				case SDLK_a:
					_inputs->_aReleased = true;
					_inputs->_aHeld = false;
					break;
				case SDLK_s:
					_inputs->_sReleased = true;
					_inputs->_sHeld = false;
					break;
				case SDLK_d:
					_inputs->_dReleased = true;
					_inputs->_dHeld = false;
					break;
				case SDLK_ESCAPE:
					_inputs->_escapeReleased = true;
					_inputs->_escapeHeld = false;
					break;
				case SDLK_SPACE:
					_inputs->_spaceReleased = true;
					_inputs->_spaceHeld = false;
					break;
				case SDLK_LSHIFT:
					_inputs->_lshiftReleased = true;
					_inputs->_lshiftHeld = false;
					break;
				}
				break;
			}
		}
	}

	std::shared_ptr<Inputs> InputManager::Input() { return _inputs; }
}