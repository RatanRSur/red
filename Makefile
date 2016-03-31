default:
	mkdir -p bin
	gcc -std=c11 -Wall -Wextra -Wpedantic -o bin/red red.c
	gcc -std=c11 -Wall -Wextra -Wpedantic -o bin/test_red test_red.c
	./bin/test_red
