OBJ = image_editor incarcare aplicare selectare decupare rotire salvare diverse
HDS = ./include/incarcare.h ./include/aplicare.h ./include/selectare.h ./include/decupare.h ./include/rotire.h ./include/salvare.h ./include/diverse.h

build: $(OBJ)
	gcc ./bin/*.o -o image_editor -lm

image_editor: image_editor.c $(HDS)
	gcc -c image_editor.c -o ./bin/image_editor.o

incarcare: ./src/incarcare.c
	gcc -c ./src/incarcare.c -o ./bin/incarcare.o

aplicare: ./src/aplicare.c ./include/diverse.h
	gcc -c ./src/aplicare.c -o ./bin/aplicare.o

selectare: ./src/selectare.c
	gcc -c ./src/selectare.c -o ./bin/selectare.o

decupare: ./src/decupare.c ./include/diverse.h
	gcc -c ./src/decupare.c -o ./bin/decupare.o

rotire: ./src/rotire.c
	gcc -c ./src/rotire.c -o ./bin/rotire.o

salvare: ./src/salvare.c
	gcc -c ./src/salvare.c -o ./bin/salvare.o

diverse: ./src/diverse.c
	gcc -c ./src/diverse.c -o ./bin/diverse.o

clean: 
	rm ./bin/*