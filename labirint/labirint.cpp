
#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <chrono>
#include <thread>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "win_setup.h"

#include <chrono>
#include <thread>
#include "simple2d.h"
#include "types.h"
#include "generate.h"
#include "draw.h"
#include "step.h"
#include "glew.h"



struct ball_state_t {
	float x;//coordinata x
	float y;//coordinata y
	float v_x;//скорость по x
	float v_y;// скорость по y


};
resuarces_t resuarces;

//struct map_state_t {
//	float x;//coordinata x
//	float y;//coordinata y
//	float x2;//скорость по x
//	float y2;// скорость по y
//
//	float color;
//};
//





int color[2];
display_t display_settings;
person_status_t person_state;


const int max_cout = 18;
cord_t cord_mob[max_cout];
int col_mob2 = 0;
int mood_e = 0;

//struct map_t
//{
//	int h;
//	int w;
//	int* field;
//};
map_t map;


int max_zv = 20;
int n = 7475474;
int st;//шаг
int mood_2 = 0;
int res = 0;
int mood_stop = 5;//кол-во шагов, после которого хорошее настроение перейдет в нормальное
bool proverka;
move_obj_desc_t der;
int start_x = 5;
int start_y = 4;
move_res_t f;
short int menu_h = 6;
short int menu_w = map.w;
short int win_h = map.h + menu_h, win_w = map.w;

 double x_p = 1024;
 double y_p = 768;
const int razmer_line=100;
int col_vo_otrez=0;
int col_vo_line = 0;
ball_state_t line[razmer_line];
ball_state_t ball;
int x_ball_line=200;
int x_ball_line2 = 300;
Node *nodes; //Nodes array
int width, height; //Maze dimensions

//CHAR_INFO* consoleBuffer = 0;
//HANDLE wHnd; /* write (output) handle */
//HANDLE rHnd; /* read (input handle */
///* A COORD struct for specificying the console's screen buffer dimensions */
//COORD bufferSize;
///* Setting up different variables for passing to WriteConsoleOutput */
//COORD characterBufferSize;
//COORD characterPosition = { 0, 0 };
//SMALL_RECT consoleWriteArea;

//enum map_cell
//{
//	space = 0,
//	stena = 1,
//	person = 2,
//	zvezda = 3,
//	move_left = 75,
//	move_right = 77,
//	move_down = 80,
//	move_up = 72
//};


void end_game()
{
	using namespace std::chrono_literals;
	S2D_PlaySound(resuarces.end_);
	S2D_StopMusic();
	std::this_thread::sleep_for(2s);
	exit(0);
}
int init()
{
	int i, j;
	Node *n;

	//Allocate memory for maze
	nodes = (Node*)calloc(width * height, sizeof(Node));
	if (nodes == NULL) return 1;

	//Setup crucial nodes
	for (i = 0; i < width; i++)
	{
		for (j = 0; j < height; j++)
		{
			n = nodes + i + j * width;
			if (i * j % 2)
			{
				n->x = i;
				n->y = j;
				n->dirs = 15; //Assume that all directions can be explored (4 youngest bits set)
				n->c = ' ';
			}
			else n->c = '#'; //Add walls between nodes
		}
	}
	return 0;
}



bool k = true;
int put_in_circular_buffer(ball_state_t* buffer, int N,int idx, ball_state_t element)
{

	if (k == false) {
		N++;
	}

	if (N-1 == idx) {
		for (int i = 1; i < N; i++) {

			buffer[i - 1]= buffer[i];

		}
		
		buffer[idx] = element;
	
		return idx;
	}
	else {
		buffer[idx] = element;
		if (k == false) {
			k == true;
		}
		k = true;
		if (idx + 1 == N-1) {
			k = false;
		}

		
		return idx+1;
		
	}

	

	
}


//void gen_level(int h, int w, int* field) {
//	main_generate(field);
//	create_room2(map_h, map_w, field);
//	zvezda_random(map_h, map_w, field);
//	mob_random(map_h, map_w, field, col_mob2, cord_mob);
//	sword_random(map_h, map_w, field);
//
//
//	fill_field(map_h, map_w, field);
//
//	draw_field(map_h, map_w, field);
//	draw_menu(menu_h, menu_w, person_state, map_h);
//}
//bool proverka_zvezd(int h, int w, int* field) 
//{
//	bool o = false;
//	for (int i = 0; i < h; i++)
//	{
//		for (int j = 0; j < w; j++) 
//		{
//			int c = field[w*i + j];
//			if (c == zvezda) 
//			{
//				o = true;
//				return o;
//
//			}
//		}
//	}
//}
//S2D_Image *img = S2D_CreateImage("D:\\Bounce2\\bounze\\app\\src\\main\\res\\drawable\\ball.png");
void draw_pictire();
//void drawText();
void on_key(S2D_Event e);

std::chrono::steady_clock::time_point prev_time;
int x_l = ball.x;
float pix_to_meters = 100;
int l = ball.y;
//const int x = 4;
//const int y = 4;
//map_state_t map_state[x][y];
void render() {


	draw_field(map, color, display_settings);
	{
		int v = 0;
		for (int i = 0; i < 625; i++) {
			if (map.field[i] == person) {
				v++;
			}
		}
		int k;
		k = v;

	}
	draw_menu(menu_h, menu_w, map, person_state, display_settings);

	if (f.name == exittt) {
		S2D_PlaySound(resuarces.level_);
		f.name = stena;
		generaty_colors(map, color);
		level_gener(map, col_mob2, mood_e, cord_mob, person_state, width, height, nodes);
		der.from_y = start_y;
		der.from_x = start_x;
		int v = 0;
		for (int i = 0; i < 625; i++) {
			if (map.field[i] == person) {
				v++;
			}
		}
		int k;
		k = v;
	}
	//S2D_DrawTriangle(x1, y1, r1, g1, b1, a1,
	//	x2, y2, r2, g2, b2, a2,
	//	x3, y3, r3, g3, b3, a3);
	int j =100;//x
	//int yT = 150+j;
	//int yT1 = 250+j;
	//int yK;
	/*yT = 100+j;*/
	int w=100;
	int l =400;//y
	int h = 100;

	//double a = x_p / x;
	//double b = y_p / y;
	//map_state[0][0].x = 0;
	//map_state[0][0].y = 0;
	int r_line;
	int g_line;
	/*int u = 0;
	int x2=0,y2=0;
	int yy = 0;
	for (int i = 0; i < y; i++) {
		for (int p = 0; p < x; p++) {
	
			map_state[i][p].x = x2;
			
			map_state[i][p].y = yy;
			map_state[i][p].x2 = map_state[i][p].x + a;
			map_state[i][p].y2 = map_state[i][p].y + b;
			x2 += a;
			y2 += b;
			
		
			if (p % 2 != 0 && i % 2 == 0) {
				u = 1;
			}
			else if (p % 2 == 0 && i % 2 != 0) {
				u = 1;
			}
			else {
				u = 0;
			}
		
			S2D_DrawQuad(map_state[i][p].x, map_state[i][p].y,0+u, 0 + u, 1, 1,
				map_state[i][p].x2, map_state[i][p].y, 0 + u, 0 + u,1, 1,
				map_state[i][p].x2, map_state[i][p].y2, 0 + u, 0 + u, 1, 1,
				map_state[i][p].x, map_state[i][p].y2, 0 + u, 0 + u, 1, 1);
	
		}
		x2 = 0;
		yy = map_state[i][0].y2;
		map_state[i][0].y = map_state[i][0].y2;
		map_state[i][0].y2 = map_state[i][0].y+b;
	}*/
	/*l = ball.y;*/
	//S2D_DrawTriangle(
	//	  100+l + w/2, 100+j-h , 1, 0, 0, 1,
	//	 0+l, 150 + j, 0, 1, 0, 1,
	//	   200+l + w, 150 + j, 0, 0, 1, 1
	//);


	//S2D_DrawQuad(x1, y1, r1, g1, b1, a1,
	//	x2, y2, r2, g2, b2, a2,
	//	x3, y3, r3, g3, b3, a3,
	//	x4, y4, r4, g4, b4, a4);
	
	/*S2D_DrawQuad(10 + l, 150 + j, 1, 0, 1, 1,
		190 + l + w, 150 + j, 0, 0, 0, 1,
		190 + l + w, 250 + j+h, 1, 1, 0, 1,
		10+l, 250 + j+h, 1, 0, 1, 0 );
*/

	//S2D_DrawLine(x1, y1, x2, y2,
	//	width,
	//	r1, g1, b1, a1,
	//	r2, g2, b2, a2,
	//	r3, g3, b3, a3,
	//	r4, g4, b4, a4);

	//S2D_DrawLine(x_ball_line, ball.y, x_ball_line2, 20,
	//	40,
	//	1, 0, 0, 1,
	//	0, 1, 0, 1,
	//	1, 0, 0, 1,
	//	0, 1, 0, 1);
	
	/*line[col_vo_line].x = ball.x;
	
	line[col_vo_line].y = ball.y;
	col_vo_line++;

	col_vo_line=put_in_circular_buffer(line, razmer_line, col_vo_line,ball);
	float a_line = 0;
	double d = 0;
	for (int i = 1; i < col_vo_line; i++)
	{
		
d = sqrt((line[i].x - line[i - 1].x)*(line[i].x - line[i - 1].x) + (line[i].y - line[i - 1].y)*(line[i].y - line[i - 1].y));
		
		if (d > 5)
		{
			S2D_DrawLine(line[i - 1].x, line[i - 1].y, line[i].x, line[i].y,
				40,
				0, 0.5, 0, a_line,
				0, 0.5, 0, a_line,
				0, 0.5, 0, a_line,
				0, 0.5, 0, a_line);
		
		}

		a_line += 1.0 / (razmer_line - 1);

	}

*/

	/*D_DrawCircle(x, y, radius, sectors, r, g, b, a);*/
	/*S2D_DrawCircle(100+l + w/2, 200+j+h/2, 40+h/4 ,100000, 1, 0, 0, 1);*/
	
	/*draw_pictire();*/
	//drawText();

	//std::chrono::steady_clock::time_point time_now = std::chrono::steady_clock::now();

	//float del_T = 0.046;
	//static bool first_iter = true;
	//if (first_iter)
	//{
	//	first_iter = false;
	//	del_T = 0.0;
	//}
	//else
	//{
	//	del_T = double(std::chrono::duration_cast<std::chrono::microseconds>(time_now - prev_time).count())/1000000.0;
	//}


	//float ground_level = 600;
	//

	//if (ball.y > ground_level)
	//{
	//	ball.y = ground_level;
	//}

	//if (ball.y < ground_level)
	//	ball.v_y = ball.v_y + (9.8*pix_to_meters*del_T);


	//ball.x += ball.v_x*del_T;
	//ball.y += ball.v_y*del_T;

	//img->x = ball.x;
	//img->y = ball.y;


	////S2D_DrawLine(ball.x,l, ball.x+50, ball.y,
	////	40,
	////	1, 0, 0, 1,
	////	0, 1, 0, 1,
	////	1, 0, 0, 1,
	////	0, 1, 0, 1);


	//prev_time = time_now;

}



int angel=20;


void draw_pictire() {
	

	//img->width = 256;
	//img->height = 512;
	//img->color.r = 1.0;
	//img->color.g = 0.8;
	//img->color.b = 0.2;
	//img->color.a = 1.0;
	//img->x =200;
	//img->y = 200;

	/*
	S2D_RotateImage(img, angel+20, S2D_CENTER);
	angel += 20;*/
	//// Or, set a custom point to rotate around
	//img->rx = 50;
	//img->ry = 75;

	//// Set the rotation angle directly
	//img->rotate = 90;


	//S2D_DrawImage(img);
}
//S2D_Text *txt = S2D_CreateText("C:/vera.ttf", "Hello world!", 20);;
//void drawText() {
//	
//	txt->x = 300;
//	txt->y = 100;
//	txt->color.r = 0.5;
//	txt->color.g = 1.0;
//	txt->color.b = 0.0;
//	txt->color.a = 0.7;
//	S2D_DrawText(txt);
//}
int op = 0;
int xx = 0;
//img->x = 200;
//img->y = 200;
//e.x = 200;
//e.y = 200;




void on_key(S2D_Event e) {
	// Check `e.key` for the key being interacted with
	//e.y += op;
	//img->y = e.y;
	//e.x = img->x;
	//e.y = img->y;
	//e.y += op;
	//img->y = e.y;
	//e.x += xx;
	//img->x = e.x;


	switch (e.type) {
	case S2D_KEY_DOWN:

		
		//ball.v_y = -10 * pix_to_meters;
		if (e.key == std::string("Down"))
		{
			res = move_down;
		}
		else if (e.key == std::string("Up"))
		{
			res = move_up;
		}
		else if (e.key == std::string("Left"))
		{
			res = move_left;
		}
		else if (e.key == std::string("Right"))
		{
			res = move_right;
		}
		/*img->y +=100;*/
	/*	op =op + 100;*/
	/*	S2D_SetText(txt, e.key);*/
		// Key was pressed

		/*if (e.key == std::string("Right"))
		{
			ball.v_x = 1* pix_to_meters;
		}

		break;*/

	case S2D_KEY_HELD:

		/*if (e.key == std::string("Right"))
		{
			ball.v_x = 1 * pix_to_meters;
		}
		else {
			ball.v_x = -1 * pix_to_meters;
		}*/
		//img->x +=+100;
		/*xx += 100;*/
		
		/*S2D_SetText(txt, "held");*/
		// Key is being held down
		break;

	case S2D_KEY_UP:
	
	//img->y -= 100;
		/*op -= 100;*/
	/*	S2D_SetText(txt, "up");*/
		// Key was released
		break;
	}
	//e.y += op;
	//img->y = e.y;
	//e.x += xx;
	//img->x = e.x;
	//xx = 0;
	//op = 0;

}


void update()
{
	/*res =0;*/
	//S2D_Sound *snd = S2D_CreateSound("sound.wav");
	//S2D_PlaySound(snd);
	

	std::this_thread::sleep_for(std::chrono::milliseconds(100));

	switch (res)
	{
	case move_down:
		der.to_x = der.from_x;
		der.to_y = der.from_y + 1;
	/*	e.type = S2D_KEY_DOWN;
		on_key(e);*/
		break;
	case move_up:
		der.to_x = der.from_x;
		der.to_y = der.from_y - 1;
		break;
	case move_left:
		der.to_x = der.from_x - 1;
		der.to_y = der.from_y;
		break;
	case move_right:
		der.to_x = der.from_x + 1;
		der.to_y = der.from_y;
		break;
	default:
		der.to_y = der.from_y;
		der.to_x = der.from_x;
		break;


	}
	res = 0;
	//std::cout << "res " << res << std::endl;
/*	step_in_labyrinth(h, w, field, res);*/
	f = move_step_in_labyrinth(map, der);
	int v = 0;
	for (int i = 0; i < 625; i++) {
		if (map.field[i] == person) {
			v++;
		}
	}
	int k;
	k = v;

	if (f.ok == true)
	{

		if (f.name == mob) {

			for (int i = 0; i < col_mob2; i++) {

				if (der.to_x == cord_mob[i].x && der.to_y == cord_mob[i].y) {

					for (int b = i; b < col_mob2 - 1; b++)
					{
						cord_mob[b].x = cord_mob[b + 1].x;
						cord_mob[b].y = cord_mob[b + 1].y;
					}
					col_mob2--;
					break;
				}

			}
		}
		if (person_state.mood == mood_good && mood_e < mood_stop)
		{
	/*		printf("\7");*/

			mood_e++;
		}
		else if (person_state.mood == mood_good && mood_e >= mood_stop)
		{
			person_state.mood = mood_normal;
			mood_e = 0;
			mood_2 = 0;
		}
		if (person_state.mood == mood_normal)
		{
			mood_2++;
			if (mood_2 >= 30)
			{
				person_state.mood = mood_bad;
			/*	printf("\7");*/
			}
		}



		der.from_x = der.to_x;
		der.from_y = der.to_y;


		if (f.name == zvezda)
		{
			person_state.mood = mood_good;
			person_state.col_zv = person_state.col_zv + 3;
			S2D_PlaySound(resuarces.zvezda_);
		/*	printf("\7");*/
			if (person_state.col_zv == max_zv) {


				end_game();
				return;
			}
		}
		if (f.name == sword)
		{
			S2D_PlaySound(resuarces.sword_);
			person_state.mood = mood_good;
			person_state.col_sw++;
		}
		if (f.name == mob)
		{
			
			if (person_state.col_sw == 0 && person_state.mood == mood_good)
			{
				S2D_PlaySound(resuarces.mob_);
				//викторина
				for (int po = 0; po < 5000; po++)
				{
					/*printf("\7");*/
				}
				return;

			}
			else if (person_state.col_sw > 0) {
				person_state.mood = mood_bad;
				S2D_PlaySound(resuarces.mob_killed);
				person_state.col_sw--;
			}
			else if (person_state.col_sw == 0)
			{
				S2D_PlaySound(resuarces.mob_);
				person_state.mood = mood_bad;
				person_state.col_hearts--;
				if (person_state.col_hearts == 0)
				{
					end_game();
					return;
				}
			}
			else
			{
				//убил монстра
			}
		}

	}
	else
	{

	}

	/*if (i == n)
	{
	std::cout << "The steps ended";

	}*/
	mob_walking(map, cord_mob, col_mob2,der);
	{
		int v = 0;
		for (int i = 0; i < 625; i++) {
			if (map.field[i] == person) {
				v++;
			}
		}
		int k;
		k = v;

	}

	

}

void on_mouse(S2D_Event e) {
	switch (e.type) {
	case S2D_MOUSE_DOWN:
		// Mouse button was pressed
		// Use `e.button` to see what button was clicked
		// Check `e.dblclick` to see if was a double click
		break;

	case S2D_MOUSE_UP:
		// Mouse button was released
		// Use `e.button` to see what button was clicked
		// Check `e.dblclick` to see if was a double click
		break;

	case S2D_MOUSE_SCROLL:
		// Mouse was scrolled
		// Check `e.direction` for direction being scrolled, normal or inverted:
		//   S2D_MOUSE_SCROLL_NORMAL
		//   S2D_MOUSE_SCROLL_INVERTED
		// Check `e.delta_x` and `e.delta_y` for the difference in x and y position
		break;

	case S2D_MOUSE_MOVE:
		/*img->x = e.x;
		img->y = e.y;*/
		// Mouse was moved
		// Check `e.delta_x` and `e.delta_y` for the difference in x and y position
		break;
	}
}

#include <SDL2\SDL_main.h>
int main(int argc, char* argv[])
{
	
	ball.x = 200;
	ball.y = 200;
	ball.v_x=0;
	ball.v_y = 0;


	///*for (int i = 0; i < 10000000; i++) {*/
	//	S2D_Window *window = S2D_CreateWindow(
	//		"Hello Triangle", x_p, y_p, update, render, 0
	//	);

	//	//window->fps_cap = 0;
	//	window->on_key = on_key;
	///*	window->on_mouse = on_mouse;*/
	//	S2D_Show(window);

	///*}*/


	/*std::string resources_path = ;*/



	std::string pp = argv[0];

	std::string directory;
	const size_t last_slash_idx = pp.rfind('\\');
	if (std::string::npos != last_slash_idx)
	{
		directory = pp.substr(0, last_slash_idx);
	}

	resuarces.resources_path = directory + "/resources/";
	/*display_t display_settings;*/
	/*S2D_Music *mus = S2D_CreateMusic("music.ogg");*/
	S2D_Music *mus = S2D_CreateMusic((resuarces.resources_path + "Saundtrek.mp3").c_str());
	S2D_PlayMusic(mus, true);
	int volume = S2D_GetMusicVolume();
	S2D_SetMusicVolume(20);  //
	resuarces.mob_killed = S2D_CreateSound((resuarces.resources_path + "mob_killed.mp3").c_str());
	resuarces.zvezda_= S2D_CreateSound((resuarces.resources_path + "zvezda.mp3").c_str());
	resuarces.mob_ = S2D_CreateSound((resuarces.resources_path + "mob.mp3").c_str());
	resuarces.sword_ = S2D_CreateSound((resuarces.resources_path + "sword.mp3").c_str());
	resuarces.level_ = S2D_CreateSound((resuarces.resources_path + "level.mp3").c_str());
	resuarces.end_ = S2D_CreateSound((resuarces.resources_path + "end.mp3").c_str());

	resuarces.brick = S2D_CreateImage((resuarces.resources_path + "brick.png").c_str());
	resuarces.mob = S2D_CreateImage((resuarces.resources_path + "mob.png").c_str());
	resuarces.sword= S2D_CreateImage((resuarces.resources_path + "sword.png").c_str());
	resuarces.zvezda = S2D_CreateImage((resuarces.resources_path + "zvezda.png").c_str());
	resuarces.person = S2D_CreateImage((resuarces.resources_path + "person.png").c_str());
	resuarces.portal = S2D_CreateImage((resuarces.resources_path + "portal.png").c_str());
	resuarces.life = S2D_CreateImage((resuarces.resources_path + "life.png").c_str());
	//resuarces.mob= S2D_CreateImage("D:\\Bounce2\\bounze\\app\\src\\main\\res\\drawable\\ball.png");




	 display_settings.consoleBuffer = 0;
	 display_settings.wHnd; /* write (output) handle */
	 display_settings.rHnd; /* read (input handle */
	     /* A COORD struct for specificying the console's screen buffer dimensions */
	 display_settings.bufferSize;
	/* Setting up different variables for passing to WriteConsoleOutput */
	 display_settings.characterBufferSize;
	 display_settings.characterPosition = { 0, 0 };
	 display_settings.consoleWriteArea;



	person_state.col_hearts = 3;
	person_state.col_sw = 0;
	person_state.mood = mood_normal;
	person_state.col_zv = 0;
	
	/*map_t map;*/
	map.h = 25;
	map.w = 25;

	 map.field = new int[map.h *map.w];
	height = map.h;
	width = map.w;
	init();

	

	setup_window(win_h, win_w, display_settings);

	

	
	level_gener( map, col_mob2, mood_e, cord_mob, person_state, width, height, nodes);
	
	//main_generate(field);
	//create_room2(map_h, map_w, field);
	//zvezda_random(map_h, map_w, field);
	//mob_random(map_h, map_w, field,col_mob2,cord_mob);
	//sword_random(map_h, map_w, field);
	//

	//fill_field(map_h, map_w, field);
	//
	//draw_field(map_h, map_w, field);
	//draw_menu(menu_h, menu_w, person_state, map_h);
	generaty_colors(map, color);
	//draw_field(map,color, display_settings);
	//draw_menu(menu_h, menu_w, map, person_state, display_settings);
	//ошибка возможна в этом месте


	der.from_y = start_y;
	der.from_x = start_x;
	der.name = person;


	/////////////////////

	

	/*for (int i = 0; i < 10000000; i++) {*/
	S2D_Window *window = S2D_CreateWindow(
		"Hello Triangle", x_p, y_p, update, render, 0
	);

	//window->fps_cap = 0;
	window->on_key = on_key;
	/*	window->on_mouse = on_mouse;*/
	S2D_Show(window);

	/*}*/


	/*step_in_labyrinth(h, w, field,res);*/
	//system("pause");

	return 0;
}


