#include <iostream>

template <typename T>
class tab_vec
{
private:
    T* tablica;     // nasz wskaźnik
    size_t rozmiar; // pojemność
    size_t obecny;  // który następny
public:
    tab_vec() : tablica{ new T[10] }, rozmiar{ 10 }, obecny{ 0 }    //konstruktor bezargumentowy
    {}

    tab_vec(size_t ile) :tablica{ new T[ile] }, rozmiar{ ile }, obecny{ 0 }  // zwykły konstruktor
    {}

    tab_vec(const tab_vec &kopiowany) : tablica{ new T[kopiowany.rozmiar] }, rozmiar{ kopiowany.rozmiar }, obecny{ kopiowany.obecny }    // kopiujący 
    {
        for (int i = 0; i < obecny; i++)
            tablica[i] = kopiowany.tablica[i];
    }

    tab_vec(tab_vec &&tymczasowy)   // przenoszący
    {
        tablica = tymczasowy.tablica;
        rozmiar = tymczasowy.rozmiar;
        obecny = tymczasowy.obecny;
        tymczasowy.tablica = nullptr;
        tymczasowy.rozmiar = 0;
        tymczasowy.obecny = 0;
    }

    ~tab_vec()
    {
        delete[] tablica;
    }

    size_t jaki_obecny()    //zwraca obecny
    {
        return obecny;
    }

    void dodaj_nowy(const T nowy)   // dodawanie nowego elementu na koniec
    {
        if (obecny == rozmiar)
        {
            rozmiar++;
            T* chwilowy = new T[rozmiar];
                for (int i = 0; i < rozmiar; i++)
                    chwilowy[i] = tablica[i];
            delete[]tablica;
            tablica = chwilowy;
        }
        tablica[obecny] = nowy;
        obecny++;
    }


    void dodaj_nowy(const T nowy, size_t x)   // dodawanie nowego elementu na indeks x przesuwajac inne elementy
    {
        if ((x < 0) || (x >= rozmiar))
            throw std::out_of_range("Index out of range");
        if (x <= obecny)
        {
            if (obecny == rozmiar)
                rozmiar++;
            T* chwilowy = new T[rozmiar];
            for (int i = 0, j = 0; j < rozmiar; i++,j++)
            {
                if (j != x)
                {
                    chwilowy[j] = tablica[i];
                }
                else
                {
                    chwilowy[j] = nowy;
                    i--;
                }
            }
            delete[]tablica;
            tablica = chwilowy;
            obecny++;
        }
        else
        {
            tablica[x] = nowy;
            obecny = x + 1;
        }
    }

    void usun_element(size_t x) //usuwanie elementu o indeksie x
    {
        if ((x < 0)||(x >= rozmiar))
            throw std::out_of_range("Index out of range");
        obecny--;
        T* chwilowy = new T[rozmiar];
        for (int i = 0, j = 0; i < rozmiar; i++, j++)
            if (i != x)
            {
                chwilowy[j] = tablica[i];
            }
            else
            {
                j--;
            }
        delete[]tablica;
        tablica = chwilowy;
    }

    void usun_element(size_t x, size_t y)   //usuwanie y elementów rozpoczęte od indeksu x
    {
        if ((x < 0) || (x+y-1 >= rozmiar))
            throw std::out_of_range("Index out of range");
        T* chwilowy = new T[rozmiar];
        for (int i = 0, j = 0; i < rozmiar; i++,j++)
            if ((i < x) || (i > x + y - 1))
            {
                chwilowy[j] = tablica[i];
            }
            else
            {
                j--;
            }
        obecny -= y;
        delete[]tablica;
        tablica = chwilowy;
    }

    T& operator[](size_t x) //operator []
    {
        if ((x<0)||(x >= rozmiar))
        {
            throw std::out_of_range("Index out of range");
        }
        return tablica[x];
    }

    tab_vec& operator =(const tab_vec& inny) //operator przypisania
    {
        if (&inny != this)
        {
            delete[] tablica;
            tablica = new T[inny.rozmiar];
            rozmiar = inny.rozmiar;
            obecny = inny.obecny;
            for (int i = 0; i < rozmiar; i++)
                tablica[i] = inny.tablica[i];
        }
        return *this;
    }

    tab_vec& operator =(tab_vec&& inny) //operator przenoszący
    {
        if (&inny != this)
        {
            delete[] tablica;
            tablica = inny.tablica;
            rozmiar = inny.rozmiar;
            obecny = inny.obecny;
            inny.tablica = nullptr;
            inny.rozmiar = 0;
            inny.obecny = 0;
        }
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const tab_vec& vector) //odczyt
    {
        for (size_t i = 0; i < vector.obecny; ++i)
        {
            os << vector.tablica[i] << " ";
        }
        return os;
    }

    friend std::istream& operator>>(std::istream& is, tab_vec& vector) //zapis
    {
        T zaw_strumienia;
        is >> zaw_strumienia;
        vector.dodaj_nowy(zaw_strumienia);
        return is;
    }
};


int main()
{
    tab_vec<int> wektor1;
    tab_vec<int> wektor2(10);
    tab_vec<int> wektor3(3);
    wektor1.dodaj_nowy(1);
    wektor1.dodaj_nowy(2);
    wektor1.dodaj_nowy(3);
    wektor1.dodaj_nowy(5);
    wektor1.dodaj_nowy(6);
    wektor1.dodaj_nowy(8);
    wektor1.dodaj_nowy(13);
    wektor2.dodaj_nowy(111);
    wektor2.dodaj_nowy(20);
    wektor2.dodaj_nowy(32);
    wektor2.dodaj_nowy(-8);
    wektor2.dodaj_nowy(5,1);
    wektor3.dodaj_nowy(7);
    wektor3.dodaj_nowy(2);
    wektor3.dodaj_nowy(8);
    //wektor2.dodaj_nowy(5, 100);
    //std::cin >> wektor2;  //działa ale nie chcę za każdym razem wpisywać


    std::cout << "Zawartosc wektora1: " << std::endl;
    for (int i = 0; i < wektor1.jaki_obecny(); i++)
    {
        std::cout << wektor1[i] << " ";
    }
    std::cout << std::endl;

    wektor1.usun_element(1);

    std::cout << "Zawartosc wektora1 po usunieciu pierwszego elementu: " << std::endl;

    std::cout << wektor1 << std::endl;

    std::cout << "Zawartosc wektora1 po usunieciu dwoch pierwszych elementow: " << std::endl;

    wektor1.usun_element(1,2);
    //wektor1.usun_element(1, 10);
    std::cout << wektor1 << std::endl;

    tab_vec<int> wektorKopiujacy(wektor2);
    std::cout << "Zawartosc wektora2: " << std::endl;
    std::cout << wektor2 << std::endl;

    std::cout << "Zawartosc wektora kopiujacego z wektora 2: " << std::endl;
    std::cout << wektorKopiujacy << std::endl;

    std::cout << "Zawartosc wektora 3: " << std::endl;
    std::cout << wektor3 << std::endl;

    tab_vec<int> wektorPrzenoszacy(std::move(wektor3));
    std::cout << "Zawartosc wektora przenoszacego z wektora3: " << std::endl;
    for (int i = 0; i < wektorPrzenoszacy.jaki_obecny(); i++)
    {
        std::cout << wektorPrzenoszacy[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}

