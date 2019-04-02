#pragma once

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
            kUnknown,
            
            kA,
            kB,
            kC,
            kD,
            kE,
            kF,
            kG,
            kH,
            kI,
            kJ,
            kK,
            kL,
            kM,
            kN,
            kO,
            kP,
            kQ,
            kR,
            kS,
            kT,
            kU,
            kV,
            kW,
            kX,
            kY,
            kZ,
            
            k0,
            k1,
            k2,
            k3,
            k4,
            k5,
            k6,
            k7,
            k8,
            k9,
            
            kNP0,
            kNP1,
            kNP2,
            kNP3,
            kNP4,
            kNP5,
            kNP6,
            kNP7,
            kNP8,
            kNP9,
            
            kUP,
            kDOWN,
            kLEFT,
            kRIGHT,
            
            kSPACE,
            kENTER,
        };
        
        
#ifdef __APPLE__
#  define vCtrlSys vCommand
#else
#  define vCtrlSys vCtrl
#endif
        
        // Definitions of Events that the user can receive
        
        struct KeyEvent;
        
		typedef struct {
			EventType type;
            
            inline KeyEvent* asKeyEvent() { return type == KEYUP || type == KEYDOWN ? (KeyEvent*) this : nullptr; }
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
        
        extern char getCharFromKey(Key keycode);
        
	}
}
