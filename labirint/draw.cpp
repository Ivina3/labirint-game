
#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "win_setup.h"
#include "simple2d.h"

#include <sstream>
#include "generate.h"
#include "draw.h"
#include "step.h"
#include "glew.h"




//
//#include <chrono>
#include <thread>
#include "types.h"

extern resuarces_t resuarces;


struct point_t
{
	double x;
	double y;
};
double h_menu = 124;
double w_menu = 1024;
double h_ = 768;
double w_ = 1024;
double mm =h_- h_menu;
double nn = 1024;



//map_t map;

struct map_state_t {
	float x;//coordinata x
	float y;//coordinata y
	float x2;//скорость по x
	float y2;// скорость по y

	float color;
};



const int a_y = 25;
const int b_x = 25;
map_state_t map_state_draw[a_y][b_x];

double u_y = mm / a_y;
double o_x = nn / b_x;


void draw_field(map_t map, int* color, display_t display)
{
	/*map_state_draw[0][0].x = 0;
	map_state_draw[0][0].y = 0;*/
	double red_ = 0;
	double green_ = 0;
	//int x2 = 0, y2 = 0;
	//int yy = 0;

	for (int y = 0; y < map.h; ++y)
	{

		for (int x = 0; x < map.w; ++x)
		{
			/*map_state_draw[y][x].x = x2;

			map_state_draw[y][x].y = yy;

			map_state_draw[y][x].x2 = map_state_draw[y][x].x + o_x;
			map_state_draw[y][x].y2 = map_state_draw[y][x].y + u_y;

			x2 += o_x;
			y2 += u_y;*/

			//consoleBuffer[x + w * y].Char.AsciiChar = (unsigned char)219;
			//consoleBuffer[x + w * y].Attributes = rand() % 256;
			


			int c = map.field[map.w*y + x];
			if (c == space)
			{

				red_ = 0.5;

				green_ = 0;


				//setcolor(pink, pink);
			/*	display.consoleBuffer[x + map.w * y].Char.AsciiChar = (unsigned char)176;
				display.consoleBuffer[x + map.w * y].Attributes = make_attrib(0, 0);*/

			}
			else if (c == stena)
			{
				red_ = 0;
				green_ = 0.5;

				//setcolor(magenta, magenta);
		/*		display.consoleBuffer[x + map.w * y].Char.AsciiChar = (unsigned char)219;
				display.consoleBuffer[x + map.w * y].Attributes = make_attrib(4, 4);*/
			}
			else if (c == zvezda)
			{
				red_ = 0.8;
				green_ = 0.3;
				//setcolor(dark_red, black);
				//setcolor(dark_magenta, dark_magenta);
			/*	display.consoleBuffer[x + map.w * y].Char.AsciiChar = (unsigned char)15;
				display.consoleBuffer[x + map.w * y].Attributes = make_attrib(6, 0);*/
			}
			else if (c == person)
			{
				red_ = 0.3;
				green_ = 0.8;
				//setcolor(aqua, pink);
				//display.consoleBuffer[x + map.w * y].Char.AsciiChar = (unsigned char)2;
				//display.consoleBuffer[x + map.w * y].Attributes = make_attrib(1, 0);
			}
			else if (c == sword)
			{
				green_ = 0.5;
				red_ = 0.9;
				/*display.consoleBuffer[x + map.w * y].Char.AsciiChar = (unsigned char)92;
				display.consoleBuffer[x + map.w * y].Attributes = make_attrib(2, 0);*/
			}
			else if (c == mob)
			{
				green_ = 0.9;
				red_ = 0.6;
				/*display.consoleBuffer[x + map.w * y].Char.AsciiChar = (unsigned char)253;
				display.consoleBuffer[x + map.w * y].Attributes = make_attrib(2, 0);*/
			}
			else if (c == exittt)
			{

				green_ = 1;
				red_ = 0.4;
				//display.consoleBuffer[x + map.w * y].Char.AsciiChar = (unsigned char)219;
				//display.consoleBuffer[x + map.w * y].Attributes = make_attrib(3, 4);
			}
			/*	consoleBuffer[x + w * y].Char.AsciiChar = (unsigned char)253;
			consoleBuffer[x + w * y].Attributes = 100;*/
			point_t p1, p2, p3, p4;
			double h = mm / a_y;
			double w = nn / b_x;
			p1.x = w * x;
			p1.y = y * h;
			p2.x = p1.x + w;
			p2.y = p1.y;
			p3.x =p1.x;
			p3.y = p1.y + h;
			p4.x = p2.x;
			p4.y = p2.y + h;



			if (c == stena) {
				S2D_Image* img = resuarces.brick;
				img->x = p1.x;
				img->y = p1.y;

				img->width = w;
				img->height = h;

				S2D_DrawImage(img);
			}
			else if(c==mob){
				S2D_Image* img = resuarces.mob;
				img->x = p1.x;
				img->y = p1.y;

				img->width = w;
				img->height = h;

				S2D_DrawImage(img);
			}
			else if (c == zvezda) {
				S2D_Image* img = resuarces.zvezda;
				img->x = p1.x;
				img->y = p1.y;

				img->width = w;
				img->height = h;

				S2D_DrawImage(img);
			}
			else if (c == sword) {
				S2D_Image* img = resuarces.sword;
				img->x = p1.x;
				img->y = p1.y;

				img->width = w;
				img->height = h;

				S2D_DrawImage(img);
			}
			else if (c == person) {
				S2D_Image* img = resuarces.person;
				img->x = p1.x;
				img->y = p1.y;

				img->width = w;
				img->height = h;

				S2D_DrawImage(img);
			}
			else if (c == exittt) {
				S2D_Image* img = resuarces.portal;
				img->x = p1.x;
				img->y = p1.y;

				img->width = w;
				img->height = h;

				S2D_DrawImage(img);
			}
			else {

				S2D_DrawQuad(p2.x, p2.y, 0.7, 0.7, 0.7, 1,
					p1.x, p1.y, 0.7, 0.7, 0.7, 1,
					p3.x, p3.y, 0.7, 0.7, 0.7, 1,
					p4.x, p4.y, 0.7, 0.7, 0.7, 1);
			}
			
		}

		/*x2 = 0;
		yy = map_state_draw[y][0].y2;
		map_state_draw[y][0].y = map_state_draw[y][0].y2;
		map_state_draw[y][0].y2 = map_state_draw[y][0].y + u_y;*/
	}


	/* Write our character buffer (a single character currently) to the console buffer */
	/*WriteConsoleOutputA(display.wHnd, display.consoleBuffer, display.characterBufferSize, display.characterPosition, &display.consoleWriteArea);
}*/
}

void draw_menu(short menu_h, short menu_w,map_t map, person_status_t state, display_t display)
{
	point_t p1, p2, p3, p4;
	p1.x = 0;
	p1.y = 768 - 124;

	for (int y =map.h; y < h_; ++y)
	{
		for (int x = 0; x <1; ++x)
		{
			
			S2D_Image* img;
			double h = h_menu / 6;
			double w = w_menu / 1;

			p1.x = w * x;
			p1.y = y * h+128;
			p2.x = p1.x + w;
			p2.y = p1.y;
			p3.x = p1.x;
			p3.y = p1.y + h+128;
			p4.x = p2.x;
			p4.y = p2.y + h+128;
			S2D_DrawQuad(p2.x, p2.y, 0.7, 0.7, 0.7, 1,
				p1.x, p1.y, 0.7, 0.7, 0.7, 1,
				p3.x, p3.y, 0.7, 0.7, 0.7, 1,
				p4.x, p4.y, 0.7, 0.7, 0.7, 1);
			/*display.consoleBuffer[x + map.w * y].Char.AsciiChar = (unsigned char)219;
			display.consoleBuffer[x + map.w * y].Attributes = make_attrib(0, 0);*/
			/*if (y == 0) {*/
			if (y == map.h) {
				
				
				resuarces.txt_->x = 8;
				resuarces.txt_->y = 644;
				resuarces.txt_->color.r = 0.3;
				resuarces.txt_->color.g = 0.3;
				resuarces.txt_->color.b = 1.0;
				resuarces.txt_->color.a = 0.7;
				/*std::ostringstream oss;
				oss << state.col_hearts;
				std::string uu = oss.str();
				std::string str = "Lifes:"+uu;*/
				
				S2D_SetText(resuarces.txt_, "Lifes:" );
				int x_lifee = 63;
				for (int i = 0; i < state.col_hearts; i++)
				{
				
					img = resuarces.life;
					img->x = x_lifee;
					x_lifee+=40;;
					img->y = p1.y;
					img->width = 20;
					img->height = 20;
					S2D_DrawImage(img);
					/*display.consoleBuffer[(i + 6) + map.w * (map.h + 0)].Char.AsciiChar = 3;
					display.consoleBuffer[(i + 6) + map.w * (map.h + 0)].Attributes = make_attrib(2, 0);
					*/
				}
				S2D_DrawText(resuarces.txt_);
				/*}*/
			}

			else if (y == map.h+1) {
				//. = S2D_CreateText("C:/vera.ttf", "Swords:", 20);;
				resuarces.txt_->x = 4;
				resuarces.txt_->y = p1.y;
				resuarces.txt_->color.r = 0.3;
				resuarces.txt_->color.g = 0.3;
				resuarces.txt_->color.b = 1.0;
				resuarces.txt_->color.a = 0.7;
					S2D_SetText(resuarces.txt_, "Swords:");
					int x_life = 80;
					for (int i = 0; i < state.col_sw; i++)
					{

						 img = resuarces.sword;
						img->x = x_life;
						x_life += 40;
						img->y = p1.y;

						img->width = 20;
						img->height = 20;

						S2D_DrawImage(img);
						/*display.consoleBuffer[(i + 6) + map.w * (map.h + 0)].Char.AsciiChar = 3;
						display.consoleBuffer[(i + 6) + map.w * (map.h + 0)].Attributes = make_attrib(2, 0);
						*/
					}
					
					S2D_DrawText(resuarces.txt_);
					/*}*/
				}
			else if (y == map.h + 2) {
				
					resuarces.txt_->x = 4;
					resuarces.txt_->y = p1.y;
					resuarces.txt_->color.r = 0.3;
					resuarces.txt_->color.g = 0.3;
					resuarces.txt_->color.b = 1.0;
					resuarces.txt_->color.a = 0.7;
				S2D_SetText(resuarces.txt_, "Stars:");
				int x_life = 60;
				for (int i = 0; i < state.col_zv; i++)
				{

					 img = resuarces.zvezda;
					img->x = x_life;
					x_life += 40;;
					img->y = p1.y;

					img->width = 20;
					img->height = 20;

					S2D_DrawImage(img);
					/*display.consoleBuffer[(i + 6) + map.w * (map.h + 0)].Char.AsciiChar = 3;
					display.consoleBuffer[(i + 6) + map.w * (map.h + 0)].Attributes = make_attrib(2, 0);
					*/
				}

				S2D_DrawText(resuarces.txt_);
				/*}*/

			}
			else if (y == map.h + 3) {
			
				resuarces.txt_->x = 4;
				resuarces.txt_->y = p1.y;
				resuarces.txt_->color.r = 0.3;
				resuarces.txt_->color.g = 0.3;
				resuarces.txt_->color.b = 1.0;
				resuarces.txt_->color.a = 0.7;
				if (state.mood == mood_good) {
					S2D_SetText(resuarces.txt_, "Mood: )");
				}
				else if (state.mood == mood_bad) {
					S2D_SetText(resuarces.txt_, "Mood: (");
				}
				else {
					S2D_SetText(resuarces.txt_, "Mood: /");
				}
				S2D_DrawText(resuarces.txt_);
				/*}*/
			}
			
		}
	}

	//for (int y = map.h; y < map.h + menu_h; ++y)
	//{
	//	for (int x = 0; x < map.w; ++x)
	//	{
	//		point_t p1, p2, p3, p4;
	//		double h = h_menu / 5;
	//		double w = w_menu / 5;
	//		p1.x = w * x;
	//		p1.y = y * h;
	//		p2.x = p1.x + w;
	//		p2.y = p1.y;
	//		p3.x = p1.x;
	//		p3.y = p1.y + h;
	//		p4.x = p2.x;
	//		p4.y = p2.y + h;
	//		/*display.consoleBuffer[x + map.w * y].Char.AsciiChar = (unsigned char)219;
	//		display.consoleBuffer[x + map.w * y].Attributes = make_attrib(0, 0);*/

	//	}
	//}

	//return;
	/*display.consoleBuffer[0 + map.w * (map.h + 0)].Attributes = make_attrib(2, 0);
	display.consoleBuffer[0 + map.w * (map.h + 0)].Char.AsciiChar = 'L';

	display.consoleBuffer[1 + map.w * (map.h + 0)].Attributes = make_attrib(2, 0);

	display.consoleBuffer[1 + map.w * (map.h + 0)].Char.AsciiChar = 'i';
	display.consoleBuffer[2 + map.w * (map.h + 0)].Attributes = make_attrib(2, 0);
	display.consoleBuffer[2 + map.w * (map.h + 0)].Char.AsciiChar = 'f';
	display.consoleBuffer[3 + map.w * (map.h + 0)].Attributes = make_attrib(2, 0);
	display.consoleBuffer[3 + map.w * (map.h + 0)].Char.AsciiChar = 'e';
	display.consoleBuffer[4 + map.w * (map.h + 0)].Attributes = make_attrib(2, 0);
	display.consoleBuffer[4 + map.w * (map.h + 0)].Char.AsciiChar = 's';
	display.consoleBuffer[5 + map.w * (map.h + 0)].Attributes = make_attrib(2, 0);
	display.consoleBuffer[5 + map.w * (map.h + 0)].Char.AsciiChar = ':';
*/
	for (int i = 0; i < state.col_hearts; i++)
	{
		/*display.consoleBuffer[(i + 6) + map.w * (map.h + 0)].Char.AsciiChar = 3;
		display.consoleBuffer[(i + 6) + map.w * (map.h + 0)].Attributes = make_attrib(2, 0);
		*/
	}
	/*display.consoleBuffer[0 + map.w * (map.h + 1)].Attributes = make_attrib(3, 0);
	display.consoleBuffer[0 + map.w * (map.h + 1)].Char.AsciiChar = 'S';
	display.consoleBuffer[1 + map.w * (map.h + 1)].Attributes = make_attrib(3, 0);
	display.consoleBuffer[1 + map.w * (map.h + 1)].Char.AsciiChar = 'w';
	display.consoleBuffer[2 + map.w * (map.h + 1)].Attributes = make_attrib(3, 0);
	display.consoleBuffer[2 + map.w * (map.h + 1)].Char.AsciiChar = 'o';
	display.consoleBuffer[3 + map.w * (map.h + 1)].Attributes = make_attrib(3, 0);
	display.consoleBuffer[3 + map.w * (map.h + 1)].Char.AsciiChar = 'r';
	display.consoleBuffer[4 + map.w * (map.h + 1)].Attributes = make_attrib(3, 0);
	display.consoleBuffer[4 + map.w * (map.h + 1)].Char.AsciiChar = 'd';
	display.consoleBuffer[5 + map.w * (map.h + 1)].Attributes = make_attrib(3, 0);
	display.consoleBuffer[5 + map.w * (map.h + 1)].Char.AsciiChar = 's';
	display.consoleBuffer[6 + map.w * (map.h + 1)].Attributes = make_attrib(3, 0);
	display.consoleBuffer[6 + map.w * (map.h + 1)].Char.AsciiChar = ':';
*/
	for (int i = 0; i < state.col_sw; i++)
	{
	/*	display.consoleBuffer[(i + 7) + menu_w * (map.h + 1)].Char.AsciiChar = sword;
		display.consoleBuffer[(i + 7) + menu_w * (map.h + 1)].Attributes = make_attrib(4, 0);
*/
	}
	/*display.consoleBuffer[0 + map.w * (map.h + 2)].Attributes = make_attrib(4, 0);
	display.consoleBuffer[0 + map.w * (map.h + 2)].Char.AsciiChar = 'S';
	display.consoleBuffer[1 + map.w * (map.h + 2)].Attributes = make_attrib(4, 0);
	display.consoleBuffer[1 + map.w * (map.h + 2)].Char.AsciiChar = 't';
	display.consoleBuffer[2 + map.w * (map.h + 2)].Attributes = make_attrib(4, 0);
	display.consoleBuffer[2 + map.w * (map.h + 2)].Char.AsciiChar = 'a';
	display.consoleBuffer[3 + map.w * (map.h + 2)].Attributes = make_attrib(4, 0);
	display.consoleBuffer[3 + map.w * (map.h + 2)].Char.AsciiChar = 'r';
	display.consoleBuffer[4 + map.w * (map.h + 2)].Attributes = make_attrib(4, 0);
	display.consoleBuffer[4 + map.w * (map.h + 2)].Char.AsciiChar = 's';
	display.consoleBuffer[5 + map.w * (map.h + 2)].Attributes = make_attrib(4, 0);
	display.consoleBuffer[5 + map.w * (map.h + 2)].Char.AsciiChar = ':';*/

	if (state.col_zv < 10) {
/*
		display.consoleBuffer[6 + menu_w * (map.h + 2)].Char.AsciiChar = state.col_zv + 48;
		display.consoleBuffer[6 + menu_w * (map.h + 2)].Attributes = make_attrib(6, 0);
*/
	}

	else {

		int u = state.col_zv % 10;
		int g = state.col_zv / 10;
		/*display.consoleBuffer[6 + menu_w * (map.h + 2)].Attributes = make_attrib(6, 0);
		display.consoleBuffer[6 + menu_w * (map.h + 2)].Char.AsciiChar = g + 48;
		display.consoleBuffer[7 + menu_w * (map.h + 2)].Attributes = make_attrib(6, 0);
		display.consoleBuffer[7 + menu_w * (map.h + 2)].Char.AsciiChar = u + 48;
*/
	}
	/*if (state.col_zv == 1) {
	consoleBuffer[6 + w * (map_h + 2)].Char.AsciiChar = 49;
	}
	else if(state)
	consoleBuffer[6 + w * (map_h + 2)].Char.AsciiChar = state.col_zv;
	}
	else {
	*/
	/*}*/
	//for (int i = 0; i < state.col_zv; i++)
	//{
	//	
	//	consoleBuffer[(i + 6) + w * (map_h + 2)].Char.AsciiChar = 15;

	//}


	//display.consoleBuffer[0 + menu_w * (map.h + 3)].Attributes = make_attrib(5, 0);
	//display.consoleBuffer[0 + menu_w * (map.h + 3)].Char.AsciiChar = 'M';
	//display.consoleBuffer[1 + menu_w * (map.h + 3)].Attributes = make_attrib(5, 0);
	//display.consoleBuffer[1 + menu_w * (map.h + 3)].Char.AsciiChar = 'o';
	//display.consoleBuffer[2 + menu_w * (map.h + 3)].Attributes = make_attrib(5, 0);
	//display.consoleBuffer[2 + menu_w * (map.h + 3)].Char.AsciiChar = 'o';
	//display.consoleBuffer[3 + menu_w * (map.h + 3)].Attributes = make_attrib(5, 0);
	//display.consoleBuffer[3 + menu_w * (map.h + 3)].Char.AsciiChar = 'd';
	//display.consoleBuffer[4 + menu_w * (map.h + 3)].Attributes = make_attrib(5, 0);
	//display.consoleBuffer[4 + menu_w * (map.h + 3)].Char.AsciiChar = ':';
	//display.consoleBuffer[5 + menu_w * (map.h + 3)].Attributes = make_attrib(3, 0);
	//display.consoleBuffer[5 + menu_w * (map.h + 3)].Char.AsciiChar = ':';
	if (state.mood == mood_good) {
	/*	display.consoleBuffer[6 + menu_w * (map.h + 3)].Char.AsciiChar = ')';
		display.consoleBuffer[6 + menu_w * (map.h + 3)].Attributes = make_attrib(3, 0);*/
	}
	else if (state.mood == mood_bad) {
		/*display.consoleBuffer[6 + menu_w * (map.h + 3)].Char.AsciiChar = '(';
		display.consoleBuffer[6 + menu_w * (map.h + 3)].Attributes = make_attrib(3, 0);*/
	}
	else {/*
		display.consoleBuffer[6 + menu_w * (map.h + 3)].Char.AsciiChar = '|';
		display.consoleBuffer[6 + menu_w * (map.h + 3)].Attributes = make_attrib(3, 0);*/
	}
	/* Write our character buffer (a single character currently) to the console buffer */
	WriteConsoleOutputA(display.wHnd, display.consoleBuffer, display.characterBufferSize, display.characterPosition, &display.consoleWriteArea);
}


