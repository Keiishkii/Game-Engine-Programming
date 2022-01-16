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
		_aDown = false, _aReleased = false;
		_bDown = false, _bReleased = false;
		_cDown = false, _cReleased = false;
		_dDown = false, _dReleased = false;
		_eDown = false, _eReleased = false;
		_fDown = false, _fReleased = false;
		_gDown = false, _gReleased = false;
		_hDown = false, _hReleased = false;
		_iDown = false, _iReleased = false;
		_jDown = false, _jReleased = false;
		_kDown = false, _kReleased = false;
		_lDown = false, _lReleased = false;
		_mDown = false, _mReleased = false;
		_nDown = false, _nReleased = false;
		_oDown = false, _oReleased = false;
		_pDown = false, _pReleased = false;
		_qDown = false, _qReleased = false;
		_rDown = false, _rReleased = false;
		_sDown = false, _sReleased = false;
		_tDown = false, _tReleased = false;
		_uDown = false, _uReleased = false;
		_vDown = false, _vReleased = false;
		_wDown = false, _wReleased = false;
		_xDown = false, _xReleased = false;
		_yDown = false, _yReleased = false;
		_zDown = false, _zReleased = false;

		_0Down = false, _0Released = false;
		_1Down = false, _1Released = false;
		_2Down = false, _2Released = false;
		_3Down = false, _3Released = false;
		_4Down = false, _4Released = false;
		_5Down = false, _5Released = false;
		_6Down = false, _6Released = false;
		_7Down = false, _7Released = false;
		_8Down = false, _8Released = false;
		_9Down = false, _9Released = false;

		_escapeDown = false, _escapeReleased = false;
		_spaceDown = false, _spaceReleased = false;
		_lShiftDown = false, _lShiftReleased = false;	
		_lControlDown = false, _lControlReleased = false;
	}

	bool Inputs::KeyDown(Keys key)
	{
		bool result = false;
		switch (key)
		{
			// Letters
			case A:
			{
				result = _aDown;
			} break;
			case B:
			{
				result = _bDown;
			} break;
			case C:
			{
				result = _cDown;
			} break;
			case D:
			{
				result = _dDown;
			} break;
			case E:
			{
				result = _eDown;
			} break;
			case F:
			{
				result = _fDown;
			} break;
			case G:
			{
				result = _gDown;
			} break;
			case H:
			{
				result = _hDown;
			} break;
			case I:
			{
				result = _iDown;
			} break;
			case J:
			{
				result = _jDown;
			} break;
			case K:
			{
				result = _kDown;
			} break;
			case L:
			{
				result = _lDown;
			} break;
			case M:
			{
				result = _mDown;
			} break;
			case N:
			{
				result = _nDown;
			} break;
			case O:
			{
				result = _oDown;
			} break;
			case P:
			{
				result = _pDown;
			} break;
			case Q:
			{
				result = _qDown;
			} break;
			case R:
			{
				result = _rDown;
			} break;
			case S:
			{
				result = _sDown;
			} break;
			case T:
			{
				result = _tDown;
			} break;
			case U:
			{
				result = _uDown;
			} break;
			case V:
			{
				result = _vDown;
			} break;
			case W:
			{
				result = _wDown;
			} break;
			case X:
			{
				result = _xDown;
			} break;
			case Y:
			{
				result = _yDown;
			} break;
			case Z:
			{
				result = _zDown;
			} break;
			// Numbers
			case k0:
			{
				result = _0Down;
			} break;
			case k1:
			{
				result = _1Down;
			} break;
			case k2:
			{
				result = _2Down;
			} break;
			case k3:
			{
				result = _3Down;
			} break;
			case k4:
			{
				result = _4Down;
			} break;
			case k5:
			{
				result = _5Down;
			} break;
			case k6:
			{
				result = _6Down;
			} break;
			case k7:
			{
				result = _7Down;
			} break;
			case k8:
			{
				result = _8Down;
			} break;
			case k9:
			{
				result = _9Down;
			} break;
			// Special Keys
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
				result = _lShiftDown;
			} break;
			case LCNTRL:
			{
				result = _lControlDown;
			} break;
		}

		return result;
	}

	bool Inputs::KeyHeld(Keys key)
	{		
		bool result = false;
		switch (key)
		{
			// Letters
			case A:
			{
				result = _aHeld;
			} break;
			case B:
			{
				result = _bHeld;
			} break;
			case C:
			{
				result = _cHeld;
			} break;
			case D:
			{
				result = _dHeld;
			} break;
			case E:
			{
				result = _eHeld;
			} break;
			case F:
			{
				result = _fDown;
			} break;
			case G:
			{
				result = _gDown;
			} break;
			case H:
			{
				result = _hHeld;
			} break;
			case I:
			{
				result = _iHeld;
			} break;
			case J:
			{
				result = _jHeld;
			} break;
			case K:
			{
				result = _kHeld;
			} break;
			case L:
			{
				result = _lHeld;
			} break;
			case M:
			{
				result = _mHeld;
			} break;
			case N:
			{
				result = _nHeld;
			} break;
			case O:
			{
				result = _oHeld;
			} break;
			case P:
			{
				result = _pHeld;
			} break;
			case Q:
			{
				result = _qHeld;
			} break;
			case R:
			{
				result = _rHeld;
			} break;
			case S:
			{
				result = _sHeld;
			} break;
			case T:
			{
				result = _tHeld;
			} break;
			case U:
			{
				result = _uHeld;
			} break;
			case V:
			{
				result = _vHeld;
			} break;
			case W:
			{
				result = _wHeld;
			} break;
			case X:
			{
				result = _xHeld;
			} break;
			case Y:
			{
				result = _yHeld;
			} break;
			case Z:
			{
				result = _zHeld;
			} break;
			// Numbers
			case k0:
			{
				result = _0Held;
			} break;
			case k1:
			{
				result = _1Held;
			} break;
			case k2:
			{
				result = _2Held;
			} break;
			case k3:
			{
				result = _3Held;
			} break;
			case k4:
			{
				result = _4Held;
			} break;
			case k5:
			{
				result = _5Held;
			} break;
			case k6:
			{
				result = _6Held;
			} break;
			case k7:
			{
				result = _7Held;
			} break;
			case k8:
			{
				result = _8Held;
			} break;
			case k9:
			{
				result = _9Held;
			} break;
			// Special Keys
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
				result = _lShiftHeld;
			} break;
			case LCNTRL:
			{
				result = _lControlHeld;
			} break;
		}

		return result;
	}

	bool Inputs::KeyReleased(Keys key)
	{
		bool result = false;
		switch (key)
		{
			//Letters
			case A:
			{
				result = _aReleased;
			} break;
			case B:
			{
				result = _bReleased;
			} break;
			case C:
			{
				result = _cReleased;
			} break;
			case D:
			{
				result = _dReleased;
			} break;
			case E:
			{
				result = _eReleased;
			} break;
			case F:
			{
				result = _fReleased;
			} break;
			case G:
			{
				result = _gReleased;
			} break;
			case H:
			{
				result = _hReleased;
			} break;
			case I:
			{
				result = _iReleased;
			} break;
			case J:
			{
				result = _jReleased;
			} break;
			case K:
			{
				result = _kReleased;
			} break;
			case L:
			{
				result = _lReleased;
			} break;
			case M:
			{
				result = _mReleased;
			} break;
			case N:
			{
				result = _nReleased;
			} break;
			case O:
			{
				result = _oReleased;
			} break;
			case P:
			{
				result = _pReleased;
			} break;
			case Q:
			{
				result = _qReleased;
			} break;
			case R:
			{
				result = _rReleased;
			} break;
			case S:
			{
				result = _sReleased;
			} break;
			case T:
			{
				result = _tReleased;
			} break;
			case U:
			{
				result = _uReleased;
			} break;
			case V:
			{
				result = _vReleased;
			} break;
			case W:
			{
				result = _wReleased;
			} break;
			case X:
			{
				result = _xReleased;
			} break;
			case Y:
			{
				result = _yReleased;
			} break;
			case Z:
			{
				result = _zReleased;
			} break;
			// Numbers
			case k0:
			{
				result = _0Released;
			} break;
			case k1:
			{
				result = _1Released;
			} break;
			case k2:
			{
				result = _2Released;
			} break;
			case k3:
			{
				result = _3Released;
			} break;
			case k4:
			{
				result = _4Released;
			} break;
			case k5:
			{
				result = _5Released;
			} break;
			case k6:
			{
				result = _6Released;
			} break;
			case k7:
			{
				result = _7Released;
			} break;
			case k8:
			{
				result = _8Released;
			} break;
			case k9:
			{
				result = _9Released;
			} break;
			// Special Keys
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
				result = _lShiftReleased;
			} break;
			case LCNTRL:
			{
				result = _lControlReleased;
			} break;
		}

		return result;
	}

	glm::vec2 Inputs::MousePosition() { return glm::vec2(_relativeXPosition, _relativeYPosition); }
	float Inputs::MouseScrollDelta() { return _scrollWheelDelta; }
	bool Inputs::QuitEvent() { return _SDLQuit; }
}