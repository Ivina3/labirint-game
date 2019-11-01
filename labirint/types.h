#pragma once
#include "win_setup.h"
#include <string>
#include <simple2d.h>
const int exittt = 35;
const int space = 0;
const int stena = 1;
const int person = 2;
const int zvezda = 3;
const int move_left = 75;
const int move_right = 77;
const int move_down = 80;
const int move_up = 72;
const int mob = 253;
const int sword = 92;


struct Node
{
	int x, y; //Node position - little waste of memory, but it allows faster generation
	void *parent; //Pointer to parent node
	char c; //Character to be displayed
	char dirs; //Directions that still haven't been explored
};

struct display_t 
{
	CHAR_INFO* consoleBuffer;
	HANDLE wHnd;
	COORD characterBufferSize;
	COORD characterPosition;
	SMALL_RECT consoleWriteArea;
	HANDLE rHnd;
	COORD bufferSize;
};
struct map_t 
{
		int h;
	int w;
	int* field;
};
struct move_obj_desc_t
{
	int from_y;
	int from_x;
	int to_y;
	int to_x;
	int name;
};
struct cord_t
{
	int x;
	int y;
}; 


enum mood_e
{
	mood_bad = 3,
	mood_normal = 2,
	mood_good = 1,
};
struct person_status_t
{// ��������� ����
	int col_hearts;// ���-�� ������
	int col_sw;// ���-�� �����, ��� �����������b c mob, -1 ���
	int mood;//���������� ���� ���� �� ������ ������ - 1-������� �� 5 ����, ���� ��� - 2-�������, ���� ����� ���(30 ����� ���) - 3-������;
	int col_zv;
};
//��������� ���������� ���� ����������;
//�������� ������� move_step_in_labyrinth ���������� ����� ���������;
struct move_res_t
{
	bool ok;//true ���� �������� ���� ��������� ���. ���� ����� �������� - false
	int name;//��� ������ �� ������� ���� ��������. ���� ok == true
};
//map_t map;

//struct S2D_Image;
struct resuarces_t
{
	S2D_Image* brick;
	S2D_Image* zvezda;
	S2D_Image* sword;
	S2D_Image* mob;
	S2D_Image* person;
	S2D_Image* portal;
	S2D_Image* life;
	S2D_Sound *zvezda_;
	S2D_Sound *mob_;
	S2D_Sound *sword_;
	S2D_Sound *level_;
	S2D_Sound *end_;
	std::string resources_path;

	S2D_Music *mus;
};