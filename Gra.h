#ifndef Gra_h
#define Gra_h

#include <iostream>
#include <string>

using std::string;

using std::cout;
using std::endl;
using std::cin;

class Gracz;
class Komplet;
class Pionek;
class PoleWlasnosc;
class KompletPol;
class GraPlanszowa;

///klasa gracz, obiekt tej klasy to bedzie nowy gracz wchodzacy do gry
class Gracz
{
  
	
	
	string kolor;
	
	
	

public:
	int stanKonta;
	string nazwa;
	int pionek; ///najwazniejszy skladnik tej klasy to Gracz::pionek , bedzie odpowiedzialny za poruszanie sie po obiekcie klasy GraPlanszowa
	

	Gracz(string n, int stan, string k, int licznik) ;
	
	///konstruktor ktory bedzie potrzebny do tworzenia obiektu o garcz ktorego skladowa nazwa = "pusty"
	Gracz(string n);

	///konstruktor kopiujacy
	Gracz(const Gracz & obj);

	
};

class Pole
{
protected:
	
	string opis;
public:
	///virtualna funkcja na ktorej opiera sie cala gra, dzieki niej chodzac po oiekcie klasy GraPlanszowa, ktrory przechowuje wskazniki do obiektow
	///Pole, bedzie wywolywana odpowiednia wersja funkcji Pole::obsluzPostoj, z klas pochodnych, od klasy POle dzieki mechanizmowi polimorfizmu
	virtual void obsluzPostoj(Gracz & odwiedzajacy, GraPlanszowa & gra);

	

public:
	string nazwa;
	Pole(string Nazwa,string Opis);


	
};

class PolePodatkowe : public Pole
{
	int kwotaPodatku;
public:
	PolePodatkowe(string n, string o, int kp);

	///fucnkaj obsluz postoj z obiektu PolePo podatkowe, bedzie odejmowala ze skladowej obiektu GRacz, odpowiednia wartosc ze stanu konta danego Gracza, na rzecz
	///ktorego zostala wywoalna funkcja obsluz postoj
	void obsluzPostoj(Gracz & odwiedzajacy, GraPlanszowa & gra);
	
};

///obiekty kklasy karta beda losowane przez funkcje oblsuzPostoj z obiektu klasy PoleSzansyRyzyka, ktorego skladowa jest obiekt klasy Talia, ktorego skladowa sa
///obiekty klasy Krata (dowolna ilosc)
class Karta
{
	
	int efekt;
public:
	string opis;
	Karta(string o, int e);
	
	friend class PoleSzansyRyzyka;
};

class Talia
{
	
	
public:
	Karta* wsk[5];
	///kontruktor Talia::Talia kopiuje do tablicy wskaznikow wsk zwartej w obiektcie klasy Talia, odpowiednia ilosc wskaznikow na obiekty klasy Karta
	Talia( Karta* adres[] ); //odbieram tablice Karta* adres[]

	///konstruktor kopiujacy robi to samo co kontstruktor poprzedni, z tym ze dostaje obiekt klasy Talia, ktory zawiera juz wskazniki na obiekty klasy Karta
	Talia( const Talia & obj);
	

};


class PoleSzansyRyzyka : public Pole 
{
	int ileJestKart;
public:
	Talia doGry ;

	PoleSzansyRyzyka(string n, string o, int ile, Talia & tal);

	///losuje obiekt klasy Karta, z obiketu klasy Talia, i wywoluje jego dzialanie na obiekcie klasy gracz, na rzecz ktorego zostala wywoalna funkcja oblsuz postoj
	virtual void obsluzPostoj(Gracz & odwiedzajacy, GraPlanszowa & gra);

};
///prosta klasa ktorej glowna skladowa to funkcja rzuc
class Kostka
{
	string nazwa;
public:
	///zwraca ona liczbe wylosowanom z zadanego przedzialu, na rzecz tego programu jest to tylko przedzial 1-2
	int rzuc();
	

	Kostka(string n);
	
};

class GraPlanszowa 
{
	
public:
	Pole* Gra[40]; ///tu beda przechowywane adresy do obiektow Pole
	///konstruktor ktory jako argument przyjmuje tablice wskaznikow do obiektow klasy Pole
	///kontruktor kopiuje je, do tablicy o nazwie GraPlanszowa::Gra
	GraPlanszowa ( Pole* zrodlo[] ) ;
	

	///funkcja ktora zwraca wskaznik na obiekt klasy Pole przechowywany w tablicy GraPLanszowa::Gra na zadanym indeksie tej tablicy
	///bedzie uzywana przez funckje obsluzPostoj z klas pochcodnych od Pole
	Pole* getKtoJestWlascicielem(int nrPola);
	


	/* Gra[0]  = &rzym;
	       1  = &neapol;
	       2 = &podatek1;
	       3 = &mediolan;
	       4 = &poludniowa;
	       5 = &szansa1
	       6 = &zachodnia;
	       7 = &polnocna;*/
};

class PoleWlasnosc : public Pole
{
protected:
	int cena;
	bool czyOddaneWZastaw;
	int koszPostoju;


	
	
	
	
public:
    

	Gracz wlasciciel;

	



	///konstruktr ktory dostaje wiele argumentow, w tym wl - nazwa wlasciciela, ktra w momencie tworzenia obiektu bedzie "pusta"
	///kosntrukttor ten uruchmi komnstruktor klasy Gracz(), i zainicjalizuje skladowa PoleWlasnosc::wlasciciel obiektem utworzonym przez ten konstruktor
	///string opis i nazwa, zostana przekazane do konstruktora "wyzej" (czyli obiektu kalasy Pple od ktorego dziedziczy klasa PoleWlasnosc)
	PoleWlasnosc(int c, bool Zastaw, int Postoj, string nazwa, string opis, string wl);
	

	int getKoszPostoju();
	
	bool getCzyOddaneWZastaw();
	
	
	int getCena();
	
	///bardzo rozbudowana funkjca obsluzPostoj ktora bedzie uruchomiana na rzecz obiektu klasy Gracz, ktory "odwiedza to pole"
	void obsluzPostoj(Gracz & odwiedzajacy, GraPlanszowa & gra);
	
			


	
	
};

class PoleDoZabudowy : public PoleWlasnosc
{
protected:
	int PoziomZabudowy;
	int cenaRozbudowy;
	int oplata1Domek;
	int oplata2Domki;
	int oplata3Domki;
	int oplata4Domki;
	int oplataHotel;
	
	
	///funkcja rozbuduj ktora bedzie uruchomiana, jesli gracz na rzecz ktorego zostala wywolana funkcja PoleDoZabudowy::ObsluzPostoj
	///jest wlascicielem calego panstwa -> moze on wiec budowac nieruchomosci na tym("this") obiekcie 
	void rozbuduj();
	



	void sprzedajPoziomZabudowy();
	
	
	

	

	

public:
	
	///kpnstruktor, ktory przekazuje "wyzej"(tj. do klas od ktorych dziedziczy) int cena, bool czyOddaneWZastaw, int koszPostoju,  n ,o, wl->do konstutktora obieku PoleWlasnosc::PoleWlasnosc
	///tenze konstruktor przekazuje znow wyzej : do konstruktora Pole::Pole n,o, -> nazwa, i opis tworzonego obiektu klasy Pole
	PoleDoZabudowy(string n, string o, int cena, bool czyOddaneWZastaw, int koszPostoju, int poziom, int cenarozbudowy, string wl,int a,int b,int c, int d, int e );
		
	///funckja ta rozni sie od PoleWlasnosc::obsluzPostoj tym ze jest poszerzona o oblsuge sytuacji w ktorej gracz na rzecz ktorego zostala wywolana funkcja PoleDoZabudowy::ObsluzPostoj
	///jest wlascicielem calego panstwa -> moze on wiec budowac nieruchomosci na tym("this") obiekcie
	void obsluzPostoj(Gracz & odwiedzajacy, GraPlanszowa & gra);
	

};

class Kolej : public PoleWlasnosc
{
		
	
	
public:
	
	

	///konstruktor obiektu klasy Kolej, podobne dzialanie do PoleDoZabudowy::PoleDoZabudowy
	Kolej(string n, string o, int cena, bool czyOddaneWZastaw, int koszPostoju, string wl);
	
	

};




#endif
