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
	XGrabKey(dpy, XKeysymToKeycode(dpy, XK_n), Mod1Mask, root, True,
			GrabModeAsync, GrabModeAsync);
	XGrabKey(dpy, XKeysymToKeycode(dpy, XK_q), Mod1Mask, root, True,
			GrabModeAsync, GrabModeAsync);
	XGrabKey(dpy, XKeysymToKeycode(dpy, XK_e), Mod1Mask, root, True,
			GrabModeAsync, GrabModeAsync);
	XGrabKey(dpy, XKeysymToKeycode(dpy, XK_Return), Mod1Mask, root, True,
			GrabModeAsync, GrabModeAsync);
	
	XSelectInput(dpy, root, SubstructureRedirectMask | SubstructureNotifyMask);


	for(;;) {
		XNextEvent(dpy, &ev);

		if (ev.type == MapRequest) {
			XRROutputInfo *out_info_hdmi= XRRGetOutputInfo(dpy, screen, screen->outputs[1]);

			if (out_info_hdmi->crtc != 0)
				crtc_info = XRRGetCrtcInfo(dpy, screen, screen->crtcs[1]);
			else
				crtc_info = XRRGetCrtcInfo(dpy, screen, screen->crtcs[0]);

			window = ev.xcreatewindow.window;
			XMoveResizeWindow(dpy, window, 0, 0, crtc_info->width, crtc_info->height);	
			XMapWindow(dpy, window);


		}
		else if (ev.type == KeyPress) {

			KeyCode keycode = ev.xkey.keycode;
			KeySym keysym = XkbKeycodeToKeysym(dpy, keycode, 0, 0);

			if (keysym == XK_Return && ev.xkey.state == Mod1Mask)
				system("st &");
			if (keysym == XK_e && ev.xkey.state == Mod1Mask)
				system("emacs &");
			else if (keysym == XK_n && ev.xkey.state == Mod1Mask && ev.xkey.subwindow != None)
				XLowerWindow(dpy,ev.xkey.subwindow);
			else if (keysym == XK_d && ev.xkey.state == Mod1Mask)
				system("dmenu_run &");
			else if (keysym == XK_q && ev.xkey.state == Mod1Mask && ev.xkey.subwindow != None) {
				XGrabServer(dpy);
				XSetCloseDownMode(dpy, DestroyAll);
				XKillClient(dpy, ev.xkey.subwindow);
				XSync(dpy, False);
				XUngrabServer(dpy);
			}

		}

	}

	XRRFreeScreenResources(screen);


	return 0;
}
