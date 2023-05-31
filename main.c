#include <stdlib.h>
#include <X11/Xlib.h>
#include <X11/XKBlib.h>
#include <X11/keysym.h>

int main () {
	Display *dpy;
	XEvent ev;
	Window root, window;

	if(!(dpy = XOpenDisplay(0x0))) return 1;

	root = DefaultRootWindow(dpy);

	XGrabKey(dpy, XKeysymToKeycode(dpy, XK_q), Mod1Mask, root, True,
			GrabModeAsync, GrabModeAsync);
	XGrabKey(dpy, XKeysymToKeycode(dpy, XK_Return), Mod1Mask, root, True,
			GrabModeAsync, GrabModeAsync);
	
	XSelectInput(dpy, root, SubstructureRedirectMask | SubstructureNotifyMask);

	for(;;) {
		XNextEvent(dpy, &ev);

		if (ev.type == CreateNotify) {
			window = ev.xcreatewindow.window;
			XMoveResizeWindow(dpy, window, 30, 30, (1920-30), (1080-30));	
			XMapWindow(dpy, window);
		}
		else if (ev.type == KeyPress) {
			KeyCode keycode = ev.xkey.keycode;
			KeySym keysym = XkbKeycodeToKeysym(dpy, keycode, 0, 0);

			if (keysym == XK_Return && ev.xkey.state == Mod1Mask)
				system("st &");
			else if (keysym == XK_q && ev.xkey.state == Mod1Mask)
				XDestroyWindow(dpy, ev.xkey.subwindow);
		}
	}

	return 0;
}
