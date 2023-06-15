CFLAGS?=-O3 -pedantic -Wall

install:
	$(CC) $(CFLAGS) main.c -lX11 -lXrandr -o minwm
	upx --best minwm

clean:
	rm -f minwm
