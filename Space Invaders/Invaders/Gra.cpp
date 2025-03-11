module Gra;


Gra::Gra()
{
}

Gra::~Gra()
{
	delete this->gamer;
	delete this->bar;
	for (auto* s : this->rockets)
	{
		delete s;
	}
	for (auto* s : this->bombs)
	{
		delete s;
	}
	for (auto* s : this->obcy)
	{
		delete s;
	}
}

int Gra::run()
{
	while (this->not_end)
	{
		this->update();
		this->render();
		next_map_or_end();
	}
	return this->points;
}

void Gra::next_map_or_end()
{
	if (life == 0)
	{
		this->update_Pasek();
		this->how_many_obcy = 0;
		this->window->display();

		sf::RectangleShape background;
		background.setFillColor(sf::Color(123, 0, 0, 100));
		background.setPosition(0, 0);
		background.setSize(this->window_size);
		window->draw(background);

		sf::Text end_map_text;
		end_map_text.setFont(font);
		end_map_text.setCharacterSize(50);
		end_map_text.setString("Przegrales!!!");
		end_map_text.setPosition(window_size.x / 2-(end_map_text.getLocalBounds().left+ end_map_text.getLocalBounds().width)/2, 
													window_size.y / 2 - (end_map_text.getLocalBounds().top+end_map_text.getLocalBounds().height)/2 - 50);
		window->draw(end_map_text);
		end_map_text.setString("Aby przejsc do menu nacisnij \"Enter\"");
		end_map_text.setPosition(window_size.x / 2 - (end_map_text.getLocalBounds().left + end_map_text.getLocalBounds().width) / 2,
			window_size.y / 2 - (end_map_text.getLocalBounds().top + end_map_text.getLocalBounds().height) / 2);
		window->draw(end_map_text);
		this->window->display();

		this->not_end = false;
		while (!(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)))
		{}
	}
	else if (how_many_obcy == 0)
	{
		erase_bombs_rockets_aliens();
		this->window->display();
		how_many_starting_lines = 3;
		if(speed_obcy < 4.f)
			speed_obcy += 0.5f;

		sf::RectangleShape background;
		background.setFillColor(sf::Color(0, 123, 0, 100));
		background.setPosition(0, 0);
		background.setSize(this->window_size);
		window->draw(background);


		sf::Text next_map_text;
		next_map_text.setFont(font);
		next_map_text.setCharacterSize(50);
		next_map_text.setString("Gratulacje!!!");
		next_map_text.setPosition(window_size.x / 2 - (next_map_text.getLocalBounds().left + next_map_text.getLocalBounds().width) / 2,
			window_size.y / 2 - (next_map_text.getLocalBounds().top + next_map_text.getLocalBounds().height) / 2 - 50);
		window->draw(next_map_text);
		next_map_text.setString("Aby przejsc do kolejnej mapy nacisnij \"Enter\"");
		next_map_text.setPosition(window_size.x / 2 - (next_map_text.getLocalBounds().left + next_map_text.getLocalBounds().width) / 2,
			window_size.y / 2 - (next_map_text.getLocalBounds().top + next_map_text.getLocalBounds().height) / 2);
		window->draw(next_map_text);
		this->window->display();

		while (!(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)))
		{}
	}
}

void Gra::update_Pasek()
{
	bar->update(life, points);
}

void Gra::update()
{
	this->update_Event();
	this->update_Obcy();
	this->update_Rakieta();
	this->update_Bombs();
	this->update_Key();
	this->update_Pasek();
}

void Gra::render()
{
	this->window->clear();

	//rysowanie obiektów
	this->gamer->render(*this->window);
	this->bar->render(*this->window);
	for (auto s : rockets)
	{
		s->render(*this->window);
	}
	for (auto s : bombs)
	{
		s->render(*this->window);
	}
	for (auto s : obcy)
	{
		s->render(*this->window);
	}

	this->window->display();
}

void Gra::erase_bombs_rockets_aliens()
{
	this->how_many_obcy = 0;
	for (auto* s : this->obcy)
	{
		delete s;
	}
	obcy.erase(obcy.begin(), obcy.begin() + obcy.size());
	for (auto* s : this->rockets)
	{
		delete s;
	}
	rockets.erase(rockets.begin(), rockets.begin() + rockets.size());
	for (auto* s : this->bombs)
	{
		delete s;
	}
	bombs.erase(bombs.begin(), bombs.begin() + bombs.size());
}

Gra::Gra(sf::RenderWindow& w, sf::Vector2f r)
	:window_size{ r }, life{ 3 }, points{ 0 }
{
	window = &w;
	this->how_many_obcy = 0;
	this->not_end = true;
	this->speed_obcy = 2.f;
	this->how_many_starting_lines = 3;
	this->iniTekstury();
	this->iniGracz();
	this->iniPaska();
}

void Gra::iniTekstury()
{
	if (this->font.loadFromFile("Data/Czcionka.otf") == false)
	{
		std::cout << "BLAD::Gra::Font::czcionka ladowani tekstur nie powiodlo sie \n";
	}
	if (this->tekstury["Czolg"].loadFromFile("Data/Czo³g.png") == false)
	{
		std::cout << "BLAD::Gra::INITEXTURE::czolg ladowani tekstur nie powiodlo sie \n";
	}
	if (this->tekstury["Rakieta"].loadFromFile("Data/Rakieta.png") == false)
	{
		std::cout << "BLAD::GRA::INITEXTURE::rakieta ladowani tekstur nie powiodlo sie \n";
	}
	if (this->tekstury["Serce"].loadFromFile("Data/Serduszko.png") == false)
	{
		std::cout << "BLAD::Gra::INITEXTURE::serce ladowani tekstur nie powiodlo sie \n";
	}
	if (this->tekstury["Gwiazda"].loadFromFile("Data/Punkty.png") == false)
	{
		std::cout << "BLAD::GRA::INITEXTURE::gwiazda ladowani tekstur nie powiodlo sie \n";
	}
	if (this->tekstury["KosmitaV1"].loadFromFile("Data/KosmitaV1.png") == false)
	{
		std::cout << "BLAD::GRA::INITEXTURE::kosmitaV1 ladowani tekstur nie powiodlo sie \n";
	}
	if (this->tekstury["KosmitaV2"].loadFromFile("Data/KosmitaV2.png") == false)
	{
		std::cout << "BLAD::GRA::INITEXTURE::kosmitaV2 ladowani tekstur nie powiodlo sie \n";
	}
	if (this->tekstury["Bomba"].loadFromFile("Data/Bomba.png") == false)
	{
		std::cout << "BLAD::GRA::INITEXTURE::bomba ladowani tekstur nie powiodlo sie \n";
	}
	if (this->tekstury["KosmitaV3_1"].loadFromFile("Data/KosmitaV3_1.png") == false)
	{
		std::cout << "BLAD::GRA::INITEXTURE::bomba ladowani tekstur nie powiodlo sie \n";
	}
	if (this->tekstury["KosmitaV3_2"].loadFromFile("Data/KosmitaV3_2.png") == false)
	{
		std::cout << "BLAD::GRA::INITEXTURE::bomba ladowani tekstur nie powiodlo sie \n";
	}
}

void Gra::update_Event()
{
	sf::Event event;
	while (this->window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			this->window->close();
		}
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
		{
			this->window->close();
		}
	}
}

void Gra::create_lines_obcy()
{
	Obcy x(this->tekstury["KosmitaV1"], 0.f, 0.f, 0.5f, 0);
	Super_obcy y(this->tekstury["KosmitaV1"], 0.f, 0.f, 0.5f, 0);
	Mega_obcy z(this->tekstury["KosmitaV3_2"], this->tekstury["KosmitaV3_1"], 0.f, 0.f, 0.5f, 0);
	if (how_many_starting_lines == 3)
		new_line_Obcy(3, & x);
	if (how_many_starting_lines == 2)
		new_line_Obcy(2, &y);
	if (how_many_starting_lines == 1)
		new_line_Obcy(1, &z);
}

void Gra::update_Obcy()		
{
	create_lines_obcy();

	int count{ 0 };
	for (auto* s : this->obcy)
	{
			s->update(window_size.x);


		if (s->can_drop_bomb())
		{
			this->bombs.push_back(this->iniBomb(s));
		}


		if (s->getPos().y + s->Bounds().height > gamer->getPos().y)
		{
			delete this->obcy[count];
			this->obcy.erase(this->obcy.begin() + count);
			count--;

			this->how_many_obcy--;
			this->life--;											//odejmowanie life gdy kosmita znajdzie sie na wysokoœci naszego czo³gu
		}
		int count_1{ 0 };
		for (auto* t : this->rockets)
		{
			if ((s->getPos().y + s->Bounds().height >= t->getPos().y) && (s->getPos().y <= t->getPos().y))
			{
				if ((s->getPos().x + s->Bounds().width >= t->getPos().x) && (s->getPos().x <= t->getPos().x))
				{
					if (s->can_kill())
					{
						if (s->can_drop_life())
						{
							this->bombs.push_back(this->iniLife(s));
						}

						if (dynamic_cast<Mega_obcy*>(obcy[count]))				//  punktów za zabicie obcego za megaobcego 3 superobcego 2 za obcego 1
							this->points += 3;
						else if (dynamic_cast<Super_obcy*>(obcy[count]))
							this->points += 2;
						else if (dynamic_cast<Obcy*>(obcy[count]))
							this->points += 1;

						delete this->obcy[count];
						obcy[count] = new Obcy();
						how_many_obcy--;
					}
					delete this->rockets[count_1];
					this->rockets.erase(this->rockets.begin() + count_1);
					count_1--;
				}
			}
			++count_1;
		}
		++count;

	}
}

void Gra::new_line_Obcy(int floor,Obiekt_graficzny* x)
{
	if (floor % 2 != 0)
	{
		for (int i = 10; i >= 0; i--)
		{
			this->how_many_obcy++;
			this->obcy.push_back(this->iniObcy(i, floor, x));
		}
	}
	else
	{
		for (int i = 0; i < 11; i++)
		{
			this->how_many_obcy++;
			this->obcy.push_back(this->iniObcy(i, floor, x));
		}
	}
	how_many_starting_lines--;
}

void Gra::update_Rakieta()
{
	int count{0};
	for (auto* s : this->rockets)
	{
		s->update();

		if (s->Bounds().top + s->Bounds().height < 0.f)
		{
			delete this->rockets[count];
			this->rockets.erase(this->rockets.begin() + count);
			count--;
		}
		++count;
	}
}

void Gra::update_Bombs()
{
	int count{ 0 };
	for (auto* s : this->bombs)
	{
		s->update();

		if (s->getPos().y + s->Bounds().height >= this->window_size.y - this->bar->Bounds().height - 20)
		{
			delete this->bombs[count];
			this->bombs.erase(this->bombs.begin() + count);
			count--;
		}
		else if  (gamer->getPos().y <= s->getPos().y + s->Bounds().height)
		{
			if ((gamer->getPos().x + gamer->Bounds().width >= s->getPos().x + s->Bounds().width/2) &&(gamer->getPos().x <= s->getPos().x + s->Bounds().width/2))
			{
				if (dynamic_cast<Zycie*>(s))
					this->life++;
				else
					this->life--;

				delete this->bombs[count];
				this->bombs.erase(this->bombs.begin() + count);
				count--;
			}
		}
		++count;
	}
}

void Gra::update_Key()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && gamer->Bounds().left > 0) 
	{
		this->gamer->move(-1.f, 0.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && gamer->Bounds().left + gamer->Bounds().width <1000)
	{
		this->gamer->move(1.f, 0.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && this->gamer->can_use())
	{
		this->rockets.push_back(this->iniRakieta());
	}
}

void Gra::iniGracz()
{
	this->gamer = new Gracz(this->tekstury["Czolg"],450, 670, 5.f);
}

void Gra::iniPaska()
{
	this->bar = new Pasek_dolny(this->tekstury["Gwiazda"], this->tekstury["Serce"],0,window_size.y-65, window_size.x,65, font, life, points);
}

Rakieta* Gra::iniRakieta()
{
	Rakieta r(this->tekstury["Rakieta"],0.f,0.f,7.f);
	return new Rakieta(this->tekstury["Rakieta"], gamer->getPos().x + gamer->Bounds().width/2 - r.Bounds().width/2, gamer->getPos().y - gamer->Bounds().height / 2 - r.Bounds().height / 2,5.5f);
}

Bomba* Gra::iniBomb(Obiekt_graficzny* s)
{
	return new Bomba(this->tekstury["Bomba"], s->getPos().x + s->Bounds().width / 2, s->getPos().y + s->Bounds().height / 2, 3.f);
}

Bomba* Gra::iniLife(Obiekt_graficzny* s)
{
	return new Zycie(this->tekstury["Serce"], s->getPos().x + s->Bounds().width / 2, s->getPos().y + s->Bounds().height / 2, 3.f);
}

Obiekt_graficzny* Gra::iniObcy(float w, float h, Obiekt_graficzny* x)
{
	if (dynamic_cast<Mega_obcy*>(x))
		return new Mega_obcy(this->tekstury["KosmitaV3_2"], this->tekstury["KosmitaV3_1"], w * x->Bounds().width, (h - 1) * x->Bounds().height, speed_obcy, h);
	else if (dynamic_cast<Super_obcy*>(x))
		return new Super_obcy(this->tekstury["KosmitaV2"], w * x->Bounds().width, (h - 1) * x->Bounds().height, speed_obcy, h);
	else if (dynamic_cast<Obcy*>(x))
		return new Obcy(this->tekstury["KosmitaV1"], w * x->Bounds().width, (h - 1) * x->Bounds().height, speed_obcy, h);
}
