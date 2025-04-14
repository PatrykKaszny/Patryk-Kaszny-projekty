using System;

namespace TabVecCS
{
    class Program
    {
        static void Main(string[] args)
        {
            var wektor1 = new TabVec<int>();
            var wektor2 = new TabVec<int>(10);
            var wektor3 = new TabVec<int>(3);

            wektor1.DodajNowy(1);
            wektor1.DodajNowy(2);
            wektor1.DodajNowy(3);
            wektor1.DodajNowy(5);
            wektor1.DodajNowy(6);
            wektor1.DodajNowy(8);
            wektor1.DodajNowy(13);

            wektor2.DodajNowy(111);
            wektor2.DodajNowy(20);
            wektor2.DodajNowy(32);
            wektor2.DodajNowy(-8);
            wektor2.DodajNowy(5, 1);

            wektor3.DodajNowy(7);
            wektor3.DodajNowy(2);
            wektor3.DodajNowy(8);

            Console.WriteLine("Zawartosc wektora1:");
            for (int i = 0; i < wektor1.JakiObecny(); i++)
                Console.Write(wektor1[i] + " ");
            Console.WriteLine();

            wektor1.UsunElement(1);
            Console.WriteLine("Po usunieciu elementu 1: " + wektor1);

            wektor1.UsunElement(1, 2);
            Console.WriteLine("Po usunieciu dwoch elementow od indeksu 1: " + wektor1);

            Console.WriteLine("Zawartosc wektora2: " + wektor2);
            Console.WriteLine("Zawartosc wektora3: " + wektor3);
        }
    }
}