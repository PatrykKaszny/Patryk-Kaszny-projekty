export module Obcy;

import Obiekt_graficzny;
import <SFML/Graphics.hpp>;
import <SFML/System.hpp>;
import <iostream>;

export class Obcy
	:public Obiekt_graficzny 
{
protected:
	void iniSprite() override;				//inicjalizuje naszego obcego 
	int which_floor;						//zmienna która pokazuje na jakim poziomie jest obcy
	bool right_down, left_down, which_side;	//zmienne potrzebne nam do ruchu obcego, jest nam potrzebne ¿eby wiedzieæ w któr¹ strone ma poruszaæ siê kosmita
public:
	Obcy();
	Obcy(sf::Texture& t, float X, float Y, float s,int p);
	virtual ~Obcy();

	void render(sf::RenderTarget& t) override;	//rysuje naszego obcego na mapie
	void update(int w);							//uaktualnia naszego obecgo
	void update()override {}					//przys³oniêta metoda
	bool can_drop_life();						//sprawdza czy przy trafieniu przez rakiete mo¿e wyrzuciæ ¿ycie które przy z³apaniu przez gracza powiêksza life o 1
	int get_floor();							//zwraca na którym piêtrze jest kosmita
};