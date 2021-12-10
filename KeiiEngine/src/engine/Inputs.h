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
			SPACE, LSHIFT, ESCAPE 
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