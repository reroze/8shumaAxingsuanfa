#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct point {
	int caozuo_last;//记录上一次的操作0,1,2,3分别代表上，下，左，有
	int juzhen[3][3];//记录本次操作后的矩阵
	int option[4];//记录本次操作后，下次能走的方向
	int zuobiaor;//记录0所在的行数，从上之下为0,1,2
	int zuobiaol;//记录0所在的列数，从左至有为0,1,2
	int g_x;//记录其到根节点的距离
	int h_x;//记录其到目标矩阵的距离
	int f_x;//=g_x+h_x
	struct point*form;//双向链表接口，因为效率不高，本例予以删除
	struct point*next;//单向列表接口，指向下一个节点
	struct point*fu;//指向父节点
};

typedef struct point pin;
pin *front0 = NULL, *pi;//根节点
pin *open0 = NULL;//open表头结点
pin *close0 = NULL;//close表头结点
pin *open, *close=close0;
int format[3][3] = { { 2,8,3 },{ 1,6,4 },{ 7,0,5 } };
int mubiao[3][3] = { { 1,2,3 },{ 8,0,4 },{ 7,6,5 } };
//int format[3][3] = { { 1,2,3 },{ 4,0,6 },{ 7,5,8 } };//初始数组
//int mubiao[3][3] = { { 1,2,3 },{ 4,5,6 },{ 7,8,0 } };//目标数组，0代表空格 
void create(pin*pi, int i);//创建新节点
void fuzhi_juzhen(pin*p, int now[3][3]);//给节点赋值操作完后的矩阵
void enqueue_open(pin*p);//open队列入队
void dequeue_open();//open队列出队
void enqueue_close(pin*p);//close队列入队
void dequeue_close();//close队列出队
void chushihua(pin*p);//节点部分元素初始化
void swap(int buffle[3][3], pin*pi, pin*p, int i);//对应的0元素的移动
int panduan(pin*p, int i);//判断0下一步的可能方向
void p_option(pin*p);//将下一步的方向赋值到节点
int bijiao(int now[3][3], int mubiao[3][3]);//比较两个节点之间的矩阵差别
int count = 0;//统计一共的步数
void print(int now[3][3]);//打印矩阵
pin* yiwei(int x);//从头结点找到某个特定的节点
void paixu_open(pin*p);//open表除open0之外按节点f_x排序，找到f_x最小的那个
int length(pin*p);//查找队列中的长度
void jiedian_swap(pin*q1, pin*q2);//交换两个节点的数据
void Gx(pin*p);//计算节点的g_x
void Hx(pin*p);//计算节点的f_x
void Fx(pin*p);//计算节点的f_x
int jiancha_open(pin*open0, pin*p);//检查open表中有没有重复的
int jiancha_close(pin*p);//检查将要拓展的节点之前是否已探索过
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
	enqueue_open(front0);//根节点初始化，并入队open
	while (1)
	{
		for (int i = 0; i < 4; i++)
		{
			if (panduan(open0, i) == 1)//判断对于ope0而言（上，下，左，右）（i=0,1,2,3）能否前进
			{
				create(open0, i);//若能，开辟新的节点
				//count++;
				if (bijiao(open0->juzhen, mubiao) == 1)//比较当前的open0节点矩阵域目标
					break;
			}

		}
		if (bijiao(open0->juzhen, mubiao) == 1)
			break;

		dequeue_open();//open表头结点移动
		count++;//步数加1
		
		dequeue_close();//close表连接刚出来的open0节点
		/*if (close0 == NULL)
		{
			close0 = open0;
			open0 = NULL;
		}*/
	}
	printf("%d", count);//输出总的步数
	pin*ye = open0;
	printf("\n");
	print(open0->juzhen);
	printf("\n");
	ye = ye->fu;
	int length = 0;
	while (ye)//输出实现的矩阵流程
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
/**********************************************************检查是否在close表里***********************************/
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
/************************************************************节点数据交换*********************************/
void jiedian_swap(pin*q1, pin*q2)
{
	pin *term = NULL;//此处数据部分采用交换数据域，但是也要交换其父节点指针
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
	q2->fu = term;//交换父节点指针
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

/**************************************************计算当前节点的g_x***************************************/
void Gx(pin*p)
{
	int count = 0;
	pin *p3 = p->fu;
	while (p3)//计算起到根节点的距离
	{
		p3 = p3->fu;
		count++;
	}
	p->g_x = count;
}

/***************************************************计算当前节点的h_x****************************************/

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
	}//计算当前节点的矩阵到目标矩阵的距离
	p->h_x = count;
}

/***************************************************************计算f_x***************************/
void Fx(pin*p)
{
	Gx(p);//计算当前节点的g_x
	Hx(p);//计算当前节点的h_x
	p->f_x = p->g_x + p->h_x;
}
/************************************************************统计队列的长度******************************/
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
/************************************************************比较两个矩阵********************************/
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
/**************************************************************open0出队*****************************/
void dequeue_open()
{
	if (close0 == NULL)
	{
		close0 = open0;
		
		open0 = open0->next;
		close0->next = NULL;
		close = close0;
	}//close表头初始化
	else {
		close= open0;
		open0 = open0->next;
		close->next = NULL;//将出来的open0接入close表中
	}
}
/******************************************************************************************/
void dequeue_close()
{
	close = close->next;//close当前指针移位
}
/***********************************************************************确认节点下一步可能路线**********************/
void p_option(pin*p)
{
	int r = p->zuobiaor;//找到当前节点的0的行数
	int l = p->zuobiaol;//找到当前节点的0的列数
	for (int i = 0; i < 4; i++)
	{
		if (i + p->caozuo_last != 1 && i + p->caozuo_last != 5)
		{//保证不进行上一次操作的反向操作，禁忌值设为1
			switch (i)
			{
			case 0:
				if (r - 1 >= 0)//如果其不在第一行，则可向上走
					p->option[0] = 1;
				break;
			case 1:
				if (r + 1 < 3)//如果其不在第三行，则可向下走
					p->option[1] = 1;
				break;
			case 2:
				if (l - 1 >= 0)//如果其不在第一列，则可向左走
					p->option[2] = 1;
				break;
			case 3:
				if (l + 1 < 3)//如果其不在第三列，则可向右走
					p->option[3] = 1;
				break;
			}
		}
	}
}
/*****************************************************判断下一步节点p i方向可走*****************************************/
int panduan(pin*p, int i)
{
	if (p->option[i] == 1)
		return 1;
	return 0;
}
/*********************************************************矩阵赋值**********************************/
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
/****************************************************************初始化**************************/
void chushihua(pin*p)
{
	for (int i = 0; i < 4; i++)
		p->option[i] = 0;
	p->next = NULL;
}
/*******************************************************************操作执行************************/
void swap(int buffle[3][3], pin *pi, pin*p, int i)
{
	int term = 0;
	p->caozuo_last = i;//将该节点的上一次操作赋值为i
	int r = pi->zuobiaor;//找到其父节点的0的行数
	int l = pi->zuobiaol;//找到其父节点的0的列数
	for (int x = 0; x < 3; x++)
	{
		for (int y = 0; y < 3; y++)
		{
			buffle[x][y] = pi->juzhen[x][y];//先将父节点的矩阵保存出来
		}
	}
	switch (i)//按i的值判定进行（上，下，左，右）操作
	{
	case 0:
		term = buffle[r - 1][l];
		buffle[r - 1][l] = 0;
		buffle[r][l] = term;
		break;//交换0的位置
	case 1:
		term = buffle[r + 1][l];
		buffle[r + 1][l] = 0;
		buffle[r][l] = term;
		break;//交换0的位置
	case 2:
		term = buffle[r][l - 1];
		buffle[r][l - 1] = 0;
		buffle[r][l] = term;
		break;//交换0的位置
	case 3:
		term = buffle[r][l + 1];
		buffle[r][l + 1] = 0;
		buffle[r][l] = term;
		break;//交换0的位置
	}
}
/*******************************************************返回队列中特定位置的节点**********************************************/
pin* yiwei(int x)
{
	pin*p = open0;
	for (int i = 0; i < x; i++)
	{
		p = p->next;
	}
	return p;
}
/************************************************************升序排序***************************************/
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
			if (q2->f_x < q1->f_x)//选择法升序排序
				jiedian_swap(q1, q2);//节点数据交换。
		}
	}
}
/************************************************检查新节点是否在open表里*********************************************/
int jiancha_open(pin*open0, pin*p)
{
	pin*p1 = open0;
	while (p1)
	{
		if (bijiao(p1->juzhen, p->juzhen) == 1)//如果新的节点与之前open表里的矩阵有相同的
		{
			if (p->f_x > p1->f_x)
				return 0;//如果新节点的f_x更大，返回0
			if (p->f_x < p1->f_x)//若果新节点的f_x更小
			{
				jiedian_swap(p1, p);
				//p1->fu = p->fu;
				paixu_open(open0);//交换新节点与之前节点的数据，并将open表重排序
				return 1;//返回1
			}
			break;
		}
		p1=p1->next;
	}
	
	return 2;//若没有相同的，返回2
}
/**********************************************判断并看情况是否将新的节点加入open表里*******************************************************/
void enqueue_open(pin*p)
{
	//int buffle[3][3] = { 0 };
	if (open0 == NULL)//open的头结点初始化
	{
		open0 = p;
		open = open0;
	}
	else {
		if (jiancha_open(open0, p) == 2)//如果新的节点不在open里
		{
			open->next = p;
			open = open->next;
			paixu_open(open0);//将新的节点加入open表，并将open表升序排序
		}
	}
	//swap(buffle, zi, i);

}
/***********************************************************************************************************/
/*void enqueue_close(pin*p)
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

}*/
/*************************************************************************开辟节点**************************************/
void create(pin*pi, int i)
{
	int buffle[3][3] = { 0 };//建立缓冲数组
	pin *p = (pin*)malloc(sizeof(pin));//分配新的节点空间
	p->fu = pi;//赋值新的节点的父节点
	chushihua(p);//初始化节点下一步，以及next指针
	swap(buffle, pi, p, i);//将执行操作后的矩阵存入缓冲数组里
	fuzhi_juzhen(p, buffle);//将缓冲数组写入节点的数组中
	p_option(p);//判断新节点的下一步可能
	Fx(p);//计算该节点的f_x
	if(jiancha_close(p)==1)//检查p是否在close表里
	enqueue_open(p);//判断并看情况是否将新的节点加入open表里

}
/****************************************************输出矩阵**********************************/
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
