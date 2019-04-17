#pragma once
#include "types.h"
void generaty_colors(map_t map, int* color);
Node *link(Node *n, int width, int height, Node *nodes);
void level_gener( map_t map, int& col_mob2, int mood_e, cord_t* cord_mob, person_status_t person_state, int width, int height, Node *nodes);
int main_generate(map_t map, int width, int height, Node *nodes);
void sword_random(map_t map);
void fill_field(map_t map);
void zvezda_random(map_t map);
void mob_random(map_t map, int& col_mob, cord_t* cord_mob);
void create_room(map_t map);
void create_room2(map_t map);

