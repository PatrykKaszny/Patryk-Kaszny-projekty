export module Mega_obcy;


import Super_obcy;

export class Mega_obcy
	:public Super_obcy
{
	bool defend;					//zmienna kt�ra okre�la nam czy obcy zosta� ju� raz trafiony (mega_obcy ma dwa �ycia)
	sf::Texture texture_not_defend;	//dodatkowa tekstura obcego bez tarczy
public:
	Mega_obcy();
	Mega_obcy(sf::Texture& t1, sf::Texture& t2, float X, float Y, float s, int p);
	virtual ~Mega_obcy();
	bool can_kill();				//je�li bool defend to true to zmienia na false, i zwraca false, w przeciwnym razie zwraca true
};