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


#include "define.h"


char wallt (int x, int y, int walls[][YWORLD])
{
	int left = (x == 0) ? 0 : walls[x - 1][y];
	int up = (y == 0) ? 0 : walls[x][y - 1];
	int right = ((x + 1) == XWORLD) ? 0 : walls[x + 1][y];
	int down = ((y + 1) == YWORLD) ? 0 : walls[x][y + 1];

	/*int sum = left + right + up + down;
	if(sum >= 3)
	  return '+';*/
	
	if(up && down)
		return '|';
	else if(left && right)
		return '-';
	else if((up || down) && !(left || right))
		return '|';
	else if((left || right) && !(up || down))
		return '-';
	else
		return'+';
}
