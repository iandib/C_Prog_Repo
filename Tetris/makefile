tetris: main.o common.o th1_gamelogic.o th2_display_sound.o ../libs/joydisp/joydrv.o ../libs/joydisp/disdrv.o ../libs/audio/SDL2/libAudioSDL2.o
	gcc main.o common.o th1_gamelogic.o th2_display_sound.o ../libs/joydisp/joydrv.o ../libs/joydisp/disdrv.o ../libs/audio/SDL2/libAudioSDL2.o -o tetris -g -Wall -lSDL2 -L/home/pi/tpf/libAudioSDL2.o -lpthread
	
main.o: main.c th1_gamelogic.h th2_display_sound.h
	gcc -c main.c -Wall -lpthread
	
common.o: common.c common.h
	gcc -c common.c -Wall -lpthread
	
th1_gamelogic.o: th1_gamelogic.c th1_gamelogic.h common.h th2_display_sound.h
	gcc -c th1_gamelogic.c -Wall -lpthread
	
th2_display_sound.o: th2_display_sound.c th2_display_sound.h common.h ../libs/joydisp/disdrv.h ../libs/joydisp/joydrv.h ../libs/audio/SDL2/src/audio.h
	gcc -c th2_display_sound.c -Wall -lpthread
