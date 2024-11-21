# Makefile for Cooke Parser Project

CC = gcc
CFLAGS = -std=c99 -Wall
TARGET = cooke_parser
SOURCES = parser.c front.c
HEADERS = parser.h front.h

all: $(TARGET)

$(TARGET): $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES)

clean:
	rm -f $(TARGET)
