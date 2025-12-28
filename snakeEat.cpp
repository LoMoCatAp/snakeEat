#define _CRT_SECURE_NO_WARNINGS
#include <graphics.h>
#include <conio.h>
#include <time.h>
#include <math.h>
#include <stdio.h>

#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

//粒子个数
#define MAX_PARTICLES 20


//ARGB
#define ARGB(a, r, g, b) ((DWORD)((((DWORD)(a)) << 24) | (((DWORD)(r)) << 16) | (((DWORD)(g)) << 8) | ((DWORD)(b))))


//屏幕尺寸
#define WIDTH 1280
#define HEIGHT 960

//移动参数
#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4

//身体结构体
struct Body
{
	int x;
	int y;
	int diretion;

};

//蛇结构体
struct Snake
{
	int length;
	Body body[10000];
	int score;
};

//身体打印函数
void printSnake(Snake snake)
{
	//setlinestyle(PS_SOLID, 3);
	for (int j = snake.length-1; j >= 0; j--)
	{
		setlinecolor(ARGB(252, 0, 145, 0));
		if (j == 0)
		{
			setbkmode(TRANSPARENT);

			//setfillcolor(ARGB(250, 0, 145, 0));
			//fillcircle(snake.body[j].x, snake.body[j].y, 23);

			setfillcolor(ARGB(100, 0, 140, 0));
			solidcircle(snake.body[j].x, snake.body[j].y, 22);

			setfillcolor(ARGB(20, 0, 135, 0));
			solidcircle(snake.body[j].x, snake.body[j].y, 21);

			setfillcolor(ARGB(0, 0, 130, 0));
			solidcircle(snake.body[j].x, snake.body[j].y, 20);
		}
		else
		{
			setbkmode(TRANSPARENT);

			//setfillcolor(ARGB(250, 0, 160, 0));
			//fillcircle(snake.body[j].x, snake.body[j].y, 23);

			//setfillcolor(ARGB(100, 0, 140, 0));
			//solidcircle(snake.body[j].x, snake.body[j].y, 22);

			setfillcolor(ARGB(20, 0, 135, 0));
			solidcircle(snake.body[j].x, snake.body[j].y, 21);

			setfillcolor(ARGB(0, 0, 120, 0));
			solidcircle(snake.body[j].x, snake.body[j].y, 20);

		}
	}
};

//身体增加函数
void addBody(Snake *snake)
{
	for(int k=0;k<3;k++)
	{
		if (snake->length < 9999)
		{
			//定义坐标


			if (snake->body[(snake->length) - 1].diretion == LEFT)
			{

				snake->body[snake->length].x = snake->body[snake->length - 1].x + 5;
				snake->body[snake->length].y = snake->body[snake->length - 1].y;
				snake->body[snake->length].diretion = snake->body[snake->length - 1].diretion;

			}
			if (snake->body[snake->length - 1].diretion == RIGHT)
			{
				snake->body[snake->length].x = snake->body[snake->length - 1].x - 5;
				snake->body[snake->length].y = snake->body[snake->length - 1].y;
				snake->body[snake->length].diretion = snake->body[snake->length - 1].diretion;

			}
			if (snake->body[snake->length - 1].diretion == UP)
			{
				snake->body[snake->length].x = snake->body[snake->length - 1].x;
				snake->body[snake->length].y = snake->body[snake->length - 1].y - 5;
				snake->body[snake->length].diretion = snake->body[snake->length - 1].diretion;

			}
			if (snake->body[snake->length - 1].diretion == DOWN)
			{
				snake->body[snake->length].x = snake->body[snake->length - 1].x;
				snake->body[snake->length].y = snake->body[snake->length - 1].y + 5;
				snake->body[snake->length].diretion = snake->body[snake->length - 1].diretion;

			}

			snake->length++;
		}
	}
}

//食物结构体
struct Food
{
	int x;
	int y;
	int active;
	float pulse;
};

//创建食物函数
Food createFood(int Snakex, int Snakey,int *count)
{
	Food food;
	food.x = 20 + rand() % (WIDTH - 40);
	food.y = 20 + rand() % (HEIGHT - 40);
	food.pulse = 0;

	if (food.x == Snakex && food.y == Snakey)
	{
		return createFood(Snakex,Snakey,count);
	}
	(*count)++;
	food.active = 1;
	return food;
} 
//食物打印函数
void printfFood(Food food[], int foodcount)
{
	for (int j = 0; j < foodcount; j++)
	{
		if (food[j].active == 1)
		{
			setlinecolor(ARGB(252, 255, 200, 0));
			//呼吸
			float r = 15 + sin(food[j].pulse) * 2;

			int cx = (int)(food[j].x + 0.5f);
			int cy = (int)(food[j].y + 0.5f);

			//外层
			setfillcolor(ARGB(250, 255, 200, 0));
			solidcircle(cx, cy, (int)(r + 8));

			setfillcolor(ARGB(60, 255, 180, 0));
			solidcircle(cx, cy, (int)(r + 4));

			//主体
			setfillcolor(ARGB(0, 255, 150, 0));
			solidcircle(cx, cy, (int)r);
			//fillcircle(food[j].x, food[j].y, 15);

			food[j].pulse += 0.08f;
		}
	}
}

//食物粒子效果

struct Particle
{
	float x, y;
	float vx, vy;
	int life;
	int active;
};

void spawnParticles(Particle p[], int count, int x, int y)
{
	for (int i = 0; i < count; i++)
	{
		p[i].x = x;
		p[i].y = y;
		p[i].vx = (rand() % 100 - 50) / 10.0f;
		p[i].vy = (rand() % 100 - 50) / 10.0f;
		p[i].life = 20 + rand() % 10;
		p[i].active = 1;
	}
}

void updateParticles(Particle p[], int count)
{
	setfillcolor(RGB(36, 173, 243));

	for (int i = 0; i < count; i++)
	{
		if (!p[i].active) continue;

		p[i].x += p[i].vx;
		p[i].y += p[i].vy;
		p[i].life--;

		if (p[i].life <= 0)
			p[i].active = 0;
		else
			solidcircle((int)p[i].x, (int)p[i].y, 3);
	}
}


//移动函数
void moveSnake(Snake* snake)
{
	for (int j = snake->length -1; j >=0; j--)
	{
		if (j == 0)
		{
			if (snake->body[0].diretion == LEFT)
			{
				snake->body[0].x -= 7;
			}
			if (snake->body[0].diretion == RIGHT)
			{
				snake->body[0].x += 7;
			}
			if (snake->body[0].diretion == UP)
			{
				snake->body[0].y -= 7;
			}
			if (snake->body[0].diretion == DOWN)
			{
				snake->body[0].y += 7;
			}
		}
		else
		{
			snake->body[j] = snake->body[j - 1];
		}
			
		
	}
}

//更新历史最高分数
int updateScore(int score)
{
	FILE* p = fopen("Bscore.txt","r");
	if (p == NULL)
	{
		printf("txt Error");
		return 0;
	}
	int historyScore;
	fscanf(p, "%d", &historyScore);

	fclose(p);

	if (historyScore < score)
	{
		FILE* p = fopen("Bscore.txt", "w");
		if (p == NULL)
		{
			printf("txt Error");
			return 0;
		}
		fprintf(p, "%d", score);
		fclose(p);
		return score;
	}
	else
	{
		return historyScore;
	}
}
//绘制文字
void printScore(int score,int bscore,int isPause,int running,int *shakeTime,int maxShakeTime,int shakeStrength)
{

	//抖动
	int offsetX = 0;
	int offsetY = 0;

	if (!running && *shakeTime > 0)
	{
		float t = (float)(*shakeTime) / maxShakeTime;
		int s = (int)(shakeStrength * t);

		offsetX = rand() % (s * 2 + 1) - s;
		offsetY = rand() % (s * 2 + 1) - s;

		(*shakeTime)--;
	}

	settextcolor(WHITE);
	settextstyle(30, 0, "Consolas");
	setbkmode(TRANSPARENT);

	//分数
	char buf[50];
	sprintf_s(buf, "Score: %d", score);
	outtextxy(20, 20, buf);
	outtextxy(20, 80, L"生命值：♥ ♥ ♡ ♡");

	//历史最高分数
	char buf1[50];
	sprintf_s(buf1, "Best score: %d", bscore);
	outtextxy(20, 50, buf1);

	//暂停
	if (isPause && running)
	{
		settextstyle(64, 0, "Consolas");
		char p[50]="Paused";
		outtextxy(570, 500 , p);
	}

	//游戏结束
	if (!running)
	{
		setfillcolor(RGB(90, 20, 20));
		solidrectangle(0, 0, WIDTH, HEIGHT);

		settextcolor(RED);
		settextstyle(64, 0, "Consolas");
		char p[50] = "You Died";
		outtextxy(550 + offsetX, 450 + offsetY, p);

		settextcolor(WHITE);
		settextstyle(36, 0, "Consolas");
		char p1[50] = "Press R to restart the game";
		outtextxy(450 + offsetX, 520 + offsetY, p1);
	}
}

//重置游戏
void resetGame(Snake *snake,int *running,int *isPause,int *food_count,int *current_count,Food *food,int *speed,Food *food1)
{
	snake->length = 1;
	snake->body[0].x = 640;
	snake->body[0].y = 480;
	snake->body[0].diretion = RIGHT;
	snake->score = 0;

	addBody(snake);

	*running = 1;
	*isPause = 0;

	food->active = 0;
	*food_count = 0;
	*current_count = 0;

	*speed = 18;
	
	*food1 = createFood(640, 480, food_count);

	//背景音乐
	mciSendString("play eat from 0", NULL, 0, NULL);
}


void main()
{
	initgraph(WIDTH,HEIGHT,EX_DBLCLKS);
	setbkcolor(RGB(20, 20, 30));
	cleardevice();
	setlinestyle(PS_SOLID, 2);

	

	//创建蛇
	Snake snake;

	snake.length = 1;
	snake.body[0].x = 640;
	snake.body[0].y = 480;
	snake.body[0].diretion = RIGHT;
	snake.score = 0;

	//初始化
	addBody(&snake);

	int isPause=0;
	int running = 1;
	int bscore = 0;

	//抖动
	int shakeTime = 0;
	int shakeStrength = 50;
	int maxShakeTime = 20;


	Particle particles[MAX_PARTICLES];

	//读取历史最高分
	FILE* fp = fopen("Bscore.txt", "r");
	if (fp == NULL)
	{
		fp = fopen("Bscore.txt", "w");
		if (fp == NULL)
		{
			printf("txt Error");
			return;
		}
		int bscore = 0;
		fprintf(fp, "%d", bscore);
		fclose(fp);
	}
	else
	{

		fclose(fp);

		fp = fopen("Bscore.txt", "r");
		
		fscanf(fp, "%d", &bscore);
		fclose(fp);
	}
	

	//初始化随机数并创建食物
	srand(time(NULL));
	Food food[1000];
	int food_count = 0;
	int current_count = 0;

	//创建食物函数
	current_count = food_count;
	food[current_count] = createFood(snake.body[food_count].x, snake.body[food_count].y,&food_count);
	
	//速率
	int speed = 18;

	//背景音乐
	mciSendString("open bgm.wav alias bgm", NULL, 0, NULL);
	mciSendString("open eat.wav alias eat", NULL, 0, NULL);
	mciSendString("open died.wav alias die", NULL, 0, NULL);

	
	mciSendString("play eat from 0", NULL, 0, NULL);

	BeginBatchDraw();
	while (1)
	{
		// 检查按键输入
		if (GetAsyncKeyState('W') || GetAsyncKeyState(VK_UP))
		{
			if (snake.body[0].diretion != DOWN) snake.body[0].diretion = UP;
		}
		else if (GetAsyncKeyState('S') || GetAsyncKeyState(VK_DOWN))
		{
			if (snake.body[0].diretion != UP) snake.body[0].diretion = DOWN;
		}
		else if (GetAsyncKeyState('A') || GetAsyncKeyState(VK_LEFT))
		{
			if (snake.body[0].diretion != RIGHT) snake.body[0].diretion = LEFT;
		}
		else if (GetAsyncKeyState('D') || GetAsyncKeyState(VK_RIGHT))
		{
			if (snake.body[0].diretion != LEFT) snake.body[0].diretion = RIGHT;
		}

		if (GetAsyncKeyState(VK_SPACE) & 0x0001 && running)
		{
			if (isPause)isPause = 0;else isPause =1;
		}
		if (GetAsyncKeyState('R') & 0x0001 && !running)
		{
			resetGame(&snake, &running, &isPause, &food_count, &current_count, &food[food_count-1], &speed,&food[0]);
		}

		//检查音频
		char bgmStatus[64];
		mciSendString("status bgm mode", bgmStatus, 64, NULL);

		if (strcmp(bgmStatus, "stopped") == 0 && running && !isPause)
		{
			mciSendString("play bgm from 0", NULL, 0, NULL);
		}

		//移动
		if(!isPause && running)
		{
			moveSnake(&snake);


			//检测食物
			for (int k = 0; k < food_count; k++)
			{
				int dx = snake.body[0].x - food[k].x;
				int dy = snake.body[0].y - food[k].y;

				if (dx * dx + dy * dy <= 1300 && food[k].active != 0)
				{
					spawnParticles(particles, MAX_PARTICLES, food[k].x, food[k].y);

					food[k].active = 0;
					snake.score++;

					mciSendString("play eat from 0", NULL, 0, NULL);

					current_count = food_count;
					food[current_count] = createFood(snake.body[food_count].x, snake.body[food_count].y, &food_count);
					addBody(&snake);
					if (snake.score % 5 == 0 && speed>5)
					{
						speed--;
					}
				}
			}

			//检测边缘
			if (snake.body[0].x < 10 || snake.body[0].x >1270 || snake.body[0].y < 10 || snake.body[0].y>950 && running ==1)
			{
				shakeTime = maxShakeTime;

				running = 0;
				bscore = updateScore(snake.score);

				mciSendString("play die from 0", NULL, 0, NULL);
				mciSendString("stop bgm", NULL, 0, NULL);

			}
			//检测身体碰撞
			for (int k = 28; k < snake.length; k++)
			{
				int dx = snake.body[0].x - snake.body[k].x;
				int dy = snake.body[0].y - snake.body[k].y;
				if (dx * dx + dy * dy <= 1550)
				{
					shakeTime = maxShakeTime;

					running = 0;
					bscore = updateScore(snake.score);

					mciSendString("play die from 0", NULL, 0, NULL);
					mciSendString("stop bgm", NULL, 0, NULL);
				}
			}
		}

		

		//绘制


		cleardevice();

		printfFood(food, food_count);
		printSnake(snake);
		printScore(snake.score,bscore,isPause,running,&shakeTime,maxShakeTime,shakeStrength);
		updateParticles(particles, MAX_PARTICLES);

		FlushBatchDraw();


		//帧率
		Sleep(speed);

	}
	EndBatchDraw();
	mciSendString("close bgm", NULL, 0, NULL);
	mciSendString("close eat", NULL, 0, NULL);
	mciSendString("close die", NULL, 0, NULL);
	
	
}

