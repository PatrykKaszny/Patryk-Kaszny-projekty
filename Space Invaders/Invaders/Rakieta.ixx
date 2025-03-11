export module Rakieta;

import Obiekt_graficzny;
import <SFML/Graphics.hpp>;
import <SFML/System.hpp>;
import <iostream>;

export class Rakieta
	:public Obiekt_graficzny
{
private:
	void iniSprite() override;		//inicjalizuje nasz� rakiete
public:
	Rakieta();
	Rakieta(sf::Texture& t, float X, float Y, float s);
	virtual ~Rakieta();

	void render(sf::RenderTarget& t) override;	//rysuje nasz� rakiete
	void update() override;						//uaktualnia nasz� rakiete
	void update(int w)override {}				//przys�oni�ta metoda
};