module Obiekt_graficzny;


bool Obiekt_graficzny::can_drop_bomb()
{
	return false;
}

bool Obiekt_graficzny::can_drop_life()
{
	return false;
}

bool Obiekt_graficzny::can_kill()
{
	return true;
}

int Obiekt_graficzny::get_floor()
{
	return 0;
}

const sf::FloatRect Obiekt_graficzny::Bounds() const
{
	return this->sprite.getGlobalBounds();
}

const sf::Vector2f Obiekt_graficzny::getPos() const
{
	return this->sprite.getPosition();
}
