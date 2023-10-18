all:
	clear
	gcc ./headers/include.h	 ./headers/map.h	./headers/solution.h	 ./arquivoC/map.c	./arquivoC/solution.c	   main.c	-lm  -o	 exec
	./exec
	
	
	make clean

clean:
	rm -rf *.o ./exec
	clear
