CC=gcc
CFLAGS=`pkg-config --cflags --libs gstreamer-1.0`

AIDJ: main.c
	$(CC) -o AIDJ main.c $(CFLAGS)



#gcc main.c -o AIDJ `pkg-config --cflags --libs gstreamer-1.0`