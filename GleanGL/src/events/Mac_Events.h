#pragma once

#ifdef __APPLE__

#include "Event.h"
#import <Carbon/Carbon.h>

#define IMPLEMENTED_KEYS 128

static const Glean::events::Key *SCANCODE_TO_KEY = new Glean::events::Key[IMPLEMENTED_KEYS] {
    Glean::events::Key::kA, //  0: a
    Glean::events::Key::kS, //  1: s
    Glean::events::Key::kD, //  2: d
    Glean::events::Key::kF, //  3: f
    Glean::events::Key::kH, //  4: h
    Glean::events::Key::kG, //  5: g
    Glean::events::Key::kZ, //  6: z
    Glean::events::Key::kX, //  7: x
    Glean::events::Key::kC, //  8: c
    Glean::events::Key::kV, //  9: v
    Glean::events::Key::kUnknown, // 10: 
    Glean::events::Key::kB, // 11: b
    Glean::events::Key::kQ, // 12: q
    Glean::events::Key::kW, // 13: w
    Glean::events::Key::kE, // 14: e
    Glean::events::Key::kR, // 15: r
    Glean::events::Key::kY, // 16: y
    Glean::events::Key::kT, // 17: t
    Glean::events::Key::k1, // 18: 1
    Glean::events::Key::k2, // 19: 2
    Glean::events::Key::k3, // 20: 3
    Glean::events::Key::k4, // 21: 4
    Glean::events::Key::k5, // 22: 5
    Glean::events::Key::k6, // 23: 6
    Glean::events::Key::kUnknown, // 24: Equal
    Glean::events::Key::k9, // 25: 9
    Glean::events::Key::k7, // 26: 7
    Glean::events::Key::kUnknown, // 27: Minus
    Glean::events::Key::k8, // 28: 8
    Glean::events::Key::k0, // 29: 0
    Glean::events::Key::kUnknown, // 30: Right bracket
    Glean::events::Key::kO, // 31: o
    Glean::events::Key::kU, // 32: u
    Glean::events::Key::kUnknown, // 33: left bracket
    Glean::events::Key::kI, // 34: i
    Glean::events::Key::kP, // 35: p
    Glean::events::Key::kUnknown, // 36: Return
    Glean::events::Key::kL, // 37: l
    Glean::events::Key::kJ, // 38: j
    Glean::events::Key::kUnknown, // 39: Quote
    Glean::events::Key::kK, // 40: k
    Glean::events::Key::kUnknown, // 41: ;
    Glean::events::Key::kUnknown, // 42: '\'
    Glean::events::Key::kUnknown, // 43: ,
    Glean::events::Key::kUnknown, // 44: /
    Glean::events::Key::kN, // 45: n
    Glean::events::Key::kM, // 46: n
    Glean::events::Key::kUnknown, // 47: .

    Glean::events::Key::kUnknown, // 48: Tab
    Glean::events::Key::kUnknown, // 49: Space

    Glean::events::Key::kUnknown, // 50: Grave

    Glean::events::Key::kUnknown, // 51: Delete
    Glean::events::Key::kUnknown, // 52: ???
    Glean::events::Key::kUnknown, // 53: Escape
    Glean::events::Key::kUnknown, // 54: RightCommand
    Glean::events::Key::kUnknown, // 55: Command
    Glean::events::Key::kUnknown, // 56: Shift
    Glean::events::Key::kUnknown, // 57: CapsLock
    Glean::events::Key::kUnknown, // 58: Option
    Glean::events::Key::kUnknown, // 59: Control
    Glean::events::Key::kUnknown, // 60: RightShift
    Glean::events::Key::kUnknown, // 61: RightOption
    Glean::events::Key::kUnknown, // 62: RightControl
    Glean::events::Key::kUnknown, // 63: Function
    Glean::events::Key::kUnknown, // 64: F17

    
    Glean::events::Key::kUnknown, // 65: Keypad Decimal
    Glean::events::Key::kUnknown, // 66: ???
    Glean::events::Key::kUnknown, // 67: Keypad *
    Glean::events::Key::kUnknown, // 68: ???
    Glean::events::Key::kUnknown, // 69: Keypad +
    Glean::events::Key::kUnknown, // 70: ???
    Glean::events::Key::kUnknown, // 71: Keypad Clear
    Glean::events::Key::kUnknown, // 72: Volume Up
    Glean::events::Key::kUnknown, // 73: Volume Down
    Glean::events::Key::kUnknown, // 74: Volume Mute
    Glean::events::Key::kUnknown, // 75: Keypad /
    Glean::events::Key::kUnknown, // 76: Keypad Enter
    Glean::events::Key::kUnknown, // 77: ???
    Glean::events::Key::kUnknown, // 78: Keypad -
    Glean::events::Key::kUnknown, // 79: F18
    Glean::events::Key::kUnknown, // 80: F19
    Glean::events::Key::kUnknown, // 81: Keypad =

    Glean::events::Key::kUnknown, // 82: Keypad 0
    Glean::events::Key::kUnknown, // 83: Keypad 1
    Glean::events::Key::kUnknown, // 84: Keypad 2
    Glean::events::Key::kUnknown, // 85: Keypad 3
    Glean::events::Key::kUnknown, // 86: Keypad 4
    Glean::events::Key::kUnknown, // 87: Keypad 5
    Glean::events::Key::kUnknown, // 88: Keypad 6
    Glean::events::Key::kUnknown, // 89: Keypad 7
    Glean::events::Key::kUnknown, // 90: F20
    Glean::events::Key::kUnknown, // 91: Keypad 8
    Glean::events::Key::kUnknown, // 92: Keypad 9

    Glean::events::Key::kUnknown, // 93: ???
    Glean::events::Key::kUnknown, // 94: ???
    Glean::events::Key::kUnknown, // 95: ???
    
    Glean::events::Key::kUnknown, // 0x60: F5
    Glean::events::Key::kUnknown, // 0x61: F6
    Glean::events::Key::kUnknown, // 0x62: F7
    Glean::events::Key::kUnknown, // 0x63: F3
    Glean::events::Key::kUnknown, // 0x64: F8
    Glean::events::Key::kUnknown, // 0x65: F9
    Glean::events::Key::kUnknown, // 0x66: ???
    Glean::events::Key::kUnknown, // 0x67: F11
    Glean::events::Key::kUnknown, // 0x68: ???
    Glean::events::Key::kUnknown, // 0x69: F13
    Glean::events::Key::kUnknown, // 0x6A: F16
    Glean::events::Key::kUnknown, // 0x6B: F14
    Glean::events::Key::kUnknown, // 0x6C: ???
    Glean::events::Key::kUnknown, // 0x6D: F10
    Glean::events::Key::kUnknown, // 0x6E: ???
    Glean::events::Key::kUnknown, // 0x6F: F12
    Glean::events::Key::kUnknown, // 0x70: ???
    Glean::events::Key::kUnknown, // 0x71: F15

    Glean::events::Key::kUnknown, // 0x72: Help
    Glean::events::Key::kUnknown, // 0x73: Home
    Glean::events::Key::kUnknown, // 0x74: PageUp
    Glean::events::Key::kUnknown, // 0x75: Delete (Forward)
    Glean::events::Key::kUnknown, // 0x76: F4
    Glean::events::Key::kUnknown, // 0x77: End
    Glean::events::Key::kUnknown, // 0x78: F2
    Glean::events::Key::kUnknown, // 0x79: PageDown
    Glean::events::Key::kUnknown, // 0x7A: F1
    Glean::events::Key::kLEFT, // 0x7B: LEFT
    Glean::events::Key::kRIGHT, // 0x7C: RIGHT
    Glean::events::Key::kDOWN, // 0x7D: DOWN
    Glean::events::Key::kUP, // 0x7E: UP
};

static const int *MAC_KEY_TO_SCANCODE = new int[IMPLEMENTED_KEYS] {
    kVK_UpArrow,
    kVK_DownArrow,
    kVK_LeftArrow,
    kVK_RightArrow,
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
};

static Glean::events::Event *translateEvent(NSEvent *event) {
    if(event.type == NSEventTypeMouseMoved) {
        //printf("Location in window: %f|%f\n", [evnt locationInWindow].x, [evnt locationInWindow].y);
    } else if(event.type == NSEventTypeKeyDown) {
        unsigned short kc = [event keyCode];
        
        if(kc >= IMPLEMENTED_KEYS) {
            printf("Not yet implemented KeyCode %d\n", kc);
            return nullptr;
        }
        
        Glean::events::KeyEvent *kEvent = new Glean::events::KeyEvent();
        kEvent->type = Glean::events::KEYDOWN;
        kEvent->key = SCANCODE_TO_KEY[kc];
        return kEvent;
    }
    
    return nullptr;
}

#endif
