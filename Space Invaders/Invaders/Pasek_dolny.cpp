#include <string>
module Pasek_dolny;


Pasek_dolny::Pasek_dolny()
{
}

Pasek_dolny::Pasek_dolny(sf::Texture& t1, sf::Texture& t2, float X, float Y, float szerokosc, float wysokosc, sf::Font& f, int l, int p)
{
	font = f;
	this->life = l;
	this->points = p;
	this->size.x = szerokosc;
	this->size.y = wysokosc;
	this->d.x = X;
	this->d.y = Y;
	this->texture = &t1;
	this->texture_life = &t2;
	this->iniSprite();
	this->iniText();
}

Pasek_dolny::~Pasek_dolny()
{
}

void Pasek_dolny::render(sf::RenderTarget& t)
{
	t.draw(this->bar);
	t.draw(this->sprite);
	t.draw(this->sprite_points);
	t.draw(this->life_text);
	t.draw(this->points_text);
}

void Pasek_dolny::update(int l, int p)
{
	life = l;
	points = p;
	this->life_text.setString(std::to_string(life));
	this->points_text.setString(std::to_string(points));
}

void Pasek_dolny::iniSprite()
{
	this->bar.setFillColor(sf::Color(43,125,2,180));
	this->bar.setPosition(this->d.x, this->d.y);
	this->bar.setSize(size);

	this->sprite.setTexture(*texture_life);
	this->sprite.setPosition(bar.getPosition().x+15, bar.getPosition().y+(size.y-45)/2);
	this->sprite.scale(0.45f, 0.45f);

	this->sprite_points.setTexture(*texture);
	this->sprite_points.setPosition(bar.getPosition().x+200,bar.getPosition().y + (size.y - 45) / 2);
	this->sprite_points.scale(0.45f, 0.45f);
}

void Pasek_dolny::iniText()
{
	this->life_text.setFont(font);
	this->life_text.setString(std::to_string(life));
	this->life_text.setPosition(bar.getPosition().x + 70, bar.getPosition().y + (size.y - 65) / 2);
	this->life_text.setCharacterSize(50);

	this->points_text.setFont(font);
	this->points_text.setString(std::to_string(points));
	this->points_text.setPosition(bar.getPosition().x + 255, bar.getPosition().y + (size.y - 65) / 2);
	this->points_text.setCharacterSize(50);
}