/*
 *Main file for the Simulator
 */



#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>
#include "./types.h"
#include "./walls.h"
#include "./define.h"

int world[YWORLD][XWORLD]; /*array which contains the world*/
int walls[YWORLD][XWORLD];
int bar[YBAR][XBAR]; /* array which contains the status bar */
int barvar[]={
	1,
	2
};
char id2char[]={     /* table for converting entity/object id to printable char */
	'.',
	'a'
};
unsigned int x = 0; /* vars for loops */
unsigned int y = 0;

unsigned int xcursor = 0;
unsigned int ycursor = 0;

/*
 * Run at the start of the session to initiate the world array to id 0
 */
int ini_world()
{
	for(y = 0; y < YWORLD; y++){
		for(x = 0; x < XWORLD; x++){
			world[y][x] = 0;
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
			world[y][x] = 0;
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
			bar[y][x] = ' ';
		}
	}
	for(x = 0; x < YBAR; x++){
			bar[y][0] = '=';
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
			
			mvaddch(y, x, id2char[ world[y][x] ]);
		}
	}

	/* Wall Part TODO: Add logic for connected worlds*/
	for(y = 0; y < YWORLD; y++){
		for(x = 0; x < XWORLD; x++){

			if(walls[y][x]){
				mvaddch(y, x, wallt(y, x,walls));
			}
		}
	}

	/* TODO Add logic to draw entities and creaste entity storage*/
	
	/* bar section */
	for(y = 0; y < YBAR; y++){
		for(x = 0; x < XBAR; x++){
			
			mvaddch(y + YWORLD, x, bar[y][x]);
		}
	}
	mvprintw(YSCREEN - 1, 0, "A: ");
	printw("%d", barvar[0]);

	/* Cursor Section */
	/*move(ycursor, xcursor);*/
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

int main()
{
	curs_set(0);
	initscr();
	/*ini_bar();
	ini_world();
	ini_wall();*/
	ini();
	world[3][3]=1;
	walls[2][2]=1;
	walls[3][2]=1;
	walls[1][2]=1;
	walls[0][2]=1;
	walls[0][1]=1;
	walls[0][0]=1;
	draw();
	getchar();
	endwin();
	curs_set(1);
	return 0;
}
