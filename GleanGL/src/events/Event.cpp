#include "Event.h"

char Glean::events::getCharFromKey(Key keycode) {
    char c = ' ';
    
    if(!keycode) c = '?';
    else if(keycode <= kZ) c = 0x40 + keycode;
    else if(keycode <= k9) c = 0x15 + keycode;
    else if(keycode <= kNP9) c = 0x0B + keycode;
    else if(keycode <= kRIGHT) c = ' '; // up down left right
    else if(keycode <= kSPACE) c = ' '; // Space
    else if(keycode <= kENTER) c = '\n'; // Return

    return c;
}
