default:
	mkdir -p bin
	gcc -std=c99 -o bin/red red.c
	gcc -std=c99 -o bin/test_red test_red.c
	./bin/test_red
