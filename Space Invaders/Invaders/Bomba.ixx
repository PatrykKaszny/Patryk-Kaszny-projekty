export module Bomba;

import Obiekt_graficzny;
import Rakieta;
import <SFML/Graphics.hpp>;
import <SFML/System.hpp>;
import <iostream>;

export class Bomba
	:public Rakieta	
{
private:
	void iniSprite() override;							//inicjalizacja naszej bomby tekstur¹ i wielkoœci¹
public:
	Bomba();
	Bomba(sf::Texture& t, float X, float Y, float s);	
	virtual ~Bomba();									
	void update() override;								// opdowiedzialna za ruch bomby
};