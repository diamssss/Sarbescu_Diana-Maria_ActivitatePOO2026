/*#include <iostream>
#include <cstring>
class Telecomanda
{
	private:
		const int id;
		static int contor;
		const int nrButoane;
		char* culoare;
	public:
		Telecomanda():nrButoane(10), culoare(NULL), id (contor++)
		{
			//this->nrButoane = 10;
			//this->culoare = new char[strlen(culoare + 1];
			//strcpy(this->culoare, culoare);
		}
		Telecomanda(int nr, const char* culoare):nrButoane(nr), id(contor++)
		{
			this->nrButoane = 10;
			this->culoare = new char[strlen(culoare) + 1];
			strcpy(this->culoare, culoare);
		}
		Telecomanda(const Telecomanda& t):nrButoane(t.nrButoane), id(contor++)
		{
			this->nrButoane = t.nrButoane;
			this->culoare = new char[strlen(t.culoare) + 1];
			strcpy(this->culoare, t.culoare);
		}
		~Telecomanda()
		{
			if (this->culoare != NULL)
			{
				delete[]this->culoare;
			}
		}
		int getNrButoane() const
		{
			this->nrButoane = 7;
			return this->nrButoane;

		}
		void setNrButoane(int nr)
		{
			this->nrButoane = nr;
		}
		void setCuloare(const char* culoare)
		{
			if (this->culoare != NULL)
			{
				delete[]this->culoare;
			}
			this->culoare = new char[strlen(culoare) + 1]
				strcpy(this->culoare, culoare);
		}
		{

		}
		int metoda()
		{
			return 6;
		}
		static int functie()
		{
			return contor;
		}
};
int Telecomanda::contor = 0;

int main()
{
	std::cout << Telecomanda::functie();

	Telecomanda t(25, "neagra");

	t.setNrButoane(56);
	std::cout << t.getNrButoane();
	Telecomanda t1(t);
	{
		Telecomanda t2 = t;
	}
	t.metoda();
	t1.metoda();
	std::cout << t.contor;
	return 0;
}*/