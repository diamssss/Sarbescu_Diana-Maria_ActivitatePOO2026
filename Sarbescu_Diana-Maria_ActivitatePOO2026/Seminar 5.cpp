//#define _CRT_SECURE_NO_WARNINGS
//#include<iostream>
//
//using namespace std;
//
//class Prajitura {
//private:
//	char* denumire;
//	float pret;
//	int cantitate;
//	bool dePost;
//	int nrIngrediente;
//	string* ingrediente;
//	const int id;
//	static int contor;//static adica nu apartine obiectului, apartine clasei
//public:
//	friend class Student;
//#pragma region Constructori
//	Prajitura(): id(contor++)
//	{
//		this->denumire = new char[strlen("Tiramisu")+1];
//		strcpy(denumire, "Tiramisu");
//		this->pret = 15;
//		this->cantitate = 250;
//		this->dePost = true;
//		this->nrIngrediente = 3;
//		this->ingrediente = new string[this->nrIngrediente];
//		this->ingrediente[0] = "piscoturi";
//		this->ingrediente[1] = "vanilie";
//		this->ingrediente[2] = "cafea";
//	}
//	Prajitura(const char*denumire,float pret): id(contor++)
//	{
//		this->denumire = new char[strlen(denumire) + 1];
//		strcpy(this->denumire, denumire);
//		this->pret = pret;
//		this->cantitate = 250;
//		this->dePost = true;
//		this->nrIngrediente = 3;
//		this->ingrediente = new string[this->nrIngrediente];
//		this->ingrediente[0] = "piscoturi";
//		this->ingrediente[1] = "vanilie";
//		this->ingrediente[2] = "cafea";
//
//	}
//	Prajitura(const Prajitura& p): id(contor++)
//	{
//		this->denumire = new char[strlen(p.denumire) + 1];
//		strcpy(this->denumire, p.denumire);
//
//		this -> pret = p.pret;
//		this->cantitate = p.cantitate;
//		this->dePost = p.dePost;
//		this->nrIngrediente = p.nrIngrediente;
//
//		this->ingrediente = new string[this->nrIngrediente];
//		for (int i= 0;i < this->nrIngrediente;i++)
//		{
//			this->ingrediente[i] = p.ingrediente[i];
//		}
//	}
//
//	~Prajitura();//declarare destructor
//	Prajitura& operator = (const Prajitura& p1)
//	{
//		if (this != &p1)
//		{
//			this->cantitate = p1.cantitate;
//
//			if (this->denumire != NULL)
//			{
//				delete[] this->denumire;
//			}
//			this->denumire = new char[strlen(p1.denumire) + 1];
//			strcpy(this->denumire, p1.denumire);
//			this->dePost = p1.dePost;
//			this->pret = p1.pret;
//			this->nrIngrediente = p1.nrIngrediente;
//			if (this->ingrediente != NULL)
//			{
//				delete[]this->ingrediente;
//			}
//			this->ingrediente = new string[this->nrIngrediente];
//			for (int i = 0; i < p1.nrIngrediente; i++)
//			{
//				this->ingrediente[i] = p1.ingrediente[i];
//			}
//		}
//		return *this;
//	}
//	
//#pragma endregion
//
//#pragma region geteri si seteri
//	int getCantitate()
//	{
//		return this->cantitate;
//	}
//
//	float getPret()
//	{
//		return this->pret;
//	}
//
//	int getNrIngrediente()
//	{
//		return this->nrIngrediente;
//	}
//
//	static int getContor()
//	{
//		return contor;
//	}
//#pragma endregion
//	Prajitura operator+(const Prajitura& p)
//	{
//		Prajitura result = *this;
//		result.pret = this->pret + p.pret;
//		result.cantitate = this->cantitate + p.cantitate;
//		return result;
//	}
//	void afisare()
//{
//		cout << "Denumire: " << this->denumire << endl;
//		cout << "Pret: " << this->pret << endl;
//		cout << "Cantitate: " << this->cantitate<< endl;
//		cout << "De Post: " << (this->dePost ? "DA" : "NU") << endl;
//		cout << "Nr ingrediente: " << this->nrIngrediente << endl;
//		cout << "Ingredientele sunt: ";
//		for (int i = 0;i < this->nrIngrediente;i++)
//		{
//			cout << this->ingrediente[i] << "; ";
//		}
//		cout << endl;
//	}
//	float costMediuGram() {
//		if (this->cantitate == 0) {
//			return 0;
//		}
//		else {
//			return this->pret / this->cantitate;
//		}
//	}
//
//	void modificaDenumire(const char* denumire) {
//		delete this->denumire;
//
//		this->denumire = new char[strlen(denumire) + 1];
//		strcpy(this->denumire, denumire);
//	}
//
//
//};
//int Prajitura::contor = 100;
//
//Prajitura::~Prajitura()//implementare destructor
//{
//	if (this->denumire != NULL) delete[]this->denumire;
//	if (this->ingrediente != NULL)delete[]this->ingrediente;
//}
//
//float calculeazaCantitateTotala(Prajitura* prajituri, int nr_prajituri) {
//	float greutate = 0;
//
//	for (int p = 0; p < nr_prajituri; p++)
//		greutate += prajituri[p].getCantitate();
//
//	return greutate;
//}
//
//float calculeazaPretPerIngredient(Prajitura p)
//{
//	if (p.getNrIngrediente() != 0)
//		return p.getPret() / p.getNrIngrediente();
//	return 0;
//}
//
//class Student
//{
//private:
//	string nume;
//	Prajitura prajitura;
//public:
//	Student()
//	{
//		this->nume = "Andrei";
//	}
//	Student(string nume, Prajitura p)
//	{
//		this->nume = nume;
//		this->prajitura = p;
//	}
//	string getNume()
//	{
//		return this->nume;
//	}
//	Prajitura getPrajitura()
//	{
//		return this->prajitura;
//	}
//	void setNume(string nume)
//	{
//		this->nume = nume;
//	}
//	void setPrajitura(Prajitura p)
//	{
//		this->prajitura = p;
//	}
//	float calculeazaNrTotalCalorii(float CaloriiPerGram)
//	{
//		float nrTotal = CaloriiPerGram * this->prajitura.getCantitate();
//		return nrTotal;
//	}
//	void afisazaMasa()
//	{
//		cout << this->nume << " mananca prajitura: " << this->prajitura.denumire << endl;
//	}
//};
//
//void main() {
//	Prajitura p;
//	p.afisare();
//	//Prajitura* pp;
//	//(*pp).afisare(); //sau pp->afisare();
//	Prajitura::getContor();
//	Prajitura p1("Amandina", 20);
//	Student s1("Cristian", p1);
//	s1.afisazaMasa();
//	cout << s1.calculeazaNrTotalCalorii(0.5) <<" cal"<< endl;
//
//	//cout << calculeazaPretPerIngredient(p);
//
//}