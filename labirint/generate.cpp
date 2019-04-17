#include "generate.h"
#include <stdlib.h>
#include <time.h>
#include "types.h"

void generaty_colors(map_t map, int* color) {
	int a = rand() % 3 + 1;
	if (a == 1) {
		color[0] = 3;
		color[1] = 4;
		color[2] = 11;
	}
	else if (a == 2) {
		color[0] = 7;
		color[1] = 5;
		color[2] = 14;
	}
	else {
		color[0] = 10;
		color[1] = 15;
		color[2] = 1;
	}
}
Node *link(Node *n,int width, int height, Node *nodes)
{
	//Connects node to random neighbor (if possible) and returns
	//address of next node that should be visited

	int x, y;
	char dir;
	Node *dest;

	//Nothing can be done if null pointer is given - return
	if (n == NULL) return NULL;

	//While there are directions still unexplored
	while (n->dirs)
	{
		//Randomly pick one direction
		dir = (1 << (rand() % 4));

		//If it has already been explored - try again
		if (~n->dirs & dir) continue;

		//Mark direction as explored
		n->dirs &= ~dir;

		//Depending on chosen direction
		switch (dir)
		{
			//Check if it's possible to go right
		case 1:
			if (n->x + 2 < width)
			{
				x = n->x + 2;
				y = n->y;
			}
			else continue;
			break;

			//Check if it's possible to go down
		case 2:
			if (n->y + 2 < height)
			{
				x = n->x;
				y = n->y + 2;
			}
			else continue;
			break;

			//Check if it's possible to go left	
		case 4:
			if (n->x - 2 >= 0)
			{
				x = n->x - 2;
				y = n->y;
			}
			else continue;
			break;

			//Check if it's possible to go up
		case 8:
			if (n->y - 2 >= 0)
			{
				x = n->x;
				y = n->y - 2;
			}
			else continue;
			break;
		}

		//Get destination node into pointer (makes things a tiny bit faster)
		dest = nodes + x + y * width;

		//Make sure that destination node is not a wall
		if (dest->c == ' ')
		{
			//If destination is a linked node already - abort
			if (dest->parent != NULL) continue;

			//Otherwise, adopt node
			dest->parent = n;

			//Remove wall between nodes
			nodes[n->x + (x - n->x) / 2 + (n->y + (y - n->y) / 2) * width].c = ' ';

			//Return address of the child node
			return dest;
		}
	}

	//If nothing more can be done here - return parent's address
	return (Node*)n->parent;
}
void level_gener( map_t map, int& col_mob2, int mood_e, cord_t* cord_mob, person_status_t person_state, int width, int height, Node *nodes) {
	short int menu_w = map.w;
	short int menu_h = 6;
	short int win_h = map.h + menu_h, win_w = map.w;
	person_state.col_hearts = 3;
	person_state.col_sw = 0;
	person_state.mood = mood_normal;
	person_state.col_zv = 0;
	col_mob2 = 0;
	mood_e = 0;

	main_generate( map, width,  height,nodes);
	create_room2( map);
	zvezda_random(map);
	mob_random(map, col_mob2, cord_mob);
	sword_random(map);
	fill_field(map);

}

//генерирует карту
int main_generate(map_t map, int width, int height, Node *nodes)
{
	Node *start, *last;

	//Check argument count



	//Seed random generator
	srand(time(NULL));
	//srand(0);



	//Setup start node
	start = nodes + 1 + width;
	start->parent = start;
	last = start;

	//Connect nodes until start node is reached and can't be left
	while ((last = link(last, width, height, nodes)) != start);
	//draw();
	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			//consoleBuffer[x + w * y].Char.AsciiChar = (unsigned char)219;
			//consoleBuffer[x + w * y].Attributes = rand() % 256;


			int c = nodes[width*y + x].c;
			if (c == ' ')
			{
			map.field[width*y + x] = space;
			}
			else
			{
				map.field[width*y + x] = stena;
			}
		}
	}

	return 0;
}

void sword_random(map_t map)
{
	int stars_cnt;
	stars_cnt = rand() % 4 + 3;
	int x_zv;
	int y_zv;
	for (int i = 0; i < stars_cnt; i++)
	{
		x_zv = rand() % (map.w - 2) + 1;
		y_zv = rand() % (map.h - 2) + 1;
		map.field[y_zv*map.w + x_zv] = sword;
	}



}
void fill_field(map_t map)
{
	
	map.field[map.w * 16 + 24] = exittt;
	map.field[map.w * 11 + 24] = exittt;
	map.field[map.w * 9 + 0] = exittt;
	map.field[map.w * 4 + 5] = person;


}

void zvezda_random(map_t map)
{
	int stars_cnt;
	stars_cnt = rand() % 50 + 3;
	int x_zv;
	int y_zv;
	for (int i = 0; i < stars_cnt; i++)
	{
		x_zv = rand() % (map.w - 2) + 1;
		y_zv = rand() % (map.h - 2) + 1;
		map.field[y_zv*map.w + x_zv] = zvezda;
	}



}
void mob_random(map_t map, int& col_mob, cord_t* cord_mob)
{

	col_mob = rand() % 15 + 3;
	int x_zv;
	int y_zv;

	for (int i = 0; i < col_mob; i++)
	{
		x_zv = rand() % (map.w - 2) + 1;
		y_zv = rand() % (map.h - 2) + 1;
		cord_mob[i].x = x_zv;
		cord_mob[i].y = y_zv;
		map.field[y_zv*map.w + x_zv] = mob;
	}



}

void create_room(map_t map)
{
	int room_cnt;
	room_cnt = rand() % 2 + 1;
	int x_room;
	int y_room;
	int x2_room;
	int y2_room;
	for (int i = 0; i <room_cnt; i++)
	{
		x_room = rand() % (map.w - 2);
		y_room = rand() % (map.h - 2);
		x2_room = rand() % (map.w - 2) + 1;
		y2_room = rand() % (map.h - 2) + 1;
		if (y_room > y2_room) {
			int t = y_room;
			y_room = y2_room;
			y2_room = t;
		}
		if (x_room > x2_room) {
			int t = x_room;
			x_room = x2_room;
			x2_room = t;
		}

		for (int y = y_room; y < y2_room; y++)
		{
			for (int x = x_room; x < x2_room; x++)
			{

				map.field[y*map.w + x] = space;
			}
		}

	}
}
void create_room2(map_t map)
{
	int room_cnt;
	room_cnt = rand() % 6 + 2;
	int a;
	int b;

	int x_room;
	int y_room;

	for (int i = 0; i < room_cnt; i++) {
		a = rand() % 5 + 2;
		b = rand() % 5 + 2;

		x_room = rand() % (map.w - 2) + 1;
		y_room = rand() % (map.h - 2) + 1;
		if (y_room + a >= map.h) {
			a = map.h - y_room - 1;
		}
		if (x_room + b >= map.w) {
			b = map.w - x_room - 1;
		}
		for (int y = y_room; y < y_room + a; y++) {
			for (int x = x_room; x < x_room + b; x++) {
				map.field[y*map.w + x] = space;
			}
		}
	}
}
