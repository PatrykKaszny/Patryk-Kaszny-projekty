#include <fstream>

module Menu;


void Menu::iniWindow()
{
    this->window = new sf::RenderWindow(sf::VideoMode(window_size.x, window_size.y), "Invaders", sf::Style::Close | sf::Style::Titlebar);
    this->window->setFramerateLimit(60);
    this->window->setVerticalSyncEnabled(false);
}

void Menu::iniFont_and_file()
{
    if (font.loadFromFile("Data/Czcionka.otf") == false)
    {
        std::cout << "BLAD::Menu::Font::czcionka ladowani tekstur nie powiodlo sie \n";
    }

    std::filesystem::path relative_path("Data/wyniki.txt");
    if (std::ifstream file{ relative_path })
    {
        std::string tmp{};
        while (std::getline(file, tmp))
        {
            std::string name, points;
            size_t div;
            div = tmp.find('*');
            name = tmp.substr(0, div);
            points = tmp.substr(div + 1, tmp.size()-2);
            results.push_back(new Result(name, stoi(points)));
        }
        file.close();
    }
    else
    {
        std::cout << "Blad otwarcia pliku" << std::endl;
    }
}

void Menu::startMenu()
{
    while (window->isOpen())
    {
        addText("Invaders", 100, sf::Color::Red, 500, 150);
        addText("Nacisnij S,", 40, sf::Color::White, 250, 375);
        addText("aby rozpoczac gre", 40, sf::Color::White, 250, 410);
        addText("Nacisnij T, aby zobaczyc", 40, sf::Color::White, 700, 375);
        addText("tablice wynikow", 40, sf::Color::White, 700, 410);
        window->clear(sf::Color::Black);
        for (const auto& text : texts)
            window->draw(text);
        window->display();
        texts.clear();
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::S)
            {
                Gra game(*window, window_size);
                int points = game.run();
                this->endGameScreen(points);
                std::string name;
                do
                {
                    window->clear(sf::Color::Black);
                    window->display();
                    name = this->nameWriting();
                } while (!(this->newResult(name, points)));
                std::cout << name << " " << points << " " << std::endl;
            }
            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::T)
            {
                this->showResults();
            }
            if (event.type == sf::Event::Closed)
            {
                window->close();
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
            {
                this->window->close();
            }
        }
    }
}

void Menu::addText(const std::string& str, int size, sf::Color color, int x, int y)
{
    sf::Text text;
    text.setFont(font);
    text.setString(str);
    text.setFillColor(color);
    text.setCharacterSize(size);
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    text.setPosition(x, y);
    texts.push_back(text);
}

Menu::Menu()
    :window_size(1000,800)
{
    this->iniWindow();
    this->iniFont_and_file();
}

Menu::~Menu()
{
    for (size_t i = 0; i < results.size(); i++)
        delete results[i];
    results.clear();
    delete this->window;
}

std::string Menu::nameWriting()
{
    std::regex pattern("^[a-zA-Z0-9]{1,10}$");
    std::string name;
    sf::Text inputText;
    inputText.setFont(font);
    inputText.setCharacterSize(40);
    inputText.setFillColor(sf::Color::White);
    inputText.setPosition(180, 300);
    bool validName = 0;
    while (!validName)
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window->close();
                return "";
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
            {
                this->window->close();
                return "";
            }
            if (event.type == sf::Event::TextEntered)
            {
                if (event.text.unicode < 128)
                {
                    char enteredChar = static_cast<char>(event.text.unicode);
                    if (enteredChar == '\b')
                    {
                        if (!name.empty())
                        {
                            name.pop_back();
                        }
                    }
                    else if (enteredChar == '\r')
                    {
                        if (std::regex_match(name, pattern))
                            validName = 1;
                        else
                        {
                            name = "";
                        }
                    }
                    else
                    {
                        name += enteredChar;
                    }
                }
                inputText.setString(name);
            }
        }
        window->clear(sf::Color::Black);
        addText("NAZWA MUSI MIEC DO 10 ZNAKOW BEZ SPECJALNYCH!!", 40, sf::Color::Red, 500, 200);
        addText("Jesli wpisanie nazwy sie nie powiedzie mozliwe ze juz istnieje", 40, sf::Color::White, 500, 550);
        addText("Wpisz swoje imie: ", 60, sf::Color::Yellow, 500, 100);
        addText("Tutaj: ", 45, sf::Color::Red, 100, 325);
        for (const auto& text : texts)
            window->draw(text);
        window->draw(inputText);
        window->display();
        texts.clear();
    }
    return name;
}

void Menu::showResults()
{
    texts.clear();
    sf::Text resultsText;
    resultsText.setFont(font);
    resultsText.setCharacterSize(35);
    resultsText.setFillColor(sf::Color::White);
    resultsText.setPosition(200, 150);
    std::string resultsStr;
    if (results.size() < 5)
    {
        for (size_t i = 0; i < results.size(); i++)
        {
            resultsStr += std::to_string(i + 1) + ". " + results[i]->getResult() + "\n";
        }
    }
    else
    {
        for (size_t i = 0; i < 5; i++)
        {
            resultsStr += std::to_string(i + 1) + ". " + results[i]->getResult() + "\n";
        }
    }
    while (1)
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window->close();
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::T)
            {
                texts.clear();
                return;
            }
            resultsText.setString(resultsStr);
        }
        addText("Nacisnij T aby wyjsc", 35, sf::Color::Red, 500, 50);
        addText("TOP 5 GRACZY", 40, sf::Color::Yellow, 500, 100);
        window->clear(sf::Color::Black);
        for (const auto& text : texts)
            window->draw(text);
        window->draw(resultsText);
        window->display();
    }
}

bool Menu::newResult(const std::string& name,  const int p)
{
    for (const auto& result : results)
    {
        if (result->name == name)
        {
            return false;
        }
    }
    std::filesystem::path path{ "Data/wyniki.txt" };
    if (results.size() == 0)
    {
        results.push_back(new Result(name, p));
    }
    else
    {
        int count = results.size();
        for (int i = 0; i < count; i++)
        {
            if (p > results[i]->points)
            {
                results.insert(results.begin() + i, new Result(name, p));
                break;
            }
            else if(count-1 == i)
                results.push_back(new Result(name, p));
        }
    }
    std::ofstream file(path);
    if (!file.is_open())
    {
        std::cout << "Blad otwarcia pliku" << std::endl;
        return false;
    }
    for (auto& result : results)
    {
        file << result->name << "*" << result->points << "\n";
    }
    file.close();
    return true;
}