#include <iostream>
#include <cstdlib>
#include <ctime>
module Super_obcy;

Super_obcy::Super_obcy()
{
}

Super_obcy::Super_obcy(sf::Texture& t, float X, float Y, float s,int p):Obcy(t,X,Y,s,p)
{
}

Super_obcy::~Super_obcy()
{

}

bool Super_obcy::can_drop_bomb()
{
	int random_number = std::rand() % 2000;
	if (random_number == 0)
		return true;

	return false;
}





