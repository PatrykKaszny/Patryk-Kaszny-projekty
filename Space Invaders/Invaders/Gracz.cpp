module Gracz;



Gracz::Gracz()
{
	
}

Gracz::Gracz(sf::Texture& t,float X, float Y,float s)
{
	this->texture = &t;
	this->speed = s;
	this->d.x = X;
	this->d.y = Y;
	this->iniSprite();
}

Gracz::~Gracz()
{

}

void Gracz::move(const float X, const float Y)
{
	this->sprite.move(this->speed*X,this->speed*Y);
}

void Gracz::render(sf::RenderTarget& t)
{
	t.draw(this->sprite);
}

bool Gracz::can_use()
{
	if (this->clock.getElapsedTime().asMilliseconds() > 700)
	{
		this->clock.restart();
		return true;
	}
	return false;
}

void Gracz::iniSprite()
{
	this->sprite.setTexture(*texture);
	this->sprite.scale(0.3f, 0.3f);
	this->sprite.setPosition(this->d.x, this->d.y);
}