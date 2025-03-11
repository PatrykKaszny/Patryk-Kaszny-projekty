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
	int which_floor;						//zmienna kt�ra pokazuje na jakim poziomie jest obcy
	bool right_down, left_down, which_side;	//zmienne potrzebne nam do ruchu obcego, jest nam potrzebne �eby wiedzie� w kt�r� strone ma porusza� si� kosmita
public:
	Obcy();
	Obcy(sf::Texture& t, float X, float Y, float s,int p);
	virtual ~Obcy();

	void render(sf::RenderTarget& t) override;	//rysuje naszego obcego na mapie
	void update(int w);							//uaktualnia naszego obecgo
	void update()override {}					//przys�oni�ta metoda
	bool can_drop_life();						//sprawdza czy przy trafieniu przez rakiete mo�e wyrzuci� �ycie kt�re przy z�apaniu przez gracza powi�ksza life o 1
	int get_floor();							//zwraca na kt�rym pi�trze jest kosmita
};