module Bomba;


Bomba::Bomba()
{

}

Bomba::Bomba(sf::Texture& t, float X, float Y, float s)
	:Rakieta(t,X,Y,s)
{}

Bomba::~Bomba()
{

}

void Bomba::update()
{
	this->sprite.move(this->speed * 0.f, this->speed * 1.f);
}

void Bomba::iniSprite()
{
	this->sprite.setTexture(*texture);
	this->sprite.setPosition(this->d.x, this->d.y);
	this->sprite.scale(0.2f, 0.2f);
}
