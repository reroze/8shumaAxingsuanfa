#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct point {
	int caozuo_last;
	int juzhen[3][3];
	int option[4];
	int zuobiaor;
	int zuobiaol;
	int g_x;
	int h_x;
	int f_x;
	struct point*form;
	struct point*next;
	struct point*fu;
};

typedef struct point pin;
pin *front0 = NULL, *pi;
pin *open0 = NULL;
pin *close0 = NULL;
pin *open, *close=close0;
int format[3][3] = { { 2,8,3 },{ 1,6,4 },{ 7,0,5 } };
int mubiao[3][3] = { { 1,2,3 },{ 8,0,4 },{ 7,6,5 } };
void create(pin*pi, int i);
void fuzhi_juzhen(pin*p, int now[3][3]);
void enqueue_open(pin*p);
void dequeue_open();
void enqueue_close(pin*p);
void dequeue_close();
void chushihua(pin*p);
void swap(int buffle[3][3], pin*pi, pin*p, int i);
int panduan(pin*p, int i);
void p_option(pin*p);
int bijiao(int now[3][3], int mubiao[3][3]);
int count = 0;
void print(int now[3][3]);
pin* yiwei(int x);
void paixu_open(pin*p);
int length(pin*p);
void jiedian_swap(pin*q1, pin*q2);
void Gx(pin*p);
void Hx(pin*p);
void Fx(pin*p);
int jiancha_open(pin*open0, pin*p);
int jiancha_close(pin*p);
/******************************************************************************************/
void main()
{

	front0 = (pin*)malloc(sizeof(pin));
	pin *p;
	fuzhi_juzhen(front0, format);
	chushihua(front0);
	front0->caozuo_last = -5;
	p_option(front0);
	pi = front0;
	front0->fu = NULL;
	enqueue_open(front0);
	while (1)
	{
		for (int i = 0; i < 4; i++)
		{
			if (panduan(open0, i) == 1)
			{
				create(open0, i);
				//count++;
				if (bijiao(open0->juzhen, mubiao) == 1)
					break;
			}

		}
		if (bijiao(open0->juzhen, mubiao) == 1)
			break;

		dequeue_open();
		count++;
		
		dequeue_close();
		/*if (close0 == NULL)
		{
			close0 = open0;
			open0 = NULL;
		}*/
	}
	printf("%d", count);
	pin*ye = open0;
	printf("\n");
	print(open0->juzhen);
	printf("\n");
	ye = ye->fu;
	int length = 0;
	while (ye)
	{
		length++;
		printf("\n");
		print(ye->juzhen);
		printf("\n");
		ye = ye->fu;
	}
	printf("\n$%d$", length);
	system("pause");
}
/***********************************************************************************************/
int jiancha_close(pin*p)
{
	pin*close1 = close0;
	while (close1)
	{
		if (bijiao(close1->juzhen, p->juzhen) == 1)
			return 0;
		close1 = close1->next;
	}
	return 1;
}
/*********************************************************************************************/
void jiedian_swap(pin*q1, pin*q2)
{
	pin *term = NULL;
	int temp = 0;
	temp = q1->caozuo_last;
	q1->caozuo_last = q2->caozuo_last;
	q2->caozuo_last = temp;
	temp = 0;
	temp = q1->zuobiaor;
	q1->zuobiaor = q2->zuobiaor;
	q2->zuobiaor = temp;
	temp = 0;
	temp = q1->zuobiaol;
	q1->zuobiaol = q2->zuobiaol;
	q2->zuobiaol = temp;
	temp = 0;
	temp = q1->g_x;
	q1->g_x = q2->g_x;
	q2->g_x = temp;
	temp = 0;
	temp = q1->h_x;
	q1->h_x = q2->h_x;
	q2->h_x = temp;
	temp = 0;
	temp = q1->f_x;
	q1->f_x = q2->f_x;
	q2->f_x = temp;
	temp = 0;
	/*term = q1->form;
	q1->form = q2->form;
	q2->form = term;
	term = NULL;
	term = q1->next;
	q1->next = q2->next;
	q2->next = term;
	term = NULL;
	*/term = q1->fu;
	q1->fu = q2->fu;
	q2->fu = term;
	term = NULL;
	for (int i = 0; i < 4; i++)
	{
		temp = q1->option[i];
		q1->option[i] = q2->option[i];
		q2->option[i] = temp;
		temp = 0;
	}
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			temp = q1->juzhen[i][j];
			q1->juzhen[i][j] = q2->juzhen[i][j];
			q2->juzhen[i][j] = temp;
			temp = 0;
		}
	}
}

/*****************************************************************************************/
void Gx(pin*p)
{
	int count = 0;
	pin *p3 = p->fu;
	while (p3)
	{
		p3 = p3->fu;
		count++;
	}
	p->g_x = count;
}

/*******************************************************************************************/

void Hx(pin*p)
{
	int count = 0;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (p->juzhen[i][j] != mubiao[i][j])
				count++;
		}
	}
	p->h_x = count;
}

/******************************************************************************************/
void Fx(pin*p)
{
	Gx(p);
	Hx(p);
	p->f_x = p->g_x + p->h_x;
}
/******************************************************************************************/
int length(pin*p)
{
	int l = 0;
	pin*p1 = p;
	while (p1)
	{
		p1 = p1->next;
		l++ ;
	}
	return l;
}
/********************************************************************************************/
int bijiao(int now[3][3], int mubiao[3][3])
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (now[i][j] != mubiao[i][j])
				return 0;
		}
	}
	return 1;
}
/*******************************************************************************************/
void dequeue_open()
{
	if (close0 == NULL)
	{
		close0 = open0;
		
		open0 = open0->next;
		close0->next = NULL;
		close = close0;
	}
	else {
		close= open0;
		
		open0 = open0->next;
		close->next = NULL;
	}
}
/******************************************************************************************/
void dequeue_close()
{
	close = close->next;
}
/*********************************************************************************************/
void p_option(pin*p)
{
	int r = p->zuobiaor;
	int l = p->zuobiaol;
	for (int i = 0; i < 4; i++)
	{
		if (i + p->caozuo_last != 1 && i + p->caozuo_last != 5)
		{
			switch (i)
			{
			case 0:
				if (r - 1 >= 0)
					p->option[0] = 1;
				break;
			case 1:
				if (r + 1 < 3)
					p->option[1] = 1;
				break;
			case 2:
				if (l - 1 >= 0)
					p->option[2] = 1;
				break;
			case 3:
				if (l + 1 < 3)
					p->option[3] = 1;
				break;
			}
		}
	}
}
/**********************************************************************************************/
int panduan(pin*p, int i)
{
	if (p->option[i] == 1)
		return 1;
	return 0;
}
/*******************************************************************************************/
void fuzhi_juzhen(pin*p, int now[3][3])
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			p->juzhen[i][j] = now[i][j];
			if (now[i][j] == 0)
			{
				p->zuobiaor = i;
				p->zuobiaol = j;
			}
		}
	}
}
/******************************************************************************************/
void chushihua(pin*p)
{
	for (int i = 0; i < 4; i++)
		p->option[i] = 0;
	p->next = NULL;
}
/*******************************************************************************************/
void swap(int buffle[3][3], pin *pi, pin*p, int i)
{
	int term = 0;
	p->caozuo_last = i;
	int r = pi->zuobiaor;
	int l = pi->zuobiaol;
	for (int x = 0; x < 3; x++)
	{
		for (int y = 0; y < 3; y++)
		{
			buffle[x][y] = pi->juzhen[x][y];
		}
	}
	switch (i)
	{
	case 0:
		term = buffle[r - 1][l];
		buffle[r - 1][l] = 0;
		buffle[r][l] = term;
		break;
	case 1:
		term = buffle[r + 1][l];
		buffle[r + 1][l] = 0;
		buffle[r][l] = term;
		break;
	case 2:
		term = buffle[r][l - 1];
		buffle[r][l - 1] = 0;
		buffle[r][l] = term;
		break;
	case 3:
		term = buffle[r][l + 1];
		buffle[r][l + 1] = 0;
		buffle[r][l] = term;
		break;
	}
}
/*****************************************************************************************************/
pin* yiwei(int x)
{
	pin*p = open0;
	for (int i = 0; i < x; i++)
	{
		p = p->next;
	}
	return p;
}
/***************************************************************************************************/
void paixu_open(pin*p)
{
	int leng = length(open0);
	pin *q1, *q2;
	for (int i = 1; i < leng - 1; i++)
	{
		for (int j = i; j < leng; j++)
		{
			q1 = yiwei(i);
			q2 = yiwei(j);
			if (q2->f_x < q1->f_x)
				jiedian_swap(q1, q2);
		}
	}
}
/*****************************************************************************************************/
int jiancha_open(pin*open0, pin*p)
{
	pin*p1 = open0;
	while (p1)
	{
		if (bijiao(p1->juzhen, p->juzhen) == 1)
		{
			if (p->f_x > p1->f_x)
				return 0;
			if (p->f_x < p1->f_x)
			{
				jiedian_swap(p1, p);
				p1->fu = p->fu;
				paixu_open(open0);
				return 1;
			}
			break;
		}
		p1=p1->next;
	}
	
	return 2;
}
/*****************************************************************************************************/
void enqueue_open(pin*p)
{
	//int buffle[3][3] = { 0 };
	if (open0 == NULL)
	{
		open0 = p;
		open = open0;
	}
	else {
		if (jiancha_open(open0, p) == 2)
		{
			open->next = p;
			open = open->next;
			paixu_open(open0);
		}
	}
	//swap(buffle, zi, i);

}
/***********************************************************************************************************/
void enqueue_close(pin*p)
{
	//int buffle[3][3] = { 0 };
	if (close0 == NULL)
	{
		close0 = p;
		close = close0;
	}
	else {
		close->next = p;
		close = close->next;
	}
	//swap(buffle, zi, i);

}
/***************************************************************************************************************/
void create(pin*pi, int i)
{
	int buffle[3][3] = { 0 };
	pin *p = (pin*)malloc(sizeof(pin));
	p->fu = pi;
	chushihua(p);
	swap(buffle, pi, p, i);
	fuzhi_juzhen(p, buffle);
	p_option(p);
	Fx(p);
	if(jiancha_close(p)==1)
	enqueue_open(p);

}
/**************************************************************************************/
void print(int now[3][3])
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			printf("%2d", now[i][j]);
		}
		printf("\n");
	}
}
/*****************************************************************************************/

/*******************************************************************************************/

/******************************************************************************************/