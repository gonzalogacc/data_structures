.PHONY: build test

build:
	gcc -o out main.c linked_list.c

test:
	gcc -o tests test_main.c linked_list.c
	./tests
