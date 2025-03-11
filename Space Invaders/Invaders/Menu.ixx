export module Menu;

import <SFML/Graphics/Text.hpp>;
import <SFML/Graphics/Font.hpp>;
import <SFML/Graphics.hpp>;
import <SFML/Window.hpp>;
import <SFML/System.hpp>;
import <SFML/Audio.hpp>;
import <iostream>;
import <chrono>;
import <time.h>;
import <regex>;
import <filesystem>;
import <string>;
import <algorithm>;
import <concepts>;
import Gra;
import Result;


export class Menu
{
    sf::Vector2f window_size;       //rozmiar naszego okna
    sf::RenderWindow* window;       //okno gry
    sf::Font font;                  //czcionka
    std::vector<sf::Text> texts;    //wektor na teksty w sfml
    std::vector<Result*> results;   //wektor na wskazniki wyników
public:
    void showResults();         //pokazuje nasz¹ table wyników wynikow
    void startMenu();           //pokazuje menu startowe 
    void iniWindow();           //inicjalizuje nasze oknio
    void iniFont_and_file();    //inicjalizuje nasz¹ czcionke oraz pobiera dane z pliku wyniki.txt

    void addText(const std::string& str, int size, sf::Color color, int x, int y); //dodawanie tekstu do wektora texts
    std::string nameWriting();                                                     //wpisywanie nazwy uzytkownika z klawiatury
    bool newResult(const std::string& name, const int p);                          //tworzenie nowego wyniku, dodawanie go do wektora i zapis do pliku

    Menu();  //konstruktor klasy menu, laduje czcionke tekstu, oraz wczytuje wyniki z pliku i wrzuca do wektora 
    ~Menu(); //destruktor klasy menu niszczy wszystkie wskazniki w wektorze z wynikami

    template<typename T> requires std::integral<T>
    void endGameScreen(T p) //ekran koncowy po przejsciu gry
    {
        std::string points = std::to_string(p);
        addText("Gratulacje", 60, sf::Color::Yellow, 500, 100);
        addText("Nacisnij S aby przejsc dalej", 40, sf::Color::White, 500, 600);
        addText("Twoje punkty: " + points, 45, sf::Color::Green, 500, 350);
        window->clear(sf::Color::Black);
        for (const auto& text : texts)
            window->draw(text);
        window->display();
        texts.clear();
        sf::Event event{};
        while (true)
        {
            while (window->pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    window->close();
                }
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::S)
                {
                    return;
                }
            }
        }
    }
};