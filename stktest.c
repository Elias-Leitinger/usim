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


#include <stdio.h>
#include "stacks.c"

/* Simple program to test stack functions*/

/*
Output should be

3 <-simple push and pop
2 <-´
99 <- push to stack with index > STCKBLK
ERR: pop on stack with index 0!  
-1        This error *should* occour! -1 is empty stack init
4  <- top function test
4  <-´

 */


int main()
{
	int i;
	stack *S = makestack();
	push(S, 2);
	push(S, 3);
	printf("%d\n", pop(S));
	printf("%d\n", pop(S));
	for(i = 0; i < 100; i++)
		push(S, i);
	printf("%d\n", pop(S));
	clearstack(S);
	printf("%d\n", pop(S));
	freestack(S);
	S = makestack();
	push(S, 4);
	printf("%d\n", top(S));
	printf("%d\n", pop(S));
	return 0;
}