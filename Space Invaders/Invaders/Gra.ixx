export module Gra;

import Gracz;
import Obiekt_graficzny;
import Rakieta;
import Bomba;
import Zycie;
import Pasek_dolny;
import Obcy;
import Super_obcy;
import Mega_obcy;
import <iostream>;
import <map>;
import <SFML/Graphics.hpp>;
import <SFML/System.hpp>;

export class Gra
{
private:
	sf::RenderWindow* window;		//okno w którym bêdzie nasza gra
	sf::Vector2f window_size;		//zapisana wielkoœæ naszego okna

	std::map<std::string, sf::Texture> tekstury;	//wewktor do którego wczytujemy wszystkie tekstury na pocz¹tku ¿eby za ka¿dym razem nie musieæ ich zczytywaæ z folderu
	sf::Font font;

	short how_many_starting_lines;			//ile tworzymy wierszy obcych na pocz¹tku
	int how_many_obcy;						//ile obcych zosta³o jeszcze na planszy, potrzebne aby wiedzieæ kiedy ma nast¹piæ koniec gry
	float speed_obcy;						//prêdkoœæ kosmitów, z ka¿d¹ map¹ staje siê troszke wiêksza a¿ do 4.0f
	int life;								//nasze ¿ycia, jeœli spadnie do zera gra zakoñczy siê pora¿k¹
	int points;								//punkty które zdobywamy za zniszenie kosmitów
	bool not_end;							//koñczy nasz¹ pêtle g³ówn¹ gry jeœli zmieni siê na false przy stracie wszystkich ¿yæ

	Pasek_dolny* bar;						//pasek który wyœwietla nasze ¿ycia oraz punkty w trakcie rozgrywki		
	Gracz* gamer;							//czo³g który sterujemy w grze
	std::vector<Rakieta*> rockets;			//wektor z wszytkimi rakietami na planszy, jeœli rakieta wyleci poza plansze albo uderzy w kosmite to jest usuwanana
	std::vector<Bomba*> bombs;				//wektor z wszytkimi bombami na planszy, jeœli bomba wyleci poza plansze albo uderzy w gracza to jest usuwanana
	std::vector<Obiekt_graficzny*> obcy;	//wektor z wszytkimi obcymi na planszy, jeœli obcy wyleci na czo³g albo uderzy w niego rakieta to jest usuwany

	void create_lines_obcy();							//uruchamia odpowiednio new_line_obcy
	void new_line_Obcy(int floor, Obiekt_graficzny* x); //tworzy ca³¹ liniê obcych w zale¿noœci jaka ma to byæ ewolucja obcego
	void next_map_or_end();								//sprawdza czy s¹ jeszcze kosmici na mapie albo czy gracz ma ¿ycia i odpowiednio reaguje
	void erase_bombs_rockets_aliens();					//usuwa wszystkie dane z wektorów obcy, rockets, bombs

	void update_Event();	//obs³uguje nasze eventy np. zamykanie okna
	void update_Obcy();		//s³u¿y do uaktualniania wektora obcych
	void update_Rakieta();	//s³u¿y do uaktualniania wektora rakiet
	void update_Bombs();	//s³u¿y do uaktualniania wektora bomb
	void update_Pasek();	//s³u¿y do uaktualniania paska czyli zmian ¿ycia i punktów
	void update_Key();		//obs³uguje nasze przyciski na klawiaturze np. strza³ki

	void iniGracz();														//inicjaliuzje gracza wartosciami
	void iniPaska();														//inicjaliuzje pasek dolny wartosciami
	void iniTekstury();														//inicjaliuzje tekstury wartosciami
	Rakieta* iniRakieta();													//inicjaliuzje rakiety wartosciami
	Bomba* iniBomb(Obiekt_graficzny* s);									//inicjaliuzje bomby wartosciami
	Bomba* iniLife(Obiekt_graficzny* s);									//dodaje do wektor bomb obiekt klasy Zycie dziedzicz¹cy po Bombie
	Obiekt_graficzny* iniObcy(float w, float h, Obiekt_graficzny* x);		//inicjaliuzje obcego wartosciami

	void update();		//uaktualnia wszystkie nasze obiekty
	void render();		//rysuje wszystkie nasze obiekty
public:
	Gra();
	Gra(sf::RenderWindow& w, sf::Vector2f r);
	virtual ~Gra();

	int run();		//tutaj znajduje siê nasz g³ówna pêtla gry która zwraca iloœæ zdobytych punktów, uruchamia metody, update() render() i next_map_or_end()		
};