
#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "win_setup.h"

#include <chrono>
#include <thread>
#include "types.h"

void mob_walking(map_t map, cord_t* co_m, int col_mob) {
	int ran;
	for (int i = 0; i < col_mob; i++) {
		int x = co_m[i].x;
		int y = co_m[i].y;
		ran = rand() % 5;

		if (ran == 0) {


		}
		else if (ran == 1) {
			if (map.field[(y - 1)*map.w + x] != stena && map.field[(y - 1)*map.w + x] != person && map.field[(y - 1)*map.w + x] != mob&& map.field[y *map.w + x + 1] != exittt) {
				map.field[(y - 1)*map.w + x] = mob;
				map.field[y *map.w + x] = space;
				co_m[i].y = y - 1;
			}

		}
		else if (ran == 2) {
			if (map.field[y *map.w + x + 1] != stena && map.field[y *map.w + x + 1] != person && map.field[y *map.w + x + 1] != mob && map.field[y *map.w + x + 1] != exittt) {
				map.field[y *map.w + x + 1] = mob;
				map.field[y *map.w + x] = space;
				co_m[i].x = x + 1;
			}
		}
		else if (ran == 3) {
			if (map.field[(y + 1)*map.w + x] != stena && map.field[(y + 1)*map.w + x] != person && map.field[(y + 1)*map.w + x] != mob && map.field[y *map.w + x + 1] != exittt) {
				map.field[(y + 1)*map.w + x] = mob;
				map.field[y *map.w + x] = space;
				co_m[i].y = y + 1;
			}
		}
		else if (ran == 4) {
			if (map.field[y *map.w + x - 1] != stena  && map.field[y *map.w + x - 1] != person && map.field[y *map.w + x - 1] != mob && map.field[y *map.w + x + 1] != exittt) {
				map.field[y *map.w + x - 1] = mob;
				map.field[y *map.w + x] = space;
				co_m[i].x = x - 1;
			}

		}
	}


	/*int c = field[w*y + x];*/


}

move_res_t move_step_in_labyrinth( map_t map, move_obj_desc_t desc)
{
	move_res_t res;

	if (desc.from_x == desc.to_x && desc.from_y == desc.to_y)
	{
		res.name = desc.name;
		res.ok = true;
		return res;
	}

	int&	to = map.field[map.w*desc.to_y + desc.to_x];
	int&	from = map.field[map.w*desc.from_y + desc.from_x];

	if (from != desc.name)
	{
		res.ok = false;
		return res;
	}

	if (to != stena)
	{
		res.name = to;
		to = desc.name;
		from = space;
		res.ok = true;

		return res;
	}
	res.ok = false;
	return res;
}
