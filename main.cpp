#include <stdio.h>
#include <graphics.h>
#include <windows.h>
#include <stdlib.h>
#include <iostream>
#include <conio.h>
#include <Mmsystem.h>

#include"driver.h"
#include"PacMap.h"

#define SND_LOOP 8
#define SND_ASYNC 1


int main();
int play();
int menuscore();
void about_us();

typedef struct {  //struct untuk kondisi Pac-Bae
    int posX;
    int posY;
    int state;
    int direction;
    int score;
} MovePacBae;

MovePacBae pac;

void loading(){ // Julid Gema dan Rizal
	int n;

	setcolor(YELLOW);
outtextxy(210,280,"L");Sleep(100);
outtextxy(220,283,"O");Sleep(100);
outtextxy(230,280,"A");Sleep(100);
outtextxy(240,283,"D");Sleep(100);
outtextxy(250,280,"I");Sleep(100);
outtextxy(255,283,"N");Sleep(100);
outtextxy(265,280,"G");Sleep(100);



for (n=0; n<420; n++)
{
   rectangle(30,590,30+n,595);
   delay(5);
}

settextstyle(3,HORIZ_DIR,2);
outtextxy(170,280,"PRESS ANY KEY");
getch();
cleardevice();
}
void menu();

int kursor(int option, int x, int y)
{
	int select=1;
	int input;
	outtextxy(x,y,">"); //menampilkan lambang kursor
	do
	{
		input=getch();
		if(input==80) //80 kode ASCII kursor bawah
		{
			outtextxy(x,y,"  ");
			y=y+20;
			 select++;
			if(select>option)
			{
				y=y-(20*option);
				select=1;
			}
			outtextxy(x,y,">"); //menampilkan lambang kursor
		}
		if(input==72) //72 kode ASCII kursor atas
		{
			outtextxy(x,y,"  ");
			y=y-20;
			select--;
			if (select<1)
			{
				y=y+(20*option);
				select=option;
			}
			outtextxy(x,y,">"); //menampilkan lambang kursor
		}
	}
	while(input!=13);
	return select;
}

int menuscore()
{
	cleardevice();
	settextstyle(3, HORIZ_DIR,5);
	outtextxy(60,30,"SCOREBOARD");
	getch();
	cleardevice();
	main();
}
//modul menampilkan cara permainan
int menuhow_to_play()
{

    cleardevice();
    settextstyle(3, HORIZ_DIR,4);
    outtextxy(100,150,"HOW TO PLAY");
    settextstyle(3, HORIZ_DIR,1);
    outtextxy(80,250,"UP = Keypad UP");
    outtextxy(80,270,"");
    outtextxy(80,300,"DOWN = Keypad DOWN");
    outtextxy(80,320,"");
    outtextxy(80,350,"RIGHT = Keypad RIGHT");
    outtextxy(80,370,"");
    outtextxy(80,400,"LEFT = Keypad LEFT");
    outtextxy(80,420,"");
    outtextxy(80,450,"BACK = BACKSPACE");
    outtextxy(80,470,"");
   getch();
   cleardevice();
   main();
}
//modul menampilkan about us
void about_us()
{
    cleardevice();
    settextstyle(3, HORIZ_DIR,4);
    outtextxy(140,150,"ABOUT US");
    settextstyle(3, HORIZ_DIR,1);
    outtextxy(80,250,"Adhitya Noor Muslim");
    outtextxy(80,270,"161511001");
    outtextxy(80,300,"Akmal Muhammad Kristanto");
    outtextxy(80,320,"161511004");
    outtextxy(80,350,"Fadhlan Ariq Mahmoeddin");
    outtextxy(80,370,"161511008");
    outtextxy(80,400,"Ira Kusnindi");
    outtextxy(80,420,"161511012");
    outtextxy(80,450,"Irza Aprilian Aliando");
    outtextxy(80,470,"161511013");
   getch();
   cleardevice();
   main();
}

void menu()      //tampilan menu
{

    outtextxy(205,360,"Start Game");
	outtextxy(205,380,"High Score");
	outtextxy(205,400,"How to Play");
	outtextxy(205,420,"About Us");
	outtextxy(205,440,"Quit");

}

void drawWall(int posX, int posY) //prosedur penggambaran wall
{
    setcolor(BLUE);
    setfillstyle(SOLID_FILL,BLUE);
    rectangle(posX, posY, posX + RecSize, posY + RecSize);
    bar(posX, posY, posX + RecSize, posY + RecSize);
}

void scoring(int arena[28][24], MovePacBae *PacBae) //prosedur scoring(beta)
{

}

void drawpac(int posX,int posY) //prosedur penggambaran pac-bae
{

    setcolor(14);
    setfillstyle(SOLID_FILL, 14);
    int state = pac.state;
    int direction = pac.direction;
    pieslice(posX, posY,45 + (90 * direction) - (30 * state), -45 + (90 * direction) + (30 * state), RecSize/2);
}

void drawFood(int posX, int posY) //prosedur penggambaran makanan
{
    setcolor(14);
    setfillstyle(SOLID_FILL,14);

    bar(posX-2, posY-2, posX + RecSize/4.5, posY + RecSize/4.5);

}

void power(int posX,int posY) //prosedur penggambaran bonus
{

    setcolor(14);

    circle(posX, posY, RecSize/2.5);

}



void mapping(int arena[28][24]) //prosedur penggambaran map
{
    int i, j;
    readimagefile("pacman.bmp",180,20,65,95);
    for (i=0;i<28;i++) {
        for(j=0;j<24;j++) {
            if (arena[i][j]==8)
            {
                drawWall(j * RecSize, i * RecSize);
            }
            if (arena[i][j]==2)
            {
                drawpac(j * RecSize + (RecSize/2), i * RecSize + (RecSize/2));
            }
            if (arena[i][j]==1)
            {
                drawFood(j * RecSize + (RecSize/2), i * RecSize + (RecSize/2));
            }
            if (arena[i][j]==7)
            {
                power(j * RecSize + (RecSize/2), i * RecSize + (RecSize/2));
            }

        }
    }
}


void changeState(int *state) //infinite loop untuk state mulut pac-bae agar terus terbuka dan tertutup
{
    if (*state == 1) {
        *state = 0;

}    else {
        *state = 1;
    }
}

void win() //kondisi ketika menang(belum fix)
{
    cleardevice();
    printf("you win");
}

void Move(int arena[28][24], MovePacBae *PacBae) //prosedur perpindahan pac-bae
{
    switch (PacBae->direction) {

        case RIGHT :

            if (arena[PacBae->posY][PacBae->posX+1]!=8) //kondisi perpindahan ke kanan (terjadi pengecekan tembok)
            {
                PlaySound("Sounds/pacman_chomp.wav",NULL,SND_ASYNC|SND_NOWAIT|SND_NOSTOP); //pemanggilan audio
                arena[PacBae->posY][PacBae->posX+1]=2;
                arena[PacBae->posY][PacBae->posX]=4;
                PacBae->posX++;
                if(arena[PacBae->posY][PacBae->posX+1]!=4) //kondisi untuk scoring
                {
                    PacBae->score+=FScore;
                    if(arena[PacBae->posY][PacBae->posX+1]==8)
                    {
                            PacBae->score-=FScore;
                    }

                    if((PacBae->posX==70 && PacBae->posY==3||PacBae->posX==70 && PacBae->posY==20)&& arena[PacBae->posY][PacBae->posX+1]==8)
                    {

                        PlaySound("Sounds/pacman_eatfruit.wav",NULL,SND_ASYNC|SND_NOWAIT|SND_PURGE);
                        PacBae->score+=(FScore*10);
                    }
                    }



            }
            if (PacBae->posX==71 && PacBae->posY==13) //kondisi teleportasi pada ujung array tertentu
            {
            PlaySound("Sounds/pacman_eatfruit.wav",NULL,SND_ASYNC|SND_NOWAIT|SND_PURGE);
            arena[PacBae->posY][PacBae->posX]=4;
            pac.posX = 48;
            pac.posY = 13;
            PacBae->score-=1;


            }
                break;
        case LEFT :
            if (arena[PacBae->posY][PacBae->posX-1]!=8) //kondisi perpindahan ke kiri (terjadi pengecekan wall)
            {
                PlaySound("Sounds/pacman_chomp.wav",NULL,SND_ASYNC|SND_NOWAIT|SND_NOSTOP);
                arena[PacBae->posY][PacBae->posX-1]=2;
                arena[PacBae->posY][PacBae->posX]=4;
                PacBae->posX--;
                if (arena[PacBae->posY][PacBae->posX-1]!=4) //kondisi scoring
                {
                    PacBae->score+=FScore;
                    if(arena[PacBae->posY][PacBae->posX-1]==8)
                    {
                        PacBae->score-=FScore;
                    }

                    if((PacBae->posX==49 && PacBae->posY==3 || PacBae->posX==49&& PacBae->posY==20) && arena[PacBae->posY][PacBae->posX-1]==8) //kondisi scoring untuk bonus
                    {
                            PlaySound("Sounds/pacman_eatfruit.wav",NULL,SND_ASYNC|SND_NOWAIT|SND_PURGE);
                            PacBae->score+=(FScore*10);
                    }
                }
            }
                if (PacBae->posX==48 && PacBae->posY==13) //kondisi teleportasi
                {
                    PlaySound("Sounds/pacman_eatfruit.wav",NULL,SND_ASYNC|SND_NOWAIT|SND_PURGE);
                    arena[PacBae->posY][PacBae->posX]=4;
                    pac.posX = 71;
                    pac.posY = 13;
                    PacBae->score-=1;
                }

                break;
        case DOWN :

            if (arena[PacBae->posY+1][PacBae->posX]!=8) //kondisi perpindahan ke bawah (terjadi pengecekan wall)
            {
                PlaySound("Sounds/pacman_chomp.wav",NULL,SND_ASYNC|SND_NOWAIT|SND_NOSTOP);
                arena[PacBae->posY+1][PacBae->posX]=2;
                arena[PacBae->posY][PacBae->posX]=4;
                PacBae->posY++;
                if (arena[PacBae->posY+1][PacBae->posX]!=4)
                {
                    PacBae->score+=FScore;
                    if(arena[PacBae->posY+1][PacBae->posX]==8)
                    {
                        PacBae->score-=FScore;
                    }
                    if((PacBae->posX==70 && PacBae->posY==20 || PacBae->posX==49 && PacBae->posY==20) && arena[PacBae->posY+1][PacBae->posX]==8)
                    {
                            PlaySound("Sounds/pacman_eatfruit.wav",NULL,SND_ASYNC|SND_NOWAIT|SND_PURGE);
                            PacBae->score+=(FScore*10);
                    }
                }
            }
                break;
        case UP :
            if (arena[PacBae->posY-1][PacBae->posX]!=8)
            {
                PlaySound("Sounds/pacman_chomp.wav",NULL,SND_ASYNC|SND_NOWAIT|SND_NOSTOP);
                arena[PacBae->posY-1][PacBae->posX]=2;
                arena[PacBae->posY][PacBae->posX]=4;
                PacBae->posY--;
                if (arena[PacBae->posY-1][PacBae->posX]!=4)
                {
                    PacBae->score+=FScore;
                    if(arena[PacBae->posY-1][PacBae->posX]==8)
                    {
                        PacBae->score-=FScore;
                    }
                    if((PacBae->posX==49 && PacBae->posY==3 || PacBae->posX==70 && PacBae->posY==3 )&& arena[PacBae->posY-1][PacBae->posX]==8)
                    {
                            PlaySound("Sounds/pacman_eatfruit.wav",NULL,SND_ASYNC|SND_NOWAIT|SND_PURGE);
                            PacBae->score+=(FScore*10);
                    }
                }
            }
                break;
    }
}


int main() //fungsi utama
{
    initwindow(481,640,"Pac-Baé");
    PlaySound("Sounds/pacman_intermission",NULL,SND_FILENAME|SND_ASYNC|SND_LOOP);
    setcolor(YELLOW);
	readimagefile("pacman.bmp",0,0,481,315);
	settextstyle(12, HORIZ_DIR,3);

    menu();
	int menu = kursor (5,190,360); // pilihan, x,y
	switch(menu) //posisin kursor
	{
		case 1 : play();break;
	    case 2 : menuscore();break;
		case 3 : menuhow_to_play();break;
		case 4 : about_us();break;
		case 5 : ;break;
	}

	getch();

    closegraph();


}

int play() //fungsi game utama
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
    PlaySound("Sounds/pacman_beginning",NULL,SND_FILENAME|SND_ASYNC);
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
        outtextxy(350,580, skor);
        if (a%2 == 0) {
        }

        page = 1-page;
        mapping(arena);
        delay(200);
    }

}
