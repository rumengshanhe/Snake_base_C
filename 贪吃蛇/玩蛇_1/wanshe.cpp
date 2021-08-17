/*
̰����_19.11.c
���ߣ�Comber���� 
	  FROM GUET
*/
#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <conio.h>
#include <stdlib.h>

#define MAPWIDTH 25
#define MAPHEIGHT 70
#define SNAKESIZE 30
#define MAX 100


/************************* ���ݲ��� ***************/
/************* SNAKE *************/
struct snake
{
	int x[SNAKESIZE];
	int y[SNAKESIZE];
	int len;
	int speed;
}snake;

/************* FOOD **************/
struct food
{
	int x;
	int y;
}food;
/************* BLOCK *************/
struct block
{
	int x[3];
	int y[3];
}block[5];

/********************* ����ģ�鲿�� **********************/
void gotoxy(int x, int y)			//gotoxy��������ʹ����ƶ���ָ��λ��, ����C++��׼����û���������, ����ֻ���Լ�����
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);//�ҵ�����̨�˴���
	COORD coord;									 //���Ľṹ��
	coord.X = x;
	coord.Y = y;									//��������
	SetConsoleCursorPosition(handle, coord);
}

void Draw_Snake(struct snake *p)
{
	gotoxy(p->x[0], p->y[0]);
	printf("@");
	for (int k = 1; k < p->len; k++)
	{
		gotoxy(p->x[k], p->y[k]);
		printf("*");
	}

}

void Rand_Food(struct food *f,struct block block[])
{
	int flag = 0;
	while (1)
	{
		srand((unsigned int)time(NULL));
		f->x = rand() % (MAPHEIGHT - 2) + 1;
		f->y = rand() % (MAPWIDTH - 2) + 1;
		for (int i = 0;i < 5;i++)
			for (int j = 0;j < 3;j++)
				if (f->x == block[i].x[j] && f->y == block[i].y[j])	//��ʳ�����ϰ����غ�
				{
					flag = 1;
					break;
				}
		if (!flag)
		{
			gotoxy(f->x, f->y);
			printf("o");
			break;
		}
	}
	
}

void Draw_Map()
{
	srand((unsigned int)time(NULL));			//�����������
	gotoxy(MAPHEIGHT + 7, 0);
	printf_s("̰����_19.11");
	gotoxy(MAPHEIGHT + 15, 1);
	printf_s("--COMBER���� ��Ʒ");
	for (int i = 0; i <= MAPHEIGHT; i++)		//����	
	{
		gotoxy(i, 0);
		printf("+");
		gotoxy(i, MAPWIDTH);
		printf("+");
	}
	for (int i = 1; i <= MAPWIDTH; i++)
	{
		gotoxy(0, i);
		printf("+");
		gotoxy(MAPHEIGHT, i);
		printf("+");
	}
	
	snake.len = 5;					//��ʼ����			
	snake.x[0] = 10;								
	snake.y[0] = 3;
	for (int k = 1; k < snake.len; k++)			
	{
		snake.x[k] = snake.x[k - 1] - 1;
		snake.y[k] = snake.y[k - 1] ;
	}
	Draw_Snake(&snake);
									
	for (int i = 0; i < 5; i++)				//�����ϰ���
	{
		block[i].x[0] = rand() % (MAPHEIGHT - 4) + 1;
		block[i].y[0] = rand() % (MAPWIDTH - 4) + 1;
		if (abs(block[i].x[0] - snake.x[0]) > 5 || abs(block[i].y[0] - snake.y[0]) > 3)
		{
			if (block[i].x[0] % 2 == 1)
			{
				gotoxy(block[i].x[0], block[i].y[0]);
				printf("+++");
				block[i].x[1] = block[i].x[0] + 1; block[i].y[1] = block[i].y[0];	//��¼�ϰ�������
				block[i].x[2] = block[i].x[1] + 1; block[i].y[2] = block[i].y[0];
			}
			else
			{
				for (int k = 0; k <= 2; k++)
				{
					gotoxy(block[i].x[0], block[i].y[0] + k);
					printf("+");
				}
				block[i].y[1] = block[i].y[0] + 1; block[i].x[1] = block[i].x[0];
				block[i].y[2] = block[i].y[1] + 1; block[i].x[2] = block[i].x[0];
			}
		}
		else
			i = 0;
	}
	Rand_Food(&food,block);		//��ʼʳ��
}

void Game_Over(struct snake *r)
{
	int score;
	int a[MAX];
	FILE *fp = NULL;
	errno_t err;
	score = r->len - 5;
	err = fopen_s(&fp,"E:/����/̰����/���а�.txt", "a+");
	fprintf(fp,"%d",score);
	system("pause");
	gotoxy(MAPHEIGHT + 5, 6);
	printf("GAME OVER...");
	gotoxy(MAPHEIGHT + 5, 7);
	printf("��ķ���Ϊ��%d", score);
	
	int i = 0, j = 0,rec;
	fread(a, MAX, 1, fp);
	gotoxy(0, MAPWIDTH + 2);
	while(i<MAX)
		printf("%d", a[i++]);
	fclose(fp);
	gotoxy(MAPHEIGHT + 5, 8);
	printf("���س����¿�ʼ ��������˳�");
	while (1)
	{
		if (_kbhit()) break;
	}
}

int Level_Choose(struct snake *s)
{											//�Ѷȵȼ�ѡ��
	char c;
	int f=0;
	s->speed = 15000;
	
	gotoxy(MAPHEIGHT + 5, 3);
	printf_s("��ѡ���Ѷȵȼ���A������ B������ C����--");
	c = _getch();
	switch (c)
	{
	case 'A':
	case 'a':	gotoxy(MAPHEIGHT + 5, 4); puts("A����-ף�����!!"); s->speed = 22000; break;
	case 'B':	
	case 'b':	 gotoxy(MAPHEIGHT + 5, 4); puts("B����-��������!!"); break;
	case 'C':	
	case 'c':	gotoxy(MAPHEIGHT + 5, 4); puts("C��-�����̶�������ô�򵥵�!!"); s->speed = 5000; break;
	case 27:	Game_Over(s); f = 1;
	default:	gotoxy(MAPHEIGHT + 5, 4); puts("Ĭ��-Ҳ̫���˰�!!"); s->speed = 5000; break;
	}
	return f;
}

void Go_Left(struct snake *top)			//�ߵ��ƶ�ģ�飨�ƶ�һ����
{
	int i;
	gotoxy(top->x[top->len-1], top->y[top->len-1]);
	printf_s(" ");
	for (i = top->len - 1; i > 0 ; i--)
	{
		top->x[i] = top->x[i - 1];
		top->y[i] = top->y[i - 1];
	}
	top->x[0] = top->x[0] - 1;
	Draw_Snake(top);
}

void Go_Dowm(struct snake *top)
{
	int i;
	gotoxy(top->x[top->len - 1], top->y[top->len - 1]);
	printf_s(" ");
	for (i = top->len - 1; i > 0; i--)
	{
		top->x[i] = top->x[i - 1];
		top->y[i] = top->y[i - 1];
	}
	top->y[0] = top->y[0] + 1;
	Draw_Snake(top);
}

void Go_Right(struct snake *top)
{
	int i;
	gotoxy(top->x[top->len - 1], top->y[top->len - 1]);
	printf_s(" ");
	for (i = top->len - 1; i > 0; i--)
	{
		top->x[i] = top->x[i - 1];
		top->y[i] = top->y[i - 1];
	}
	top->x[0] = top->x[0] + 1;
	Draw_Snake(top);
}

void Go_Up(struct snake *top)
{
	int i;
	gotoxy(top->x[top->len - 1], top->y[top->len - 1]);
	printf_s(" ");
	for (i = top->len - 1; i > 0; i--)
	{
		top->x[i] = top->x[i - 1];
		top->y[i] = top->y[i - 1];
	}
	top->y[0] = top->y[0] - 1;
	Draw_Snake(top);
}

void Delay_ms(int m)	//����ʱ
{
	int i, j;
	for (i = 0; i < m; i++)
		for (j = 0; j < 10000; j++);
}

void Catch_check(struct snake *t,struct food *f,struct block block[])	//�Ե�ʳ����
{
	if (t->x[0] == f->x&&t->y[0]==f->y)
	{
		Rand_Food(f,block);
		t->len++;
	}
}

int Over_check(struct snake *q,struct block b[])	//��Ϸ�������
{
	int i, j, k;
	int flag=0;
	for (i = 0; i < 5; i++)
		for (j = 0; j < 3; j++)
		{
			if (q->x[0] == b[i].x[j] && q->y[0] == b[i].y[j])
			{
				Game_Over(q);
				flag = 1; 
			}
		}
	for (k = 1; k < q->len; k++)
		if (q->x[0] == q->x[k] && q->y[0] == q->y[k])
		{
			Game_Over(q);
			flag = 1; 	
		}
	if (q->x[0] == 0 || q->x[0] == MAPHEIGHT - 1)
	{
			Game_Over(q);
			flag = 1; 
	}
	if (q->y[0] == 0 || q->y[0] == MAPWIDTH - 1)
	{
			Game_Over(q);
			flag = 1;	
	}
	return flag;
}


/************************* ͳ�� ʵ�ֲ��� **************************/
int Operate(struct snake *top , struct food *fo,struct block b[],char ch)
{
	int speed=top->speed;
	gotoxy(top->x[0],top->y[0]);
	int m=0;
	char ch1 = ch;
	if (_kbhit())
	{
		fflush(stdin);
		ch = _getch();
	}
	switch (ch)
	{
		case 75:	Go_Left( top ); break;	
		case 72:	Go_Up( top ); break;
		case 77:	Go_Right( top ); break;
		case 80:	Go_Dowm( top ); break;
		case 27:	Game_Over(top); return 1;
	}
	Catch_check(top,fo,b);
	m = Over_check( top, b);
	if(m)		//��Ϸ�������
		return m;
	if(ch1 != ch && top->speed==5000)//��Сת�򰴼��ӳ�
		Delay_ms(25000 - speed - 11000 );		//�����ٶ�,
	else if(ch1 != ch && top->speed == 15000)
		Delay_ms(25000-speed-3000);
	else
	Delay_ms(25000 - speed);
	
	Operate(top , fo ,b,ch );
}

int Restart_check(int flag)
{
	char ch;
	if (flag == 1)
	{
		ch = _getch();
		if (ch == 13)		//�س�-������Ϸ��������˳�
		{
			system("cls");
			return 1;
		}
		else
			exit(0);
	}
	else return 0;
}

int main()
{
	char ch1 = 77, ch2 = 0;
	int flag1 = 0, flag2 = 0, a[MAX];
	FILE* fp = NULL;
	errno_t err1;

	while (1)
	{
		Draw_Map();
		flag1 = Level_Choose(&snake);
		flag2 = Restart_check(flag1);
		if (flag2 == 1)
			continue;				//ʵ��������Ϸ
		flag1 = Operate(&snake, &food, block, ch1);
		flag2 = Restart_check(flag1);
		if (flag2 == 1)
			continue;
	}
	
	return 0;
}