#ifndef Gra_cpp
#define Gra_cpp

#include "Gra.h"
#include <iostream>
#include <string>
#include <time.h>


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

Gracz::Gracz(string n, int stan, string k, int licznik) 
{
  	
	    kolor = k;
		nazwa = n;
		stanKonta = stan;
		pionek = licznik;
		
}

Gracz::Gracz(string n) :  stanKonta(0), pionek(0)
	{ 
		
	  kolor = "brak";
	  
	   nazwa = n;
	}

Gracz::Gracz(const Gracz & obj) : stanKonta(0), pionek(0)
	{
		
	    kolor = "brak";
        nazwa = obj.nazwa;
		
		
		
	}

void Pole::obsluzPostoj(Gracz & odwiedzajacy, GraPlanszowa & gra)
	{
		
	}
	


	
Pole::Pole(string Nazwa,string Opis)
    {
		
		nazwa = Nazwa;
		opis = Opis;
	}

PolePodatkowe::PolePodatkowe(string n, string o, int kp) : Pole(n,o)
	{
		
		kwotaPodatku = kp;
	}

void PolePodatkowe::obsluzPostoj(Gracz & odwiedzajacy, GraPlanszowa & gra)
	{
		cout << "obsluga postoju pola podatkowego " << endl;
		cout << "musisz zaplacic " << this->nazwa << " w kwocie " << this->kwotaPodatku << endl;
		odwiedzajacy.stanKonta -= this->kwotaPodatku ;
		return;

	}

Karta::Karta(string o, int e)
	{
		opis = o;
		efekt = e;
	}

Talia::Talia( Karta* adres[] ) //odbieram tablice Karta* adres[]
	{
	
		for(int i = 0; i < sizeof(adres)+1  ; i++) //nie wiem czemu sizeof(adres) + 1 ale dziala, jesli jakis blad, to szukac tutaj!!!!
		 {
			 wsk[i] = adres[i];
		 
		 }
	}
Talia::Talia( const Talia & obj)
	{
		
		for(int i = 0; i < sizeof(*obj.wsk)+1  ; i++) 
		 {
			 wsk[i] = obj.wsk[i];
		 
		 }
	}

PoleSzansyRyzyka::PoleSzansyRyzyka(string n, string o, int ile, Talia & tal) : doGry( Talia(tal)), Pole(n,o)
	{
		ileJestKart = ile-1;
		
	}

void PoleSzansyRyzyka::obsluzPostoj(Gracz & odwiedzajacy, GraPlanszowa & gra)
	{
		srand ( time(NULL) );
		int losowanie = rand() % this->ileJestKart+1;
		cout << "Stanoles na polu Szansy/Ryzyka, zostanie wylosowana szansa " << endl;
		cout << this->doGry.wsk[losowanie]->opis << endl;

		
		
			odwiedzajacy.stanKonta += this->doGry.wsk[losowanie]->efekt;
			return;
		
	}

int Kostka::rzuc()
	{
		char odp;

		cout << "jesli chcesz losowac liczbe wpisz 'l' i nacisnij Enter " << endl;
		cin >> odp;
		
		if( tolower(odp) == 'l')
		{
		srand ( time(NULL) );
		int los =  1+( rand() % 2); //z przedzialu 1 - 2
		cout << "wylosowales " << los << " oczka !!" << endl;
		return los;
		}
		
		else
		{
			cout << " nie wpisales odpowiedniej litery, wiec Kosc nie zostala rzucona" << endl;
			return 0;
		}
		
	}

Kostka::Kostka(string n)
	{
		nazwa = n;

	}

GraPlanszowa::GraPlanszowa ( Pole* zrodlo[] ) 
	{
		
		for(int i = 0; i < 8  ; i++) //narazie mam 7 obiektow wiec i < 7 
		 {
			 Gra[i] = zrodlo[i];
		 
		 }

	}

Pole* GraPlanszowa::getKtoJestWlascicielem(int nrPola)
	{
		return Gra[nrPola];

	}

PoleWlasnosc::PoleWlasnosc(int c, bool Zastaw, int Postoj, string nazwa, string opis, string wl) : wlasciciel(Gracz(wl) ),  Pole(nazwa,opis) 
	{
		
		
		
		cena = c;
	    czyOddaneWZastaw = Zastaw;
		koszPostoju = Postoj;
		
	}

int PoleWlasnosc::getKoszPostoju()
	{
		return koszPostoju;
	}
bool PoleWlasnosc::getCzyOddaneWZastaw()
	{
		return czyOddaneWZastaw; 
	}
	
int PoleWlasnosc::getCena()
	{
		return cena;
		
	}

void PoleWlasnosc::obsluzPostoj(Gracz & odwiedzajacy, GraPlanszowa & gra)
	{
		


		cout << "funkcja obsluz postoj " << endl;
		
		///jesli skladowa klasy wlasciciel.nazwa = pusty, to znaczy ze obiekt nie ma wlasciciela, wiec Gracz odiwedzajacy to Pole, moze je zakupic
		if (wlasciciel.nazwa == "pusty" )
		{
			char odp;
			cout << "czy chcesz zakupic  " << this->nazwa << " za : " << this->cena << " [t/n]" << endl;
			cin >> odp;
			if(tolower(odp) == 't' ) 
			{
				if(odwiedzajacy.stanKonta > this->cena)
				{
				cout << "zdecydowales sie kupic " << this->nazwa << " z twojego konta zostanie odjete : " << this->cena << endl;
				odwiedzajacy.stanKonta -= this->cena;
				cout << odwiedzajacy.nazwa << " twoj obecny stan konta to : " << odwiedzajacy.stanKonta << endl;
				this->wlasciciel = odwiedzajacy;
				return;
				}
				if(odwiedzajacy.stanKonta < this->cena)
				{
					cout << "nie stac cie na zakup tego pola !! " << endl;
					return;
				}
			}
			else 
			{
				cout << " Zdecydowales sie nie kupowac : " << this->nazwa << " idziesz dalej " << endl;
				return;
			}
		  }


		///jesli skladowa klasy wlasciciel.nazwa nie jest "pusty", to znaczy ze obiekt ma wlasciciela

		
		if (!(wlasciciel.nazwa == "pusty" ))
		{
			///jesli wlascicielem jest gracz odiedzajacy nic sie nie dzieje
			if(wlasciciel.nazwa == odwiedzajacy.nazwa)
			{
				cout << "jestes u siebie, nic nie robisz " << endl;
				return;
			}
			
			cout << "wlascicielem " << this->nazwa << " jest : " << this->wlasciciel.nazwa << endl;
			
			
			
			///jesli nie to dla tego obiektu Klasy pole, w zaleznosci od wielu warunkow, bedzie pobierana oplata za postoj od obiektu klasy Gracz,
			///na rzecz kotrego ta fucnkja zostala wywolana

			//rozpisuje mozliwosci dla staniecia na Wlochy----------------------------
			if(this->nazwa == "Rzym" ) //1.dla Rzym 
			{
				Pole* wskPom = gra.getKtoJestWlascicielem(1);
				Pole* wskPom2 = gra.getKtoJestWlascicielem(3);

			
				//------------------------------------
			 	if(this->wlasciciel.nazwa == ((PoleWlasnosc*)wskPom)->wlasciciel.nazwa)
				{
					if(this->wlasciciel.nazwa == ((PoleWlasnosc*)wskPom2)->wlasciciel.nazwa)
					{
						cout << this->wlasciciel.nazwa << " jest wlascicielem calego panstwa tj. : " << this->nazwa << ", " <<
							wskPom->nazwa << ", " << wskPom2->nazwa << endl;
						cout << "wiec musisz zaplacic mu potrojnie, czyli : " << (this->koszPostoju)*3 << endl;
						odwiedzajacy.stanKonta -= (this->koszPostoju)*3 ;
						return;
					}

				else
				  {
					cout << this->wlasciciel.nazwa << " jest rowniez wlascicielem : " << wskPom->nazwa << endl;
					cout << "wiec musisz zaplacic mu podwojnie, czyli : " << (this->koszPostoju)*2 << endl;
			     	odwiedzajacy.stanKonta -= (this->koszPostoju)*2;
					return;
				  }
				}
				//----------------------------

				if(this->wlasciciel.nazwa == ((PoleWlasnosc*)wskPom2)->wlasciciel.nazwa)
				{
					if(this->wlasciciel.nazwa == ((PoleWlasnosc*)wskPom)->wlasciciel.nazwa)
					{
						cout << this->wlasciciel.nazwa << " jest wlascicielem calego panstwa tj. : " << this->nazwa << ", " <<
							wskPom->nazwa << ", " << wskPom2->nazwa << endl;
						cout << "wiec musisz zaplacic mu potrojnie, czyli : " << (this->koszPostoju)*3 << endl;
						odwiedzajacy.stanKonta -= (this->koszPostoju)*3 ;
						return;
					}

				else
				   {
					cout << this->wlasciciel.nazwa << " jest rowniez wlascicielem : " << wskPom2->nazwa << endl;
					cout << "wiec musisz zaplacic mu podwojnie, czyli : " << (this->koszPostoju)*2 << endl;
			     	odwiedzajacy.stanKonta -= (this->koszPostoju)*2;
					return;
				   }
				}
			}
				
				
				if(this->nazwa == "Neapol" ) //2.dla Neapol
			{
				Pole* wskPom = gra.getKtoJestWlascicielem(0);
				Pole* wskPom2 = gra.getKtoJestWlascicielem(3);

			
				//------------------------------------
			 	if(this->wlasciciel.nazwa == ((PoleWlasnosc*)wskPom)->wlasciciel.nazwa)
				{
					if(this->wlasciciel.nazwa == ((PoleWlasnosc*)wskPom2)->wlasciciel.nazwa)
					{
						cout << this->wlasciciel.nazwa << " jest wlascicielem calego panstwa tj. : " << this->nazwa << ", " <<
							wskPom->nazwa << ", " << wskPom2->nazwa << endl;
						cout << "wiec musisz zaplacic mu potrojnie, czyli : " << (this->koszPostoju)*3 << endl;
						odwiedzajacy.stanKonta -= (this->koszPostoju)*3 ;
						return;
					}

				else
				  {
					cout << this->wlasciciel.nazwa << " jest rowniez wlascicielem : " << wskPom->nazwa << endl;
					cout << "wiec musisz zaplacic mu podwojnie, czyli : " << (this->koszPostoju)*2 << endl;
			     	odwiedzajacy.stanKonta -= (this->koszPostoju)*2;
					return;
				  }
				}
				//----------------------------

				if(this->wlasciciel.nazwa == ((PoleWlasnosc*)wskPom2)->wlasciciel.nazwa)
				{
					if(this->wlasciciel.nazwa == ((PoleWlasnosc*)wskPom)->wlasciciel.nazwa)
					{
						cout << this->wlasciciel.nazwa << " jest wlascicielem calego panstwa tj. : " << this->nazwa << ", " <<
							wskPom->nazwa << ", " << wskPom2->nazwa << endl;
						cout << "wiec musisz zaplacic mu potrojnie, czyli : " << (this->koszPostoju)*3 << endl;
						odwiedzajacy.stanKonta -= (this->koszPostoju)*3 ;
						return;
					}

				else
				   {
					cout << this->wlasciciel.nazwa << " jest rowniez wlascicielem : " << wskPom2->nazwa << endl;
					cout << "wiec musisz zaplacic mu podwojnie, czyli : " << (this->koszPostoju)*2 << endl;
			     	odwiedzajacy.stanKonta -= (this->koszPostoju)*2;
					return;
				   }
				 }
				}

				if(this->nazwa == "Mediolan" ) //3.dla Mediolan
			{
				Pole* wskPom = gra.getKtoJestWlascicielem(0);
				Pole* wskPom2 = gra.getKtoJestWlascicielem(1);

			
				//------------------------------------
			 	if(this->wlasciciel.nazwa == ((PoleWlasnosc*)wskPom)->wlasciciel.nazwa)
				{
					if(this->wlasciciel.nazwa == ((PoleWlasnosc*)wskPom2)->wlasciciel.nazwa)
					{
						cout << this->wlasciciel.nazwa << " jest wlascicielem calego panstwa tj. : " << this->nazwa << ", " <<
							wskPom->nazwa << ", " << wskPom2->nazwa << endl;
						cout << "wiec musisz zaplacic mu potrojnie, czyli : " << (this->koszPostoju)*3 << endl;
						odwiedzajacy.stanKonta -= (this->koszPostoju)*3 ;
						return;
					}

				else
				  {
					cout << this->wlasciciel.nazwa << " jest rowniez wlascicielem : " << wskPom->nazwa << endl;
					cout << "wiec musisz zaplacic mu podwojnie, czyli : " << (this->koszPostoju)*2 << endl;
			     	odwiedzajacy.stanKonta -= (this->koszPostoju)*2;
					return;
				  }
				}
				//----------------------------

				if(this->wlasciciel.nazwa == ((PoleWlasnosc*)wskPom2)->wlasciciel.nazwa)
				{
					if(this->wlasciciel.nazwa == ((PoleWlasnosc*)wskPom)->wlasciciel.nazwa)
					{
						cout << this->wlasciciel.nazwa << " jest wlascicielem calego panstwa tj. : " << this->nazwa << ", " <<
							wskPom->nazwa << ", " << wskPom2->nazwa << endl;
						cout << "wiec musisz zaplacic mu potrojnie, czyli : " << (this->koszPostoju)*3 << endl;
						odwiedzajacy.stanKonta -= (this->koszPostoju)*3 ;
						return;
					}

				else
				   {
					cout << this->wlasciciel.nazwa << " jest rowniez wlascicielem : " << wskPom2->nazwa << endl;
					cout << "wiec musisz zaplacic mu podwojnie, czyli : " << (this->koszPostoju)*2 << endl;
			     	odwiedzajacy.stanKonta -= (this->koszPostoju)*2;
					return;
				   }
				 }
				}

				
				
				
				



				
				
				//---------------------------
				else
				{
					cout << "musisz zaplacic mu czynsz za postuj: " << this->koszPostoju << endl;
			        wlasciciel.stanKonta += this->koszPostoju;
			        odwiedzajacy.stanKonta -= this->koszPostoju;
			        return;

				}



			}
			

			cout << "musisz zaplacic mu czynsz za postuj: " << this->koszPostoju << endl;
			wlasciciel.stanKonta += this->koszPostoju;
			odwiedzajacy.stanKonta -= this->koszPostoju;
			return;
		}
			




void PoleDoZabudowy::rozbuduj()
	{
		cout << "tu funkjca rozbuduj z klasy PoleDoZabudowy " << endl;
		char odp;

		if(this->PoziomZabudowy < 6 )
		{	
			cout << "miasto " << this->nazwa << " jest rozbudowane do poziomu : " << this->PoziomZabudowy << endl;
			cout << "koszt rozbudowy to " << this->cenaRozbudowy << endl;
			cout << "czy chcesz rozbudowac miasto do poziomu " << (this->PoziomZabudowy)+1 << " ? [t/n]" << endl;
			cin >> odp;
			cout << "!!!!!!!!!!! Twoj stan konta to : !!!!!!!!!!!!!!" << this->wlasciciel.stanKonta << endl;
			if( tolower(odp) == 't' )
			{
				cout << "zdecydowales sie rozbudowac "<< this->nazwa << endl;
				if(this->cenaRozbudowy <= this->wlasciciel.stanKonta )
				{
				 cout << "z twojego konta zostanie zabrane : " << this->cenaRozbudowy << endl;
				 this->wlasciciel.stanKonta -= this->cenaRozbudowy;
				 this->PoziomZabudowy++;
				 cout << "obecny poziom zabudowy to : " << this->PoziomZabudowy << endl << endl;
				 return;
				 
				}
				else
				{
					cout << "nie stac cie na rozbudowe " << endl;
				}
			}
		}
		else
		{
			cout << "miasto jest juz rozbudowane do poziomu : " << this->PoziomZabudowy << endl;
			cout << "oznacza to ze stoi na nim hotel " << endl;
		}
		  
		
}

void PoleDoZabudowy::sprzedajPoziomZabudowy()
	{}




PoleDoZabudowy::PoleDoZabudowy(string n, string o, int cena, bool czyOddaneWZastaw, int koszPostoju, int poziom, int cenarozbudowy, string wl,int a,int b,int c, int d, int e )
		: PoleWlasnosc(cena, czyOddaneWZastaw, koszPostoju, n ,o, wl)
	{
		oplata1Domek = a;
		oplata2Domki = b;
		oplata3Domki = c;
		oplata4Domki = d;
		oplataHotel = e;

		
		PoziomZabudowy = poziom;
		cenaRozbudowy = cenarozbudowy;
	   
	}

void PoleDoZabudowy::obsluzPostoj(Gracz & odwiedzajacy, GraPlanszowa & gra)
	{
		
	

		cout << "funkcja obsluz postoj " << endl;
		
		if (wlasciciel.nazwa == "pusty" )
		{
			char odp;
			cout << "czy chcesz zakupic  " << this->nazwa << " za : " << this->cena << " [t/n]" << endl;
			cin >> odp;
			if(tolower(odp) == 't' ) 
			{
				if(odwiedzajacy.stanKonta > this->cena)
				{
				cout << "zdecydowales sie kupic " << this->nazwa << " z twojego konta zostanie odjete : " << this->cena << endl;
				odwiedzajacy.stanKonta -= this->cena;
				cout << odwiedzajacy.nazwa << " twoj obecny stan konta to : " << odwiedzajacy.stanKonta << endl;
				this->wlasciciel = odwiedzajacy;
				return;
				}
				if(odwiedzajacy.stanKonta < this->cena)
				{
					cout << "nie stac cie na zakup tego pola !! " << endl;
					return;
				}
			}
			else 
			{
				cout << " Zdecydowales sie nie kupowac : " << this->nazwa << " idziesz dalej " << endl;
				return;
			}
		  }



		if (!(wlasciciel.nazwa == "pusty" ))
		{
			if(wlasciciel.nazwa == odwiedzajacy.nazwa)
			{
				//rozpatruje mozliwosci dla bycia wlascicielem dla wlochy bedac wlascicielem ktoregos z pola -------------------
				if(this->nazwa == "Rzym" ) //1.dla Rzym 
			{
				Pole* wskPom = gra.getKtoJestWlascicielem(1);
				Pole* wskPom2 = gra.getKtoJestWlascicielem(3);

			
				//------------------------------------
			 	if(this->wlasciciel.nazwa == ((PoleWlasnosc*)wskPom)->wlasciciel.nazwa)
				{
					if(this->wlasciciel.nazwa == ((PoleWlasnosc*)wskPom2)->wlasciciel.nazwa)
					{
						cout << this->wlasciciel.nazwa << " jestes wlascicielem calego panstwa tj. : " << this->nazwa << ", " <<
							wskPom->nazwa << ", " << wskPom2->nazwa << endl;
						cout << "wiec mozesz sie tu budowac  " << endl;
						this->rozbuduj();
						return;
					}

				else
				  {
					cout << this->wlasciciel.nazwa << " jestes rowniez wlascicielem : " << wskPom->nazwa << endl;
					cout <<"aby muc budowac sie w tym kraju kup tez : " << wskPom2->nazwa << endl;
			     	
					return;
				  }
				}
				//----------------------------

				if(this->wlasciciel.nazwa == ((PoleWlasnosc*)wskPom2)->wlasciciel.nazwa)
				{
					if(this->wlasciciel.nazwa == ((PoleWlasnosc*)wskPom)->wlasciciel.nazwa)
					{
						cout << this->wlasciciel.nazwa << " jestes wlascicielem calego panstwa tj. : " << this->nazwa << ", " <<
							wskPom->nazwa << ", " << wskPom2->nazwa << endl;
						cout << "wiec mozesz sie tu budowac  " << endl;
						this->rozbuduj();

						return;
					}

				else
				   {
					cout << this->wlasciciel.nazwa << " jestes rowniez wlascicielem : " << wskPom2->nazwa << endl;
					cout <<"aby muc budowac sie w tym kraju kup tez : " << wskPom->nazwa << endl;
					return;
				   }
				}
			}
				
				
				if(this->nazwa == "Neapol" ) //2.dla Neapol
			{
				Pole* wskPom = gra.getKtoJestWlascicielem(0);
				Pole* wskPom2 = gra.getKtoJestWlascicielem(3);

			
				//------------------------------------
			 	if(this->wlasciciel.nazwa == ((PoleWlasnosc*)wskPom)->wlasciciel.nazwa)
				{
					if(this->wlasciciel.nazwa == ((PoleWlasnosc*)wskPom2)->wlasciciel.nazwa)
					{
						cout << this->wlasciciel.nazwa << " jest wlascicielem calego panstwa tj. : " << this->nazwa << ", " <<
							wskPom->nazwa << ", " << wskPom2->nazwa << endl;
						cout << "wiec mozesz sie tu budowac  " << endl;
						this->rozbuduj();

						return;
					}

				else
				  {
					cout << this->wlasciciel.nazwa << " jest rowniez wlascicielem : " << wskPom->nazwa << endl;
						cout <<"aby muc budowac sie w tym kraju kup tez : " << wskPom2->nazwa << endl;
					return;
				  }
				}
				//----------------------------

				if(this->wlasciciel.nazwa == ((PoleWlasnosc*)wskPom2)->wlasciciel.nazwa)
				{
					if(this->wlasciciel.nazwa == ((PoleWlasnosc*)wskPom)->wlasciciel.nazwa)
					{
						cout << this->wlasciciel.nazwa << " jest wlascicielem calego panstwa tj. : " << this->nazwa << ", " <<
							wskPom->nazwa << ", " << wskPom2->nazwa << endl;
						cout << "wiec mozesz sie tu budowac  " << endl;
						this->rozbuduj();
						return;
					}

				else
				   {
					cout << this->wlasciciel.nazwa << " jest rowniez wlascicielem : " << wskPom2->nazwa << endl;
					cout <<"aby muc budowac sie w tym kraju kup tez : " << wskPom->nazwa << endl;
					return;
				   }
				 }
				}

				if(this->nazwa == "Mediolan" ) //3.dla Mediolan
			{
				Pole* wskPom = gra.getKtoJestWlascicielem(0);
				Pole* wskPom2 = gra.getKtoJestWlascicielem(1);

			
				//------------------------------------
			 	if(this->wlasciciel.nazwa == ((PoleWlasnosc*)wskPom)->wlasciciel.nazwa)
				{
					if(this->wlasciciel.nazwa == ((PoleWlasnosc*)wskPom2)->wlasciciel.nazwa)
					{
						cout << this->wlasciciel.nazwa << " jest wlascicielem calego panstwa tj. : " << this->nazwa << ", " <<
							wskPom->nazwa << ", " << wskPom2->nazwa << endl;
						cout << "wiec mozesz sie tu budowac  " << endl;
						this->rozbuduj();
						return;
					}

				else
				  {
					cout << this->wlasciciel.nazwa << " jest rowniez wlascicielem : " << wskPom->nazwa << endl;
					cout <<"aby muc budowac sie w tym kraju kup tez : " << wskPom2->nazwa << endl;
					return;
				  }
				}
				//----------------------------

				if(this->wlasciciel.nazwa == ((PoleWlasnosc*)wskPom2)->wlasciciel.nazwa)
				{
					if(this->wlasciciel.nazwa == ((PoleWlasnosc*)wskPom)->wlasciciel.nazwa)
					{
						cout << this->wlasciciel.nazwa << " jest wlascicielem calego panstwa tj. : " << this->nazwa << ", " <<
							wskPom->nazwa << ", " << wskPom2->nazwa << endl;
							cout << "wiec mozesz sie tu budowac  " << endl;
							this->rozbuduj();
						return;
					}

				else
				   {
					cout << this->wlasciciel.nazwa << " jest rowniez wlascicielem : " << wskPom2->nazwa << endl;
					cout <<"aby muc budowac sie w tym kraju kup tez : " << wskPom->nazwa << endl;
					return;
				   }
				 }
				}


				else
				{
					cout << "jestes u siebie, nie robisz nic " << endl;
					return;
				}

				
			}
			
			
			
			
			
			
			
			
			
			
			
			else
	        {//rozpisuje mozliwosci dla staniecia na Wlochy- nie bedac wlascicielem pola---------------------------
			
				if(this->nazwa == "Rzym" ) //1.dla Rzym 
			{
				Pole* wskPom = gra.getKtoJestWlascicielem(1);
				Pole* wskPom2 = gra.getKtoJestWlascicielem(3);

			
				//------------------------------------
			 	if(this->wlasciciel.nazwa == ((PoleWlasnosc*)wskPom)->wlasciciel.nazwa)
				{
					if(this->wlasciciel.nazwa == ((PoleWlasnosc*)wskPom2)->wlasciciel.nazwa)
					{
						if(this->PoziomZabudowy == 0 )
						{
							cout << this->wlasciciel.nazwa << " jest wlascicielem calego panstwa tj. : " << this->nazwa << ", " <<
						    wskPom->nazwa << ", " << wskPom2->nazwa << endl;
						    cout << "wiec musisz zaplacic mu potrojnie, czyli : " << (this->koszPostoju)*3 << endl;
						    odwiedzajacy.stanKonta -= (this->koszPostoju)*3 ;
						    return;
						}
						if(this->PoziomZabudowy == 1 )
						{
							cout << this->wlasciciel.nazwa << " jest wlascicielem calego panstwa tj. : " << this->nazwa << ", " <<
						    wskPom->nazwa << ", " << wskPom2->nazwa << endl;
							cout << this->nazwa << " posiada jeden domek, koszt postoju wynosi teraz : " << this->oplata1Domek << endl; 
							odwiedzajacy.stanKonta -=this->oplata1Domek ;
						    return;
                        }
						if(this->PoziomZabudowy == 2 )
						{
							cout << this->wlasciciel.nazwa << " jest wlascicielem calego panstwa tj. : " << this->nazwa << ", " <<
						    wskPom->nazwa << ", " << wskPom2->nazwa << endl;
							cout << this->nazwa << " posiada dwa domki, koszt postoju wynosi teraz : " << this->oplata2Domki << endl; 
							odwiedzajacy.stanKonta -=this->oplata2Domki ;
						    return;
                        }

						if(this->PoziomZabudowy == 3 )
						{
							cout << this->wlasciciel.nazwa << " jest wlascicielem calego panstwa tj. : " << this->nazwa << ", " <<
						    wskPom->nazwa << ", " << wskPom2->nazwa << endl;
							cout << this->nazwa << " posiada trzy domki, koszt postoju wynosi teraz : " << this->oplata3Domki << endl; 
							odwiedzajacy.stanKonta -=this->oplata3Domki ;
						    return;
                        }

						if(this->PoziomZabudowy == 4 )
						{
							cout << this->wlasciciel.nazwa << " jest wlascicielem calego panstwa tj. : " << this->nazwa << ", " <<
						    wskPom->nazwa << ", " << wskPom2->nazwa << endl;
							cout << this->nazwa << " posiada cztery domki, koszt postoju wynosi teraz : " << this->oplata4Domki << endl; 
							odwiedzajacy.stanKonta -=this->oplata4Domki ;
						    return;
                        }

							if(this->PoziomZabudowy == 5 )
						{
							cout << this->wlasciciel.nazwa << " jest wlascicielem calego panstwa tj. : " << this->nazwa << ", " <<
						    wskPom->nazwa << ", " << wskPom2->nazwa << endl;
							cout << this->nazwa << " posiada Hotel, koszt postoju wynosi teraz : " << this->oplataHotel << endl; 
							odwiedzajacy.stanKonta -=this->oplataHotel ;
						    return;
                        }

					}

				else
				  {
					cout << this->wlasciciel.nazwa << " jest rowniez wlascicielem : " << wskPom->nazwa << endl;
					cout << "wiec musisz zaplacic mu podwojnie, czyli : " << (this->koszPostoju)*2 << endl;
			     	odwiedzajacy.stanKonta -= (this->koszPostoju)*2;
					return;
				  }
				}
				//----------------------------

				if(this->wlasciciel.nazwa == ((PoleWlasnosc*)wskPom2)->wlasciciel.nazwa)
				{
					if(this->wlasciciel.nazwa == ((PoleWlasnosc*)wskPom)->wlasciciel.nazwa)
					{
						cout << this->wlasciciel.nazwa << " jest wlascicielem calego panstwa tj. : " << this->nazwa << ", " <<
							wskPom->nazwa << ", " << wskPom2->nazwa << endl;
						cout << "wiec musisz zaplacic mu potrojnie, czyli : " << (this->koszPostoju)*3 << endl;
						odwiedzajacy.stanKonta -= (this->koszPostoju)*3 ;
						return;
					}

				else
				   {
					cout << this->wlasciciel.nazwa << " jest rowniez wlascicielem : " << wskPom2->nazwa << endl;
					cout << "wiec musisz zaplacic mu podwojnie, czyli : " << (this->koszPostoju)*2 << endl;
			     	odwiedzajacy.stanKonta -= (this->koszPostoju)*2;
					return;
				   }
				}
			}
				
				
				if(this->nazwa == "Neapol" ) //2.dla Neapol
			{
				Pole* wskPom = gra.getKtoJestWlascicielem(0);
				Pole* wskPom2 = gra.getKtoJestWlascicielem(3);

			
				//------------------------------------
			 	if(this->wlasciciel.nazwa == ((PoleWlasnosc*)wskPom)->wlasciciel.nazwa)
				{
					if(this->wlasciciel.nazwa == ((PoleWlasnosc*)wskPom2)->wlasciciel.nazwa)
					{
						cout << this->wlasciciel.nazwa << " jest wlascicielem calego panstwa tj. : " << this->nazwa << ", " <<
							wskPom->nazwa << ", " << wskPom2->nazwa << endl;
						cout << "wiec musisz zaplacic mu potrojnie, czyli : " << (this->koszPostoju)*3 << endl;
						odwiedzajacy.stanKonta -= (this->koszPostoju)*3 ;
						return;
					}

				else
				  {
					cout << this->wlasciciel.nazwa << " jest rowniez wlascicielem : " << wskPom->nazwa << endl;
					cout << "wiec musisz zaplacic mu podwojnie, czyli : " << (this->koszPostoju)*2 << endl;
			     	odwiedzajacy.stanKonta -= (this->koszPostoju)*2;
					return;
				  }
				}
				//----------------------------

				if(this->wlasciciel.nazwa == ((PoleWlasnosc*)wskPom2)->wlasciciel.nazwa)
				{
					if(this->wlasciciel.nazwa == ((PoleWlasnosc*)wskPom)->wlasciciel.nazwa)
					{
						cout << this->wlasciciel.nazwa << " jest wlascicielem calego panstwa tj. : " << this->nazwa << ", " <<
							wskPom->nazwa << ", " << wskPom2->nazwa << endl;
						cout << "wiec musisz zaplacic mu potrojnie, czyli : " << (this->koszPostoju)*3 << endl;
						odwiedzajacy.stanKonta -= (this->koszPostoju)*3 ;
						return;
					}

				else
				   {
					cout << this->wlasciciel.nazwa << " jest rowniez wlascicielem : " << wskPom2->nazwa << endl;
					cout << "wiec musisz zaplacic mu podwojnie, czyli : " << (this->koszPostoju)*2 << endl;
			     	odwiedzajacy.stanKonta -= (this->koszPostoju)*2;
					return;
				   }
				 }
				}

				if(this->nazwa == "Mediolan" ) //3.dla Mediolan
			{
				Pole* wskPom = gra.getKtoJestWlascicielem(0);
				Pole* wskPom2 = gra.getKtoJestWlascicielem(1);

			
				//------------------------------------
			 	if(this->wlasciciel.nazwa == ((PoleWlasnosc*)wskPom)->wlasciciel.nazwa)
				{
					if(this->wlasciciel.nazwa == ((PoleWlasnosc*)wskPom2)->wlasciciel.nazwa)
					{
						cout << this->wlasciciel.nazwa << " jest wlascicielem calego panstwa tj. : " << this->nazwa << ", " <<
							wskPom->nazwa << ", " << wskPom2->nazwa << endl;
						cout << "wiec musisz zaplacic mu potrojnie, czyli : " << (this->koszPostoju)*3 << endl;
						odwiedzajacy.stanKonta -= (this->koszPostoju)*3 ;
						return;
					}

				else
				  {
					cout << this->wlasciciel.nazwa << " jest rowniez wlascicielem : " << wskPom->nazwa << endl;
					cout << "wiec musisz zaplacic mu podwojnie, czyli : " << (this->koszPostoju)*2 << endl;
			     	odwiedzajacy.stanKonta -= (this->koszPostoju)*2;
					return;
				  }
				}
				//----------------------------

				if(this->wlasciciel.nazwa == ((PoleWlasnosc*)wskPom2)->wlasciciel.nazwa)
				{
					if(this->wlasciciel.nazwa == ((PoleWlasnosc*)wskPom)->wlasciciel.nazwa)
					{
						cout << this->wlasciciel.nazwa << " jest wlascicielem calego panstwa tj. : " << this->nazwa << ", " <<
							wskPom->nazwa << ", " << wskPom2->nazwa << endl;
						cout << "wiec musisz zaplacic mu potrojnie, czyli : " << (this->koszPostoju)*3 << endl;
						odwiedzajacy.stanKonta -= (this->koszPostoju)*3 ;
						return;
					}

				else
				   {
					cout << this->wlasciciel.nazwa << " jest rowniez wlascicielem : " << wskPom2->nazwa << endl;
					cout << "wiec musisz zaplacic mu podwojnie, czyli : " << (this->koszPostoju)*2 << endl;
			     	odwiedzajacy.stanKonta -= (this->koszPostoju)*2;
					return;
				   }
				 }
				}

				
				
				
			cout << "wlascicielem " << this->nazwa << " jest : " << this->wlasciciel.nazwa << endl;
			cout << "musisz zaplacic mu czynsz za postuj: " << this->koszPostoju << endl;
			wlasciciel.stanKonta += this->koszPostoju;
			odwiedzajacy.stanKonta -= this->koszPostoju;
			return;
			}
		}
	


 }



	
 Kolej::Kolej(string n, string o, int cena, bool czyOddaneWZastaw, int koszPostoju, string wl)
		: PoleWlasnosc(cena, czyOddaneWZastaw, koszPostoju, n ,o, wl)
	{
	   cout << "";
	}



#endif
