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

#include "stacks.c"


/* create object type, which contains the infrmation for in game objects*/
typedef struct object object;
/* create type for moving things*/
typedef struct entity entity;
// struct which contains the needs of people
typedef struct needs needs;


/*
id: unique object identifier, if 0, ignore object
type: object type, determines properties of object
user: entity who is using the object
content: content pointer points to contents of the object, use depends on object type. (Box content, Table top)
 */
struct object {
	int id;
	int x;
	int y;
	int type;
	object *content;
};                           

struct needs {
	float food; //values from 0 - 100
	float sleep;//100 is always best,
        float fun;  //0 is always worst
	float toilet;
};

struct entity {
	int type;
	int x;
	int y;
	char *name;
	object *using;
	object *target;
	stack *tasks;
	stack *path_x;
	stack *path_y;
	needs need;
	/* TODO! */
};

