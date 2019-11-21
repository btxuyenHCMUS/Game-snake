#include "Util.h"
#include <time.h>
#include "SnakeLib.h"

Food::Food() {
	bool res;
	do {
		srand(time(NULL));
		_food.x = rand() % GWIDTH;
		_food.y = rand() % GHEIGHT;
		res = ((_food.x >= 10 && _food.x < GWIDTH - 10) && (_food.y == 5 || _food.y == 15)) || (_food.x < GWIDTH - 15 && _food.x >= 15 && _food.y == 15);
	} while (res == true);
}

void Food::randFood(Barrier bar) {
	do {
		srand(time(NULL));
		_food.x = rand() % GWIDTH;
		_food.y = rand() % GHEIGHT;
	} while (bar.isBarrier(_food));
}

void Food::drawFood() {
	SetBGColor(8);
	SetColor(12);
	gotoxy(_food.x, _food.y);
	printf("%c", 2);
}

void Barrier::drawBarrier() {
	for (int i = 10; i <= GWIDTH - 10; i++) {
		gotoxy(i, 5);
		SetColor(10);
		printf("%c", 5);
	}
	for (int i = 15; i <= GWIDTH - 15; i++) {
		gotoxy(i, 10);
		SetColor(10);
		printf("%c", 5);
	}
	for (int i = 10; i <= GWIDTH - 10; i++) {
		gotoxy(i, 15);
		SetColor(10);
		printf("%c", 5);
	}
}

bool Barrier::isBarrier(Point2D _p) {
	if ((_p.y == 5 || _p.y == 15) && (_p.x <= GWIDTH - 10 && _p.x >= 10)) return true;
	if (_p.y == 10 && _p.x >= 15 && _p.x <= GWIDTH - 15) return true;

	return false;
}

Snake::Snake() {
	_Snake[0].x = 5; _Snake[0].y = 6;
	_Snake[1].x = 4; _Snake[1].y = 6;
	_Snake[2].x = 3; _Snake[2].y = 6;
	_Snake[3].x = 2; _Snake[3].y = 6;
	_Snake[4].x = 1; _Snake[4].y = 6;
	this->length = 5;
}

void Snake::moveSnake(Point2D dir, bool &endGame, Food &_food, int &score, Barrier bar) {
	//kiem tra con ran co an thuc an chua
	if (_Snake[0].x == _food.getx() && _Snake[0].y == _food.gety()) {
		_Snake[length].x = _Snake[length - 1].ox; _Snake[length].y = _Snake[length - 1].oy;
		length++;
		_food.randFood(bar);
		_food.drawFood();
		score++;
	}

	//kiem tra co dung trung vat can hay khong
	if (bar.isBarrier(_Snake[0])) endGame = true;

	for (int i = 0; i < length; i++) {
		if (_Snake[i].x == _food.getx() && _Snake[i].y == _food.gety()) {
			_food.randFood(bar);
			_food.drawFood();
		}
		if (i == 0) {
			//di chuyen dau ran
			_Snake[0].ox = _Snake[0].x; _Snake[0].oy = _Snake[0].y;
			_Snake[0].x += dir.x; _Snake[0].y += dir.y;
		}
		else {
			// di chuyen than ran
			_Snake[i].ox = _Snake[i].x; _Snake[i].oy = _Snake[i].y;
			_Snake[i].x = _Snake[i - 1].ox; _Snake[i].y = _Snake[i - 1].oy;
		}

		//khi ran vuot ra khoi man hinh
		if (_Snake[i].x >= GWIDTH) _Snake[i].x = 0;
		if (_Snake[i].x < 0) _Snake[i].x = GWIDTH - 1;
		if (_Snake[i].y >= GHEIGHT) _Snake[i].y = 0;
		if (_Snake[i].y < 0) _Snake[i].y = GHEIGHT - 1;

		//kiem tra co can trung than hay khong
		if (i != 0 && (_Snake[0].x == _Snake[i].x && _Snake[0].y == _Snake[i].y)) endGame = true;
	}
}

void Snake::drawSnake(int x) {
	SetBGColor(8);
	SetColor(x);
	gotoxy(_Snake[0].x, _Snake[0].y);
	printf("%c", 4);

	gotoxy(_Snake[length - 1].ox, _Snake[length - 1].oy);
	printf(" ");
}

void Snake::drawinit(int x) {
	SetBGColor(8);
	SetColor(14);

	for (int i = 0; i < length; i++) {
		gotoxy(_Snake[i].x, _Snake[i].y);
		printf("%c", 4);
	}
}

Game::Game() {
	_tickCount = 0;
	maxTick = 60;

	endGame = false;
	score = 0;

	direction.x = 0; direction.y = 1;//huong di chuyen xuong duoi
}

void Game::init() {
	SetBGColor(8);//dat mau nen cho game
	for (int i = 0; i < GWIDTH; i++) {
		for (int j = 0; j < GHEIGHT; j++) {
			gotoxy(i, j);
			printf(" ");
		}
	}
	_food.drawFood();
	Oject_Snake.drawinit(14);

	bar.drawBarrier();

	gotoxy(52, 5);
	SetBGColor(0);
	SetColor(10);
	printf("Score: %d", score);

	_help.drawHelp();
	_help.draw();
}

void Game::setmaxTick(double db) {
	this->maxTick = db;
}

void Game::resetTick() {
	_tickCount = 0;
}

void Game::tickCount() {
	_tickCount += 0.07;
}

double Game::getTick() {
	return _tickCount;
}

void Game::Tick() {
	tickCount();
	if (_tickCount > maxTick) {
		resetTick();
		mainloop();
	}
	drawGame();
}

void Game::drawGame() {
	Oject_Snake.drawSnake(14);
	gotoxy(52, 5);
	SetBGColor(0);
	SetColor(10);
	printf("Score: %d", score);
}

void Game::mainloop() {
	Oject_Snake.moveSnake(direction, endGame, _food, score, bar);
	if (checkKey(KEY_LEFT)) {
		if (direction.x != 1) {
			direction.x = -1; direction.y = 0;
		}
	}
	else if (checkKey(KEY_RIGHT)) {
		if (direction.x != -1) {
			direction.x = 1; direction.y = 0;
		}
	}
	else if (checkKey(KEY_UP)) {
		if (direction.y != 1) {
			direction.y = -1; direction.x = 0;
		}
	}
	else if (checkKey(KEY_DOWN)) {
		if (direction.y != -1) {
			direction.y = 1; direction.x = 0;
		}
	}

	if (checkKey(KEY_ESC)) {
		endGame = true;
	}
	if (checkKey(KEY_ENTER)) {
		Pause();
	}
}

void Game::Pause() {
	//clrscr();
	deleteBackgroud();
	gotoxy(15, 9);
	SetColor(17);
	printf("Enter: Contine game.");
	gotoxy(18, 11);
	SetColor(71);
	printf("ESC: Exit.");
	while (true) {
		Sleep(100);
		if (checkKey(KEY_ENTER)) break;
		if (checkKey(KEY_ESC)) {
			endGame = true;
			break;
		}
	}
	deleteBackgroud();
	bar.drawBarrier();
	_food.drawFood();
}

void Game::deleteBackgroud() {
	for (int i=0;i<GWIDTH;i++)
		for (int j = 0; j < GHEIGHT; j++) {
			SetBGColor(8);
			gotoxy(i, j);
			printf(" ");
		}
}

void Game::mainGame() {
	init();
	ShowCur(false);//an con tro

	while (!endGame) {
		Tick();
	}
	clrscr();
	gotoxy(20, 10);
	printf("GAME OVER.....");
	Sleep(1000);
}

Game2::Game2() {
	_tickCount = 0;
	maxTick = 60;

	endGame = false;
	score1 = score2 = 0;

	direction1.x = 0; direction1.y = 1;//huong di chuyen 1 xuong duoi
	direction2.x = 1; direction2.y = 0;//huong di chuyen 2 sang ngang
}

void Game2::init() {
	SetBGColor(8);//dat mau nen cho game
	for (int i = 0; i < GWIDTH; i++) {
		for (int j = 0; j < GHEIGHT; j++) {
			gotoxy(i, j);
			printf(" ");
		}
	}

	bar.drawBarrier();
	_food.drawFood();

	Oject_Snake1.drawinit(14);
	Oject_Snake2.drawinit(16);

	gotoxy(52, 5);
	SetColor(10);

	printf("Score1: %d", score1);
	gotoxy(62, 5);
	SetColor(10);
	printf("Score2: %d", score2);

	_help.drawHelp();
	_help.draw2();
}

void Game2::setmaxTick(double db) {
	this->maxTick = db;
}

void Game2::resetTick() {
	_tickCount = 0;
}

void Game2::tickCount() {
	_tickCount += 0.1;
}

double Game2::getTick() {
	return _tickCount;
}

void Game2::drawGame() {
	Oject_Snake1.drawSnake(14);
	Oject_Snake2.drawSnake(16);

	SetBGColor(0);
	gotoxy(52, 5);
	SetColor(10);
	printf("Score1: %d", score1);
	gotoxy(62, 5);
	SetColor(10);
	printf("Score2: %d", score2);
}

void Game2::Pause() {
	deleteBackgroud();
	gotoxy(15, 9);
	SetColor(17);
	printf("Enter: Contine game.");
	gotoxy(18, 11);
	SetColor(71);
	printf("ESC: Exit.");
	while (true) {
		Sleep(100);
		if (checkKey(KEY_ENTER)) break;
		if (checkKey(KEY_ESC)) {
			endGame = true;
			break;
		}
	}
	deleteBackgroud();
	bar.drawBarrier();
	_food.drawFood();
	}

void Game2::deleteBackgroud() {
	for (int i = 0; i<GWIDTH; i++)
		for (int j = 0; j < GHEIGHT; j++) {
			SetBGColor(8);
			gotoxy(i, j);
			printf(" ");
		}
}

void Game2::mainloop() {
	Oject_Snake1.moveSnake(direction1, endGame, _food, score1, bar);
	Oject_Snake2.moveSnake(direction2, endGame, _food, score2, bar);

	//xu ly ket thuc game
	if (checkKey(KEY_ESC)) {
		endGame = true;
	}
	if (checkKey(KEY_ENTER)) {
		Pause();
	}
	//xu ly voi con ran 1
	if (checkKey(KEY_LEFT)) {
		if (direction1.x != 1) {
			direction1.x = -1; direction1.y = 0;
		}
	}
	else if (checkKey(KEY_RIGHT)) {
		if (direction1.x != -1) {
			direction1.x = 1; direction1.y = 0;
		}
	}
	else if (checkKey(KEY_UP)) {
		if (direction1.y != 1) {
			direction1.y = -1; direction1.x = 0;
		}
	}
	else if (checkKey(KEY_DOWN)) {
		if (direction1.y != -1) {
			direction1.y = 1; direction1.x = 0;
		}
	}
	//xu ly voi con ran 2
	if (checkKey(KEY_A)) {
		if (direction2.x != 1) {
			direction2.x = -1; direction2.y = 0;
		}
	}
	else if (checkKey(KEY_D)) {
		if (direction2.x != -1) {
			direction2.x = 1; direction2.y = 0;
		}
	}
	else if (checkKey(KEY_W)) {
		if (direction2.y != 1) {
			direction2.y = -1; direction2.x = 0;
		}
	}
	else if (checkKey(KEY_S)) {
		if (direction2.y != -1) {
			direction2.y = 1; direction2.x = 0;
		}
	}
}

void Game2::Tick() {
	tickCount();
	if (_tickCount > maxTick) {
		resetTick();
		mainloop();
	}
	drawGame();
}

void Game2::mainGame() {
	init();
	ShowCur(false);//an con tro
	while (!endGame) {
		Tick();
	}
	clrscr();
	gotoxy(20, 10);
	printf("GAME OVER.....");
	Sleep(1000);
}

void help::drawHelp() {
	SetBGColor(9);
	for (int i = GWIDTH + 1; i <= GWIDTH + 20; i++)
		for (int j = 10; j < 20; j++) {
			gotoxy(i, j);
			printf(" ");
		}
	SetBGColor(8);
}

void help::draw() {
	SetBGColor(9);
	SetColor(14);
	gotoxy(GWIDTH + 2, 11); printf("ESC: exit");
	gotoxy(GWIDTH + 2, 13); printf("Up: Len");
	gotoxy(GWIDTH + 2, 15); printf("Down: Xuong");
	gotoxy(GWIDTH + 2, 17); printf("Left: Trai");
	gotoxy(GWIDTH + 2, 19); printf("Right: Phai");
	SetBGColor(8);
}

void help::draw2() {
	SetBGColor(9);
	SetColor(14);
	gotoxy(GWIDTH + 2, 11); printf("ESC: exit");
	gotoxy(GWIDTH + 2, 13); printf("Up, W: Len");
	gotoxy(GWIDTH + 2, 15); printf("Down, S: Xuong");
	gotoxy(GWIDTH + 2, 17); printf("Left, A: Trai");
	gotoxy(GWIDTH + 2, 19); printf("Right, D: Phai");
	SetBGColor(8);
}

Menu::Menu() {
	this->dokho = 60;
	this->type = 0;
}

void Menu::printfBoder() {
	clrscr();
	SetColor(25);
	for (int i = 10; i <= 40; i++) {
		gotoxy(i, 5 - 1);
		printf("_");
		gotoxy(i, 15);
		printf("_");
	}
	for (int j = 5; j <= 15; j++) {
		gotoxy(10, j);
		printf("|");
		gotoxy(40, j);
		printf("|");
	}
}

void Menu::printfMenu() {
	gotoxy(21, 7);
	printf("1 Player");
	gotoxy(21, 9);
	printf("2 Player");
	gotoxy(21, 11);
	printf("Muc choi");
	gotoxy(21, 13);
	printf("Exit game");
}

int Menu::chonMenu() {
	while (1) {
		Sleep(100);
		if (this->type == 0) {
			gotoxy(21, 7);
			printf("          ");
			Sleep(200);
			gotoxy(21, 7);
			printf("1 Player");
		}
		if (this->type == 1) {
			gotoxy(21, 9);
			printf("         ");
			Sleep(200);
			gotoxy(21, 9);
			printf("2 Player");
		}
		if (this->type == 2) {
			gotoxy(21, 11);
			printf("         ");
			Sleep(200);
			gotoxy(21, 11);
			printf("Muc choi");
		}
		if (this->type == 3) {
			gotoxy(21, 13);
			printf("          ");
			Sleep(200);
			gotoxy(21, 13);
			printf("Exit game");
		}
		if (checkKey(KEY_DOWN)) type = (type + 1) % 4;
		if (checkKey(KEY_UP)) type = (type + 3) % 4;
		if (checkKey(KEY_ENTER)) break;
	}
	return this->type;
}

double Menu::chondokho()
{
	for (int i = 15; i < 40; i++)
		for (int j = 5; j < 15; j++) {
			gotoxy(i, j);
			printf(" ");
		}
	gotoxy(24, 8); printf("De");
	gotoxy(20, 11); printf("Trung binh");
	gotoxy(24, 14); printf("Kho");
	while (1) {
		Sleep(100);
		if (this->dokho == 60) {
			gotoxy(24, 8);
			printf("        ");
			Sleep(200);
			gotoxy(24, 8);
			printf("De");
		}
		if (this->dokho == 40) {
			gotoxy(20, 11);
			printf("           ");
			Sleep(200);
			gotoxy(20, 11);
			printf("Trung Binh");
		}
		if (this->dokho == 20) {
			gotoxy(24, 14);
			printf("        ");
			Sleep(200);
			gotoxy(24, 14);
			printf("Kho");
		}
		if (checkKey(KEY_UP) && this->dokho < 60) this->dokho += 20;
		if (checkKey(KEY_DOWN) && this->dokho > 20) this->dokho -= 20;
		if (checkKey(KEY_ENTER)) break;
	}

	return this->dokho;
}
