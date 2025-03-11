module Mega_obcy;

Mega_obcy::Mega_obcy()
{
}

Mega_obcy::Mega_obcy(sf::Texture& t1, sf::Texture& t2, float X, float Y, float s, int p):Super_obcy(t1,X,Y,s,p)
{
	this->defend = true;
	this->texture_not_defend = t2;
}

Mega_obcy::~Mega_obcy()
{
}

bool Mega_obcy::can_kill()
{
	if (this->defend)
	{
		this->defend = false;
		sprite.setTexture(texture_not_defend);
		return false;
	}
	return true;
}
