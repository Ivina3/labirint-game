#pragma once
#include "win_setup.h"
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