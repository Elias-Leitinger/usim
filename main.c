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
int collision[XWORLD][YWORLD]; /*Used for collision detection*/
entity people[MAXENT];
int barvar[]={
	1,
	2
};
char type2char[]={     /* table for converting entity/object id to printable char */
	'.',
	'a'
};
//unsigned int x = 0; /* vars for loops */
//unsigned int y = 0;
//unsigned int tmp = 0;
int run = 1;  //main game loop enabled
char input; //used for input processing
long int cycle = 0; //cycle counter

unsigned int xcursor = 0; //x and y pos of cursor
unsigned int ycursor = 0;

typedef struct selection selection;

struct selection{   //struct for selections
	unsigned int x;
	unsigned int y;
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
	for(int y = 0; y < YWORLD; y++){
		for(int x = 0; x < XWORLD; x++){
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
	for(int y = 0; y < YWORLD; y++){
		for(int x = 0; x < XWORLD; x++){
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

	for(int y = 0; y < YBAR; y++){
		for(int x = 0; x < XBAR; x++){
			bar[x][y] = ' ';
		}
	}
	for(int x = 0; x < XBAR; x++){
			bar[x][0] = '=';
		}
	return 0;
}

int ini_people()
{
	for(int tmp = 0; tmp < MAXENT; tmp++)
		people[tmp].type = 0;
	return 0;
}

int ini()
{
	ini_bar();
	ini_world();
	ini_wall();
	ini_people();
	build.x = 0;
	build.y = 0;
	build.enabled = 0;
	return 0;
}


void makecoll() //TODO: Test
{
	for(int y = 0; y < YWORLD; y++){
		for(int x = 0; x < XWORLD; x++){
			collision[x][y] = walls[x][y] == 1 ? 1 : collision[x][y];
			collision[x][y] = world[x][y] != 0 ? 1 : collision[x][y];
			//mvaddch(y, x, type2char[ world[x][y] ]);
		}
	}
}


int move_peeps()
{
	for(int index = 0; index < MAXENT; index++){
		if(people[index].type){
			int x = pop(people[index].path_x);
			int y = pop(people[index].path_y);
			if(x != INT_MIN && y != INT_MIN){
				people[index].x = x;
				people[index].y = y;
			}
				
		}
			
	}
	return 0;
}

/*
 * Draw the World and the status bar in the appropriate locations
 */
int draw()
{
	
	/* World Part */
	for(int y = 0; y < YWORLD; y++){
		for(int x = 0; x < XWORLD; x++){
			
			mvaddch(y, x, type2char[ world[x][y] ]);
		}
	}

	/* Wall Part TODO: Add logic for connected worlds*/
	for(int y = 0; y < YWORLD; y++){
		for(int x = 0; x < XWORLD; x++){

			if(walls[x][y]){
				mvaddch(y, x, wallt(x, y,walls));
			}
		}
	}

	/* TODO Add logic to draw entities and creaste entity storage*/

	for(int tmp = 0; tmp < MAXENT; tmp++){
		if(people[tmp].type != 0)
			mvaddch(people[tmp].y, people[tmp].x, type2char[people[tmp].type]);
	}
	
	/* bar section */
	for(int y = 0; y < YBAR; y++){
		for(int x = 0; x < XBAR; x++){
			
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

	makecoll();
	
	return 0;
}


int bwall(int org_x,int org_y,int des_x,int des_y)
{
	int start; //smaller number 
	int end;
	int other;
	int x_diff = org_x != des_x ? 1 : 0;
	int y_diff = org_y != des_y ? 1 : 0;
	int loop; //loop iteration variable
	if(x_diff == y_diff){ //if both pairs are equal or different
		walls[org_x][org_y] = 1;
		return 1;
	}
	if(x_diff){
		start = org_x < des_x ? org_x : des_x;
		end = org_x > des_x ? org_x : des_x;
		other = org_y;
	}
	if(y_diff){
		start = org_y < des_y ? org_y : des_y;
		end = org_y > des_y ? org_y : des_y;
		other = org_x;
	}

	for(loop = start; loop <= end; loop++){
		if(x_diff)
			walls[loop][other] = 1;
		if(y_diff)
			walls[other][loop] = 1;
	}
	
	return 0;
}

void wtest()  //remove asap!!
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
	people[0].type = 1;
	people[0].x = 10;
	people[0].y = 10;
	people[0].path_x = makestack();
	people[0].path_y = makestack();
	push(people[0].path_x, 20);
	push(people[0].path_y, 15);
}

int setbcurs(){
	int samepos = 0;
	if(build.x == xcursor && build.y == ycursor)
		samepos = 1;
	build.x = xcursor;
	build.y = ycursor;
	if(build.enabled && samepos)
		build.enabled = 0;
	else
		build.enabled = 1;
	return 0;
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
		walls[xcursor][ycursor] = 2;
		break;
	case 'e':
		setbcurs();
		break;
	case 'r':
		if(build.enabled){
			bwall(xcursor, ycursor, build.x, build.y);
			build.x = xcursor;
			build.y = ycursor;
		}
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
		if(cycle % 100 == 0)
			move_peeps();
	        gettimeofday(&end, NULL); //cycle time end
		duration = end.tv_usec - start.tv_usec;
		usleep(CYCLETIME - duration); //sleep to make sure cycle takes ~CYCLETIME
	}
	
	endwin();
	curs_set(1);
	return 0;
}
