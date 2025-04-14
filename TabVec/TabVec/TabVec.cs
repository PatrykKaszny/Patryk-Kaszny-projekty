using System;
using System.Collections;
using System.Collections.Generic;

namespace TabVecCS
{
    public class TabVec<T>
    {
        private T[] _tablica;
        private int _rozmiar;
        private int _obecny;

        // Konstruktor domyślny
        public TabVec()
        {
            _rozmiar = 10;
            _tablica = new T[_rozmiar];
            _obecny = 0;
        }

        // Konstruktor z określonym rozmiarem
        public TabVec(int size)
        {
            _rozmiar = size;
            _tablica = new T[_rozmiar];
            _obecny = 0;
        }

        // Zwraca liczbę aktualnych elementów
        public int JakiObecny() => _obecny;

        // Dodaje nowy element na koniec tablicy
        public void DodajNowy(T nowy)
        {
            if (_obecny == _rozmiar)
            {
                _rozmiar++;
                Array.Resize(ref _tablica, _rozmiar);
            }
            _tablica[_obecny++] = nowy;
        }

        // Dodaje nowy element w określonym indeksie
        public void DodajNowy(T nowy, int index)
        {
            if (index < 0 || index >= _rozmiar)
                throw new ArgumentOutOfRangeException();

            if (index <= _obecny)
            {
                if (_obecny == _rozmiar)
                    Array.Resize(ref _tablica, ++_rozmiar);

                for (int i = _obecny; i > index; i--)
                    _tablica[i] = _tablica[i - 1];

                _tablica[index] = nowy;
                _obecny++;
            }
            else
            {
                _tablica[index] = nowy;
                _obecny = index + 1;
            }
        }

        // Usuwa element z określonego indeksu
        public void UsunElement(int index)
        {
            if (index < 0 || index >= _rozmiar)
                throw new ArgumentOutOfRangeException();

            for (int i = index; i < _obecny - 1; i++)
                _tablica[i] = _tablica[i + 1];

            _obecny--;
        }

        // Usuwa kilka elementów zaczynając od określonego indeksu
        public void UsunElement(int index, int count)
        {
            if (index < 0 || index + count - 1 >= _rozmiar)
                throw new ArgumentOutOfRangeException();

            for (int i = index; i < _obecny - count; i++)
                _tablica[i] = _tablica[i + count];

            _obecny -= count;
        }

        // Operator indeksowania
        public T this[int index]
        {
            get
            {
                if (index < 0 || index >= _rozmiar)
                    throw new ArgumentOutOfRangeException();
                return _tablica[index];
            }
        }

        // Zwraca reprezentację tablicy jako ciąg znaków
        public override string ToString()
        {
            string result = "";
            for (int i = 0; i < _obecny; i++)
                result += _tablica[i] + " ";
            return result.TrimEnd();
        }
    }
}
