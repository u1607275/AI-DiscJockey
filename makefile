CC=gcc
CFLAGS=`pkg-config --cflags --libs gstreamer-1.0`
LIBS='-lm'

AIDJ: main.c
	$(CC) -o AIDJ main.c $(LIBS) $(CFLAGS)