module Rakieta;

Rakieta::Rakieta()
{

}

Rakieta::Rakieta(sf::Texture& t, float X, float Y, float s)
{
	this->texture = &t;
	this->d.x = X;
	this->d.y = Y;
	this->speed = s;
	this->iniSprite();
}

Rakieta::~Rakieta()
{
}

//funkcje publiczne
void Rakieta::render(sf::RenderTarget& t)
{
	t.draw(this->sprite);
}

void Rakieta::update()
{
	this->sprite.move(this->speed * 0.f, this->speed * -1.f);
}

//funkcje prywatne
void Rakieta::iniSprite()
{
	this->sprite.setTexture(*texture);
	this->sprite.setPosition(this->d.x, this->d.y);
	this->sprite.scale(0.2f, 0.2f);
}
