module Zycie;


Zycie::Zycie()
{

}

Zycie::Zycie(sf::Texture& t, float X, float Y, float s)
	:Bomba(t, X, Y, s)
{}

Zycie::~Zycie()
{

}

void Zycie::update()
{
	this->sprite.move(this->speed * 0.f, this->speed * 1.f);
}

void Zycie::iniSprite()
{
	this->sprite.setTexture(*texture);
	this->sprite.setPosition(this->d.x, this->d.y);
	this->sprite.scale(0.2f, 0.2f);
}
