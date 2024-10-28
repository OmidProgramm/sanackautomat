#include <iostream>
#include<iomanip>
#include <windows.h>
#include <conio.h>

#define ANZ 3

using namespace std;

int ganzzahl(int);
double gleitkomma(int ,int );
void gotoxy(int,int);
void hidecursor(void);
void setColor(int);

class automat
{
	
	private:
		struct fach
		{
			double preis;
			int inhalt;
			string artikel;
		}f[10];
		double zahlung;
		int produkt;
		int posX;
		int posY;
		int aProdukt;
		
	public:
		void zeichne(void);
		void setPosX(int sPosX){posX=sPosX;};	
		void setPosY(int sPosY){posY=sPosY;};
		void setFach(int,int,string,double);
		void setZahlung(void){zahlung=gleitkomma(1,2);};
		int setProdukt(void);
		void ausgabe(void);
			
};

void automat::ausgabe(void)
{
	if(f[aProdukt-1].preis <= zahlung)
	{
		gotoxy(40,20);
		cout <<  "Produkt " << f[aProdukt-1].artikel << " entnehmen";
		f[aProdukt-1].inhalt--;	
	}
	if(f[aProdukt-1].preis < zahlung)
	{
		gotoxy(40,21);
		cout <<  "Restgeld " << zahlung-f[aProdukt-1].preis << " entnehmen";	
	}
	if(f[aProdukt-1].preis > zahlung)
	{
		gotoxy(40,21);
		cout <<  "Geld reicht nicht" ;	
	}
getch();
	gotoxy(30,20);
	cout << "                                              ";
	gotoxy(30,21);
	cout << "                                              ";
};

int automat::setProdukt(void)
{
	int auswahl;
	while(1)
	{
		gotoxy(30,21);
		cout << "                 ";
		gotoxy(30,21);
		auswahl=ganzzahl(2);
		if(auswahl<10 && f[auswahl-1].inhalt>0) 
		{
			aProdukt=auswahl;
			return 1;
		}
		else return 0;
		
	}
};

void automat::setFach(int sNr,int sInhalt,string sArtikel,double sPreis)
{
	f[sNr].artikel=sArtikel;
	f[sNr].preis=sPreis;
	f[sNr].inhalt=sInhalt;
};

void automat::zeichne(void)
{
	int i;
	gotoxy(posX-2,posY-1);
	cout << (char)201 << setfill((char)205) << setw(32) << (char)187;
	gotoxy(posX-2,posY);
	cout << (char)186 << setfill(' ') << setw(5) << "Fach " << setw(6) << "Stck. " ;
	cout << setw(15) << "Artikel " << setw(5) << "Preis" <<(char)186;
	for(i=1;i<11;i++)
	{
		gotoxy(posX-2,posY+i);
		cout << (char)186 << setfill(' ') << setw(4) << i << setw(5) << f[i-1].inhalt ;
		cout << setw(16) << f[i-1].artikel << setw(5) << f[i-1].preis <<" " << (char)186;
	}
	gotoxy(posX-2,posY+i);
	cout << (char)200 << setfill((char)205) << setw(32) << (char)188;

	
}

int main(void)
{
	int temp,kGeld=0,kProdukt=0,aktiv=0;
	automat snack[ANZ];
//	int i=0;
	for(int j=0;j<ANZ;j++)
	{
		snack[j].setPosX(10+j*35);
		snack[j].setPosY(3);
		snack[j].setFach(0,2,"Duplo",1.20);
		snack[j].setFach(1,8,"Hanuta",1.00);
		snack[j].setFach(2,4,"Snickers",0.9);
		snack[j].setFach(3,6,"Mars",1.00);
		snack[j].setFach(4,8,"Bounty",1.10);
		snack[j].setFach(5,8,"Twix",0.80);
		snack[j].setFach(6,9,"Ritter Sport",1.50);
		snack[j].setFach(7,1,"Studentenfutter",1.30);
		snack[j].setFach(8,8,"m&m",1.00);
		snack[j].setFach(9,5,"KitKat",1.00);
	}
		snack[0].setFach(0,2,"Gummib\204rchen",1.20);
	do
	{
		for(int j=0;j<ANZ;j++)
		{
			if(j==aktiv)setColor(2);
			gotoxy(22+j*35,1);
			cout << j+1;
			setColor(7);
			snack[j].zeichne();
		}
		
//		hidecursor();
		gotoxy(5,18);
		cout << "Automat w\204hlen:";
		gotoxy(5,20);
		cout << "g --> Geledeinwurf";
		gotoxy(5,21);
		cout << "p --> Produktwahl";
		gotoxy(5,22);
		cout << "r --> R\201ckgabe";
		temp=getch();
		if(temp>='1' && temp<='3')
		{
			aktiv=temp-49;
		}
		if(temp=='g')
		{
			gotoxy(30,20);
			snack[aktiv].setZahlung();
			kGeld=1;
		}
		if(temp=='p')
		{
			gotoxy(30,21);
			kProdukt=snack[aktiv].setProdukt();
		}
		if(temp=='r')
		{
			gotoxy(30,21);
			cout << "                        ";
			gotoxy(30,20);
			cout << "                        ";
			kProdukt=0;
			kGeld=0;
		}
		if(kProdukt==1&&kGeld==1)
		{
			kGeld=0;
			kProdukt=0;
			snack[aktiv].ausgabe();
		}
	}while(temp!='x');
	cout << "\n\n\nAutomat aus ";
	return 0;
	
}

void hidecursor(void)
{
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = FALSE;
   SetConsoleCursorInfo(consoleHandle, &info);
};

void gotoxy(int x, int y)
{
  COORD coord;
  coord.X = x;
  coord.Y = y;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
};

void setColor(int color)
{
  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleTextAttribute(hConsole, color);
};


int ganzzahl(int max)
{
	string zeichenkette;
	char temp;
	int stellen=0,zahl=0,faktor=1;
	do
	{
		temp=getch();
		if(temp==8 && stellen>0)
		{
			stellen--;
			cout << temp;
			cout << '_';
			cout << temp;
			zeichenkette.erase(stellen);			
		}
		
		
		if(stellen<max && temp>=48 && temp<=57)
		{
			cout << temp;
			zeichenkette+=temp;
			stellen++;
		}
		
	}while(temp != 13);
	for(stellen-=1;stellen>=0;stellen--)
	{
		zahl+=(zeichenkette[stellen]-48)*faktor;
		faktor*=10;
	}
	return zahl;

}




double gleitkomma(int maxVorkomma,int maxNachkomma)
{
	string arrayVorkomma,arrayNachkomma;
	char temp;
	int zVorkomma=0,zNachkomma=0,komma=0,i=0;
	double zahl=0,faktor=1;
	do
	{
		temp=getch();
		if(temp==8 && zVorkomma>0 && komma==0)
		{
			zVorkomma--;
			cout << temp;
			cout << '_';
			cout << temp;
			arrayVorkomma.erase(zVorkomma);
			
		}
		if(temp==8 && zNachkomma>0 && komma==1)
		{
			zNachkomma--;
			cout << temp;
			cout << '_';
			cout << temp;
			arrayNachkomma.erase(zNachkomma);
		}
		if(temp==8 && zNachkomma==0 && komma==1)
		{
			komma=0;
			cout << temp;
			cout << '_';
			cout << temp;
		}
		if((temp==',' || temp=='.') && komma==0)
		{
			komma=1;
			cout << ',';
		}
	
		
		if(komma==0 && zVorkomma<maxVorkomma && temp>=48 && temp<=57 )
		{
			cout << temp;
			arrayVorkomma+=temp;
			zVorkomma++;
		}
		if(komma==1 && zNachkomma<maxNachkomma && temp>=48 && temp<=57 )
		{
			cout << temp;
			arrayNachkomma+=temp;
			zNachkomma++;
		}		
	}while(temp != 13);
	for(zVorkomma-=1;zVorkomma>=0;zVorkomma--)
	{
		zahl+=(arrayVorkomma[zVorkomma]-48)*faktor;
		faktor*=10;
	}
	faktor=0.1;
	for(i=0;i<zNachkomma;i++)
	{
		zahl+=(arrayNachkomma[i]-48)*faktor;
		faktor*=0.1;
	}
	return zahl;

}
