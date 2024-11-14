tetris: main.o gameLogic.o handler.o common.o raspy.o joydrv.o disdrv.o libAudioSDL2.o
	gcc main.o gameLogic.o handler.o common.o raspy.o joydrv.o disdrv.o libAudioSDL2.o -o tetris -g -Wall -lSDL2 -L/home/pi/tpf/libAudioSDL2.o
 
main.o: main.c gameLogic.h common.h
	gcc -c main.c -o main.o -Wall -g

gameLogic.o: gameLogic.c gameLogic.h handler.h common.h 
	gcc -c gameLogic.c -o gameLogic.o -Wall -g

handler.o: handler.c handler.h allegro.h
	gcc -c handler.c -o handler.o -Wall -g

raspy.o: raspy.c raspy.h common.h disdrv.h joydrv.h libaudio.h
	gcc -c raspy.c -o raspy.o -Wall -g
	
common.o: common.c common.h
	gcc -c common.c -o common.o -Wall -g
clean:
	rm *.o
