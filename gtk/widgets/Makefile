all: stockbutton togglebutton checkbutton radiobutton gtkentry spinbutton

stockbutton: stockbutton.c
	cc `pkg-config --cflags --libs gtk+-2.0` $^ -o $@
togglebutton: togglebutton.c
	cc `pkg-config --cflags --libs gtk+-2.0` $^ -o $@
checkbutton: checkbutton.c
	cc `pkg-config --cflags --libs gtk+-2.0` $^ -o $@
radiobutton: radiobutton.c
	cc `pkg-config --cflags --libs gtk+-2.0` $^ -o $@
gtkentry: gtkentry.c
	cc `pkg-config --cflags --libs gtk+-2.0` $^ -o $@
spinbutton: spinbutton.c
	cc `pkg-config --cflags --libs gtk+-2.0` $^ -o $@
clean:
	rm -rf stockbutton togglebutton checkbutton radiobutton gtkentry spinbutton
