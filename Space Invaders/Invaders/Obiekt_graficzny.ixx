export module Obiekt_graficzny;

import <SFML/Graphics.hpp>;
import <SFML/System.hpp>;
import <iostream>;

export class Obiekt_graficzny	//nasza klasa abstrakcyja po któej dziedzicz¹ wszystkie klasy które bêd¹ rysowane na ekranie
{
protected:
	sf::Sprite sprite;		//nasz obiekt do rysowania
	sf::Texture* texture;	//pobrana tekstura
	float speed;			//prêdkoœæ 
	sf::Vector2f d;			//punkt (X,Y) gdzie znajduje siê nasz obiekt
public:
	virtual void render(sf::RenderTarget& t) = 0;
	virtual void update() = 0;
	virtual void update(int w) = 0;
	virtual bool can_drop_bomb();
	virtual bool can_drop_life();
	virtual bool can_kill();
	virtual int get_floor();
	virtual ~Obiekt_graficzny() {};
	Obiekt_graficzny() {};
	Obiekt_graficzny(sf::Texture& t, float X, float Y, float s) {};
	virtual void iniSprite() = 0;
	const sf::FloatRect Bounds() const;
	const  sf::Vector2f getPos() const;
};