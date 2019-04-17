
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

void draw_field(map_t map, int* color,display_t display)
{


	for (int y = 0; y < map.h; ++y)
	{
		for (int x = 0; x < map.w; ++x)
		{
			//consoleBuffer[x + w * y].Char.AsciiChar = (unsigned char)219;
			//consoleBuffer[x + w * y].Attributes = rand() % 256;


			int c = map.field[map.w*y + x];
			if (c == space)
			{
				//setcolor(pink, pink);
				display.consoleBuffer[x + map.w * y].Char.AsciiChar = (unsigned char)176;
				display.consoleBuffer[x + map.w * y].Attributes = color[0];
			}
			else if (c == stena)
			{
				//setcolor(magenta, magenta);
				display.consoleBuffer[x + map.w * y].Char.AsciiChar = (unsigned char)219;
				display.consoleBuffer[x + map.w * y].Attributes = color[1];
			}
			else if (c == zvezda)
			{
				//setcolor(dark_magenta, dark_magenta);
				display.consoleBuffer[x + map.w * y].Char.AsciiChar = (unsigned char)15;
				display.consoleBuffer[x + map.w * y].Attributes = 6;
			}
			else if (c == person)
			{
				//setcolor(aqua, pink);
				display.consoleBuffer[x + map.w * y].Char.AsciiChar = (unsigned char)2;
				display.consoleBuffer[x + map.w * y].Attributes = 13;
			}
			else if (c == sword)
			{

				display.consoleBuffer[x + map.w * y].Char.AsciiChar = (unsigned char)92;
				display.consoleBuffer[x + map.w * y].Attributes = color[2];
			}
			else if (c == mob)
			{
				display.consoleBuffer[x + map.w * y].Char.AsciiChar = (unsigned char)253;
				display.consoleBuffer[x + map.w * y].Attributes = 1;
			}
			else if (c == exittt)
			{
				display.consoleBuffer[x + map.w * y].Char.AsciiChar = (unsigned char)219;
				display.consoleBuffer[x + map.w * y].Attributes = 8;
			}
			/*	consoleBuffer[x + w * y].Char.AsciiChar = (unsigned char)253;
			consoleBuffer[x + w * y].Attributes = 100;*/




		}
	}


	/* Write our character buffer (a single character currently) to the console buffer */
	WriteConsoleOutputA(display.wHnd, display.consoleBuffer, display.characterBufferSize, display.characterPosition, &display.consoleWriteArea);
}

void draw_menu(short menu_h, short menu_w,map_t map, person_status_t state, display_t display)
{


	for (int y = map.h; y < map.h + menu_h; ++y)
	{
		for (int x = 0; x < map.w; ++x)
		{


			display.consoleBuffer[x + map.w * y].Char.AsciiChar = (unsigned char)219;
			display.consoleBuffer[x + map.w * y].Attributes = 5;

		}
	}
	//return;
	display.consoleBuffer[0 + map.w * (map.h + 0)].Char.AsciiChar = 'L';
	display.consoleBuffer[1 + map.w * (map.h + 0)].Char.AsciiChar = 'i';
	display.consoleBuffer[2 + map.w * (map.h + 0)].Char.AsciiChar = 'f';
	display.consoleBuffer[3 + map.w * (map.h + 0)].Char.AsciiChar = 'e';
	display.consoleBuffer[4 + map.w * (map.h + 0)].Char.AsciiChar = 's';
	display.consoleBuffer[5 + map.w * (map.h + 0)].Char.AsciiChar = ':';

	for (int i = 0; i < state.col_hearts; i++)
	{
		display.consoleBuffer[(i + 6) + map.w * (map.h + 0)].Char.AsciiChar = 3;
	}
	display.consoleBuffer[0 + map.w * (map.h + 1)].Char.AsciiChar = 'S';
	display.consoleBuffer[1 + map.w * (map.h + 1)].Char.AsciiChar = 'w';
	display.consoleBuffer[2 + map.w * (map.h + 1)].Char.AsciiChar = 'o';
	display.consoleBuffer[3 + map.w * (map.h + 1)].Char.AsciiChar = 'r';
	display.consoleBuffer[4 + map.w * (map.h + 1)].Char.AsciiChar = 'd';
	display.consoleBuffer[5 + map.w * (map.h + 1)].Char.AsciiChar = 's';
	display.consoleBuffer[6 + map.w * (map.h + 1)].Char.AsciiChar = ':';

	for (int i = 0; i < state.col_sw; i++)
	{
		display.consoleBuffer[(i + 7) + menu_w * (map.h + 1)].Char.AsciiChar = sword;

	}

	display.consoleBuffer[0 + map.w * (map.h + 2)].Char.AsciiChar = 'S';
	display.consoleBuffer[1 + map.w * (map.h + 2)].Char.AsciiChar = 't';
	display.consoleBuffer[2 + map.w * (map.h + 2)].Char.AsciiChar = 'a';
	display.consoleBuffer[3 + map.w * (map.h + 2)].Char.AsciiChar = 'r';
	display.consoleBuffer[4 + map.w * (map.h + 2)].Char.AsciiChar = 's';
	display.consoleBuffer[5 + map.w * (map.h + 2)].Char.AsciiChar = ':';
	if (state.col_zv < 10) {

		display.consoleBuffer[6 + menu_w * (map.h + 2)].Char.AsciiChar = state.col_zv + 48;

	}
	else {
		int u = state.col_zv % 10;
		int g = state.col_zv / 10;
		display.consoleBuffer[6 + menu_w * (map.h + 2)].Char.AsciiChar = g + 48;
		display.consoleBuffer[7 + menu_w * (map.h + 2)].Char.AsciiChar = u + 48;
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



	display.consoleBuffer[0 + menu_w * (map.h + 3)].Char.AsciiChar = 'M';
	display.consoleBuffer[1 + menu_w * (map.h + 3)].Char.AsciiChar = 'o';
	display.consoleBuffer[2 + menu_w * (map.h + 3)].Char.AsciiChar = 'o';
	display.consoleBuffer[3 + menu_w * (map.h + 3)].Char.AsciiChar = 'd';
	display.consoleBuffer[4 + menu_w * (map.h + 3)].Char.AsciiChar = ':';
	display.consoleBuffer[5 + menu_w * (map.h + 3)].Char.AsciiChar = ':';
	if (state.mood == mood_good) {
		display.consoleBuffer[6 + menu_w * (map.h + 3)].Char.AsciiChar = ')';
	}
	else if (state.mood == mood_bad) {
		display.consoleBuffer[6 + menu_w * (map.h + 3)].Char.AsciiChar = '(';
	}
	else {
		display.consoleBuffer[6 + menu_w * (map.h + 3)].Char.AsciiChar = '|';
	}
	/* Write our character buffer (a single character currently) to the console buffer */
	WriteConsoleOutputA(display.wHnd, display.consoleBuffer, display.characterBufferSize, display.characterPosition, &display.consoleWriteArea);
}


