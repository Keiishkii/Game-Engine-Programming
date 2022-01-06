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
				case SDLK_a:
					_inputs->_aDown = true;
					_inputs->_aHeld = true;
					break;
				case SDLK_b:
					_inputs->_bDown = true;
					_inputs->_bHeld = true;
					break;
				case SDLK_c:
					_inputs->_cDown = true;
					_inputs->_cHeld = true;
					break;
				case SDLK_d:
					_inputs->_dDown = true;
					_inputs->_dHeld = true;
					break;
				case SDLK_e:
					_inputs->_eDown = true;
					_inputs->_eHeld = true;
					break;
				case SDLK_f:
					_inputs->_fDown = true;
					_inputs->_fHeld = true;
					break;
				case SDLK_g:
					_inputs->_gDown = true;
					_inputs->_gHeld = true;
					break;
				case SDLK_h:
					_inputs->_hDown = true;
					_inputs->_hHeld = true;
					break;
				case SDLK_i:
					_inputs->_iDown = true;
					_inputs->_iHeld = true;
					break;
				case SDLK_j:
					_inputs->_jDown = true;
					_inputs->_jHeld = true;
					break;
				case SDLK_k:
					_inputs->_kDown = true;
					_inputs->_kHeld = true;
					break;
				case SDLK_l:
					_inputs->_lDown = true;
					_inputs->_lHeld = true;
					break;
				case SDLK_m:
					_inputs->_mDown = true;
					_inputs->_mHeld = true;
					break;
				case SDLK_n:
					_inputs->_nDown = true;
					_inputs->_nHeld = true;
					break;
				case SDLK_o:
					_inputs->_oDown = true;
					_inputs->_oHeld = true;
					break;
				case SDLK_p:
					_inputs->_pDown = true;
					_inputs->_pHeld = true;
					break;
				case SDLK_q:
					_inputs->_qDown = true;
					_inputs->_qHeld = true;
					break;
				case SDLK_r:
					_inputs->_rDown = true;
					_inputs->_rHeld = true;
					break;
				case SDLK_s:
					_inputs->_sDown = true;
					_inputs->_sHeld = true;
					break;
				case SDLK_t:
					_inputs->_tDown = true;
					_inputs->_tHeld = true;
					break;
				case SDLK_u:
					_inputs->_uDown = true;
					_inputs->_uHeld = true;
					break;
				case SDLK_v:
					_inputs->_vDown = true;
					_inputs->_vHeld = true;
					break;
				case SDLK_w:
					_inputs->_wDown = true;
					_inputs->_wHeld = true;
					break;
				case SDLK_x:
					_inputs->_xDown = true;
					_inputs->_xHeld = true;
					break;
				case SDLK_y:
					_inputs->_yDown = true;
					_inputs->_yHeld = true;
					break;
				case SDLK_z:
					_inputs->_zDown = true;
					_inputs->_zHeld = true;
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
					_inputs->_lShiftDown = true;
					_inputs->_lShiftHeld = true;
					break;
				case SDLK_LCTRL:
					_inputs->_lControlDown = true;
					_inputs->_lControlHeld = true;
					break;
				}
				break;
			case SDL_KEYUP:
				switch (event.key.keysym.sym)
				{
				case SDLK_a:
					_inputs->_aReleased = true;
					_inputs->_aHeld = false;
					break;
				case SDLK_b:
					_inputs->_bReleased = true;
					_inputs->_bHeld = false;
					break;
				case SDLK_c:
					_inputs->_cReleased = true;
					_inputs->_cHeld = false;
					break;
				case SDLK_d:
					_inputs->_dReleased = true;
					_inputs->_dHeld = false;
					break;
				case SDLK_e:
					_inputs->_eReleased = true;
					_inputs->_eHeld = false;
					break;
				case SDLK_f:
					_inputs->_fReleased = true;
					_inputs->_fHeld = false;
					break;
				case SDLK_g:
					_inputs->_gReleased = true;
					_inputs->_gHeld = false;
					break;
				case SDLK_h:
					_inputs->_hReleased = true;
					_inputs->_hHeld = false;
					break;
				case SDLK_i:
					_inputs->_iReleased = true;
					_inputs->_iHeld = false;
					break;
				case SDLK_j:
					_inputs->_jReleased = true;
					_inputs->_jHeld = false;
					break;
				case SDLK_k:
					_inputs->_kReleased = true;
					_inputs->_kHeld = false;
					break;
				case SDLK_l:
					_inputs->_lReleased = true;
					_inputs->_lHeld = false;
					break;
				case SDLK_m:
					_inputs->_mReleased = true;
					_inputs->_mHeld = false;
					break;
				case SDLK_n:
					_inputs->_nReleased = true;
					_inputs->_nHeld = false;
					break;
				case SDLK_o:
					_inputs->_oReleased = true;
					_inputs->_oHeld = false;
					break;
				case SDLK_p:
					_inputs->_pReleased = true;
					_inputs->_pHeld = false;
					break;
				case SDLK_q:
					_inputs->_qReleased = true;
					_inputs->_qHeld = false;
					break;
				case SDLK_r:
					_inputs->_rReleased = true;
					_inputs->_rHeld = false;
					break;
				case SDLK_s:
					_inputs->_sReleased = true;
					_inputs->_sHeld = false;
					break;
				case SDLK_t:
					_inputs->_tReleased = true;
					_inputs->_tHeld = false;
					break;
				case SDLK_u:
					_inputs->_uReleased = true;
					_inputs->_uHeld = false;
					break;
				case SDLK_v:
					_inputs->_vReleased = true;
					_inputs->_vHeld = false;
					break;
				case SDLK_w:
					_inputs->_wReleased = true;
					_inputs->_wHeld = false;
					break;
				case SDLK_x:
					_inputs->_xReleased = true;
					_inputs->_xHeld = false;
					break;
				case SDLK_y:
					_inputs->_yReleased = true;
					_inputs->_yHeld = false;
					break;
				case SDLK_z:
					_inputs->_zReleased = true;
					_inputs->_zHeld = false;
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
					_inputs->_lShiftReleased = true;
					_inputs->_lShiftHeld = false;
					break;
				case SDLK_LCTRL:
					_inputs->_lControlReleased = true;
					_inputs->_lControlHeld = false;
					break;
				}
				break;
			}
		}
	}

	std::shared_ptr<Inputs> InputManager::Input() { return _inputs; }
}