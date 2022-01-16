#include <glm/glm.hpp>

namespace Engine
{
	struct InputManager;
	struct Inputs
	{
		friend InputManager;

	public:
		enum Keys 
		{ 
			A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z, 
			k0, k1, k2, k3, k4, k5, k6, k7, k8, k9,
			SPACE, LSHIFT, LCNTRL, ESCAPE 
		};

	private:
	// Events
		bool _SDLQuit;

	// Mouse Input
		float _relativeXPosition;
		float _relativeYPosition;
		float _scrollWheelDelta;

	// Keyboard Input
		bool _aDown, _aHeld, _aReleased;
		bool _bDown, _bHeld, _bReleased;
		bool _cDown, _cHeld, _cReleased;
		bool _dDown, _dHeld, _dReleased;
		bool _eDown, _eHeld, _eReleased;
		bool _fDown, _fHeld, _fReleased;
		bool _gDown, _gHeld, _gReleased;
		bool _hDown, _hHeld, _hReleased;
		bool _iDown, _iHeld, _iReleased;
		bool _jDown, _jHeld, _jReleased;
		bool _kDown, _kHeld, _kReleased;
		bool _lDown, _lHeld, _lReleased;
		bool _mDown, _mHeld, _mReleased;
		bool _nDown, _nHeld, _nReleased;
		bool _oDown, _oHeld, _oReleased;
		bool _pDown, _pHeld, _pReleased;
		bool _qDown, _qHeld, _qReleased;
		bool _rDown, _rHeld, _rReleased;
		bool _sDown, _sHeld, _sReleased;
		bool _tDown, _tHeld, _tReleased;
		bool _uDown, _uHeld, _uReleased;
		bool _vDown, _vHeld, _vReleased;
		bool _wDown, _wHeld, _wReleased;
		bool _xDown, _xHeld, _xReleased;
		bool _yDown, _yHeld, _yReleased;
		bool _zDown, _zHeld, _zReleased;

		bool _0Down, _0Held, _0Released;
		bool _1Down, _1Held, _1Released;
		bool _2Down, _2Held, _2Released;
		bool _3Down, _3Held, _3Released;
		bool _4Down, _4Held, _4Released;
		bool _5Down, _5Held, _5Released;
		bool _6Down, _6Held, _6Released;
		bool _7Down, _7Held, _7Released;
		bool _8Down, _8Held, _8Released;
		bool _9Down, _9Held, _9Released;

		bool _escapeDown, _escapeHeld, _escapeReleased;
		bool _spaceDown, _spaceHeld, _spaceReleased;
		bool _lShiftDown, _lShiftHeld, _lShiftReleased;
		bool _lControlDown, _lControlHeld, _lControlReleased;
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