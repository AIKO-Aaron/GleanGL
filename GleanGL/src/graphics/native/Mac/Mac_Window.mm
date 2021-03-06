//
//  Mac_Window.m
//  GleanGL
//
//  Created by Aaron Hodel on 01.04.19.
//  Copyright © 2019 Aaron Hodel. All rights reserved.
//

#ifdef __APPLE__

#import <Cocoa/Cocoa.h>
#include "../../Window.h"

typedef void (Glean::graphics::Window::*loopFunc)(); // Just because apple needs the appdelegate

@interface AppDelegate : NSObject<NSApplicationDelegate>

@end

@implementation AppDelegate
{
    Glean::graphics::Window *window;
    loopFunc loop;
}

- (instancetype)initWithWindow: (Glean::graphics::Window*) iWindow loopFunction: (loopFunc) f {
    self = [super init];
    if (self) {
        window = iWindow;
        loop = f;
    }
    return self;
}

-(void) onQuit:(__unused id) sender {
    [[NSApplication sharedApplication] terminate:nil];
}

- (void)applicationDidFinishLaunching:(NSNotification *)notification {
    (window->*loop)();
}

- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)sender {
    return NO;
}

@end

@interface __AWindow : NSWindow

@end

@implementation __AWindow

- (void)keyDown:(NSEvent *)event {
    
}

@end

Glean::graphics::Window::Window(const char *title, int width, int height) {
    [NSApplication sharedApplication]; // Create variable NSApp for later use
    [NSApp setActivationPolicy:NSApplicationActivationPolicyRegular];
    [NSApp activateIgnoringOtherApps: YES];
    [NSApp setDelegate: [[AppDelegate alloc] initWithWindow: this loopFunction: &Glean::graphics::Window::loop]];
    NSScreen *mainScreen = [NSScreen mainScreen];
    
    NSRect windowRect = NSMakeRect((mainScreen.frame.size.width - width) / 2.0, (mainScreen.frame.size.height - height) / 2.0, (double) width, (double) height);
    NSWindow *w = [[__AWindow alloc] initWithContentRect:windowRect styleMask: NSWindowStyleMaskTitled|NSWindowStyleMaskClosable|NSWindowStyleMaskMiniaturizable|NSWindowStyleMaskResizable backing:NSBackingStoreBuffered defer: NO screen:mainScreen];
    window = (__internalWindow) w;
    
    [w setTitle: [NSString stringWithUTF8String:title]];
    [w setReleasedWhenClosed: NO];
    [w setAcceptsMouseMovedEvents: YES];
    [w setOpaque: NO];
    [w makeKeyAndOrderFront: nil];
	
    NSPoint mouseLoc = [w mouseLocationOutsideOfEventStream];
    Glean::events::mouseX = mouseLoc.x;
    Glean::events::mouseY = mouseLoc.y;
    
    init();
}

void Glean::graphics::Window::makeFullscreen() {
	[(NSWindow*) window toggleFullScreen: nil];
	glViewport(0, 0, [(NSWindow*) window frame].size.width, [(NSWindow*) window frame].size.height);
}

bool Glean::graphics::Window::fetchEvents() {
    NSWindow *window = (__bridge NSWindow*) this->window;
    NSEvent *evnt;
    do {
        evnt = [window nextEventMatchingMask:NSEventMaskAny untilDate:[NSDate distantPast] inMode:NSDefaultRunLoopMode dequeue:YES];
        if(evnt) {
            if(evnt.type == NSEventTypeKeyDown) keysPressed[Glean::events::SCANCODE_TO_KEY[evnt.keyCode] % IMPLEMENTED_KEYS] = true;
            if(evnt.type == NSEventTypeKeyUp) keysPressed[Glean::events::SCANCODE_TO_KEY[evnt.keyCode] % IMPLEMENTED_KEYS] = false;
            
            if(evnt.type == NSEventTypeFlagsChanged) {
                keysPressed[Glean::events::kSHIFT] = evnt.modifierFlags & NSEventModifierFlagShift;
                keysPressed[Glean::events::kCONTROL] = evnt.modifierFlags & NSEventModifierFlagOption;
                keysPressed[Glean::events::kALT] = evnt.modifierFlags & NSEventModifierFlagOption;
            }
            
            // printf("%s\n", [evnt.description UTF8String]);
            
            Glean::events::Event *e = Glean::events::translateEvent((__bridge __internalEvent) evnt);
            if(e) dispatchEvent(e);
            [NSApp sendEvent: evnt]; // Do with event whatever is necessary
        }
    } while(evnt);
    
    if(![window isVisible]) [NSApp stop: nil]; // Stop the application from running, but not terminate it
    return [window isVisible];
}

void Glean::graphics::Window::start() { [NSApp run]; }

void Glean::graphics::Window::captureMouse() {
    [NSCursor hide];
    //CGDisplayMoveCursorToPoint(kCGDirectMainDisplay, CGPointZero); // If above
    CGAssociateMouseAndMouseCursorPosition(NO); // Mouse is not cursor
    mouseCaptured = true;
}

void Glean::graphics::Window::uncaptureMouse() {
    [NSCursor unhide];
    CGAssociateMouseAndMouseCursorPosition(YES);
    mouseCaptured = false;
}

void Glean::graphics::Window::close() { [NSApp stop: nil]; }
#endif
