#include <iostream>
#include <conio.h>
#include <dos.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>


#define MIN_X 32
#define MIN_Y 8
#define MAX_X 89
#define MAX_Y 26

void dessiner_Bordure();
void dessiner_Briques();
void curseur_frapper_ball();
void curseur_frapper_briques();
void jouer();

using namespace std;
HANDLE console=GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

//33=QTE ELEMENTS, 2=NBRES ELEMENTS STOCKER DANS CHAQUES CASE
int briques[33][2]={
	/*Y=8,  X=33,...*/		{8,33},{8,38},{8,43},{8,48},{8,53},{8,58},{8,63},{8,68},{8,73},{8,78},{8,83},
	/*Y=10, X=33,...*/		{10,33},{10,38},{10,43},{10,48},{10,53},{10,58},{10,63},{10,68},{10,73},{10,78},{10,83},
	/*Y=12, X=33,...*/		{12,33},{12,38},{12,43},{12,48},{12,53},{12,58},{12,63},{12,68},{12,73},{12,78},{12,83}
			    };
int briques_visibles[36]={5,5,5,  5,5,5,  5,5,5,  5,5,5,  5,5,5,  5,5,5,  5,5,5,  5,5,5,  5,5,5,  5,5,5,  5,5,5};
int position_curseur[2]={26,56};    // Y=26, X=56
int position_ball[2]={25,60};       // Y=25, X=60
int lancer_ball=0, direction=1, briques_a_Gauche=33, gagner=0, perdu=0;



void gotoxy(int x, int y){
	CursorPosition.X=x;
	CursorPosition.Y=y;
	SetConsoleCursorPosition(console, CursorPosition);
}

void setcursor(bool visible, DWORD size){
	if(size==0){
		size=20;
	}
	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible=visible;
	lpCursor.dwSize=size;
	SetConsoleCursorInfo(console, &lpCursor);
}

main(){
	setcursor(0, 0);
	char choix;
	do{
		system("cls");
		gotoxy(8, 5);cout<<"ÛßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßÛ";
		gotoxy(8, 6);cout<<"Û                                                                                                       Û";
		gotoxy(8, 7);cout<<"Û   Ûßßßß ÛßßßÛ Ûßßßß Ûßßßß Ûßßßß Û   Û ÛßßßÛ    ÛßßÜ  Ûßßß   ÛßßßÛ  ÛßßßÛ  Û ÛßßßÛ Û   Û Ûßßßß Ûßßßß   Û";
		gotoxy(8, 8);cout<<"Û   Û     Û   Û Û     Û     Û     Û   Û Û   Û    Û   Û Ûßß    Û   Û  Û   Û  Û Û   Û Û   Û Û     Û       Û";
		gotoxy(8, 9);cout<<"Û   Û     ÛßßßÛ ßßßßÛ ßßßßÛ Ûßßß  Û   Û ÛßßßßÛ   Û   Û Û      ÛßßßßÛ ÛßßßßÛ Û Û   Û Û   Û Ûßßß  ßßßßÛ   Û";
		gotoxy(8, 10);cout<<"Û   Û     Û   Û     Û     Û Û     Û   Û Û    Û   ßßßßß ßßßß   Û    Û Û    Û Û Û Û Û Û   Û Û         Û   Û";
		gotoxy(8, 11);cout<<"Û   ßßßßß ß   ß ßßßßß ßßßßß ßßßßß ßßßßß ß    ß                ßßßßßß ß    ß ß ßßÛßß ßßßßß ßßßßß ßßßßß   Û";
		gotoxy(8, 12);cout<<"Û                                                                               ß                       Û ";
		gotoxy(8, 13);cout<<"ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß";
		gotoxy(42, 15);cout<<"1.- COMMENCER\t\t\t 2.- QUITTER";
		gotoxy(35, 17);cout<<"- Copyright HAITI DEVELOPPEURS - Tous droit reserves -";
		choix=getche();
		switch(choix){
			case '1':{
				jouer();
				if(perdu==1){
					system("cls");
					gotoxy(50, 14);cout<<"Desole, t'as perdu\a";
					getch();
				     exit(0);
				}

				if(gagner==1){
					system("cls");
					gotoxy(48, 14);cout<<"Bravoooo!, t'as gagne\a\a";
					getch();
				     exit(0);
				}
				break;
			}
			case '2':{
				system("cls");
				gotoxy(40, 15);cout<<"\t\tA LA PROCHAINE";
				getch();
				exit(0);
				break;
			}
		}
	}while(1);
	return 0;
}

void dessiner_Bordure(){
	gotoxy(53, 3);
	cout<<"H D    G A M E";
	gotoxy(29, 5);     //X=29, Y=5
	cout<<"ÛÛÛÛÛÛÛÛÛÛ   C A S S E U R   D E   B R I Q U E S    ÛÛÛÛÛÛÛÛÛÛÛ";
	gotoxy(29, 27);    //X=29, Y=27
	cout<<"ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß";
	gotoxy(20, 28);cout<<"<- 'a' ou 'T.GAUCHE'";
	gotoxy(48, 28);cout<<"'BackSpace' pour DEMARRER";
	gotoxy(80, 28);cout<<"'d' ou 'T.DROITE' ->";

	for(int i=5; i<27; i++){
		gotoxy(29, i);cout<<"Û";//X=29, Y=i
		gotoxy(91, i);cout<<"Û";//X=91, Y=i
	}
}

void dessiner_Briques(){
	for(int i=0; i<33; i++){
		if(briques_visibles[i]==5){
			gotoxy(briques[i][1], briques[i][0]);
			cout<<"ÛÛÛÛ";
		}
	}
}

void curseur_frapper_ball(){
	if(position_ball[1]>=position_curseur[1] && position_ball[1]<=position_curseur[1]+8){
		if(position_ball[0]==position_curseur[0]-1){
			if(direction==3){
				direction=2;
			}
			else if(direction==4){
				direction=1;
			}
		}
	}
}

void curseur_frapper_briques(){
	for(int i=0; i<33; i++){
		if(briques_visibles[i]==5){
			if(position_ball[1]>=briques[i][1] && position_ball[1]<=briques[i][1]+8){
				if(position_ball[0] == briques[i][0]){
					briques_visibles[i]=0;
					briques_a_Gauche--;
				}
			}
		}
	}
}

void jouer(){
//	char choix;
	while(1){

		system("cls");
		dessiner_Briques();
		dessiner_Bordure();
		gotoxy(position_ball[1], position_ball[0]);cout<<"o";
		gotoxy(position_curseur[1], position_curseur[0]);cout<<"ßßßßßßßßß";

		if(kbhit()){
			char choix=getch();
			if(choix=='d' || choix=='D' || choix==77){
				if(position_curseur[1] <= 79){
					position_curseur[1] = position_curseur[1]+6;
				}
			}
			if(choix=='a' || choix=='A' || choix==75){
				if(position_curseur[1] >= 34){
					position_curseur[1] = position_curseur[1]-6;
				}
			}
			if(choix==32){
				lancer_ball=1;
			}
			if(choix==27){
				break;
			}
		}
		if(lancer_ball==1){
			//direction en Haut_a_Droite
			if(direction==1){
				position_ball[0] = position_ball[0]-1;
				position_ball[1] = position_ball[1]+2;
				if(position_ball[1] > MAX_X){
					direction=2;
				}
				else if(position_ball[0] < MIN_Y){
					direction=4;
				}
			}
			//direction en Haut_a_Gauche
			else if(direction==2){
				position_ball[0] = position_ball[0]-1;
				position_ball[1] = position_ball[1]-2;
				if(position_ball[0] < MIN_Y){
					direction=3;
				}
				else if(position_ball[1] < MIN_X){
					direction=1;
				}
			}
			//direction en Bas_a_Gauche
			else if(direction==3){
				position_ball[0] = position_ball[0]+1;
				position_ball[1] = position_ball[1]-2;
				if(position_ball[0] > MAX_Y){
					perdu=1;
					break;
				}
				else if(position_ball[1] < MIN_X){
					direction=4;
				}
			}
			//direction en Bas_a_Droite
			else if(direction==4){
				position_ball[0] = position_ball[0]+1;
				position_ball[1] = position_ball[1]+2;
				if(position_ball[1] > MAX_X){
					direction=3;
				}
				else if(position_ball[0] > MAX_Y){
					perdu=1;
					break;
				}
			}
			curseur_frapper_ball();

		}
		curseur_frapper_briques();
		if(briques_a_Gauche==0){
			gagner=1;
			break;
		}
	}
}


