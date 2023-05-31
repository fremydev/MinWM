CFLAGS?=-O3 -pedantic -Wall

install:
	$(CC) $(CFLAGS) main.c -lX11 -o minwm

clean:
	rm -f minwm
