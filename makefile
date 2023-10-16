all:
	clear
	gcc ./headers/include.h	 ./headers/map.h	 ./arquivoC/map.c	   main.c	-lm  -o	 exec
	./exec
	
	
	make clean

clean:
	rm -rf *.o ./exec
	clear
