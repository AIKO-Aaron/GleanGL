#ifdef __APPLE__

#include "Event.h"
#import <Carbon/Carbon.h>
#import <Cocoa/Cocoa.h>

using namespace Glean::events;

const Key *Glean::events::SCANCODE_TO_KEY = new Key[IMPLEMENTED_KEYS] {
    Key::kA, //  0: a
    Key::kS, //  1: s
    Key::kD, //  2: d
    Key::kF, //  3: f
    Key::kH, //  4: h
    Key::kG, //  5: g
    Key::kZ, //  6: z
    Key::kX, //  7: x
    Key::kC, //  8: c
    Key::kV, //  9: v
    Key::kUnknown, // 10: 
    Key::kB, // 11: b
    Key::kQ, // 12: q
    Key::kW, // 13: w
    Key::kE, // 14: e
    Key::kR, // 15: r
    Key::kY, // 16: y
    Key::kT, // 17: t
    Key::k1, // 18: 1
    Key::k2, // 19: 2
    Key::k3, // 20: 3
    Key::k4, // 21: 4
    Key::k5, // 22: 5
    Key::k6, // 23: 6
    Key::kUnknown, // 24: Equal
    Key::k9, // 25: 9
    Key::k7, // 26: 7
    Key::kUnknown, // 27: Minus
    Key::k8, // 28: 8
    Key::k0, // 29: 0
    Key::kUnknown, // 30: Right bracket
    Key::kO, // 31: o
    Key::kU, // 32: u
    Key::kUnknown, // 33: left bracket
    Key::kI, // 34: i
    Key::kP, // 35: p
    Key::kENTER, // 36: Return
    Key::kL, // 37: l
    Key::kJ, // 38: j
    Key::kUnknown, // 39: Quote
    Key::kK, // 40: k
    Key::kUnknown, // 41: ;
    Key::kUnknown, // 42: '\'
    Key::kUnknown, // 43: ,
    Key::kUnknown, // 44: /
    Key::kN, // 45: n
    Key::kM, // 46: n
    Key::kUnknown, // 47: .

    Key::kUnknown, // 48: Tab
    Key::kSPACE, // 49: Space

    Key::kUnknown, // 50: Grave

    Key::kUnknown, // 51: Delete
    Key::kUnknown, // 52: ???
    Key::kUnknown, // 53: Escape
    Key::kUnknown, // 54: RightCommand
    Key::kUnknown, // 55: Command
    Key::kSHIFT, // 56: Shift
    Key::kUnknown, // 57: CapsLock
    Key::kALT, // 58: Option
    Key::kCONTROL, // 59: Control
    Key::kUnknown, // 60: RightShift
    Key::kUnknown, // 61: RightOption
    Key::kUnknown, // 62: RightControl
    Key::kUnknown, // 63: Function
    Key::kUnknown, // 64: F17

    
    Key::kUnknown, // 65: Keypad Decimal
    Key::kUnknown, // 66: ???
    Key::kUnknown, // 67: Keypad *
    Key::kUnknown, // 68: ???
    Key::kUnknown, // 69: Keypad +
    Key::kUnknown, // 70: ???
    Key::kUnknown, // 71: Keypad Clear
    Key::kUnknown, // 72: Volume Up
    Key::kUnknown, // 73: Volume Down
    Key::kUnknown, // 74: Volume Mute
    Key::kUnknown, // 75: Keypad /
    Key::kUnknown, // 76: Keypad Enter
    Key::kUnknown, // 77: ???
    Key::kUnknown, // 78: Keypad -
    Key::kUnknown, // 79: F18
    Key::kUnknown, // 80: F19
    Key::kUnknown, // 81: Keypad =

    Key::kUnknown, // 82: Keypad 0
    Key::kUnknown, // 83: Keypad 1
    Key::kUnknown, // 84: Keypad 2
    Key::kUnknown, // 85: Keypad 3
    Key::kUnknown, // 86: Keypad 4
    Key::kUnknown, // 87: Keypad 5
    Key::kUnknown, // 88: Keypad 6
    Key::kUnknown, // 89: Keypad 7
    Key::kUnknown, // 90: F20
    Key::kUnknown, // 91: Keypad 8
    Key::kUnknown, // 92: Keypad 9

    Key::kUnknown, // 93: ???
    Key::kUnknown, // 94: ???
    Key::kUnknown, // 95: ???
    
    Key::kUnknown, // 0x60: F5
    Key::kUnknown, // 0x61: F6
    Key::kUnknown, // 0x62: F7
    Key::kUnknown, // 0x63: F3
    Key::kUnknown, // 0x64: F8
    Key::kUnknown, // 0x65: F9
    Key::kUnknown, // 0x66: ???
    Key::kUnknown, // 0x67: F11
    Key::kUnknown, // 0x68: ???
    Key::kUnknown, // 0x69: F13
    Key::kUnknown, // 0x6A: F16
    Key::kUnknown, // 0x6B: F14
    Key::kUnknown, // 0x6C: ???
    Key::kUnknown, // 0x6D: F10
    Key::kUnknown, // 0x6E: ???
    Key::kUnknown, // 0x6F: F12
    Key::kUnknown, // 0x70: ???
    Key::kUnknown, // 0x71: F15

    Key::kUnknown, // 0x72: Help
    Key::kUnknown, // 0x73: Home
    Key::kUnknown, // 0x74: PageUp
    Key::kUnknown, // 0x75: Delete (Forward)
    Key::kUnknown, // 0x76: F4
    Key::kUnknown, // 0x77: End
    Key::kUnknown, // 0x78: F2
    Key::kUnknown, // 0x79: PageDown
    Key::kUnknown, // 0x7A: F1
    Key::kLEFT, // 0x7B: LEFT
    Key::kRIGHT, // 0x7C: RIGHT
    Key::kDOWN, // 0x7D: DOWN
    Key::kUP, // 0x7E: UP
	Key::kUnknown, // 0x7F: ???
};

const int *Glean::events::KEY_TO_SCANCODE = new int[IMPLEMENTED_KEYS] {
    0,
    kVK_ANSI_A,
    kVK_ANSI_B,
    kVK_ANSI_C,
    kVK_ANSI_D,
    kVK_ANSI_E,
    kVK_ANSI_F,
    kVK_ANSI_G,
    kVK_ANSI_H,
    kVK_ANSI_I,
    kVK_ANSI_J,
    kVK_ANSI_K,
    kVK_ANSI_L,
    kVK_ANSI_M,
    kVK_ANSI_N,
    kVK_ANSI_O,
    kVK_ANSI_P,
    kVK_ANSI_Q,
    kVK_ANSI_R,
    kVK_ANSI_S,
    kVK_ANSI_T,
    kVK_ANSI_U,
    kVK_ANSI_V,
    kVK_ANSI_W,
    kVK_ANSI_X,
    kVK_ANSI_Y,
    kVK_ANSI_Z,
    
    kVK_ANSI_0,
    kVK_ANSI_1,
    kVK_ANSI_2,
    kVK_ANSI_3,
    kVK_ANSI_4,
    kVK_ANSI_5,
    kVK_ANSI_6,
    kVK_ANSI_7,
    kVK_ANSI_8,
    kVK_ANSI_9,

    kVK_ANSI_Keypad0,
    kVK_ANSI_Keypad1,
    kVK_ANSI_Keypad2,
    kVK_ANSI_Keypad3,
    kVK_ANSI_Keypad4,
    kVK_ANSI_Keypad5,
    kVK_ANSI_Keypad6,
    kVK_ANSI_Keypad7,
    kVK_ANSI_Keypad8,
    kVK_ANSI_Keypad9,
    
    kVK_UpArrow,
    kVK_DownArrow,
    kVK_LeftArrow,
    kVK_RightArrow,
    
    kVK_Space,
    kVK_Return,
    
    kVK_Shift,
    kVK_Control,
    kVK_Option,
};

Event *Glean::events::translateEvent(__internalEvent evt) {
	NSEvent *event = (__bridge NSEvent*) evt;
    if(event.type == NSEventTypeMouseMoved) {
		unsigned int x = [event locationInWindow].x;
		unsigned int y = [event locationInWindow].y;

		MouseMotionEvent *mEvent = new MouseMotionEvent();
		mEvent->type = MOUSEMOTION;
		mEvent->dx = [event deltaX];
		mEvent->dy = [event deltaY];
        mouseX = x;
		mouseY = y;

		return mEvent;
    } else if(event.type == NSEventTypeKeyDown || event.type == NSEventTypeKeyUp) {
        unsigned short kc = [event keyCode];
        
        if(kc >= IMPLEMENTED_KEYS) {
            printf("[GLEAN][ERROR] Not yet implemented KeyCode %d\n", kc);
            return nullptr;
        }
        
        KeyEvent *kEvent = new KeyEvent();
        kEvent->type = event.type == NSEventTypeKeyDown ? KEYDOWN : KEYUP;
        kEvent->key = SCANCODE_TO_KEY[kc];
        NSEventModifierFlags flags = [event modifierFlags];
        
        kEvent->isShiftDown = flags & NSEventModifierFlagShift;
        kEvent->isControlDown = flags & NSEventModifierFlagControl;
        kEvent->isCommandDown = flags & NSEventModifierFlagCommand;
        kEvent->isAltDown = flags & NSEventModifierFlagOption;
        kEvent->isCapsLockOn = flags & NSEventModifierFlagCapsLock;
        kEvent->isHelpDown = flags & NSEventModifierFlagHelp;
        kEvent->isFunctionDown = flags & NSEventModifierFlagFunction;

        return kEvent;
    } else {
        // printf("%s\n", [event.description UTF8String]);
    }
    
    return nullptr;
}

#endif
