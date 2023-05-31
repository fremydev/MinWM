#include <X11/Xlib.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))

int main () {
	Display *dpy;
	XEvent ev;

	if(!(dpy = XOpenDisplay(0x0))) return 1;

	for(;;) {
		XNextEvent(dpy, &ev);
	}

	return 0;
}
