#include "define.h"
char wallt (int x, int y, int walls[][YWORLD])
{
	int left = (x == 0) ? 0 : walls[x - 1][y];
	int up = (y == 0) ? 0 : walls[x][y - 1];
	int right = ((x + 1) == XWORLD) ? 0 : walls[x + 1][y];
	int down = ((y + 1) == YWORLD) ? 0 : walls[x][y + 1];

	int sum = left + right + up + down;
	if(sum >= 3){
		return '+';
	}else if(left && right){
		return '-';
	}else if(up && down){
		return '|';
	}
	else{
		return'+';
	}
}
