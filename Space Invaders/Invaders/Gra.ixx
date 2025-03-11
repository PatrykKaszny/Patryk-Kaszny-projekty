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
	sf::RenderWindow* window;		//okno w kt�rym b�dzie nasza gra
	sf::Vector2f window_size;		//zapisana wielko�� naszego okna

	std::map<std::string, sf::Texture> tekstury;	//wewktor do kt�rego wczytujemy wszystkie tekstury na pocz�tku �eby za ka�dym razem nie musie� ich zczytywa� z folderu
	sf::Font font;

	short how_many_starting_lines;			//ile tworzymy wierszy obcych na pocz�tku
	int how_many_obcy;						//ile obcych zosta�o jeszcze na planszy, potrzebne aby wiedzie� kiedy ma nast�pi� koniec gry
	float speed_obcy;						//pr�dko�� kosmit�w, z ka�d� map� staje si� troszke wi�ksza a� do 4.0f
	int life;								//nasze �ycia, je�li spadnie do zera gra zako�czy si� pora�k�
	int points;								//punkty kt�re zdobywamy za zniszenie kosmit�w
	bool not_end;							//ko�czy nasz� p�tle g��wn� gry je�li zmieni si� na false przy stracie wszystkich �y�

	Pasek_dolny* bar;						//pasek kt�ry wy�wietla nasze �ycia oraz punkty w trakcie rozgrywki		
	Gracz* gamer;							//czo�g kt�ry sterujemy w grze
	std::vector<Rakieta*> rockets;			//wektor z wszytkimi rakietami na planszy, je�li rakieta wyleci poza plansze albo uderzy w kosmite to jest usuwanana
	std::vector<Bomba*> bombs;				//wektor z wszytkimi bombami na planszy, je�li bomba wyleci poza plansze albo uderzy w gracza to jest usuwanana
	std::vector<Obiekt_graficzny*> obcy;	//wektor z wszytkimi obcymi na planszy, je�li obcy wyleci na czo�g albo uderzy w niego rakieta to jest usuwany

	void create_lines_obcy();							//uruchamia odpowiednio new_line_obcy
	void new_line_Obcy(int floor, Obiekt_graficzny* x); //tworzy ca�� lini� obcych w zale�no�ci jaka ma to by� ewolucja obcego
	void next_map_or_end();								//sprawdza czy s� jeszcze kosmici na mapie albo czy gracz ma �ycia i odpowiednio reaguje
	void erase_bombs_rockets_aliens();					//usuwa wszystkie dane z wektor�w obcy, rockets, bombs

	void update_Event();	//obs�uguje nasze eventy np. zamykanie okna
	void update_Obcy();		//s�u�y do uaktualniania wektora obcych
	void update_Rakieta();	//s�u�y do uaktualniania wektora rakiet
	void update_Bombs();	//s�u�y do uaktualniania wektora bomb
	void update_Pasek();	//s�u�y do uaktualniania paska czyli zmian �ycia i punkt�w
	void update_Key();		//obs�uguje nasze przyciski na klawiaturze np. strza�ki

	void iniGracz();														//inicjaliuzje gracza wartosciami
	void iniPaska();														//inicjaliuzje pasek dolny wartosciami
	void iniTekstury();														//inicjaliuzje tekstury wartosciami
	Rakieta* iniRakieta();													//inicjaliuzje rakiety wartosciami
	Bomba* iniBomb(Obiekt_graficzny* s);									//inicjaliuzje bomby wartosciami
	Bomba* iniLife(Obiekt_graficzny* s);									//dodaje do wektor bomb obiekt klasy Zycie dziedzicz�cy po Bombie
	Obiekt_graficzny* iniObcy(float w, float h, Obiekt_graficzny* x);		//inicjaliuzje obcego wartosciami

	void update();		//uaktualnia wszystkie nasze obiekty
	void render();		//rysuje wszystkie nasze obiekty
public:
	Gra();
	Gra(sf::RenderWindow& w, sf::Vector2f r);
	virtual ~Gra();

	int run();		//tutaj znajduje si� nasz g��wna p�tla gry kt�ra zwraca ilo�� zdobytych punkt�w, uruchamia metody, update() render() i next_map_or_end()		
};