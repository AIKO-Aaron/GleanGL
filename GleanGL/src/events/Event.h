#pragma once

#ifdef __APPLE__

#define IMPLEMENTED_KEYS 0x80
typedef void* __internalEvent;

#elif defined(_WIN32)

#  include <Windows.h>
#  define IMPLEMENTED_KEYS 0xFF
typedef MSG __internalEvent;

#else

#endif

namespace Glean {
	namespace events {
		
		enum EventType {
			UNKNOWN = 0,
			KEYDOWN,
			KEYUP,
			MOUSEMOTION,
			MOUSEDOWN,
			MOUSEUP
		};
        
        enum Key {
            kUnknown = 0,
            kA, kB, kC, kD, kE, kF, kG, kH, kI, kJ, kK, kL, kM, kN, kO, kP, kQ, kR, kS, kT, kU, kV, kW, kX, kY, kZ,
            k0, k1, k2, k3, k4, k5, k6, k7, k8, k9,
            kNP0, kNP1,  kNP2, kNP3, kNP4, kNP5, kNP6, kNP7, kNP8, kNP9,
			kCOMMA, kPERIOD, kMINUS, kPLUS,
            kUP, kDOWN, kLEFT, kRIGHT,
            kSPACE, kTAB, kENTER, kESCAPE,
			kF1, kF2, kF3, kF4, kF5, kF6, kF7, kF8, kF9, kF10, kF11, kF12, kF13, kF14, kF15
        };
        
        
#ifdef __APPLE__
#  define vCtrlSys vCommand
#else
#  define vCtrlSys vCtrl
#endif
        
        // Definitions of Events that the user can receive
        
		struct KeyEvent; struct MouseMotionEvent;
        
		typedef struct {
			EventType type;
            
            inline KeyEvent* asKeyEvent() { return type == KEYUP || type == KEYDOWN ? (KeyEvent*) this : nullptr; }
			inline MouseMotionEvent* asMouseMotionEvent() { return type == MOUSEMOTION ? (MouseMotionEvent*)this : nullptr; }
		} Event;
        
        typedef struct KeyEvent : Event {
            Key key;
            
            bool isShiftDown = false;
            bool isControlDown = false;
            bool isAltDown = false;
            bool isCapsLockOn = false;
            bool isHelpDown = false;
            bool isFunctionDown = false;
            bool isCommandDown = false;
            
#ifdef __APPLE__
            inline bool isPlatformCtrlDown() { return isCommandDown; }
#else
            inline bool isPlatformCtrlDown() { return isControlDown; }
#endif
        } KeyEvent;
     
		struct MouseMotionEvent : Event {
            signed int xPos, yPos;
            signed int dx, dy;

			bool isLeftMousePressed = false;
			bool isMiddleMousePressed = false;
			bool isRightMousePressed = false;
		};

		//
		// Actual platform specific definitions
		//

		extern unsigned int mouseX, mouseY;

		extern char getCharFromKey(Key keycode);
		extern Event *translateEvent(__internalEvent evt);
		extern const Key *SCANCODE_TO_KEY;
		extern const int *KEY_TO_SCANCODE;
	}
}
