#pragma once
#include "types.h"
void mob_walking(map_t map, cord_t* co_m, int col_mob);
move_res_t move_step_in_labyrinth(map_t map, move_obj_desc_t desc);