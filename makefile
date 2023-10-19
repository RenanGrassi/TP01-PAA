all:
	clear
	gcc ./headers/include.h	 ./headers/map.h	./headers/solution.h	./headers/terminal.h	 ./arquivoC/map.c	./arquivoC/solution.c	./arquivoC/terminal.c	   main.c	-lncurses	-lm  -o	 exec
	./exec
	
	
	make clean

clean:
	rm -rf *.o ./exec
	clear
