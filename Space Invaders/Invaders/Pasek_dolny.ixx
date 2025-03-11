export module Pasek_dolny;

import Obiekt_graficzny;
import <SFML/Graphics.hpp>;
import <SFML/System.hpp>;
import <iostream>;

export class Pasek_dolny
	:public Obiekt_graficzny
{
private:
	sf::Font font;						//czcionka w naszym pasku
	sf::Text life_text, points_text;	//tekst przedstawiaj¹cy nasze punkty i ¿ycia
	sf::Vector2f size;					//rozmiar paska
	int points, life;					//nasze punkty i ¿ycia
	sf::Texture* texture_life;			//dodatkowa tekstura ¿ycia
	sf::RectangleShape bar;				//nasz pasek
	sf::Sprite sprite_points;

	void iniSprite() override;		//inicjalizuje nasze sprite
	void iniText();					//inicjalizuje teksty ¿ycia i punktów
public:
	Pasek_dolny();
	Pasek_dolny(sf::Texture& t1, sf::Texture& t2, float X, float Y, float szerokosc, float wysokosc, sf::Font& font, int l, int p);
	virtual ~Pasek_dolny();
	void render(sf::RenderTarget& t) override;	//rysuje nasz pasek oraz teksty
	void update(int l, int p);					//uaktualnia nasze teksty w pasku

	void update() override {};
	void update(int w)override {}
};