all: hello hello2

hello: hello.c
	cc `pkg-config --cflags --libs gtk+-2.0` $^ -o $@
hello2: hello2.c
	cc `pkg-config --cflags --libs gtk+-2.0` $^ -o $@
clean:
	rm -rf hello hello2
