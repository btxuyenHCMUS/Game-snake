#include <stdio.h>
#include <conio.h>

#define GWIDTH 50
#define GHEIGHT 20

struct Point2D {
	int x, y;
	int ox, oy;
};

class Barrier {
public:
	void drawBarrier();
	bool isBarrier(Point2D _p);
};

class Food {
private:
	Point2D _food;
public:
	Food();
	int getx() {
		return _food.x;
	}
	int gety() {
		return _food.y;
	}
	void randFood(Barrier bar);
	void drawFood();
};

class Snake {
private:
	Point2D _Snake[100];
	int length;
public:
	Snake();
	void moveSnake(Point2D dir, bool &endGame, Food &_food, int &score, Barrier bar);
	void drawSnake(int x);
	void drawinit(int x);
};

class help {
public:
	void drawHelp();
	void draw();
	void draw2();
};

class Game {
private:
	help _help;

	double _tickCount;
	double maxTick;
	Barrier bar;//vat can cho game
	Food _food;//thuc an cho con ran
	int score;//diem cho game;

	Snake Oject_Snake;
	Point2D direction;//huong di chuyen cua con ran
	bool endGame;//bien ket thuc game
public:
	Game();
	void init();

	//bo ham lien quan den thoi gian
	void setmaxTick(double);
	void resetTick();
	void tickCount();
	double getTick();
	void Tick();

	//bo ham cho con ran chay
	void drawGame();
	void mainloop();

	//ham pause
	void Pause();
	void deleteBackgroud();

	void mainGame();
};

class Game2 {
private:
	help _help;
	double _tickCount;
	double maxTick;

	Food _food;//bien thuc an
	int score1, score2; //bien diem cho 2 ran
	Barrier bar;

	Snake Oject_Snake1, Oject_Snake2;
	Point2D direction1, direction2;//huong di chuyen cua con ran
	bool endGame;//bien ket thuc game
public:
	Game2();
	void init();

	//bo ham lien quan den thoi gian
	void setmaxTick(double db);
	void resetTick();
	void tickCount();
	double getTick();
	void Tick();

	//bo ham cho con ran chay
	void drawGame();
	void mainloop();

	//ham pause
	void Pause();
	void deleteBackgroud();

	void mainGame();
};

class Menu {
	double dokho;
	int type;
public:
	Menu();
	void printfBoder();
	void printfMenu();
	int chonMenu();
	double chondokho();
};