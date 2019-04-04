#ifdef _WIN32

#include <Windows.h>
#include <Windowsx.h>
#include "Event.h"
#include <stdio.h>

using namespace Glean::events;

const Key *Glean::events::SCANCODE_TO_KEY = new Glean::events::Key[IMPLEMENTED_KEYS] {
	Key::kUnknown, // 0x0
	Key::kUnknown, // 0x1
	Key::kUnknown, // 0x2
	Key::kUnknown, // 0x3
	Key::kUnknown, // 0x4
	Key::kUnknown, // 0x5
	Key::kUnknown, // 0x6
	Key::kUnknown, // 0x7
	Key::kUnknown, // 0x8
	Key::kTAB, // 0x9
	Key::kUnknown, // 0xA
	Key::kUnknown, // 0xB
	Key::kUnknown, // 0xC
	Key::kENTER, // 0xD
	Key::kUnknown, // 0xE
	Key::kUnknown, // 0xF
	Key::kUnknown, // 0x10
	Key::kUnknown, // 0x11
	Key::kUnknown, // 0x12
	Key::kUnknown, // 0x13
	Key::kUnknown, // 0x14
	Key::kUnknown, // 0x15
	Key::kUnknown, // 0x16
	Key::kUnknown, // 0x17
	Key::kUnknown, // 0x18
	Key::kUnknown, // 0x19
	Key::kUnknown, // 0x1A
	Key::kESCAPE, // 0x1B
	Key::kUnknown, // 0x1C
	Key::kUnknown, // 0x1D
	Key::kUnknown, // 0x1E
	Key::kUnknown, // 0x1F
	Key::kSPACE, // 0x20
	Key::kUnknown, // 0x21
	Key::kUnknown, // 0x22
	Key::kUnknown, // 0x23
	Key::kUnknown, // 0x24
	Key::kLEFT, // 0x25
	Key::kUP, // 0x26
	Key::kRIGHT, // 0x27
	Key::kDOWN, // 0x28
	Key::kUnknown, // 0x29
	Key::kUnknown, // 0x2A
	Key::kUnknown, // 0x2B
	Key::kUnknown, // 0x2C
	Key::kUnknown, // 0x2D
	Key::kUnknown, // 0x2E
	Key::kUnknown, // 0x2F
	Key::k0, // 0x30
	Key::k1, // 0x31
	Key::k2, // 0x32
	Key::k3, // 0x33
	Key::k4, // 0x34
	Key::k5, // 0x35
	Key::k6, // 0x36
	Key::k7, // 0x37
	Key::k8, // 0x38
	Key::k9, // 0x39
	Key::kUnknown, // 0x3A
	Key::kUnknown, // 0x3B
	Key::kUnknown, // 0x3C
	Key::kUnknown, // 0x3D
	Key::kUnknown, // 0x3E
	Key::kUnknown, // 0x3F
	Key::kUnknown, // 0x40
	Key::kA, // 0x41
	Key::kB, // 0x42
	Key::kC, // 0x43
	Key::kD, // 0x44
	Key::kE, // 0x45
	Key::kF, // 0x46
	Key::kG, // 0x47
	Key::kH, // 0x48
	Key::kI, // 0x49
	Key::kJ, // 0x4A
	Key::kK, // 0x4B
	Key::kL, // 0x4C
	Key::kM, // 0x4D
	Key::kN, // 0x4E
	Key::kO, // 0x4F
	Key::kP, // 0x50
	Key::kQ, // 0x51
	Key::kR, // 0x52
	Key::kS, // 0x53
	Key::kT, // 0x54
	Key::kU, // 0x55
	Key::kV, // 0x56
	Key::kW, // 0x57
	Key::kX, // 0x58
	Key::kY, // 0x59
	Key::kZ, // 0x5A
	Key::kUnknown, // 0x5B
	Key::kUnknown, // 0x5C
	Key::kUnknown, // 0x5D
	Key::kUnknown, // 0x5E
	Key::kUnknown, // 0x5F
	Key::kNP0, // 0x60
	Key::kNP1, // 0x61
	Key::kNP2, // 0x62
	Key::kNP3, // 0x63
	Key::kNP4, // 0x64
	Key::kNP5, // 0x65
	Key::kNP6, // 0x66
	Key::kNP7, // 0x67
	Key::kNP8, // 0x68
	Key::kNP9, // 0x69
	Key::kUnknown, // 0x6A
	Key::kUnknown, // 0x6B
	Key::kUnknown, // 0x6C
	Key::kUnknown, // 0x6D
	Key::kUnknown, // 0x6E
	Key::kUnknown, // 0x6F
	Key::kF1, // 0x70
	Key::kF2, // 0x71
	Key::kF3, // 0x72
	Key::kF4, // 0x73
	Key::kF5, // 0x74
	Key::kF6, // 0x75
	Key::kF7, // 0x76
	Key::kF8, // 0x77
	Key::kF9, // 0x78
	Key::kF10, // 0x79
	Key::kF11, // 0x7A
	Key::kF12, // 0x7B
	Key::kF13, // 0x7C
	Key::kF14, // 0x7D
	Key::kF15, // 0x7F
	Key::kUnknown, // 0x80
	Key::kUnknown, // 0x81
	Key::kUnknown, // 0x82
	Key::kUnknown, // 0x83
	Key::kUnknown, // 0x84
	Key::kUnknown, // 0x85
	Key::kUnknown, // 0x86
	Key::kUnknown, // 0x87
	Key::kUnknown, // 0x88
	Key::kUnknown, // 0x89
	Key::kUnknown, // 0x8A
	Key::kUnknown, // 0x8B
	Key::kUnknown, // 0x8C
	Key::kUnknown, // 0x8D
	Key::kUnknown, // 0x8E
	Key::kUnknown, // 0x8F
	Key::kUnknown, // 0x90
	Key::kUnknown, // 0x91
	Key::kUnknown, // 0x92
	Key::kUnknown, // 0x93
	Key::kUnknown, // 0x94
	Key::kUnknown, // 0x95
	Key::kUnknown, // 0x96
	Key::kUnknown, // 0x97
	Key::kUnknown, // 0x98
	Key::kUnknown, // 0x99
	Key::kUnknown, // 0x9A
	Key::kUnknown, // 0x9B
	Key::kUnknown, // 0x9C
	Key::kUnknown, // 0x9D
	Key::kUnknown, // 0x9E
	Key::kUnknown, // 0x9F
	Key::kUnknown, // 0xA0
	Key::kUnknown, // 0xA1
	Key::kUnknown, // 0xA2
	Key::kUnknown, // 0xA3
	Key::kUnknown, // 0xA4
	Key::kUnknown, // 0xA5
	Key::kUnknown, // 0xA6
	Key::kUnknown, // 0xA7
	Key::kUnknown, // 0xA8
	Key::kUnknown, // 0xA9
	Key::kUnknown, // 0xAA
	Key::kUnknown, // 0xAB
	Key::kUnknown, // 0xAC
	Key::kUnknown, // 0xAD
	Key::kUnknown, // 0xAE
	Key::kUnknown, // 0xAF
	Key::kUnknown, // 0xB0
	Key::kUnknown, // 0xB1
	Key::kUnknown, // 0xB2
	Key::kUnknown, // 0xB3
	Key::kUnknown, // 0xB4
	Key::kUnknown, // 0xB5
	Key::kUnknown, // 0xB6
	Key::kUnknown, // 0xB7
	Key::kUnknown, // 0xB8
	Key::kUnknown, // 0xB9
	Key::kUnknown, // 0xBA
	Key::kPLUS, // 0xBB
	Key::kCOMMA, // 0xBC
	Key::kMINUS, // 0xBD
	Key::kPERIOD, // 0xBE
	Key::kUnknown, // 0xBF
	Key::kUnknown, // 0xC0
	Key::kUnknown, // 0xC1
	Key::kUnknown, // 0xC2
	Key::kUnknown, // 0xC3
	Key::kUnknown, // 0xC4
	Key::kUnknown, // 0xC5
	Key::kUnknown, // 0xC6
	Key::kUnknown, // 0xC7
	Key::kUnknown, // 0xC8
	Key::kUnknown, // 0xC9
	Key::kUnknown, // 0xCA
	Key::kUnknown, // 0xCB
	Key::kUnknown, // 0xCC
	Key::kUnknown, // 0xCD
	Key::kUnknown, // 0xCE
	Key::kUnknown, // 0xCF
	Key::kUnknown, // 0xD0
	Key::kUnknown, // 0xD1
	Key::kUnknown, // 0xD2
	Key::kUnknown, // 0xD3
	Key::kUnknown, // 0xD4
	Key::kUnknown, // 0xD5
	Key::kUnknown, // 0xD6
	Key::kUnknown, // 0xD7
	Key::kUnknown, // 0xD8
	Key::kUnknown, // 0xD9
	Key::kUnknown, // 0xDA
	Key::kUnknown, // 0xDB
	Key::kUnknown, // 0xDC
	Key::kUnknown, // 0xDD
	Key::kUnknown, // 0xDE
	Key::kUnknown, // 0xDF
	Key::kUnknown, // 0xE0
	Key::kUnknown, // 0xE1
	Key::kUnknown, // 0xE2
	Key::kUnknown, // 0xE3
	Key::kUnknown, // 0xE4
	Key::kUnknown, // 0xE5
	Key::kUnknown, // 0xE6
	Key::kUnknown, // 0xE7
	Key::kUnknown, // 0xE8
	Key::kUnknown, // 0xE9
	Key::kUnknown, // 0xEA
	Key::kUnknown, // 0xEB
	Key::kUnknown, // 0xEC
	Key::kUnknown, // 0xED
	Key::kUnknown, // 0xEE
	Key::kUnknown, // 0xEF
	Key::kUnknown, // 0xF0
	Key::kUnknown, // 0xF1
	Key::kUnknown, // 0xF2
	Key::kUnknown, // 0xF3
	Key::kUnknown, // 0xF4
	Key::kUnknown, // 0xF5
	Key::kUnknown, // 0xF6
	Key::kUnknown, // 0xF7
	Key::kUnknown, // 0xF8
	Key::kUnknown, // 0xF9
	Key::kUnknown, // 0xFA
	Key::kUnknown, // 0xFB
	Key::kUnknown, // 0xFC
	Key::kUnknown, // 0xFD
	Key::kUnknown, // 0xFE
};

const int *Glean::events::KEY_TO_SCANCODE = new int[IMPLEMENTED_KEYS] {
	0,
	'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
	'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
	VK_NUMPAD0, VK_NUMPAD1, VK_NUMPAD2, VK_NUMPAD3, VK_NUMPAD4, VK_NUMPAD5, VK_NUMPAD6, VK_NUMPAD7, VK_NUMPAD8, VK_NUMPAD9,
	VK_OEM_COMMA, VK_OEM_PERIOD, VK_OEM_MINUS, VK_OEM_PLUS,
	VK_UP, VK_DOWN, VK_LEFT, VK_RIGHT,

	VK_SPACE,
	VK_TAB,
	VK_RETURN,

	VK_F1, VK_F2, VK_F3, VK_F4, VK_F5, VK_F6, VK_F7, VK_F8, VK_F9, VK_F10, VK_F11, VK_F12, VK_F13, VK_F14, VK_F15
};

Glean::events::Event *Glean::events::translateEvent(__internalEvent evt) {
	if (evt.message == WM_KEYDOWN || evt.message == WM_KEYUP) {
		unsigned int kc = evt.wParam;

		if (kc >= IMPLEMENTED_KEYS) {
			printf("[GLEAN][ERROR] Not yet implemented KeyCode %d\n", kc);
			return nullptr;
		}

		Glean::events::KeyEvent *kEvent = new Glean::events::KeyEvent();
		kEvent->type = evt.message == WM_KEYDOWN ? Glean::events::KEYDOWN : Glean::events::KEYUP;
		kEvent->key = SCANCODE_TO_KEY[kc];

		kEvent->isShiftDown = GetKeyState(VK_SHIFT) & 0x8000;
		kEvent->isControlDown = GetKeyState(VK_CONTROL) & 0x8000;
		kEvent->isCommandDown = false; // no command key... probably
		kEvent->isAltDown = GetKeyState(VK_MENU) & 0x8000;
		kEvent->isCapsLockOn = GetKeyState(VK_CAPITAL) & 0x8000;
		kEvent->isHelpDown = GetKeyState(VK_HELP) & 0x8000;
		kEvent->isFunctionDown = false; // no fn key... probably

		return kEvent;
	} else if(evt.message == WM_MOUSEMOVE) {
		unsigned int x = GET_X_LPARAM(evt.lParam);
		unsigned int y = GET_Y_LPARAM(evt.lParam);

		MouseMotionEvent *mEvent = new MouseMotionEvent();
		mEvent->type = MOUSEMOTION;
        mEvent->dx = x - mouseX;
        mEvent->dy = y - mouseY;
		mEvent->xPos = x;
		mEvent->yPos = y;

		mouseX = x;
		mouseY = y;

		return mEvent;
	}

	return nullptr;
}

#endif
