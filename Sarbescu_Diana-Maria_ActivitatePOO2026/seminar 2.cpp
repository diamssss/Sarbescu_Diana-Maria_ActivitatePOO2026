#include <iostream>
using namespace std;
struct Cladire
{
	char* culoare;
	float inaltime;
	int nrEtaje;
	bool deschis;

};
//functie care citeste o cladire:
Cladire citireCladire() //e "Cladire" si nu "void" pt ca tipul de data returnata este de tip cladire nu void mmmyes
{
	Cladire c;
	char x[100];//ocupa 100 de octeti, e situat pe stackul fctiei "Cladire" (nu pe hip, pt ca e static)
	cout << "Culoare: "; cin >> x;
	c.culoare = new char[strlen(x) + 1];
	strcpy_s(c.culoare, strlen(x) + 1, x); //strcpy(destinatia, sursa)
	cout << "\nInaltime: "; cin >> c.inaltime;
	cout << "\nNrEtaje: "; cin >> c.nrEtaje;
	cout << "\nDeschis (0/1): "; cin >> c.deschis;
	return c; //pt ca avem 2 stive de memorie
}
void modificareNrEtaje(int noulNrEtaje, Cladire* c)
{
	(*c).nrEtaje = noulNrEtaje;//in memorie se sterge val veche, si se schimba cu altcv sau cv de genu de asemene deferentiez cu *
}
void modificNrEtajePrinReferinta(int noulNrEtaje, Cladire& c)
{
	c.nrEtaje = noulNrEtaje;
}

//functia de afisare;
void afisareCladire(Cladire c)
{
	cout << "Culoarea: " << c.culoare;
	cout << "\nInaltimea: " << c.inaltime;
	cout << "\nNr etaje: " << c.nrEtaje;
	cout << "\nDeschisa: " << c.deschis;
}

void main()
{
	Cladire c = citireCladire();
	afisareCladire(c);
	modificareNrEtaje(20, &c);
	afisareCladire(c);
	modificNrEtajePrinReferinta(21, c);
	afisareCladire(c);
	/*char* vectorC;
	vectorC = new char[strlen("POO") + 1];
	strcpy_s(vectorC, strlen("POO") + 1, "POO");

	Cladire c;
	int nrCladiri=5;
	Cladire* clairi;
	cladiri = new Cladire[nrCladiri + 1];*/
	//cladiri=(Cladire*)malloc(sizeof(Cladire)*nrCladiri)
}
