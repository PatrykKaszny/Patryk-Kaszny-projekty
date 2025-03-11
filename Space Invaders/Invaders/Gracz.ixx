export module Gracz;

import Obiekt_graficzny;
import <SFML/Graphics.hpp>;
import <SFML/System.hpp>;
import <iostream>;

export class Gracz
	:public Obiekt_graficzny
{
private:
	sf::Clock clock;				//zlicza czas i sluzy nam do obliczania cooldownu strzelania rakietami
	void iniSprite() override;		//inicjalizuje nasze dzialo
public:
	Gracz();
	Gracz(sf::Texture& t, float X,float Y,float s);
	virtual ~Gracz();

	void move(const float X, const float Y);	//obsluguje ruch naszego dziala
	void render(sf::RenderTarget& t) override;	//rysuje nasze dzia³o na ekranie
	bool can_use();								// sprawdza czy min¹³ cooldown na strzelanie

	void update() override {};					//przys³oniête dwie metody
	void update(int w)override {}
};