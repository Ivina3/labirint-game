
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
#include <random>

void mob_walking(map_t map, cord_t* co_m, int col_mob, move_obj_desc_t der) {
	int ran;
	for (int i = 0; i < col_mob; i++) {
		int x = co_m[i].x;
		int y = co_m[i].y;
		double dx1 = x - der.to_x, dy1 = y - der.to_y;
		double s1 = sqrt(dx1*dx1 + dy1 * dy1);

		 dx1=x-der.to_x, dy1 = y-1-der.to_y;
		double dx2 = x+1 -der.to_x, dy2 = y -der.to_y;
		double s2 = sqrt(dx1*dx1 + dy1*dy1);
		double s3= sqrt(dx2*dx2 + dy2*dy2);
		 dx1 = x - der.to_x, dy1 = y+1 - der.to_y;
		 dx2 = x-1 - der.to_x, dy2 = y - der.to_y;
		 double s4 = sqrt(dx1*dx1 + dy1 * dy1);
		 double s5 = sqrt(dx2*dx2 + dy2 * dy2);

		


		double p[5];
		p[0] = 1.0 / (s1 + 0.00000001);
		p[1] = 1.0 / (s2 + 0.00000001);
		p[2] = 1.0 / (s3 + 0.00000001);
		p[3] = 1.0 / (s4 + 0.00000001);
		p[4] = 1.0 / (s5 + 0.00000001);
		double sum_p = p[0] + p[1] + p[2] + p[3] + p[4];
		p[0] = p[0] / sum_p;
		p[1] = p[1] / sum_p;
		p[2] = p[2] / sum_p;
		p[3] = p[3] / sum_p;
		p[4] = p[4] / sum_p;

		//ran = rand() % 5;

		static std::random_device rd;
		static std::mt19937 gen(rd());
		std::discrete_distribution<> d({ p[0], p[1], p[2], p[3], p[4] });
		
		ran = d(gen);

		/*double bigger_p = 0;
		int best_idx = 0;
		for (int c = 0; c < 5; c++)
		{
			if (p[c] > bigger_p)
			{
				bigger_p = p[c];
				best_idx = c;
			}
		}

		ran = best_idx;*/

		if (ran == 0)
		{

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
