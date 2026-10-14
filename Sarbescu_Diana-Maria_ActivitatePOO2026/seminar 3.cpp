#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

class Prajitura
{
	public:
		char* denumire;
		float pret;
		int cantitate;
		bool dePost;
		int nrIngrediente;
		string* ingrediente;
		//const int id;
		Prajitura() //constructorul intializeaza cu valori
		{
			this->denumire = new char[strlen("Tiramisu") + 1];//new deja face adresa si nu mai are nev de * char
			strcpy(this->denumire, "Tiramisu");
			this->pret = 15;
			this->cantitate = 250;
			this->dePost = true;
			this->nrIngrediente = 4;
			//alocam dinamic
			this->ingrediente = new string[this->nrIngrediente];
			//nu mai folosim strcpy, folosim operatorul =
			this->ingrediente[0] = "piscoturi";
			this->ingrediente[1] = "vanilie";
			this->ingrediente[2] = "cafea";
			
		}
		Prajitura(const char*denumire, float pret) 
		{
			this->denumire = new char[strlen(denumire) + 1];
			strcpy(this->denumire, denumire);
			this->pret = 15;
			this->cantitate = 250;
			this->dePost = true;
			this->nrIngrediente = 4;
			//alocam dinamic
			this->ingrediente = new string[this->nrIngrediente];
			//nu mai folosim strcpy, folosim operatorul =
			this->ingrediente[0] = "piscoturi";
			this->ingrediente[1] = "vanilie";
			this->ingrediente[2] = "cafea";
		}
		void afisare()
		{
			cout << "Denumire: " << this->denumire << endl;
			cout << "Pret: " << this->pret << endl;
			cout << "Cantitate: " << this->cantitate << endl;
			cout << "De post: " << (this->dePost ? "Da" : "Nu") << endl;
			cout << "Nr ingrediente: " << this->nrIngrediente << endl;
			cout << "Ingrediente: ";
			for (int i = 0 ; i < this->nrIngrediente ; i++)
			{
				cout << this->ingrediente[i] << ", ";
			}
			cout << endl;
		}
		float costMediuGram()
		{
			if (this->cantitate == 0)
			{
				return 0;
			}
			else
			{
				return this->pret / this->cantitate;
			}
		}
		void modificaDenumire(const char* denumire)
		{
			delete this->denumire;
			this->denumire = new char[strlen(denumire) + 1];
			strcpy(this->denumire, denumire);
		}

};
float calcCantitateaTotala(Prajitura* prajituri, int nrPrajituri)
{
	float greutate = 0;
	for (int p = 0;p < nrPrajituri;p++)
	{
		greutate += prajituri[p].cantitate;
	}
}

void main()
{
	Prajitura p;
	p.afisare();
	Prajitura p2("Amandina", 40);
	p2.afisare();
	cout<<"Cost mediu per gram: "<<p.costMediuGram()<<endl;
	//vector alocat dinamic
	Prajitura* prajituri;
	prajituri = new Prajitura[3];
	prajituri[2].afisare();
	prajituri[1].pret = 50;
	prajituri[2].cantitate = 70;

	prajituri[0].modificaDenumire("Tort");
	prajituri[1].modificaDenumire("Ecler");
	for (int i = 0;i < 3;i++)
	{
		//cout << prajituri[i].costMediuGram << endl;
		cout << prajituri[i].denumire<<' '<<prajituri[i].costMediuGram() << endl;
	}
	float greutateTotala = calcCantitateaTotala(prajituri, 3);
	cout<<"Total: "<<greutateTotala<<endl;
}