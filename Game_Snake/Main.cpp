#include "SnakeLib.h"
#include <iostream>
#include <Windows.h>
#include <mmsystem.h>

using namespace std;

int main() {
	//PlaySound(TEXT("1612835.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);

	Menu _menu;
	int method;
	double dokho = 60;

	_menu.printfBoder();
	_menu.printfMenu();
	method = _menu.chonMenu();
	while (1)
	{
		if (method == 0) {
			Game object1;
			object1.setmaxTick(dokho);
			object1.mainGame();
		}
		else if (method == 1) {
			Game2 object2;
			object2.setmaxTick(dokho);
			object2.mainGame();
		}
		else if (method == 2) {
			dokho = _menu.chondokho();
		}
		else if (method == 3) {
			return 0;
		}
		_menu.printfBoder();
		_menu.printfMenu();
		method = _menu.chonMenu();
	}

	return 0;
}