#include <stdio.h>
#include <graphics.h>
#include <windows.h>
#include <stdlib.h>
#include <iostream>
#include <conio.h>
#include "driver.h"
#include "PacMap.h"


typedef struct {
    int posX;
    int posY;
    int state;
    int direction;
    int score;


} MovePacboy;

  int isWall(int x)   {
    return x & 8;
}
int ispac(int x)    {
    return x & 2;
}
int isFood(int x)   {
    return x & 1;
}

MovePacboy pac;

int play();
int menuscore();
void about_us();
void loading();
void changeState(int *state);
void Move(int arena[28][24], MovePacboy *PacBoy);
void mapping(int arena[28][24]);




int play()
{
	cleardevice();
	loading();
	char input;
    pac.posX = 59;
    pac.posY = 19;


    pac.state = 1;
    pac.direction = 5;



    pac.score = 0;
    char skor[20];
    int page = 0;
    int a = 0;
    while (true)
        {
            printf("X=%d Y=%d \n",pac.posX,pac.posY);
            a++;
            setactivepage(page);
            setvisualpage(1 - page);
            cleardevice();

            if (kbhit())
            {
                input = getch();
                switch(input)
                {
                    case RightArrow     :   pac.direction = RIGHT;break;
                    case LeftArrow      :   pac.direction = LEFT;break;
                    case DownArrow      :   pac.direction = DOWN;break;
                    case UpArrow        :   pac.direction = UP;break;
                }
            }

        Move(arena, &pac);
        changeState(&pac.state);
        sprintf(skor, "Score : %d", pac.score);
        setcolor(YELLOW);
        outtextxy(380,580, skor);
        if (a%2 == 0) {
        }

        page = 1-page;
        mapping(arena);
        delay(150);
    }

}
