#include "IndependentInclude.h"
#include "Game.h"
//#include "Graphics.h"
//#include "Image.h"
//#include "Input.h"
//#include "Screen.h"

int main(int argc, char *args[]){
	Game game;
	return game.Execute(new Screen,800,400,"Snake2");
}