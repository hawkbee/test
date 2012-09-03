all: stockbutton 

stockbutton: stockbutton.c
	cc `pkg-config --cflags --libs gtk+-2.0` $^ -o $@
clean:
	rm -rf stockbutton
