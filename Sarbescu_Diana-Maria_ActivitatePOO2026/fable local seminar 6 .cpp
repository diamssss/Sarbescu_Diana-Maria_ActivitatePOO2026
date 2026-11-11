// --------------------------------------------------------------------------
// NOTIUNI DE BAZA
// --------------------------------------------------------------------------
//
// 1. MEMORIA
//    Memoria calculatorului este un sir foarte lung de casute.
//    Fiecare casuta tine 1 octet (byte).
//    Fiecare casuta are un numar. Numarul ei se numeste ADRESA.
//
// 2. VARIABILA
//    O variabila este un nume dat unor casute.
//    int x = 5;  -> compilatorul rezerva 4 casute, le numeste x, pune 5 in ele.
//
// 3. CELE DOUA ZONE DE MEMORIE
//    STIVA (stack):
//      - automata.
//      - Variabilele declarate normal intr-o functie stau aici.
//        Exemple: int x;   Prajitura p;
//      - Cand programul ajunge la acolada } care inchide blocul,
//        ele dispar singure. Tu nu faci nimic.
//    HEAP:
//      - manuala.
//      - Ceri memorie cu new. Memoria ramane acolo pana o eliberezi cu delete.
//      - Daca uiti delete: memoria ramane ocupata degeaba. Se numeste
//        MEMORY LEAK (scurgere de memorie).
//      - Daca faci delete de doua ori pe acelasi bloc: DOUBLE FREE. Programul
//        se poate prabusi.
//
// 4. POINTER
//    Un pointer este o variabila care tine o ADRESA, nu o valoare.
//    char* p;  -> p tine adresa unui caracter.
//    Gandeste-te la un bilet pe care scrie "casa nr. 5000".
//    Biletul NU este casa. Daca rupi biletul, casa ramane.
//    Daca darami casa, biletul inca exista, dar arata spre ruine.
//
// 5. new SI delete
//    new char[9]   -> cere 9 casute in heap si iti da adresa primei casute.
//    delete[] p    -> da inapoi casutele de la adresa p.
//    Regula: new X      se pereche cu  delete
//            new X[n]   se pereche cu  delete[]   (cand e vector, cu paranteze)
//
// 6. REFERINTA (&)
//    O referinta este un al doilea nume pentru o variabila care exista deja.
//    NU este o copie. Ce faci prin referinta se face direct pe original.
//    int a = 5;  int& r = a;  r = 7;  -> acum si a este 7.
//
// 7. PRIN VALOARE vs PRIN REFERINTA (la parametrii functiilor)
//    void f(Prajitura p)              -> f primeste o COPIE. Se face o copie noua.
//    void f(Prajitura& p)             -> f lucreaza pe ORIGINAL.
//    void f(const Prajitura& p)       -> f lucreaza pe original, dar promite
//                                        ca nu il schimba. Nu se face copie.
//
// 8. COPIE SUPERFICIALA vs COPIE IN ADANCIME
//    Un obiect care are un pointer tine doar ADRESA datelor, nu datele.
//    Copie superficiala (shallow) = copiezi doar adresa:
//        A.denumire = 5000 --+
//                            +--> [ a m a n d i n a \0 ]   (un singur bloc)
//        B.denumire = 5000 --+
//      Problema: cand A dispare, sterge blocul. B arata acum spre memorie
//      eliberata. Cand B dispare, sterge iar acelasi bloc: DOUBLE FREE.
//    Copie in adancime (deep) = faci un bloc NOU si copiezi continutul:
//        A.denumire = 5000 ---> [ a m a n d i n a \0 ]
//        B.denumire = 9000 ---> [ a m a n d i n a \0 ]   (copie proprie)
//      Fiecare obiect isi sterge doar blocul lui. Nicio problema.
//
// 9. REGULA CELOR TREI
//    Daca o clasa are pointeri spre memorie din heap, are nevoie de toate trei:
//      - destructor            (sterge memoria cand obiectul dispare)
//      - constructor de copiere (copie in adancime la creare)
//      - operator=             (copie in adancime cand obiectul exista deja)
//    Clasa Prajitura le are pe toate trei. De aceea arata asa cum arata.
//==========================================================================
//
// LINIA DE MAI JOS: #define _CRT_SECURE_NO_WARNINGS
// - Liniile care incep cu # sunt pentru PREPROCESOR. Preprocesorul ruleaza
//   inainte de compilare si doar lipeste/inlocuieste text.
// - Visual Studio considera functia strcpy "nesigura" si refuza sa compileze.
//   Linia asta ii spune lui Visual Studio sa nu mai faca asta.
// - Trebuie pusa INAINTEA include-urilor, altfel nu are efect.
#define _CRT_SECURE_NO_WARNINGS
// #include<iostream>
// - Lipeste aici continutul bibliotecii iostream.
// - Iti da cout (afisare pe ecran) si endl (rand nou).
// - Pe Visual Studio, iostream aduce "din greseala" si string si strlen/strcpy.
//   Pe alte compilatoare (g++) ar trebui adaugate si <string> si <cstring>.
#include<iostream>

// using namespace std;
// - Tot ce vine din biblioteca standard sta intr-un "spatiu de nume" numit std.
// - Fara linia asta ai scrie std::cout, std::string, std::endl.
// - Cu ea poti scrie direct cout, string, endl.
using namespace std;

// ==========================================================================
// CLASA PRAJITURA
// ==========================================================================
// O CLASA este un plan de constructie, ca planul unei case.
// Un OBIECT este o casa construita dupa plan.
//   class Prajitura { ... };   -> planul
//   Prajitura p;               -> un obiect (o prajitura concreta)
// Fiecare obiect are propria copie a campurilor de mai jos
// (cu exceptia celor static, vezi contor).
class Prajitura {
	// private: tot ce urmeaza poate fi atins DOAR de functiile clasei.
	// Codul din afara (de exemplu main) nu poate scrie p.pret = -5;
	// Asta e rostul unei clase: nimeni din afara nu poate strica obiectul.
private:
	// char* denumire
	// - char = un caracter (o litera). Ocupa 1 octet.
	// - char* = POINTER la char = tine ADRESA unde incep literele.
	// - Literele propriu-zise NU stau in obiect. Stau in HEAP, create cu new.
	// - De ce pointer si nu char denumire[50]? Pentru ca numele poate avea orice
	//   lungime. Ceri exact cat iti trebuie.
	// - Pretul platit: tu trebuie sa faci new si delete. De aici vine toata
	//   complicatia cu destructorul si copierea.
	char* denumire;
	// float pret, int cantitate, bool dePost
	// - Valori simple. Stau CHIAR IN obiect, nu in heap.
	// - float = numar cu zecimale (20.6). int = numar intreg (250).
	//   bool = true sau false.
	// - Pentru ele nu trebuie new/delete. Se copiaza singure corect.
	float pret;
	int cantitate;
	bool dePost;
	// int nrIngrediente + string* ingrediente
	// - string* este un POINTER spre primul element al unui VECTOR de string-uri
	//   aflat in heap.
	// - Un pointer nu stie cate elemente are vectorul. De aceea tinem separat
	//   numarul lor in nrIngrediente.
	// - Desen:
	//     ingrediente = 7000 ---> [ "piscoturi" ][ "vanilie" ][ "cafea" ]
	//     nrIngrediente = 3
	int nrIngrediente;
	string* ingrediente;
	// const int id
	// - const = constant. Odata setat, nu se mai poate schimba niciodata.
	// - Un membru const poate primi valoare DOAR in lista de initializare a
	//   constructorului (partea cu : de dupa paranteze, vezi mai jos).
	const int id;
	// static int contor
	// - static = exista O SINGURA DATA pentru toata clasa, nu cate unul pentru
	//   fiecare obiect.
	// - Toate prajiturile vad acelasi contor. Il folosim ca sa dam fiecarei
	//   prajituri un id diferit: 100, 101, 102 ...
	// - Aici doar e DECLARAT. Spatiul real i se da mai jos, la linia
	//   int Prajitura::contor = 100;
	static int contor;
	// public: tot ce urmeaza poate fi folosit de oricine, inclusiv din main.
public:
	// #pragma region / #pragma endregion
	// - Doar pentru Visual Studio. Iti lasa sa strangi (fold) o bucata de cod
	//   in editor. Nu are niciun efect asupra programului.
#pragma region Constructori
	// friend class Student;
	// - Ii da clasei Student voie sa citeasca campurile PRIVATE ale prajiturii.
	// - Fara linia asta, Student nu ar putea scrie this->prajitura.denumire.
	// - Se foloseste mai jos, in Student::afiseazaMasa.
	friend class Student;
	// --------------------------------------------------------------------------
	// CONSTRUCTORUL IMPLICIT (fara parametri)
	// --------------------------------------------------------------------------
	// - Un CONSTRUCTOR este o functie care ruleaza AUTOMAT cand se creeaza un
	//   obiect. Are acelasi nume ca clasa si nu are tip de return.
	// - "Implicit" = fara parametri. Ruleaza la:  Prajitura p;
	// - :id(contor++) este LISTA DE INITIALIZARE.
	//     * Ruleaza INAINTE de corpul { }.
	//     * Este singurul loc unde un membru const (id) poate primi valoare.
	//     * contor++ = "post-incrementare": da valoarea curenta, APOI creste cu 1.
	//       Daca contor era 100: id primeste 100, contor devine 101.
	Prajitura() :id(contor++) {
		// this->denumire = new char[strlen("Tiramisu")+1];
		// - this = un pointer spre obiectul curent (prajitura care se construieste).
		//   this->denumire = campul denumire al ACESTUI obiect.
		// - strlen("Tiramisu") = numara literele = 8.
		// - +1 pentru caracterul '\0'. Un sir de caractere in stil C se termina
		//   mereu cu '\0'. Asa stie programul unde se opreste textul.
		//   Fara +1 nu ar fi loc pentru '\0' si textul ar "curge" in memoria altcuiva.
		// - new char[9] = cere 9 casute in HEAP si intoarce adresa primei.
		// - Adresa se salveaza in denumire. Memoria arata acum asa:
		//     p (pe stiva)                     heap
		//     denumire = 5000  ------------>  [ ? ? ? ? ? ? ? ? ? ]   (inca gol)
		this->denumire = new char[strlen("Tiramisu") + 1];
		// strcpy(denumire, "Tiramisu");
		// - strcpy = string copy. Copiaza literele, plus '\0', la adresa denumire.
		//     denumire = 5000  ------------>  [ T i r a m i s u \0 ]
		// - De ce nu denumire = "Tiramisu"? Pentru ca asta ar copia doar o adresa
		//   (a textului fix din program), nu literele. Iar blocul de la new s-ar pierde.
		strcpy(denumire, "Tiramisu");
		// Campurile simple primesc valori direct. Nu e nevoie de new.
		this->pret = 15;
		this->cantitate = 250;
		this->dePost = true;
		this->nrIngrediente = 3;
		// this->ingrediente = new string[this->nrIngrediente];
		// - new string[3] = cere in HEAP un vector de 3 string-uri goale.
		// - Adresa primului se pune in ingrediente.
		//     ingrediente = 7000 ---> [ "" ][ "" ][ "" ]
		this->ingrediente = new string[this->nrIngrediente];
		// ingrediente[0], [1], [2] = completam fiecare casuta din vector.
		// - Indexarea incepe de la 0. Un vector de 3 are pozitiile 0, 1, 2.
		//     ingrediente = 7000 ---> [ "piscoturi" ][ "vanilie" ][ "cafea" ]
		this->ingrediente[0] = "piscoturi";
		this->ingrediente[1] = "vanilie";
		this->ingrediente[2] = "cafea";
	}
	// --------------------------------------------------------------------------
	// CONSTRUCTORUL CU PARAMETRI (nume si pret)
	// --------------------------------------------------------------------------
	// - Ruleaza la:  Prajitura P1("amandina", 20.6);
	// - const char* denumire = adresa unui text pe care NU il modificam (const).
	// - Aceeasi idee ca la constructorul implicit.
	// - Atentie la nume: parametrul se numeste denumire, la fel ca membrul.
	//     * In functie, "denumire" simplu = PARAMETRUL (cel mai apropiat nume).
	//     * "this->denumire" = MEMBRUL obiectului.
	//   De aceea aici this-> este obligatoriu. Fara el ai scrie peste parametru.
	Prajitura(const char* denumire, float pret) :id(contor++) {
		// strlen(denumire) aici masoara textul primit ca parametru ("amandina" = 8),
		// +1 pentru '\0'. Apoi strcpy copiaza literele in blocul nou din heap.
		this->denumire = new char[strlen(denumire) + 1];
		strcpy(this->denumire, denumire);
		this->pret = pret;
		this->cantitate = 250;
		this->dePost = true;
		this->nrIngrediente = 3;
		this->ingrediente = new string[this->nrIngrediente];
		this->ingrediente[0] = "piscoturi";
		this->ingrediente[1] = "vanilie";
		this->ingrediente[2] = "cafea";
	}

	// --------------------------------------------------------------------------
	// CONSTRUCTORUL DE COPIERE
	// --------------------------------------------------------------------------
	// - Ruleaza cand construiesti o prajitura NOUA dintr-una existenta:
	//     * Prajitura b = a;
	//     * cand pasezi o prajitura unei functii PRIN VALOARE  (f(Prajitura p))
	//     * cand o functie returneaza o prajitura PRIN VALOARE
	// - De ce trebuie scris de mana? Daca nu il scrii, C++ face unul automat care
	//   copiaza campurile unul cate unul. Pentru pointeri, asta copiaza doar
	//   ADRESA (copie superficiala). Doua prajituri ar imparti acelasi bloc.
	//   La distrugere, blocul s-ar sterge de doua ori: DOUBLE FREE, crash.
	// - Parametrul este const Prajitura& p:
	//     * & = referinta = lucram pe ORIGINAL, fara copie.
	//       E OBLIGATORIU. Fara &, ca sa pasezi argumentul ar trebui facuta o
	//       copie, care apeleaza constructorul de copiere, care cere o copie...
	//       la nesfarsit.
	//     * const = promitem ca nu stricam originalul.
	// - :id(contor++) = copia este un obiect NOU, deci primeste un id NOU.
	Prajitura(const Prajitura& p) :id(contor++) {
		// COPIE IN ADANCIME pentru nume:
		// 1. new = bloc NOU in heap, de marimea numelui lui p (+1 pentru '\0').
		// 2. strcpy = copiem LITERELE, nu adresa.
		//   Rezultat:
		//     p.denumire    = 5000 ---> [ a m a n d i n a \0 ]
		//     this->denumire = 9000 ---> [ a m a n d i n a \0 ]   (bloc propriu)
		this->denumire = new char[strlen(p.denumire) + 1];
		strcpy(this->denumire, p.denumire);

		// Campurile simple se copiaza direct cu =. Ele nu au memorie in heap.
		this->pret = p.pret;
		this->cantitate = p.cantitate;
		this->dePost = p.dePost;
		this->nrIngrediente = p.nrIngrediente;

		// COPIE IN ADANCIME pentru ingrediente:
		// 1. Vector NOU in heap, de aceeasi marime.
		// 2. Bucla for copiaza fiecare string, unul cate unul.
		//    for (int i = 0; i < n; i++) = repeta pentru i = 0, 1, 2, ..., n-1.
		this->ingrediente = new string[this->nrIngrediente];
		for (int i = 0; i < this->nrIngrediente; i++) {
			this->ingrediente[i] = p.ingrediente[i];
		}
	}
	// --------------------------------------------------------------------------
	// DESTRUCTORUL (doar declarat aici)
	// --------------------------------------------------------------------------
	// - ~Prajitura() = destructorul. Numele clasei cu ~ in fata.
	// - Ruleaza AUTOMAT cand obiectul dispare:
	//     * la } -ul care inchide blocul unde a fost declarat (obiecte pe stiva)
	//     * la delete (obiecte create cu new)
	// - Aici e doar DECLARAT (promisiunea ca exista). Corpul e scris mai jos,
	//   in afara clasei. E doar o alegere de stil.
	~Prajitura();//declarare destructor
	// --------------------------------------------------------------------------
	// OPERATORUL DE ATRIBUIRE  =
	// --------------------------------------------------------------------------
	// - Ruleaza la  a = b;  cand a EXISTA DEJA.
	//   Diferenta fata de constructorul de copiere:
	//     Prajitura a = b;   -> a se naste acum   -> constructor de copiere
	//     a = b;             -> a exista deja     -> operator=
	// - Pentru ca a exista deja, are deja memorie in heap. Trebuie:
	//     1. sa stearga memoria veche (altfel memory leak)
	//     2. sa aloce memorie noua, de marimea datelor lui b
	//     3. sa copieze continutul
	// - De ce trebuie scris de mana?
	//     * Versiunea automata ar face copie superficiala (problema de mai sus).
	//     * In plus, clasa are const int id. Un const nu poate fi atribuit, deci
	//       versiunea automata nici nu ar exista.
	// - Returneaza Prajitura& (referinta la obiectul insusi), ca sa mearga
	//   a = b = c;  (adica a = (b = c)).
	Prajitura& operator=(const Prajitura& P1) {
		// if (this != &P1)
		// - &P1 = adresa lui P1.  this = adresa obiectului curent.
		// - Daca sunt egale, cineva a scris  a = a;
		// - Fara verificare: stergem propriul nume, apoi incercam sa copiem din el.
		//   Dar el tocmai a fost sters. Rezultat: gunoi sau crash.
		if (this != &P1) {

			this->cantitate = P1.cantitate;
			// NULL = "adresa nicio", un pointer care nu arata spre nimic.
			// if (... != NULL) delete[] ...  = stergem numele vechi doar daca exista.
			// (Informativ: delete[] pe NULL nu face nimic, deci verificarea e doar
			// prudenta.)
			// Dupa delete[], vechiul bloc e dat inapoi. Apoi facem bloc nou cu new si
			// copiem literele cu strcpy.
			if (this->denumire != NULL)
				delete[]this->denumire;
			this->denumire = new char[strlen(P1.denumire) + 1];
			strcpy(this->denumire, P1.denumire);
			this->dePost = P1.dePost;
			this->pret = P1.pret;
			this->nrIngrediente = P1.nrIngrediente;
			// Acelasi lucru pentru vectorul de ingrediente:
			// stergem vectorul vechi, facem unul nou de marimea lui P1, copiem fiecare
			// element.
			if (this->ingrediente != NULL)
				delete[]this->ingrediente;
			this->ingrediente = new string[this->nrIngrediente];
			for (int i = 0;i < P1.nrIngrediente; i++)
				this->ingrediente[i] = P1.ingrediente[i];
		}

		// return *this;
		// - this este un pointer (adresa). *this = obiectul de la acea adresa.
		// - Tipul de return este Prajitura&, deci returnam obiectul INSUSI, nu o
		//   copie. Asa merge a = b = c.
		return *this;
	}

#pragma endregion

	// --------------------------------------------------------------------------
	// GETTERI
	// --------------------------------------------------------------------------
	// Campurile sunt private, deci main nu le poate citi direct.
	// Un getter este o functie publica ce doar intoarce valoarea unui camp.
	// Asa codul din afara poate CITI, dar nu poate SCRIE.
#pragma region geteri si seteri
	int getCantitate() {
		return this->cantitate;
	}
	int getNrIngrediente() {
		return this->nrIngrediente;
	}
	float getPret() {
		return this->pret;
	}
	// static int getContor()
	// - static = functia apartine clasei, nu unui obiect.
	// - Nu are this, deci poate atinge doar membri static (contor).
	// - Se apeleaza fara obiect:  Prajitura::getContor();
	static int getContor() {
		return contor;
	}

#pragma endregion
	// ==========================================================================
	// OPERATORI
	// ==========================================================================
	// C++ te lasa sa dai sens simbolurilor (+, [], ==, -= ...) pentru clasa ta.
	// Cand scrii  a + b,  C++ apeleaza de fapt  a.operator+(b).
	// a este obiectul curent (this). b este parametrul.
#pragma region Operatori
	// operator+   (a + b)
	// - Primeste const Prajitura& p: referinta, fara copie, fara modificare.
	// - Returneaza Prajitura PRIN VALOARE (fara &). Corect aici: rezultatul este
	//   o prajitura NOUA. Nu putem returna referinta la result, pentru ca result
	//   este o variabila locala care dispare la }.
	// - a si b raman neschimbate.
	Prajitura operator+(const Prajitura& p) {
		// Prajitura result = *this;
		// - *this = obiectul curent (a).
		// - result se NASTE aici dintr-o alta prajitura -> CONSTRUCTOR DE COPIERE.
		//   Deci result are propriul nume si propriile ingrediente in heap.
		// - Apoi doar schimbam pretul si cantitatea in sume.
		Prajitura result = *this;
		result.pret = this->pret + p.pret;
		result.cantitate = this->cantitate + p.cantitate;
		return result;
	}
	// operator[]   (p[1])
	// - Intoarce ingredientul de pe pozitia ceruta.
	// - De ce string& (cu &)? Raspuns la intrebarea ta din comentariu:
	//     * Cu &  -> returneaza o REFERINTA = chiar string-ul din vector.
	//       p[1] = "Frisca";  schimba ingredientul REAL din prajitura.
	//     * Fara & -> returneaza o COPIE. p[1] = "Frisca"; ar schimba copia,
	//       care dispare imediat. Prajitura ar ramane neschimbata.
	//     * Bonus: cu & nu se face nicio copie, deci e si mai rapid.
	// - Daca pozitia e gresita (negativa sau prea mare), intoarce primul
	//   ingredient in loc sa citeasca memorie straina (care ar putea da crash).
	string& operator[](int pozitie) //sa caut pt ca n am inteles de ce se pune &
	{
		if (pozitie >= 0 && pozitie < nrIngrediente)
		{
			return this->ingrediente[pozitie];
		}
		return ingrediente[0];
	}

	// explicit operator float()   ((float)P1)
	// - OPERATOR DE CONVERSIE: spune cum se transforma o prajitura in float.
	// - Nu are tip de return scris in fata. Numele operatorului ESTE tipul.
	// - "e unar si returneaza deja this" (comentariul tau): da, nu are parametri.
	//   Lucreaza doar pe obiectul curent (this) si intoarce pretul lui.
	// - explicit = conversia se face DOAR daca o ceri cu un cast:
	//     float x = (float)P1;   -> merge
	//     float x = P1;          -> NU se compileaza (te protejeaza de greseli)
	explicit operator float()//e unar si returneaza deja this
	{
		return this->pret;
	}

	// explicit operator int()   ((int)P1)
	// Acelasi lucru, dar transforma prajitura in int si intoarce cantitatea.
	explicit operator int()
	{
		return this->cantitate;
	}

	// operator()   (obiectul folosit ca o functie)
	// - Iti lasa sa scrii P1() ca si cum P1 ar fi o functie.
	// - Sunt TREI versiuni cu acelasi nume. Se numeste SUPRAINCARCARE (overloading).
	//   C++ o alege pe cea potrivita dupa tipul argumentului:
	//     P1()        -> versiunea fara parametri
	//     P1(0.21f)   -> versiunea cu float
	//     P1(10)      -> versiunea cu int
	// - Aceasta versiune (fara parametri) intoarce pretul pe gram.
	float operator()()
	{
		return this->costMediuGram();
	}

	// operator()(float TVA)   (P1(0.21f))
	// - Pret cu TVA: pret + pret * TVA. Apoi impartit la cantitate = pe gram.
	// - Pentru amandina: (20.6 + 20.6 * 0.21) / 250 = 24.926 / 250 = aprox. 0.0997
	// - De ce in main se scrie 0.21f si nu 0.21?
	//     * 0.21 simplu este de tip double (alt tip de numar cu zecimale).
	//     * Nu exista versiune cu double. C++ ar putea transforma double in float
	//       SAU in int, la fel de bine. Nu stie pe care s-o aleaga: eroare
	//       "ambiguous".
	//     * f la final = "acesta e float". Atunci alegerea e clara.
	float operator()(float TVA)
	{
		return (this->pret + (this->pret * TVA)) / this->cantitate;
	}

	// operator()(int discount)   (P1(10))
	// - Pret dupa reducere: pret - (discount / 100) * pret.
	// - Pentru amandina: 20.6 - 0.1 * 20.6 = 18.54.
	//   Atentie: asta e PRETUL TOTAL redus, nu pret pe gram, desi in main
	//   textul afisat spune "per gram".
	//
	// Intrebarea ta: "de ce nu pot sa pun float aici?"
	// - Exista deja operator()(float TVA). Doua functii cu acelasi nume si
	//   ACELASI tip de parametri nu pot exista: C++ nu ar sti pe care s-o apeleze.
	// - Supraincarcarea merge doar daca parametrii DIFERA. Aici difera prin
	//   tip: una primeste float, cealalta int.
	//
	// Intrebarea ta: "de ce e .0?"
	// - discount este int. 100 este int.
	// - int / int in C++ = IMPARTIRE INTREAGA. Partea cu virgula se taie.
	//     10 / 100   = 0      (0.1 taiat la 0)
	// - 100.0 este double (are zecimale). int / double = impartire normala.
	//     10 / 100.0 = 0.1
	// - Fara .0, reducerea ar fi mereu 0 (pentru discount sub 100).
	float operator()(int discount)//de ce nu pot sa pun float aici?
	{
		return (this->pret - (discount / 100.0) * this->pret);//si de ce e .0 :(  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	}

	// operator==   (p == P1)
	// - Intoarce true daca prajiturile sunt "egale", altfel false.
	// - strcmp(a, b) compara doua siruri de caractere litera cu litera.
	//     intoarce 0 daca sunt identice, alt numar daca difera.
	//   De ce nu this->denumire == prajitura.denumire? Pentru ca ar compara
	//   ADRESELE (pointerii), nu literele. Doua blocuri diferite cu acelasi text
	//   au adrese diferite.
	// - Verifica numele, cantitatea, dePost si numarul de ingrediente.
	//   La prima diferenta intoarce false si se opreste.
	// - Atentie: parametrul este Prajitura prajitura (PRIN VALOARE, fara &).
	//   La fiecare comparatie se face o COPIE completa prin constructorul de
	//   copiere (new pentru nume si ingrediente), iar la final copia se distruge.
	//   Merge corect, dar e risipa. const Prajitura& ar evita copia.
	bool operator==(Prajitura prajitura)
	{
		if (strcmp(this->denumire, prajitura.denumire) != 0)
		{
			return false;
		}
		if (this->cantitate != prajitura.cantitate)
		{
			return false;
		}
		if (this->dePost != prajitura.dePost)
		{
			return false;
		}
		if (this->nrIngrediente != prajitura.nrIngrediente)
		{
			return false;
		}
		return true;
	}

	// operator-=   (p -= P1)
	// - Scade pretul lui P1 din pretul lui p. Daca ar iesi negativ, pune 0.
	// - Parametrul const Prajitura p este PRIN VALOARE (fara &). Deci se face
	//   o copie a lui P1 (cu id nou) si se distruge la final. const doar
	//   interzice modificarea copiei.
	//
	// Intrebarea ta: de ce Prajitura& la return?
	// - a -= b modifica obiectul a. Rezultatul operatiei ESTE chiar a.
	// - Cu &: returnam o REFERINTA la a, adica obiectul insusi, deja existent.
	//     * Nu se face nicio copie.
	//     * Merge "apelul in cascada": (a -= b) -= c;  al doilea -= lucreaza tot
	//       pe a, nu pe o copie.
	// - Fara &: s-ar returna o COPIE a lui a. Orice operatie in cascada ar lucra
	//   pe copie, iar a nu s-ar mai modifica a doua oara.
	// - Asta e regula pentru operatorii care modifica obiectul (=, +=, -=):
	//   returneaza *this prin referinta.
	Prajitura& operator-=(const Prajitura p)//avem Prajitura ca sa permita apel in cascada. deoarece returnam un obiect deja existent... ceva ceva n am intls
	{
		if (this->pret > p.pret)
		{
			this->pret = this->pret - p.pret;
		}
		else this->pret = 0;
		return *this;
	}

	// operator+=   (p += "Faina")
	// - Adauga un ingredient la final.
	// - PROBLEMA: un vector din heap NU poate creste. Are marimea fixata la new.
	//   Solutia: facem unul nou, mai mare, si mutam totul in el.
	// - "Faina" din main este text C (const char*). C++ il transforma automat
	//   intr-un string temporar ca sa se potriveasca parametrului.
	// - Returneaza Prajitura PRIN VALOARE (fara &). Deci la fiecare += se face
	//   o copie a prajiturii care e aruncata imediat. Merge, dar e risipa.
	//   Prajitura& ar fi mai bun (vezi explicatia de la -=).
	Prajitura operator+=(string ingredient)
	{
		// PASUL 1: vector nou, cu un loc in plus.
		//     ingrediente = 7000 ---> [ piscoturi ][ Frisca ][ cafea ]
		//     aux         = 8000 ---> [    ""     ][   ""   ][  ""   ][  ""  ]
		string* aux = new string[this->nrIngrediente + 1];
		// PASUL 2: copiem elementele vechi in vectorul nou.
		//     aux         = 8000 ---> [ piscoturi ][ Frisca ][ cafea ][  ""  ]
		for (int i = 0; i < this->nrIngrediente;i++)
		{
			aux[i] = this->ingrediente[i];
		}
		// PASUL 3: noul ingredient pe ultima pozitie (indexul nrIngrediente = 3).
		//     aux         = 8000 ---> [ piscoturi ][ Frisca ][ cafea ][ Faina ]
		aux[this->nrIngrediente] = ingredient;
		// PASUL 4: stergem vectorul vechi. Altfel ar ramane ocupat degeaba (leak).
		//     ingrediente = 7000 ---> (eliberat, nu mai e al nostru)
		delete[] this->ingrediente;
		// PASUL 5: pointerul ingrediente arata acum spre vectorul nou.
		//     ingrediente = 8000 ---> [ piscoturi ][ Frisca ][ cafea ][ Faina ]
		// PASUL 6: crestem numarul de ingrediente (3 -> 4).
		// aux era doar o variabila locala (un pointer pe stiva). Dispare la },
		// dar blocul din heap ramane, pentru ca acum il tine ingrediente.
		this->ingrediente = aux;
		this->nrIngrediente++;
		return *this;
	}
#pragma endregion
	// afisare()
	// - Afiseaza toate campurile cu cout.
	// - (this->dePost ? "DA" : "NU") este OPERATORUL TERNAR:
	//     conditie ? valoare_daca_true : valoare_daca_false
	//   Este un if scurt: daca dePost e true, scrie DA, altfel NU.
	// - Bucla for parcurge vectorul de la 0 la nrIngrediente - 1.
	void afisare()
	{
		cout << "Denumire: " << this->denumire << endl;
		cout << "Pret: " << this->pret << endl;
		cout << "Cantitate: " << this->cantitate << endl;
		cout << "De Post: " << (this->dePost ? "DA" : "NU") << endl;
		cout << "Nr ingrediente: " << this->nrIngrediente << endl;
		cout << "Ingredientele sunt: ";
		for (int i = 0;i < this->nrIngrediente;i++)
		{
			cout << this->ingrediente[i] << "; ";
		}
		cout << endl;

	}
	// costMediuGram()
	// - Pret impartit la cantitate = pret pe gram.
	// - Verifica intai daca cantitatea e 0. Impartirea la zero nu are sens si
	//   poate strica programul. In acel caz intoarce 0.
	// - pret este float, deci impartirea float / int da rezultat cu zecimale.
	float costMediuGram() {
		if (this->cantitate == 0) {
			return 0;
		}
		else {
			return this->pret / this->cantitate;
		}
	}

	// modificaDenumire()
	// - Schimba numele prajiturii.
	// - Acelasi tipar ca in operator=: stergi blocul vechi, faci unul nou,
	//   copiezi literele.
	// - GRESEALA pe linia de mai jos: denumire a fost creat cu new char[...],
	//   deci trebuie sters cu delete[], nu cu delete.
	//   new[] se pereche cu delete[]. Amestecarea lor este "comportament
	//   nedefinit": poate merge, poate da crash, nu ai garantii.
	void modificaDenumire(const char* denumire) {
		delete this->denumire;

		this->denumire = new char[strlen(denumire) + 1];
		strcpy(this->denumire, denumire);
	}


};

// int Prajitura::contor = 100;
// - Membrul static a fost doar DECLARAT in clasa. Aici primeste spatiul
//   real in memorie, o singura data pentru tot programul.
// - Prajitura:: = "contor din clasa Prajitura".
// - Valoarea de start este 100. Prima prajitura creata primeste id 100.
int Prajitura::contor = 100;

// --------------------------------------------------------------------------
// DESTRUCTORUL (implementarea)
// --------------------------------------------------------------------------
// - Prajitura:: spune ca functia apartine clasei Prajitura.
// - Ruleaza automat cand o prajitura dispare.
// - Elibereaza cele doua blocuri din heap. Fara el, fiecare prajitura ar
//   lasa in urma numele si ingredientele ei: memory leak.
// - delete[] pentru ca ambele au fost create cu new[].
// - Campurile simple (pret, cantitate ...) nu trebuie sterse. Ele stau in
//   obiect si dispar odata cu el.
Prajitura::~Prajitura() {//implementare destructor
	delete[] this->denumire;
	delete[] this->ingrediente;
}
// ==========================================================================
// FUNCTII LIBERE (nu apartin niciunei clase)
// ==========================================================================
// calculeazaCantitateTotala(Prajitura* prajituri, int nr_prajituri)
// - Primeste ADRESA primului element dintr-un vector de prajituri.
// - Un pointer nu stie cate elemente urmeaza. De aceea numarul lor se da
//   separat, in nr_prajituri.
// - prajituri[p] = elementul de pe pozitia p (merge si pe pointeri).
// - Aduna cantitatile tuturor prajiturilor.
// - Se paseaza doar adresa, deci NU se copiaza nicio prajitura.
// - (Nu este apelata in main.)
float calculeazaCantitateTotala(Prajitura* prajituri, int nr_prajituri) {
	float greutate = 0;

	for (int p = 0; p < nr_prajituri; p++)
		greutate += prajituri[p].getCantitate();

	return greutate;
}

// calculeazaPretPerIngredient(Prajitura p)
// - Prajitura p = PRIN VALOARE. La apel se face o COPIE prin constructorul
//   de copiere. La } copia se distruge (destructorul ruleaza).
// - Imparte pretul la numarul de ingrediente. Daca nu exista niciunul,
//   intoarce 0 (ca sa nu imparta la zero).
// - p.getPret() si nu p.pret, pentru ca pret e private, iar functia asta
//   nu face parte din clasa.
// - (Apelul din main este comentat, deci nu ruleaza.)
float calculeazaPretPerIngredient(Prajitura p) {
	if (p.getNrIngrediente() != 0)
		return p.getPret() / p.getNrIngrediente();

	return 0;
}


// ==========================================================================
// CLASA STUDENT
// ==========================================================================
// Un student are un nume si O PRAJITURA INTREAGA ca membru.
// Asta se numeste COMPOZITIE: un obiect in interiorul altui obiect.
class Student {
private:
	// string nume
	// - string (din biblioteca standard) isi gestioneaza singur memoria.
	//   Nu ai nevoie de new/delete pentru el. Se copiaza corect singur.
	// - Prin contrast, char* denumire din Prajitura trebuie gestionat de mana.
	string nume;
	// Prajitura prajitura
	// - Un obiect Prajitura intreg, in interiorul fiecarui Student.
	// - Cand un Student se creeaza, se creeaza si prajitura lui (constructor).
	// - Cand un Student dispare, dispare si prajitura lui (~Prajitura ruleaza
	//   automat). De aceea Student nu are nevoie de destructor propriu.
	Prajitura prajitura;
public:
	// Student()
	// - Constructorul implicit. Seteaza numele "Andrei".
	// - Inainte de corpul { }, membrul prajitura se construieste automat cu
	//   constructorul implicit al Prajiturii (Tiramisu, id nou).
	Student() {
		this->nume = "Andrei";
	}
	// Student(string nume, Prajitura p)
	// - Ambii parametri vin PRIN VALOARE, deci sunt COPII:
	//     nume este o copie a textului, p este o copie a prajiturii (id nou).
	// - Ordinea reala:
	//     1. se copiaza argumentele in parametri (p prin constructorul de copiere)
	//     2. inainte de { }, membrul prajitura se construieste cu
	//        constructorul IMPLICIT (Tiramisu, alt id nou)
	//     3. in corp, this->prajitura = p; ruleaza Prajitura::operator=
	//        (sterge Tiramisu-ul, copiaza datele lui p)
	//     4. la final, parametrul p este distrus
	// - Merge corect, dar construieste o prajitura care e imediat inlocuita.
	//   O lista de initializare  : nume(nume), prajitura(p)  ar evita asta.
	Student(string nume, Prajitura p) {
		this->nume = nume;
		this->prajitura = p;
	}
	// Getteri si setteri pentru nume si prajitura.
	// - getPrajitura returneaza PRIN VALOARE, deci o COPIE a prajiturii.
	// - setPrajitura primeste o copie si o atribuie membrului cu operator=.
	string getNume() {
		return this->nume;
	}
	Prajitura getPrajitura() {
		return this->prajitura;
	}
	void setNume(string nume) {
		this->nume = nume;
	}
	void setPrajitura(Prajitura p) {
		this->prajitura = p;
	}
	// calculeazaNrTotalCalorii
	// - Calorii pe gram inmultit cu cantitatea prajiturii (in grame).
	// - Foloseste getCantitate(), un getter public.
	float calculeazaNrTotalCalorii(float caloriiPerGram) {
		float nrTotal = caloriiPerGram * this->prajitura.getCantitate();
		return nrTotal;
	}
	// afiseazaMasa
	// - Scrie de exemplu: "Cristian mananca prajitura amandina".
	// - this->prajitura.denumire este un camp PRIVATE al Prajiturii.
	//   Student are voie sa il citeasca doar pentru ca Prajitura a scris
	//   friend class Student;
	// - cout << char*  afiseaza literele pana la '\0', nu adresa.
	void afiseazaMasa() {
		cout << this->nume << " mananca prajitura " << this->prajitura.denumire << endl;
	}
};


// ==========================================================================
// MAIN: AICI INCEPE PROGRAMUL
// ==========================================================================
// - main este prima functie care ruleaza.
// - void main() este acceptat de Visual Studio, dar standardul C++ cere
//   int main(). Pe g++ nu se compileaza. Pentru teme pe VS, merge.
// - Numaratoarea id-urilor (contor porneste de la 100) este urmarita mai jos.
void main() {
	// PASUL 1: Prajitura p;
	// - Constructorul implicit. Tiramisu, pret 15, cantitate 250, id 100.
	// - Memoria:
	//     STIVA                         HEAP
	//     p.denumire    = 5000 ---->   [ T i r a m i s u \0 ]
	//     p.ingrediente = 7000 ---->   [ piscoturi ][ vanilie ][ cafea ]
	//     p.pret = 15, p.cantitate = 250 ... (stau direct in p)
	Prajitura p;
	//p.afisare();
	// PASUL 2: Prajitura::getContor();
	// - Apel static, fara obiect. Intoarce 101, dar rezultatul nu e folosit
	//   nicaieri, deci linia nu are niciun efect vizibil.
	Prajitura::getContor();
	// PASUL 3: Prajitura P1("amandina", 20.6);
	// - Constructorul cu parametri. id 101.
	// - 20.6 este double. Se transforma automat in float (parametrul pret).
	Prajitura P1("amandina", 20.6);
	// PASUL 4: Student s1("Cristian", P1);
	// - Copie a lui P1 in parametrul p (constructor de copiere): id 102.
	// - Membrul s1.prajitura se construieste implicit (Tiramisu): id 103.
	// - s1.prajitura = p;  operator= : sterge Tiramisu, copiaza amandina.
	// - Copia din parametru (102) se distruge, destructorul ii sterge memoria.
	// - Acum s1.prajitura are propria amandina, cu blocuri proprii in heap.
	Student s1("Cristian", P1);
	// Liniile comentate de mai jos nu ruleaza (incep cu //).
	//s1.afiseazaMasa();
	//cout << s1.calculeazaNrTotalCalorii(0.5);
	//
	//cout << endl;
	//cout << calculeazaPretPerIngredient(p);
	// PASUL 5: cout << p[1]
	// - operator[] intoarce referinta la ingrediente[1]. Afiseaza: vanilie
	cout << p[1] << endl;
	// PASUL 6: p[1] = "Frisca";
	// - p[1] este o REFERINTA la string-ul real din vector.
	// - Deci atribuirea schimba direct ingredientul din prajitura.
	//     p.ingrediente ---> [ piscoturi ][ Frisca ][ cafea ]
	// - Linia urmatoare afiseaza: Frisca
	p[1] = "Frisca";
	cout << p[1] << endl;
	// PASUL 7: pret = (float) P1;
	// - (float) este un CAST: cere explicit conversia la float.
	// - Apeleaza explicit operator float(). pret devine 20.6.
	float pret;
	pret = (float)P1;
	cout << "Pret: " << pret << endl;
	// PASUL 8: cantitate = (int) P1;
	// - Apeleaza explicit operator int(). cantitate devine 250.
	int cantitate;
	cantitate = (int)P1;
	cout << "Cantitate: " << cantitate << endl;
	// PASUL 9: cele trei apeluri operator()
	// - P1()       -> fara argument -> 20.6 / 250            = 0.0824
	// - P1(0.21f)  -> float         -> (20.6 * 1.21) / 250   = aprox. 0.0997
	// - P1(10)     -> int           -> 20.6 - 0.1 * 20.6     = 18.54
	//   (al treilea e pretul total redus, nu pe gram, desi textul spune
	//   "per gram")
	cout << "Pret per gram: " << P1() << endl;
	cout << "Pret cu TVA per gram: " << P1(0.21f) << endl;
	cout << "Pret cu discount per gram: " << P1(10) << endl;
	// PASUL 10: if (p == P1)
	// - Apeleaza p.operator==(P1). Parametrul e prin valoare, deci se face o
	//   copie a lui P1 (id 104), distrusa dupa comparatie.
	// - "Tiramisu" difera de "amandina", strcmp nu da 0 -> false.
	// - Se afiseaza: Nu sunt la fel/egale.
	if (p == P1)
	{
		cout << "Sunt la fel/egale." << endl;
	}
	else
	{
		cout << "Nu sunt la fel/egale." << endl;
	}

	// PASUL 11: p -= P1;
	// - Parametrul e prin valoare: copie a lui P1 (id 105), distrusa la final.
	// - 15 > 20.6? Nu. Deci pretul lui p devine 0.
	// - Linia urmatoare afiseaza: 0
	p -= P1;
	cout << p.getPret() << endl;
	// PASUL 12: p += "Faina";
	// - "Faina" devine un string temporar.
	// - Vectorul de ingrediente creste de la 3 la 4 (vezi pasii din operator+=).
	// - operator+= returneaza prin valoare, deci se face o copie a lui p
	//   (id 106), aruncata imediat.
	p += "Faina";
	// PASUL 13: cout << p[3]  afiseaza: Faina
	//
	// SFARSIT (la } de mai jos):
	// - Toate obiectele de pe stiva dispar AUTOMAT, in ordine INVERSA crearii:
	//     1. s1  -> dispare si s1.prajitura -> ~Prajitura sterge amandina ei
	//     2. P1  -> ~Prajitura sterge numele si ingredientele lui P1
	//     3. p   -> ~Prajitura sterge Tiramisu si cele 4 ingrediente
	// - Fiecare new din program are un delete pereche. Nimic nu ramane ocupat.
	//
	// IDEEA CARE LEAGA TOT:
	// - Fiecare new are un delete pereche.
	// - Fiecare obiect cu pointeri isi primeste propria copie in adancime.
	// - Pentru asta exista destructorul, constructorul de copiere si operator=.
	cout << p[3] << endl;
}