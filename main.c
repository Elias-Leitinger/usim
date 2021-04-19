/*
 *Main file for the Simulator
 */



#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>
#include "./types.h"
#include "./walls.c"
#include "./define.h"

int world[XWORLD][YWORLD]; /*array which contains the world*/
int walls[XWORLD][YWORLD];
int bar[XBAR][YBAR]; /* array which contains the status bar */
int barvar[]={
	1,
	2
};
char type2char[]={     /* table for converting entity/object id to printable char */
	'.',
	'a'
};
unsigned int x = 0; /* vars for loops */
unsigned int y = 0;
int run = 1;
char input;
int cycle = 0;

unsigned int xcursor = 0;
unsigned int ycursor = 0;

/*
 * Run at the start of the session to initiate the world array to id 0
 */
int ini_world()
{
	for(y = 0; y < YWORLD; y++){
		for(x = 0; x < XWORLD; x++){
			world[x][y] = 0;
		}
	}
	return 0;
}

/*
 *Initiate wall array
 */
int ini_wall()
{
	for(y = 0; y < YWORLD; y++){
		for(x = 0; x < XWORLD; x++){
			world[x][y] = 0;
		}
	}
	return 0;
}

/*
 * Clear bar and initiate fill it with '='
 */
int ini_bar()
{

	for(y = 0; y < YBAR; y++){
		for(x = 0; x < XBAR; x++){
			bar[x][y] = ' ';
		}
	}
	for(x = 0; x < XBAR; x++){
			bar[x][0] = '=';
		}
	return 0;
}


/*
 * Draw the World and the status bar in the appropriate locations
 */
int draw()
{
	
	/* World Part */
	for(y = 0; y < YWORLD; y++){
		for(x = 0; x < XWORLD; x++){
			
			mvaddch(y, x, type2char[ world[x][y] ]);
		}
	}

	/* Wall Part TODO: Add logic for connected worlds*/
	for(y = 0; y < YWORLD; y++){
		for(x = 0; x < XWORLD; x++){

			if(walls[x][y]){
				mvaddch(y, x, wallt(x, y,walls));
			}
		}
	}

	/* TODO Add logic to draw entities and creaste entity storage*/
	
	/* bar section */
	for(y = 0; y < YBAR; y++){
		for(x = 0; x < XBAR; x++){
			
			mvaddch(y + YWORLD, x, bar[x][y]);
		}
	}
	mvprintw(YSCREEN - 1, 0, "A: ");
	/*printw("%d", barvar[0]);*/
	printw("%d", cycle++);

	/* Cursor Section */
	move(ycursor, xcursor);
	refresh();
	
	return 0;
}

int ini()
{
	ini_bar();
	ini_world();
	ini_wall();
	return 0;
}

void wtest()
{
	world[3][3]=1;
	walls[2][2]=1;
	walls[3][2]=1;
	walls[1][2]=1;
	walls[0][2]=1;
	walls[0][1]=1;
	walls[0][0]=1;
	walls[1][0]=1;
	walls[2][0]=1;
	walls[2][0]=1;
	walls[3][0]=1;
	walls[3][1]=1;
}

int evalkey(char input){
	switch(input){
	case ESC:
		run = 0;
		break;
	case 'w':
		if(ycursor != 0)
			ycursor--;
		break;
	case 's':
		if(ycursor < YWORLD - 1)
			ycursor++;
		break;
	case 'a':
		if(xcursor != 0)
			xcursor--;
		break;
	case 'd':
		if(xcursor < XWORLD - 1)
			xcursor++;
		break;
	case 'q':
		walls[xcursor][ycursor] = 1;
		break;
	default:{};
	}
	return 0;
}

int main()
{
	curs_set(0);
	initscr();
	cbreak(); /*No line break for getch*/
	noecho(); /*No echoing*/
	nodelay(stdscr, TRUE); /*no getch timeout*/

	
        /*ini_bar();
	ini_world();
	ini_wall();*/
 	ini();
	wtest();
	draw();
	while(run){
		input = getch();
		if(input != ERR)
			evalkey(input);
		draw();
	}
	
	endwin();
	curs_set(1);
	return 0;
}
