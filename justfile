watch:
	find | entr -c zsh -i -c 'gcc main.c -o main -Wall -Wpedantic && ./main'
