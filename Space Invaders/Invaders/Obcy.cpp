module Obcy;

Obcy::Obcy()
{
}

Obcy::Obcy(sf::Texture& t, float X, float Y, float s, int p)
{
	this->which_floor = p;
	if (p % 2)
	{
		this->right_down = true;
		this->which_side = true;
		this->left_down = false;
	}
	else
	{
		this->right_down = false;
		this->which_side = false;
		this->left_down = true;
	}
	this->texture = &t;
	this->d.x = X;
	this->d.y = Y;
	this->speed = s;
	this->iniSprite();
}

Obcy::~Obcy()
{
}

int Obcy::get_floor()
{
	return this->which_floor;
}

void Obcy::render(sf::RenderTarget& t)
{
	t.draw(this->sprite);
}

void Obcy::update(int w)
{
	if ((this->getPos().x + this->Bounds().width <= w) && (right_down))
	{

		this->sprite.move(this->speed * 1.f, this->speed * 0.f);
		if (this->getPos().x + this->Bounds().width == w)
		{
			right_down = false;
		}
	}
	else if ((this->getPos().x >= 0) && (left_down))
	{
		this->sprite.move(this->speed * -1.f, this->speed * 0.f);
		if (this->getPos().x == 0)
		{
			left_down = false;
		}
	}
	else
	{
		this->sprite.move(this->speed * 0.f, this->speed * 1.f);
		if ((this->getPos().y / this->which_floor >= this->Bounds().height)&&(which_side))
		{
			which_floor++;
			left_down = true;
			right_down = false;
			which_side = false;
		}
		else if ((this->getPos().y / this->which_floor >= this->Bounds().height) && (!which_side))
		{
			which_floor++;
			right_down = true;
			left_down = false;
			which_side = true;
		}
	}
}

bool Obcy::can_drop_life()
{
	int random_number = std::rand() % 30;
	if (random_number == 0)
		return true;

	return false;
}

void Obcy::iniSprite()
{
	this->sprite.setTexture(*texture);
	this->sprite.setPosition(this->d.x, this->d.y);
	this->sprite.scale(0.18f, 0.18f);
}