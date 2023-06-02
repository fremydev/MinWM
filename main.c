#include <stdlib.h>
#include <X11/Xlib.h>
#include <X11/XKBlib.h>
#include <X11/extensions/Xrandr.h>

int main () {
	Display *dpy;
	XEvent ev;
	Window root, window;
	XRRScreenResources *screen;
	XRRCrtcInfo *crtc_info;


	if(!(dpy = XOpenDisplay(NULL))) return 1;

	root = DefaultRootWindow(dpy);
	screen = XRRGetScreenResources(dpy, root);

	XGrabKey(dpy, XKeysymToKeycode(dpy, XK_d), Mod1Mask, root, True,
			GrabModeAsync, GrabModeAsync);
	XGrabKey(dpy, XKeysymToKeycode(dpy, XK_j), Mod1Mask, root, True,
			GrabModeAsync, GrabModeAsync);
	XGrabKey(dpy, XKeysymToKeycode(dpy, XK_Return), Mod1Mask, root, True,
			GrabModeAsync, GrabModeAsync);
	
	XSelectInput(dpy, root, SubstructureRedirectMask | SubstructureNotifyMask);


	for(;;) {
		XNextEvent(dpy, &ev);

		if (ev.type == MapRequest) {
			crtc_info = XRRGetCrtcInfo(dpy, screen, screen->crtcs[0]);

			window = ev.xcreatewindow.window;
			XMoveResizeWindow(dpy, window, 30, 30, ((crtc_info->width)-60), ((crtc_info->height)-60));	
			XMapWindow(dpy, window);


		}
		else if (ev.type == KeyPress) {

			KeyCode keycode = ev.xkey.keycode;
			KeySym keysym = XkbKeycodeToKeysym(dpy, keycode, 0, 0);

			if (keysym == XK_Return && ev.xkey.state == Mod1Mask)
				system("st &");
			else if (keysym == XK_j && ev.xkey.state == Mod1Mask && ev.xkey.subwindow != None)
				XLowerWindow(dpy,ev.xkey.subwindow);
			else if (keysym == XK_d && ev.xkey.state == Mod1Mask)
				system("dmenu_run &");
		}
	}

	XRRFreeScreenResources(screen);


	return 0;
}
