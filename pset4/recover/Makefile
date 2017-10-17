recover: recover.c
	clang -fsanitize=integer -fsanitize=undefined -ggdb3 -O0 -std=c11 -Wall -Werror -Wextra -Wno-sign-compare -Wshadow    recover.c  -lcrypt -lcs50 -lm -o recover

clean:
	rm -f *.jpg