.PHONY: build test

build:
	gcc -Wall -o out main.c linked_list.c

test:
	gcc -Wall -o tests test_main.c linked_list.c && ./tests
