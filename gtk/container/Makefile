all: vbox vpaned table

vbox: gtkvbox.c
	cc `pkg-config --cflags --libs gtk+-2.0` $^ -o $@
vpaned: gtkvpaned.c
	cc `pkg-config --cflags --libs gtk+-2.0` $^ -o $@
table: gtktable.c
	cc `pkg-config --cflags --libs gtk+-2.0` $^ -o $@
clean:
	rm -rf vbox vpaned table
