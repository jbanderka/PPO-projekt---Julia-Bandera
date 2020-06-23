#include <iostream>
#include <string>
#include <list>
#include <bits/stdc++.h>
#include <fstream>

#include "classes.h"

using namespace std;

int main() {
	SolidFigure *FiguraPrzestrzenna = new SolidFigure;
	Pyramid *Ostroslup = new Pyramid;
	SolidOfRevolution *BrylaObrotowa = new SolidOfRevolution;
	Prism *Graniastoslup = new Prism;
	Cylinder *Walec = new Cylinder;
	Sphere *Kula = new Sphere;
	RightPrism *GrProsty = new RightPrism;
	ObliquePrism *GrPochyly = new ObliquePrism;
	RegularPrism *GrPrawidlowy = new RegularPrism;

	SolidFigure *node = FiguraPrzestrzenna;

	cout << "Dostepne komendy:" << endl << "CD [nazwa wezla] - zmiana wezla w strukturze. Dostepne wezly:" << endl << "\tSolidFigure" << endl << "\tPyramid" << endl << "\tSolidOfRevolution" << endl << "\tPrism" << endl << "\tCylinder" << endl << "\tSphere"
	<< endl << "\tRightPrism" << endl << "\tObliquePrism" << endl << "\tRegularPrism" << endl << "MO - tworzy obiekt biezacego liscia" << endl << "DO - usuwa obiekt biezacego liscia" << endl << "MDO - modyfikacja obiektu biezacego liscia"
	<< endl << "DIR - wyswietla informacje o obiektach widocznych z danego poziomu" << endl << "SHOW - wyswietla szczegolowe informacje o obiekcie" << endl << "SAVE - zapis zbioru do pliku" << endl << "READ - odczyt zbioru z pliku"
	<< endl << "TREE - wyswietla cala strukture" << endl << "EXIT - koniec programu" << endl << endl;

	string command, name;
	while(command != "EXIT"){
		getline(cin, command);
		transform(command.begin(), command.end(), command.begin(), ::toupper);
		if(command == "CD SOLIDFIGURE"){
			node = FiguraPrzestrzenna;
			cout << "Jestes w wezle: SolidFigure (Figura przestrzenna)" << endl;
		}
		if(command == "CD PYRAMID"){
			node = Ostroslup;
			cout << "Jestes w wezle: Pyramid (Ostroslup)" << endl;
		}
		if(command == "CD SOLIDOFREVOLUTION"){
			node = BrylaObrotowa;
			cout << "Jestes w wezle: SolidOfRevolution (Bryla obrotowa)" << endl;
		}
		if(command == "CD PRISM"){
			node = Graniastoslup;
			cout << "Jestes w wezle: Prism (Graniastoslup)" << endl;
		}
		if(command == "CD CYLINDER"){
			node = Walec;
			cout << "Jestes w wezle: Cylinder (Walec)" << endl;
		}
		if(command == "CD SPHERE"){
			node = Kula;
			cout << "Jestes w wezle: Sphere (Kula)" << endl;
		}
		if(command == "CD RIGHTPRISM"){
			node = GrProsty;
			cout << "Jestes w wezle: RightPrism (Graniastoslup prosty)" << endl;
		}
		if(command == "CD OBLIQUEPRISM"){
			node = GrPochyly;
			cout << "Jestes w wezle: ObliquePrism (Graniastoslup pochyly)" << endl;
		}
		if(command == "CD REGULARPRISM"){
			node = GrPrawidlowy;
			cout << "Jestes w wezle: RegularPrism (Graniastoslup prawidlowy)" << endl;
		}
		if(command == "MO"){
			if(node->leaf){
				cout << "Podaj nazwe obiektu: ";
				cin >> name;
				node->addObj(name);
			}
			else
				cout << "Aktualny wezel nie jest lisciem. Wybierz inny wezel, by wynonac dana operacje" << endl;
		}
		if(command == "DO"){
			if(node->leaf){
				cout << "Podaj nazwe obiektu: "; cin >> name;
				node->deleteObj(name);
			}
			else
				cout << "Aktualny wezel nie jest lisciem. Wybierz inny wezel, by wynonac dana operacje" << endl;
		}
		if(command == "MDO"){
			if(node->leaf){
				cout << "Podaj nazwe obiektu: "; cin >> name;
				node->changeObj(name);
			}
			else
				cout << "Aktualny wezel nie jest lisciem. Wybierz inny wezel, by wynonac dana operacje" << endl;
		}
		if(command == "DIR"){
			if(node->leaf){
				node->showlist();
			}
			else{
				string nodename = node->name();
				if(nodename == "SolidFigure"){
					if(!Ostroslup->list_ob.empty()) Ostroslup->showlist();
					if(!Walec->list_ob.empty()) Walec->showlist();
					if(!Kula->list_ob.empty()) Kula->showlist();
					if(!GrPochyly->list_ob.empty()) GrPochyly->showlist();
					if(!GrPrawidlowy->list_ob.empty()) GrPrawidlowy->showlist();
				}
				if(nodename == "SolidOfRevolution"){
					if(!Walec->list_ob.empty()) Walec->showlist();
					if(!Kula->list_ob.empty()) Kula->showlist();
				}
				if(nodename == "Prism"){
					if(!GrPochyly->list_ob.empty()) GrPochyly->showlist();
					if(!GrPrawidlowy->list_ob.empty()) GrPrawidlowy->showlist();
				}
				if(nodename == "RightPrism")
					if(!GrPrawidlowy->list_ob.empty()) GrPrawidlowy->showlist();
			}
		}
		if(command == "SHOW"){
			if(node->leaf){
				cout << "Podaj nazwe obiektu: "; cin >> name;
				node->showinfo(name);
			}
			else
				cout << "Aktualny wezel nie jest lisciem. Wybierz inny wezel, by wynonac dana operacje" << endl;
		}
		if(command == "SAVE"){
			string filename;
			cout << "Podaj nazwe pliku: "; cin >> filename;
			filename = filename + ".txt";

			fstream fileCheck;
			fileCheck.open(filename.c_str(), ios::out);			//otwarcie pliku; jesli taki plik juz istnieje, to bedzie nadpisywany
			fileCheck.close();

			Ostroslup->save(filename.c_str());				//.c_str() przekazuje const char*
			Walec->save(filename.c_str());
			Kula->save(filename.c_str());
			GrPochyly->save(filename.c_str());
			GrPrawidlowy->save(filename.c_str());
			cout << "Dokonano zapisu do pliku." << endl;
		}
		if(command == "READ"){
			if(!Ostroslup->list_ob.empty()){				//usuniecie wszystkich istniejacych obiektow przed odczytem z pliku
				for(unsigned int i = 0; i < Ostroslup->list_ob.size(); i++)
					delete Ostroslup->list_ob[i];
				Ostroslup->list_ob.clear();
			}
			if(!Walec->list_ob.empty()){
				for(unsigned int i = 0; i < Walec->list_ob.size(); i++)
					delete Walec->list_ob[i];
				Walec->list_ob.clear();
			}
			if(!Kula->list_ob.empty()){
				for(unsigned int i = 0; i < Kula->list_ob.size(); i++)
					delete Kula->list_ob[i];
				Kula->list_ob.clear();
			}
			if(!GrPochyly->list_ob.empty()){
				for(unsigned int i = 0; i < GrPochyly->list_ob.size(); i++)
					delete GrPochyly->list_ob[i];
				GrPochyly->list_ob.clear();
			}
			if(!GrPrawidlowy->list_ob.empty()){
				for(unsigned int i = 0; i < GrPrawidlowy->list_ob.size(); i++)
					delete GrPrawidlowy->list_ob[i];
				GrPrawidlowy->list_ob.clear();
			}

			string filename;
			cout << "Podaj nazwe pliku: "; cin >> filename;
			filename = filename + ".txt";

			Ostroslup->read(filename.c_str());		//.c_str() przekazuje const char*
			Walec->read(filename.c_str());
			Kula->read(filename.c_str());
			GrPochyly->read(filename.c_str());
			GrPrawidlowy->read(filename.c_str());
			cout << "Dokonano odczytu z pliku." << endl;
		}
		if(command == "TREE") FiguraPrzestrzenna->tree();
	}

    return 0;
}
