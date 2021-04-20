/*
 *
 *  Microsim (µsim) - small life simulation game
 *  Copyright (C) 2021 Elias Leitinger (eliasleiti@gmail.com)
 *
 *  usim is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as
 *  published by the Free Software Foundation, either version 3 of the
 *  License, or any later version.
 *
 *  usim is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */



/*
 *Main file for the Simulator
 */



#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include <ncurses.h>
#include "./types.h"
#include "./walls.c"
#include "./define.h"
#include "stacks.c"

int world[XWORLD][YWORLD]; /*array which contains the world*/
int walls[XWORLD][YWORLD]; //wall array
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
int run = 1;  //main game loop enabled
char input; //used for input processing
long int cycle = 0; //cycle counter

unsigned int xcursor = 0; //x and y pos of cursor
unsigned int ycursor = 0;

struct selection{   //struct for selections
	int x;
	int y;
	int enabled;
};

struct selection build; //point selection for building

struct timeval start, end; //timevals which contain start and end time of main loop
/*struct timespec wait, rem;*/
long duration; //end - start




/*
 * Sleep for number of microseconds
 */

void usleep(long microseconds)
{
	struct timespec ts;
	if(microseconds < 0)
		return;
	ts.tv_sec = 0;             /* whole seconds */
	ts.tv_nsec = (microseconds % 1000000) * 1000;    /* remainder, in nanoseconds */
	nanosleep(&ts, NULL);
}



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

int ini()
{
	ini_bar();
	ini_world();
	ini_wall();
	build.x = 0;
	build.y = 0;
	build.enabled = 0;
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

	/* build selection */
	if(build.enabled){
		mvaddch(build.y, build.x, 'X');
	}
	
	mvprintw(YSCREEN - 1, 0, "A: ");
	/*printw("%d", barvar[0]);*/
	printw("%d", cycle++);

	/* Cursor Section */
	move(ycursor, xcursor);
	refresh();
	
	return 0;
}



void wtest()
{
	world[3][3]=1;
	walls[2][2]=1;
	walls[3][2]=1;
	walls[1][2]=1;
	walls[0][2]=1;
	walls[0][1]=2;
	walls[0][0]=1;
	walls[1][0]=1;
	walls[2][0]=1;
	walls[2][0]=1;
	walls[3][0]=1;
	walls[3][1]=1;
}


/*
 * called to process input when required
 */

int evalkey(char input)
{
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
	case 'e':
		build.x = xcursor;
		build.y = ycursor;
		if(build.enabled)
			build.enabled = 0;
		else
			build.enabled = 1;
		break;
	case 'r':
		//bwall(xcursor, ycursor, build); TODO!
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

	
 	ini();
	wtest();
	draw();
	while(run){
		gettimeofday(&start, NULL); //cycle time start
	
		input = getch();
		if(input != ERR)
			evalkey(input);
		draw();

	        gettimeofday(&end, NULL); //cycle time end
		duration = end.tv_usec - start.tv_usec;
		usleep(CYCLETIME - duration); //sleep to make sure cycle takes ~CYCLETIME
	}
	
	endwin();
	curs_set(1);
	return 0;
}
