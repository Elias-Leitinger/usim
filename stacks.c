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

#include <stdlib.h>
#include <stdio.h>
#include "define.h"

/* type for stacks */
typedef struct stack stack;

/*
 * *elements: pointer to array elements
 * size: amount of allocated array elements
 * index: index of highest element 
 * example: highest element of array: { *(stack.elements + stack.index) }
 * TODO: TEST FUNCTIONS
 * TODO: make stack->elements samaller when possible in pop function
 */
struct stack {
	int *elements;
	int size;
	int index;
};

stack * makestack()
{
	stack *stack;
	stack = malloc(sizeof(stack));
	stack->elements = malloc(STCKBLK * sizeof(int));
	
	stack->size = STCKBLK;
	stack->index = 0;
	stack->elements[0] = STCKINI;
	return stack;
}

int freestack(stack *stack)
{
	free(stack->elements);
	free(stack);
	return 0;
}

int clearstack(stack *stack)
{
	
	freestack(stack);
	stack = malloc(sizeof(stack));
	stack->elements = malloc(STCKBLK * sizeof(int));
	
	stack->index = 0;
	stack->size = STCKBLK;
	stack->elements[0] = STCKINI;
	return 0;
}

int push(stack *stack, int value)
{
	if((stack->index + 1) >= stack->size){
		stack = realloc(stack, stack->size + STCKBLK);
		stack->size += STCKBLK;
	}
	
	stack->index++;
	stack->elements[stack->index] = value;
	return 0;
}

int top(stack *stack)
{
	return stack->elements[stack->index];
}

int pop(stack *stack)
{
	if(stack->index == 0){
		printf("ERR: pop on stack with index 0!");
		return stack->elements[0];
	}
	else
		return stack->elements[stack->index--];
}
