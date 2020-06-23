#ifndef CLASSES_H_INCLUDED
#define CLASSES_H_INCLUDED

#include <limits>
#include <vector>
#include <fstream>

using namespace std;

class SolidFigure {								//klasa figura przestrzenna
	string obj_name;
protected:
	virtual double volume() { return 0; }
public:
	bool leaf;
	SolidFigure(){
		obj_name = "SolidFigure";
		leaf = false;
	}
	virtual ~SolidFigure() {}

	virtual void addObj(string name){}
	virtual void deleteObj(string name){}
	virtual void changeObj(string name){}
	virtual void showlist(){}
	virtual void showinfo(string name){}

	void tree(){
		cout << "SolidFigure" << endl << "\tPyramid" << endl << "\tSolidOfRevolution" << endl << "\t\tCylinder" << endl << "\t\tSphere"
		<< endl << "\tPrism" << endl << "\t\tRightPrism" << endl << "\t\t\tRegularPrism" << endl << "\t\tObliquePrism" << endl;
	}

	void showvolume(){							//metoda wyswietlajaca objetosc figury przestrzennej
		cout << "Objetosc: " << volume() << endl;
	}

	virtual void showname(){
		cout << obj_name << endl;
	}

	virtual string name(){
		return obj_name;
	}
};

class Pyramid : public SolidFigure {			//klasa ostroslup (z kwadratem jako podstawa)
	string obj_name;
	int base_length;
	int height;
protected:
	double volume() {
		return (base_length * base_length * height)/3.0;
	}
public:
	Pyramid() {
		obj_name = "Pyramid";
		leaf = true;
	}
	Pyramid(string name, int b, int h): obj_name(name), base_length(b), height(h) {}
	~Pyramid() {}
	vector<Pyramid*> list_ob;

	void addObj(string name) {					//dodawanie obiektu
	    int b, h;
		cout << "Podaj dlugosc boku podstawy: ";
		cin >> b;
		cout << "Podaj wysokosc: ";
		cin >> h;
		Pyramid *ptrPyramid = new Pyramid(name, b, h);
		list_ob.push_back(ptrPyramid);
		cout << "Dodano obiekt." << endl;
	}

	void deleteObj(string name) {				//usuwanie obiektu
		if(!list_ob.empty()){
			bool found = false;
			for(vector<Pyramid*>::iterator i = list_ob.begin(); i < list_ob.end(); i++){
				if((*i)->obj_name == name){
					found = true;
					delete *i;
					list_ob.erase(i);
					cout << "Usunieto obiekt." << endl;
				}
			}
			if(!found)
				cout << "Nie istnieje obiekt o podanej nazwie." << endl;
		}
		else
			cout << "Lista jest pusta." << endl;
	}

	void changeObj(string name) {				//modyfikacja obiektu
		if(!list_ob.empty()){
			string option;
			bool found = false;
			for(vector<Pyramid*>::iterator i = list_ob.begin(); i < list_ob.end(); i++)
				if((*i)->obj_name == name){
					found = true;
					cout << "Czy chcesz zmienic nazwe obiektu? Wpisz 'tak' lub 'nie'" << endl;
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					getline(cin, option);
					if(option == "tak"){
						cout << "Wpisz nowa nazwe: ";
						getline(cin, (*i)->obj_name);
					}
					cout << "Czy chcesz zmienic dlugosc krawedzi podstawy obiektu? Wpisz 'tak' lub 'nie'" << endl;
					getline(cin, option);
					if(option == "tak"){
						cout << "Wpisz nowa dlugosc: ";
						cin >> (*i)->base_length;
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
					}
					cout << "Czy chcesz zmienic wysokosc obiektu? Wpisz 'tak' lub 'nie'" << endl;
					getline(cin, option);
					if(option == "tak"){
						cout << "Wpisz nowa wysokosc: ";
						cin >> (*i)->height;
					}
					cout << "Dokonano zmian w obiekcie." << endl;
				}
			if(!found)
				cout << "Nie istnieje obiekt o podanej nazwie." << endl;
		}
		else
			cout << "Lista jest pusta." << endl;
	}

	void showlist() {					//metoda wyswietla nazwy obiektow w liscie
		if(!list_ob.empty()){
			cout << "Wezel: " << obj_name << endl;
			for(vector<Pyramid*>::iterator i = list_ob.begin(); i < list_ob.end(); i++)
				cout << "\tNazwa obiektu: " << (*i)->obj_name << endl;
		}
		else
			cout << "Lista jest pusta." << endl;
	}

	void showinfo(string name) {		//metoda wyswietla szczegolowe o danym obiekcie
		if(!list_ob.empty()){
			bool found = false;
			for(vector<Pyramid*>::iterator i = list_ob.begin(); i < list_ob.end(); i++)
				if((*i)->obj_name == name){
					found = true;
					cout << "Nazwa obiektu: " << (*i)->obj_name << endl;
					(*i)->showvolume();
					cout << "Dlugosc krawedzi podstawy: " << (*i)->base_length << endl << "Wysokosc: " << (*i)->height << endl;
				}
				if(!found)
					cout << "Nie istnieje obiekt o podanej nazwie." << endl;
		}
		else
			cout << "Lista jest pusta." << endl;
	}

	void save(const char* filename) {
		fstream file(filename, ios::out | ios::app);
		if(file.good()){
			if(!list_ob.empty()){
				file << "P" << endl;
				file << list_ob.size() << endl;
				for(vector<Pyramid*>::iterator i = list_ob.begin(); i < list_ob.end(); i++){
					file << (*i)->obj_name << endl;
					file << (*i)->base_length << endl;
					file << (*i)->height << endl;
				}
				file.close();
			}
		}
		else
			cout << "Blad przy otwieraniu pliku!" << endl;
	}

	void read(const char* filename) {
		fstream file(filename, ios::in);
		if(file.good()){
			string leaf;
			do file >> leaf;
			while(leaf != "P" && !file.eof());
			if(leaf == "P"){
				string name;
				int counter, b, h;
				file >> counter;
				for(int i = 0; i < counter; i++){
					file >> name;
					file >> b;
					file >> h;
					Pyramid *ptrPyramid = new Pyramid(name, b, h);
            		list_ob.push_back(ptrPyramid);
				}
			}
		}
		else
			cout << "Blad przy otwieraniu pliku!" << endl;
	}

	void showname() {
		cout << obj_name << endl;
	}

};

class SolidOfRevolution : public SolidFigure {		//klasa bryla obrotowa
	string obj_name;
	int radius;
	int height;
protected:
	virtual double volume() { return 0; }
public:
	SolidOfRevolution() {
		obj_name = "SolidOfRevolution";
		leaf = false;
	}
	~SolidOfRevolution() {}

	virtual void showname(){
		cout << obj_name << endl;
	}

	string name(){
		return obj_name;
	}
};

class Prism : public SolidFigure {					//klasa graniastoslup (tak naprawde bierzemy pod uwage prostopadlosciany)
	string obj_name;
	int height;
protected:
	virtual double volume() { return 0; }
public:
	Prism() {
		obj_name = "Prism";
		leaf = false;
	}
	~Prism() {}

	virtual void showname(){
		cout << obj_name << endl;
	}

	virtual string name(){
		return obj_name;
	}
};

class Cylinder : public SolidOfRevolution {			//klasa walec; dziedziczy po brylach obrotowych
	string obj_name;
	int radius;
	int height;
protected:
	double volume() {
		return 3.14 * radius * radius * height;
	}
public:
	Cylinder() {
		obj_name = "Cylinder";
		leaf = true;
	}
	Cylinder(string name, int r, int h): obj_name(name), radius(r), height(h) {}
	~Cylinder() {}
	vector<Cylinder*> list_ob;

	void addObj(string name) {					//dodawanie obiektu
	    int r, h;
		cout << "Podaj dlugosc promienia: ";
		cin >> r;
		cout << "Podaj wysokosc: ";
		cin >> h;
		Cylinder *ptrCylinder = new Cylinder(name, r, h);
		list_ob.push_back(ptrCylinder);
		cout << "Dodano obiekt." << endl;
	}

	void deleteObj(string name) {				//usuwanie obiektu
		if(!list_ob.empty()){
			bool found = false;
			for(vector<Cylinder*>::iterator i = list_ob.begin(); i < list_ob.end(); i++){
				if((*i)->obj_name == name){
					found = true;
					delete *i;
					list_ob.erase(i);
					cout << "Usunieto obiekt." << endl;
				}
			}
			if(!found)
				cout << "Nie istnieje obiekt o podanej nazwie." << endl;
		}
		else
			cout << "Lista jest pusta." << endl;
	}

	void changeObj(string name) {				//modyfikacja obiektu
		if(!list_ob.empty()){
			string option;
			bool found = false;
			for(vector<Cylinder*>::iterator i = list_ob.begin(); i < list_ob.end(); i++)
				if((*i)->obj_name == name){
					found = true;
					cout << "Czy chcesz zmienic nazwe obiektu? Wpisz 'tak' lub 'nie'" << endl;
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					getline(cin, option);
					if(option == "tak"){
						cout << "Wpisz nowa nazwe: ";
						getline(cin, (*i)->obj_name);
					}
					cout << "Czy chcesz zmienic dlugosc promienia obiektu? Wpisz 'tak' lub 'nie'" << endl;
					getline(cin, option);
					if(option == "tak"){
						cout << "Wpisz nowa dlugosc: ";
						cin >> (*i)->radius;
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
					}
					cout << "Czy chcesz zmienic wysokosc obiektu? Wpisz 'tak' lub 'nie'" << endl;
					getline(cin, option);
					if(option == "tak"){
						cout << "Wpisz nowa wysokosc: ";
						cin >> (*i)->height;
					}
					cout << "Dokonano zmian w obiekcie." << endl;
				}
			if(!found)
				cout << "Nie istnieje obiekt o podanej nazwie." << endl;
		}
		else
			cout << "Lista jest pusta." << endl;
	}

	void showlist() {					//metoda wyswietla nazwy obiektow w liscie
		if(!list_ob.empty()){
			cout << "Wezel: " << obj_name << endl;
			for(vector<Cylinder*>::iterator i = list_ob.begin(); i < list_ob.end(); i++)
				cout << "\tNazwa obiektu: " << (*i)->obj_name << endl;
		}
		else
			cout << "Lista jest pusta." << endl;
	}

	void showinfo(string name) {		//metoda wyswietla szczegolowe o danym obiekcie
		if(!list_ob.empty()){
			bool found = false;
			for(vector<Cylinder*>::iterator i = list_ob.begin(); i < list_ob.end(); i++)
				if((*i)->obj_name == name){
					found = true;
					cout << "Nazwa obiektu: " << (*i)->obj_name << endl;
					(*i)->showvolume();
					cout << "Dlugosc promienia: " << (*i)->radius << endl << "Wysokosc: " << (*i)->height << endl;
				}
				if(!found)
					cout << "Nie istnieje obiekt o podanej nazwie." << endl;
		}
		else
			cout << "Lista jest pusta." << endl;
	}

	void save(const char* filename) {
		ofstream file(filename, ios::out | ios::app);
		if(file.good()){
			if(!list_ob.empty()){
				file << "C" << endl;
				file << list_ob.size() << endl;
				for(vector<Cylinder*>::iterator i = list_ob.begin(); i < list_ob.end(); i++){
					file << (*i)->obj_name << endl;
					file << (*i)->radius << endl;
					file << (*i)->height << endl;
				}
				file.close();
			}
		}
		else
			cout << "Blad przy otwieraniu pliku!" << endl;
	}

	void read(const char* filename) {
		fstream file(filename, ios::in);
		if(file.good()){
			string leaf;
			do file >> leaf;
			while(leaf != "C" && !file.eof());
			if(leaf == "C"){
				string name;
				int counter, r, h;
				file >> counter;
				for(int i = 0; i < counter; i++){
					file >> name;
					file >> r;
					file >> h;
					Cylinder *ptrCylinder = new Cylinder(name, r, h);
					list_ob.push_back(ptrCylinder);
				}
			}
		}
		else
			cout << "Blad przy otwieraniu pliku!" << endl;
	}

	void showname() {
		cout << obj_name << endl;
	}
};

class Sphere : public SolidOfRevolution {			//klasa kula; dziedziczy po brylach obrotowych
	string obj_name;
	int radius;
protected:
	double volume() {
		return (4.0 * 3.14 * radius * radius * radius)/3.0;
	}
public:
	Sphere() {
		obj_name = "Sphere";
		leaf = true;
	}
	Sphere(string name, int r): obj_name(name), radius(r) {}
	~Sphere() {}
	vector<Sphere*> list_ob;

	void addObj(string name) {					//dodawanie obiektu
	    int r;
		cout << "Podaj dlugosc promienia: ";
		cin >> r;
		Sphere *ptrSphere = new Sphere(name, r);
		list_ob.push_back(ptrSphere);
		cout << "Dodano obiekt." << endl;
	}

	void deleteObj(string name) {				//usuwanie obiektu
		if(!list_ob.empty()){
			bool found = false;
			for(vector<Sphere*>::iterator i = list_ob.begin(); i < list_ob.end(); i++){
				if((*i)->obj_name == name){
					found = true;
					delete *i;
					list_ob.erase(i);
					cout << "Usunieto obiekt." << endl;
				}
			}
			if(!found)
				cout << "Nie istnieje obiekt o podanej nazwie." << endl;
		}
		else
			cout << "Lista jest pusta." << endl;
	}

	void changeObj(string name) {				//modyfikacja obiektu
		if(!list_ob.empty()){
			string option;
			bool found = false;
			for(vector<Sphere*>::iterator i = list_ob.begin(); i < list_ob.end(); i++)
				if((*i)->obj_name == name){
					found = true;
					cout << "Czy chcesz zmienic nazwe obiektu? Wpisz 'tak' lub 'nie'" << endl;
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					getline(cin, option);
					if(option == "tak"){
						cout << "Wpisz nowa nazwe: ";
						getline(cin, (*i)->obj_name);
					}
					cout << "Czy chcesz zmienic dlugosc promienia obiektu? Wpisz 'tak' lub 'nie'" << endl;
					getline(cin, option);
					if(option == "tak"){
						cout << "Wpisz nowa dlugosc: ";
						cin >> (*i)->radius;
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
					}
					cout << "Dokonano zmian w obiekcie." << endl;
				}
			if(!found)
				cout << "Nie istnieje obiekt o podanej nazwie." << endl;
		}
		else
			cout << "Lista jest pusta." << endl;
	}

	void showlist() {					//metoda wyswietla nazwy obiektow w liscie
		if(!list_ob.empty()){
			cout << "Wezel: " << obj_name << endl;
			for(vector<Sphere*>::iterator i = list_ob.begin(); i < list_ob.end(); i++)
				cout << "\tNazwa obiektu: " << (*i)->obj_name << endl;
		}
		else
			cout << "Lista jest pusta." << endl;
	}

	void showinfo(string name) {		//metoda wyswietla szczegolowe o danym obiekcie
		if(!list_ob.empty()){
			bool found = false;
			for(vector<Sphere*>::iterator i = list_ob.begin(); i < list_ob.end(); i++)
				if((*i)->obj_name == name){
					found = true;
					cout << "Nazwa obiektu: " << (*i)->obj_name << endl;
					(*i)->showvolume();
					cout << "Dlugosc promienia: " << (*i)->radius << endl;
				}
				if(!found)
					cout << "Nie istnieje obiekt o podanej nazwie." << endl;
		}
		else
			cout << "Lista jest pusta." << endl;
	}

	void save(const char* filename) {
		fstream file(filename, ios::out | ios::app);
		if(file.good()){
			if(!list_ob.empty()){
				file << "S" << endl;
				file << list_ob.size() << endl;
				for(vector<Sphere*>::iterator i = list_ob.begin(); i < list_ob.end(); i++){
					file << (*i)->obj_name << endl;
					file << (*i)->radius << endl;
				}
				file.close();
			}
		}
		else
			cout << "Blad przy otwieraniu pliku!" << endl;
	}

	void read(const char* filename) {
		fstream file(filename, ios::in);
		if(file.good()){
			string leaf;
			do file >> leaf;
			while(leaf != "S" && !file.eof());
			if(leaf == "S"){
				string name;
				int counter, r;
				file >> counter;
				for(int i = 0; i < counter; i++){
					file >> name;
					file >> r;
					Sphere *ptrSphere = new Sphere(name, r);
					list_ob.push_back(ptrSphere);
				}
			}
		}
		else
			cout << "Blad przy otwieraniu pliku!" << endl;
	}

	void showname(){
		cout << obj_name << endl;
	}
};

class RightPrism : public Prism {				//klasa graniastoslup prosty (klasa abstrakcyjna); dziedziczy po graniastoslupie
	string obj_name;
	int a, b, c;								//przyjmujemy, ze jest to prostopadloscian
protected:
	virtual double volume() { return 0; }
public:
	RightPrism() {
		obj_name = "RightPrism";
		leaf = false;
	}
	~RightPrism() {}

	virtual void showname(){
		cout << obj_name << endl;
	}

	string name(){
		return obj_name;
	}
};

class ObliquePrism : public Prism {				//klasa graniastoslup pochyly; dziedziczy po graniastoslupie
	string obj_name;
	int a, b, c;
protected:
	double volume() {							//przyjmujemy, ze kat miedzy a c jest rowny 60 stopni
		return a * b * c/2.0 * 1.73;
	}
public:
	ObliquePrism() {
		obj_name = "ObliquePrism";
		leaf = true;
	}
	ObliquePrism(string name, int edge1, int edge2, int edge3): obj_name(name), a(edge1), b(edge2), c(edge3) {}
	~ObliquePrism() {}
	vector<ObliquePrism*> list_ob;

	void addObj(string name) {					//dodawanie obiektu
	    int edge1, edge2, edge3;
		cout << "Podaj dlugosc krawedzi jednego boku: ";
		cin >> edge1;
		cout << "Podaj dlugosc krawedzi drugiego boku: ";
		cin >> edge2;
		cout << "Podaj dlugosc krawedzi trzeciego boku: ";
		cin >> edge3;
		ObliquePrism *ptrObliquePrism = new ObliquePrism(name, edge1, edge2, edge3);
		list_ob.push_back(ptrObliquePrism);
		cout << "Dodano obiekt." << endl;
	}

	void deleteObj(string name) {				//usuwanie obiektu
		if(!list_ob.empty()){
			bool found = false;
			for(vector<ObliquePrism*>::iterator i = list_ob.begin(); i < list_ob.end(); i++){
				if((*i)->obj_name == name){
					found = true;
					delete *i;
					list_ob.erase(i);
					cout << "Usunieto obiekt." << endl;
				}
			}
			if(!found)
				cout << "Nie istnieje obiekt o podanej nazwie." << endl;
		}
		else
			cout << "Lista jest pusta." << endl;
	}

	void changeObj(string name) {				//modyfikacja obiektu
		if(!list_ob.empty()){
			string option;
			bool found = false;
			for(vector<ObliquePrism*>::iterator i = list_ob.begin(); i < list_ob.end(); i++)
				if((*i)->obj_name == name){
					found = true;
					cout << "Czy chcesz zmienic nazwe obiektu? Wpisz 'tak' lub 'nie'" << endl;
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					getline(cin, option);
					if(option == "tak"){
						cout << "Wpisz nowa nazwe: ";
						getline(cin, (*i)->obj_name);
					}
					cout << "Czy chcesz zmienic dlugosc krawedzi boku obiektu? Wpisz 'tak' lub 'nie'" << endl;
					getline(cin, option);
					if(option == "tak"){
						cout << "Wpisz nowa dlugosc: ";
						cin >> (*i)->a;
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
					}
					cout << "Czy chcesz zmienic dlugosc krawedzi kolejnego boku obiektu? Wpisz 'tak' lub 'nie'" << endl;
					getline(cin, option);
					if(option == "tak"){
						cout << "Wpisz nowa dlugosc: ";
						cin >> (*i)->b;
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
					}
					cout << "Czy chcesz zmienic dlugosc krawedzi kolejnego boku obiektu? Wpisz 'tak' lub 'nie'" << endl;
					getline(cin, option);
					if(option == "tak"){
						cout << "Wpisz nowa dlugosc: ";
						cin >> (*i)->c;
					}
					cout << "Dokonano zmian w obiekcie." << endl;
				}
			if(!found)
				cout << "Nie istnieje obiekt o podanej nazwie." << endl;
		}
		else
			cout << "Lista jest pusta." << endl;
	}

	void showlist() {					//metoda wyswietla nazwy obiektow w liscie
		if(!list_ob.empty()){
			cout << "Wezel: " << obj_name << endl;
			for(vector<ObliquePrism*>::iterator i = list_ob.begin(); i < list_ob.end(); i++)
				cout << "\tNazwa obiektu: " << (*i)->obj_name << endl;
		}
		else
			cout << "Lista jest pusta." << endl;
	}

	void showinfo(string name) {		//metoda wyswietla szczegolowe o danym obiekcie
		if(!list_ob.empty()){
			bool found = false;
			for(vector<ObliquePrism*>::iterator i = list_ob.begin(); i < list_ob.end(); i++)
				if((*i)->obj_name == name){
					found = true;
					cout << "Nazwa obiektu: " << (*i)->obj_name << endl;
					(*i)->showvolume();
					cout << "Dlugosc krawedzi jednego boku: " << (*i)->a << endl << "Dlugosc krawedzi drugiego boku: " << (*i)->b << endl << "Dlugosc krawedzi trzeciego boku: " << (*i)->c << endl;
				}
				if(!found)
					cout << "Nie istnieje obiekt o podanej nazwie." << endl;
		}
		else
			cout << "Lista jest pusta." << endl;
	}

	void save(const char* filename) {
		fstream file(filename, ios::out | ios::app);
		if(file.good()){
			if(!list_ob.empty()){
				file << "O" << endl;
				file << list_ob.size() << endl;
				for(vector<ObliquePrism*>::iterator i = list_ob.begin(); i < list_ob.end(); i++){
					file << (*i)->obj_name << endl;
					file << (*i)->a << endl;
					file << (*i)->b << endl;
					file << (*i)->c << endl;
				}
				file.close();
			}
		}
		else
			cout << "Blad przy otwieraniu pliku!" << endl;
	}

	void read(const char* filename) {
		fstream file(filename, ios::in);
		if(file.good()){
			string leaf;
			do file >> leaf;
			while(leaf != "O" && !file.eof());
			if(leaf == "O"){
				string name;
				int counter, edge1, edge2, edge3;
				file >> counter;
				for(int i = 0; i < counter; i++){
					file >> name;
					file >> edge1;
					file >> edge2;
					file >> edge3;
					ObliquePrism *ptrObliquePrism = new ObliquePrism(name, edge1, edge2, edge3);
					list_ob.push_back(ptrObliquePrism);
				}
			}
		}
		else
			cout << "Blad przy otwieraniu pliku!" << endl;
	}

	void showname(){
		cout << obj_name << endl;
	}
};

class RegularPrism : public RightPrism {		//klasa graniastoslup prawidlowy
	string obj_name;
	int a, h;									//przyjmujemy, ze w podstawie jest kwadrat
protected:
	double volume() {
		return a * a * h;
	}
public:
	RegularPrism() {
		obj_name = "RegularPrism";
		leaf = true;
	}
	RegularPrism(string name, int edge, int height): obj_name(name), a(edge), h(height) {}
	~RegularPrism() {}
	vector<RegularPrism*> list_ob;

	void addObj(string name) {					//dodawanie obiektu
	    int edge, height;
		cout << "Podaj dlugosc krawedzi podstawy: ";
		cin >> edge;
		cout << "Podaj wysokosc: ";
		cin >> height;
		RegularPrism *ptrRegularPrism = new RegularPrism(name, edge, height);
		list_ob.push_back(ptrRegularPrism);
		cout << "Dodano obiekt." << endl;
	}

	void deleteObj(string name) {				//usuwanie obiektu
		if(!list_ob.empty()){
			bool found = false;
			for(vector<RegularPrism*>::iterator i = list_ob.begin(); i < list_ob.end(); i++){
				if((*i)->obj_name == name){
					found = true;
					delete *i;
					list_ob.erase(i);
					cout << "Usunieto obiekt." << endl;
				}
			}
			if(!found)
				cout << "Nie istnieje obiekt o podanej nazwie." << endl;
		}
		else
			cout << "Lista jest pusta." << endl;
	}

	void changeObj(string name) {				//modyfikacja obiektu
		if(!list_ob.empty()){
			string option;
			bool found = false;
			for(vector<RegularPrism*>::iterator i = list_ob.begin(); i < list_ob.end(); i++)
				if((*i)->obj_name == name){
					found = true;
					cout << "Czy chcesz zmienic nazwe obiektu? Wpisz 'tak' lub 'nie'" << endl;
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					getline(cin, option);
					if(option == "tak"){
						cout << "Wpisz nowa nazwe: ";
						getline(cin, (*i)->obj_name);
					}
					cout << "Czy chcesz zmienic dlugosc krawedzi podstawy obiektu? Wpisz 'tak' lub 'nie'" << endl;
					getline(cin, option);
					if(option == "tak"){
						cout << "Wpisz nowa dlugosc: ";
						cin >> (*i)->a;
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
					}
					cout << "Czy chcesz zmienic wysokosc obiektu? Wpisz 'tak' lub 'nie'" << endl;
					getline(cin, option);
					if(option == "tak"){
						cout << "Wpisz nowa wysokosc: ";
						cin >> (*i)->h;
					}
					cout << "Dokonano zmian w obiekcie." << endl;
				}
			if(!found)
				cout << "Nie istnieje obiekt o podanej nazwie." << endl;
		}
		else
			cout << "Lista jest pusta." << endl;
	}

	void showlist() {					//metoda wyswietla nazwy obiektow w liscie
		if(!list_ob.empty()){
			cout << "Wezel: " << obj_name << endl;
			for(vector<RegularPrism*>::iterator i = list_ob.begin(); i < list_ob.end(); i++)
				cout << "\tNazwa obiektu: " << (*i)->obj_name << endl;
		}
		else
			cout << "Lista jest pusta." << endl;
	}

	void showinfo(string name) {		//metoda wyswietla szczegolowe o danym obiekcie
		if(!list_ob.empty()){
			bool found = false;
			for(vector<RegularPrism*>::iterator i = list_ob.begin(); i < list_ob.end(); i++)
				if((*i)->obj_name == name){
					found = true;
					cout << "Nazwa obiektu: " << (*i)->obj_name << endl;
					(*i)->showvolume();
					cout << "Dlugosc krawedzi podstawy: " << (*i)->a << endl << "Wysokosc: " << (*i)->h << endl;
				}
				if(!found)
					cout << "Nie istnieje obiekt o podanej nazwie." << endl;
		}
		else
			cout << "Lista jest pusta." << endl;
	}

	void save(const char* filename) {
		fstream file(filename, ios::out | ios::app);
		if(file.good()){
			if(!list_ob.empty()){
				file << "R" << endl;
				file << list_ob.size() << endl;
				for(vector<RegularPrism*>::iterator i = list_ob.begin(); i < list_ob.end(); i++){
					file << (*i)->obj_name << endl;
					file << (*i)->a << endl;
					file << (*i)->h << endl;
				}
				file.close();
			}
		}
		else
			cout << "Blad przy otwieraniu pliku!" << endl;
	}

	void read(const char* filename) {
		fstream file(filename, ios::in);
		if(file.good()){
			string leaf;
			do file >> leaf;
			while(leaf != "R" && !file.eof());
			if(leaf == "R"){
				string name;
				int counter, edge, height;
				file >> counter;
				for(int i = 0; i < counter; i++){
					file >> name;
					file >> edge;
					file >> height;
					RegularPrism *ptrRegularPrism = new RegularPrism(name, edge, height);
					list_ob.push_back(ptrRegularPrism);
				}
			}
		}
		else
			cout << "Blad przy otwieraniu pliku!" << endl;
	}

	void showname(){
		cout << obj_name << endl;
	}
};

#endif // CLASSES_H_INCLUDED
