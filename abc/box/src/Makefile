all: libbox.so

libbox.so: box.c
	gcc -o libbox.so -fPIC -shared box.c

clean:
	rm -rf libbox.so

install:
	cp libbox.so /usr/lib
	rm /usr/include/box -rf
	mkdir /usr/include/box
	cp *.h /usr/include/box

uninstall:
	sudo rm /usr/lib/libbox.so
	sudo rm -rf /usr/include/box
