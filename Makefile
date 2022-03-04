test1: lab1
	./a.out test1

test2: lab1
	./a.out test2

test3: lab1
	./a.out test3

test4: lab1
	./a.out test4

test5: lab1
	./a.out test5

lab1: urvs_lab1.c
	gcc urvs_lab1.c -Wall -Werror -Wextra