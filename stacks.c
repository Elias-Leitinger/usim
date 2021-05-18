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
#ifndef STACKS_H
#define STACKS_H



#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <limits.h>
#include "define.h"

/* type for stacks */
typedef struct stack stack;

/*
 * *elements: pointer to array elements
 * size: amount of allocated array elements
 * index: index of highest element 
 */
struct stack {
	int *elements;
	int size;
	int index;
};


stack * makestack()
{
	stack *st;
	st = malloc(sizeof(stack));
	if(st == NULL)
		exit(11);
	st->elements = malloc(STCKBLK * sizeof(st->elements));
	if(st->elements == NULL)
		exit(11);
	
	st->size = STCKBLK;
	st->index = 0;
	st->elements[0] = STCKINI;
	return st;
}

int freestack(stack *st)
{
	free(st->elements);
	free(st);
	return 0;
}

/*int clearstack(stack *st)  FUBAR
{
	
	freestack(st);
	st = malloc(sizeof(stack));
	st->elements = malloc(STCKBLK  * sizeof(st->elements));
	
	st->index = 0;
	st->size = STCKBLK;
	st->elements[0] = STCKINI;
	return 0;
	}*/

int push(stack *st, int value)
{
	if((st->index + 1) >= st->size){
		st->elements = realloc(st->elements, (st->size + STCKBLK) * sizeof(st->elements));
		if(st->elements == NULL)
			exit(11);
		st->size += STCKBLK;
	}
	
	st->index++;
	st->elements[st->index] = value;
	return 0;
}

int top(stack *st)
{
	return st->elements[st->index];
}

int pop(stack *st)
{
	if(st->index == 0){
		return INT_MIN;
	}else if(st->index < (st->size - STCKBLK)){
		st->elements = realloc(st->elements, sizeof(int) * st->size -\
				       sizeof(int) * STCKBLK);
		st->size -= STCKBLK;
		return st->elements[st->index--];
	}else
		return st->elements[st->index--];
}


#endif
