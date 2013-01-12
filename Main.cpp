#include "Gra.h"

#include <iostream>
#include <string>
#include <time.h>
#include <fstream>


using std::string;
using std::ofstream;
using std::cout;
using std::endl;
using std::cin;
using std::ios;

class Gracz;
class Komplet;
class Pionek;
class PoleWlasnosc;
class KompletPol;
class GraPlanszowa;








int main()
{

  
	
	PoleDoZabudowy rzym("Rzym", "Stolica Wloch", 200, 0, 15, 0 , 400, "pusty", 150, 250, 350, 500, 1000 );
	PoleDoZabudowy neapol("Neapol", "Miasto Polozone na poludniu Wloch", 300, 0, 25, 0 , 300, "pusty", 250, 350, 450, 550, 1100);
	PoleDoZabudowy mediolan("Mediolan", "Miasto o wielkich tradycjach pilkarskich", 400, 0, 35, 0 , 500, "pusty", 350, 450, 550, 650, 1200);
	Kolej poludniowa("Kolej Poludniowa", "Kolej pierwsza", 250, 0, 25, "pusty");
	Kolej zachodnia("Kolej Zachodnia", "Kolej druga", 250, 0, 25, "pusty");
    PolePodatkowe podatek1("Podatek od wzbogacenia", "placisz kwote 200 zl", 200); //!!!!!!!!!!1
	Kolej polnocna("Kolej Polnocna", "Kolej trzecia", 250, 0, 25, "pusty");
	

	
		
	
	

	Pole *WSKpole1  = &rzym;
	Pole *WSKpole2  = &neapol;
	Pole *WSKpole3 = &podatek1;
	Pole *WSKpole4 = &mediolan;
	Pole *WSKpole5 = &poludniowa;
	Pole *WSKpole7 = &zachodnia;
	Pole *WSKpole8 = &polnocna;
	


	Pole* Gra[40];
	Gra[0] = WSKpole1;
	Gra[1] = WSKpole2;
	Gra[2] = WSKpole3;
	Gra[3] = WSKpole4;
	Gra[4] = WSKpole5;
	Gra[6] = WSKpole7;
	Gra[7] = WSKpole8;
	


	



	//tworze karty szans ryzyka
	Karta* WSK0 = new Karta("Jest Remont pobliskiego szpitala, musisz zaplacic 200zl ", -200); //!!!!!!
	Karta* WSK1 = new Karta( "Twoj Los na loteri, okazal sie byc wygranym. Dostajesz 500zl! ", 500);
	Karta* WSK2 = new Karta("Dostaejsz mandat za szybka jazde. Placisz 100zl ", -100);
	Karta* WSK3 = new Karta("Wyslales prace do konkursu plastycznego, ktora okazala sie wygrana. Dostajesz 400zl ", 400);
	Karta* WSK4 = new Karta("Twoja Babcia umarla. Dostajesz w spadku 1000zl ! ", 1000);

	

	Karta* tabl[5];
	tabl[0] = WSK0;
	tabl[1] = WSK1;
	tabl[2] = WSK2;
    tabl[3] = WSK3;
	tabl[4] = WSK4;

	

	Talia tal(tabl); //przesylam do konstruktora tabl ( czyli adres poczatku Karta* tabl[5] )
	
	//wkladam utworzona talie do gry do obiektu klasy PoleSzansyRyzyka

	PoleSzansyRyzyka szansa1("PoleSzansy", "Losujesz karte z szansa ", 5, tal);
	Pole * WSKpole6 = &szansa1;
	Gra[5] = WSKpole6;
	
	
	


   
	Gracz Ja("Tomek", 1000, "niebieski", 0);
	Gracz Ty("Karol", 1000, "zielony", 0);
	//konstruuje GraPlanszowa
	GraPlanszowa Monopoly(Gra);
	cout << "----------------------------zaczynam Gre--------------------------------\n\n" << endl;

	
	Kostka kosc("pierwsza");
	

	
	
	int KtoNastepny = 2;
	
try
{
	for( ; Ja.pionek < 8; )
	    {   
			if(Ja.stanKonta < 0)
				{
					cout <<Ja.nazwa << " zbankrutowal " << endl;
					throw (Ty);
				}

		cout <<"----------teraz ruch gracza " << Ja.nazwa << endl;
		 Ja.pionek = Ja.pionek + kosc.rzuc();
		 Monopoly.Gra[Ja.pionek]->obsluzPostoj(Ja,Monopoly); 
		 
		 
		 
		 if(Ja.pionek >= 6)
		 {
			 Ja.pionek = 0;
		 }
		 KtoNastepny = 2;
		 
		 if( KtoNastepny == 2)
		  {
			 for( ; Ty.pionek < 8;  ) //pionek Karol
	        {   

				if(Ty.stanKonta < 0)
				{
					cout << Ty.nazwa << " zbankrutowal " << endl;
					throw (Ja);
				}
				cout <<"---------teraz ruch gracza " << Ty.nazwa << endl;
				Ty.pionek = Ty.pionek + kosc.rzuc(); //inkrementacje pionek musze zapisac tutaj, bo jesli byla by w pentli for,
					                //tak jak jest w petli dla gracza Ja, nie zdazylo by sie wykonac, prez to ze jest instrukcja "break", 
					             // -pentla zostala by opuszczona za sprawa "break", zanim wykonal by sie tenze warunek w for
				
		        Monopoly.Gra[Ty.pionek]->obsluzPostoj(Ty,Monopoly); 
		 
		     
		     
		     if(Ty.pionek >= 6)
		     {
		     	 Ty.pionek = 0;
		     }
		      KtoNastepny = 1;
		      
			   if(KtoNastepny == 1)
			    {
			    	 
					  
					  break;
			    }
		
             }
		  }
		
		 
       }
}

catch( Gracz wygral)
{
	ofstream strum;
	strum.open("Wygrales.txt", ios::out);
	
	cout << "Gracz : "<< wygral.nazwa << " wygral Gre Monopol !!!!! Gratulacje !!!!! " << endl; 
	strum << "Gracz : "<< wygral.nazwa << " wygral Gre Monopol !!!!! Gratulacje !!!!! " << endl; 
};


return 0;
}
