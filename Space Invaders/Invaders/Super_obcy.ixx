export module Super_obcy;

import Obcy;

export class Super_obcy
	:public Obcy
{
public:
	Super_obcy();
	Super_obcy(sf::Texture& t, float X, float Y, float s, int p);
	virtual ~Super_obcy();

	bool can_drop_bomb();		//funkcja kt�ra sprawdza czy kosmita mo�e wyrzuci� bombe je�li tak zwraca true
};