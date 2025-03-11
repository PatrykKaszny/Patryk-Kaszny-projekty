export module Zycie;

import Obiekt_graficzny;
import Bomba;
import <SFML/Graphics.hpp>;
import <SFML/System.hpp>;
import <iostream>;

export class Zycie
	:public Bomba
{
private:
	void iniSprite() override;		//inicjalizuje nasze ¿ycie
public:
	Zycie();
	Zycie(sf::Texture& t, float X, float Y, float s);
	virtual ~Zycie();

	void update() override;			//uaktualnia nasze ¿ycie
};