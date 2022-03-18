#include <iostream>
#include <string>
#include <fstream>
#include <ctime>

using namespace std;

void upis_pitanja(int kategorija);
void igra();
int popunjavanje_strukture(int kategorija=1);
void ispis_pitanja(int kategorija);
void nasumicni_brojevi(int *niz, int n);
void odgovaranje(int *niz, int *flags,int rez);
int pomoci(int i,int *niz,int *flags);
void mesanje(int *niz);
int skor();
void brisanje(int kategorija);

fstream f1,f2;

struct pitanja {
	string pitanje;
	string o1, o2, o3, o4, to;
}*s;

int k = -1;

int main()	
{
	int opcija,kategorija;
	cout << "Dobrodosli u igru MILIONER" << endl;
	srand(time(NULL));
	while (1)
	{
		cout << "\nUnesite broj opcije" << endl;
		cout << "1.Zapocnite igru" << endl;
		cout << "2.Unesite nova pitanja" << endl;
		cout << "3.Pregled baze pitanja" << endl;
		cout << "4.Brisanje pitanja" << endl;
		cout << "5.Uputsvo" << endl;
		cout << "0.Izlaz" << endl;

		cin >> opcija;
		
		switch (opcija)
		{
		case 1:
			igra();
			break;
		case 2:
			do {
				cout << "Za koju kategoriju zelite da unesete pitanja(1/2/3) ";
				cin >> kategorija;
			} while (kategorija < 1 || kategorija >3);
			upis_pitanja(kategorija);
			break;
		case 3:
			do{
			cout << "Za koju kategoriju zelite da prikazete pitanja(1/2/3) ";
			cin >> kategorija;
		} while (kategorija < 1 || kategorija >3);
			ispis_pitanja(kategorija);
			break;
		case 4:
			do {
				cout << "Zakoju kategoriju zelite da izbrisete pitanje(1/2/3) ";
				cin >> kategorija;
			} while (kategorija < 1 || kategorija >3);
			brisanje(kategorija);
		break;
		case 5:
			cout << "Igra se sastoji od 15 pitanja iz tri razlicite oblasti." << endl;
			cout << "Za unos odgovora koristite opcije A,B,C,D." << endl;
			cout << "Da bi ste upotrebili pomoc iskoristite opciju P a" << endl;
			cout << "da bi ste odustali iskoristite opciju O\n" << endl;
			cout << "*Kod unosa pitanja odgovor mora biti jedna rec."<<endl;
			break;
		case 0:
			return -1;
		default:
			cout << endl << opcija << "nije postojeca opcija" << endl;
			continue;
		}

	}
	return 0;
}

void upis_pitanja(int kategorija) 
{
	string pitanje;
	string o1, o2, o3, o4, to;
	int br_pitanja;

	if (kategorija == 1)											//Otvaranje datoteka za upis
	{
		f1.open("Pitanja1.txt", ios::out | ios::app);				
		f2.open("Odgovori1.txt", ios::out | ios::app);
	}
	if (kategorija == 2)
	{
		f1.open("Pitanja2.txt", ios::out | ios::app);				
		f2.open("Odgovori2.txt", ios::out | ios::app);
	}
	if (kategorija == 3) 
	{
		f1.open("Pitanja3.txt", ios::out | ios::app);				
		f2.open("Odgovori3.txt", ios::out | ios::app);
	}


	if (!f1 || !f2) {												//Provera
		cout << "Greska pri otvaranju datoteke";
		exit(1);
	}

	cout << "Koliko pitanja zelite da unesete: ";			//Unos broja pitanja
	cin >> br_pitanja;
	
	for (int i = 0; i < br_pitanja; i++)
	{
		cout << "\nUnesite zeljeno pitanje" << endl;				//Unos teksta pitanja
		cin.ignore();
		getline(cin,pitanje);
		f1<< pitanje << endl;

		cout << "Unesite odgovore za uneto pitanje" << endl;	//Unos odgovora
		cin >> o1 >> o2 >> o3 >> o4;
		f2 << o1 << " " << o2 << " " << o3 << " " << o4 << " ";
		cout << "Koji od ovih odgovora je tacan:" << endl;
		cin >> to;
		f2 << to << endl;
	}
	f1.close();
	f2.close();
}

void igra()	
{
	int flags[4] = { 0,0,0,0 };												
	int br_pitanja;
	int niz[5];
	int rez=0;

	br_pitanja = popunjavanje_strukture();									//Ucitavanje pitanja za prvu kategoriju
	nasumicni_brojevi(niz, br_pitanja);										//Izbor nasumicnih pitanja
	mesanje(niz);
	odgovaranje(niz,flags,rez);													//Unos odgovora i opcija
	rez = 3;

	if (flags[3] == 0) {
		k--;
		cout << "Imate prvu zagarntovanu sumu:" << skor()<<"din" << endl << endl;

		br_pitanja = popunjavanje_strukture(2);								//Ucitavanje pitanja za drugu kategoriju											
		nasumicni_brojevi(niz, br_pitanja);									//Izbor nasumicnih pitanja
		mesanje(niz);
		odgovaranje(niz,flags,rez);												//Unos odgovora i opcija
		
	}

		rez = 8;

	if (flags[3] == 0) {
		k--;
		cout << "Imate drugu zagarntovanu sumu:" << skor()<<"din"<< endl << endl;

		br_pitanja = popunjavanje_strukture(3);								//Ucitavanje pitanja za trecu kategoriju
		nasumicni_brojevi(niz, br_pitanja);									//Izbor nasumicnih pitanja
		mesanje(niz);
		odgovaranje(niz,flags,rez);												//Unos odgovora i opcija
	}
	if (flags[3] == 0) {
		cout << "CESTITAMO POSTALI STE MILIONER\n" << endl;
	}
}

int popunjavanje_strukture(int kategorija)
{
	string pom;
	int n = 0, i;

	if (kategorija == 1)
	{
		f1.open("Pitanja1.txt", ios::in);				//Otvaranje datoteke za citanje
		f2.open("Odgovori1.txt", ios::in);
	}
	if (kategorija == 2)
	{
		f1.open("Pitanja2.txt", ios::in);				
		f2.open("Odgovori2.txt", ios::in);
	}
	if (kategorija == 3)
	{
		f1.open("Pitanja3.txt", ios::in);		
		f2.open("Odgovori3.txt", ios::in);
	}

	if (!f1 || !f2){									//Provera 
		cout << "Greska pri otvaranju datoteke";
		exit(1);
	}

	while (getline(f1, pom)) {							//Br pitanja
		n++;
	}
	
	f1.clear();
	f1.seekg(0);										//Povratak na pocetak datoteke
	s = new pitanja[n];									//Dinamicka dodela memorije

	if (s == NULL) {									//Provera
		cout << "Greska pri dodeli dinamicke memorije";
		exit(1);
	}

	for (i = 0; i < n; i++)								//Upis u strukturu
	{
		getline(f1, s[i].pitanje);
		f2 >> s[i].o1 >> s[i].o2 >> s[i].o3 >> s[i].o4 >> s[i].to;
	}
	

	f1.close();
	f2.close();
	return n;
}

void ispis_pitanja(int kategorija) 
{
	int br_pitanja;
	
	br_pitanja=popunjavanje_strukture(kategorija);

	for (int i = 0; i < br_pitanja; i++)						//Ispis pitanja
	{
		cout << i+1 << ".";
		cout << s[i].pitanje << endl << endl;
		cout << "\t  A: " << s[i].o1 << "\t\tB: " << s[i].o2 << endl;
		cout << "\t  C: " << s[i].o3 << "\t\tD: " << s[i].o4 << endl << endl;
	}
}

void nasumicni_brojevi(int *niz, int n)								//Kreiranje niza nasumicnih brojeva				
{
	
	for (int i = 0; i < 5; i++)								
	{
		niz[i] = rand() % n;

		for (int j = 0; j < i; j++)
			if (niz[i] == niz[j])
				i--;
	}
}

void odgovaranje(int *niz, int *flags,int rez)
{	
	char odgovor;
	int o=0;

	for (int i = 0; i < 5; i++)
	{
		cout << "Pitanje za: " << skor() <<"din"<< endl;
		cout << s[niz[i]].pitanje << endl << endl;						//Prikaz
		cout << "\t  A: " << s[niz[i]].o1 << "\t\tB: " << s[niz[i]].o2 << endl;
		cout << "\t  C: " << s[niz[i]].o3 << "\t\tD: " << s[niz[i]].o4 << endl << endl;

		cout << "Unesite vas odgovor(A/B/C/D): ";
		cin >> odgovor;
		odgovor = toupper(odgovor);

		switch (odgovor)												//Provera tacnosti odgovora
		{
		case 'A':
			if (s[niz[i]].o1 == s[niz[i]].to)
			{
				cout << "\nVas odgovor je TACAN\n" << endl;
				break;
			}
			else
			{
				cout << "\nVas odgovor NIJE TACAN" << endl;
				flags[3]++;
				break;
			}

		case 'B':
			if (s[niz[i]].o2 == s[niz[i]].to)
			{
				cout << "\nVas odgovor je TACAN\n" << endl;
				break;
			}
			else
			{
				cout << "\nVas odgovor NIJE TACAN\n" << endl;
				flags[3]++;
				break;
			}

		case 'C':
			if (s[niz[i]].o3 == s[niz[i]].to)
			{
				cout << "\nVas odgovor je TACAN\n" << endl;
				break;
			}
			else
			{
				cout << "\nVas odgovor NIJE TACAN" << endl;
				flags[3]++;
				break;
			}

		case 'D':
			if (s[niz[i]].o4 == s[niz[i]].to)
			{
				cout << "\nVas odgovor je TACAN\n" << endl;
				break;
			}
			else
			{
				cout << "\nVas odgovor NIJE TACAN" << endl;
				flags[3]++;
				break;
			}

		case 'P':															//Aktiviranje pomoci
			{
			
			i=pomoci(i,niz,flags);
			break;
			}

		case 'O':															//Odustajanje
			k--;
			o++;
			flags[3]++;
			break;

		default:
		{
			cout << "\nUneli ste opciju koja ne postoji\n" << endl;
			i--;
			k--;
			break;
		}
		}

		if (flags[3] != 0)													// Kraj u slucaju pogresnog odgovora
		{
			if (o != 0)
			{
				k--;
				if (rez == 0)
					cout << "Osvojili ste: 0din" << endl;
				else {
					cout << "\nIzabrali ste opciju da odustanete" << endl;
					cout << "Vasa osvojena suma je: " << skor() << endl << endl;
				}
			}
			else if (rez == 0)
				cout << "Osvojili ste: 0din" << endl;
			else 
			{
				k = rez;
				cout << "Osvojili ste: " << skor() << "din"<<endl;
			}
			cout << "Kraj igre\n" << endl;
			k = -1;
			break;
		}

	}
}

int pomoci(int i,int *niz,int *flags) 
{
	int n;
	char pom;
	
	if (flags[0] == 1 && flags[1] == 1 && flags[2] == 1)            //Provera iskoriscenosti poruka
	{
		cout << "Iskoristili ste sve pomoci\n" << endl;
		k--;
		return --i;
	}
	else
	{
		cout << "Izaberite pomoc koju zelite: " << endl;			//Izbor pomoci koje nisu iskoriscene
		if (flags[0] == 1)
			cout << "(iskorisceno)";
		cout << "1.Pomoc prijatelja" << endl;						
		if (flags[1] == 1)
			cout << "(iskorisceno)";
		cout << "2.Pomoc publike" << endl;
		if (flags[2] == 1)
			cout << "(iskorisceno)";
		cout << "3.Pomoc pola-pola" << endl;

		do {														//Unos br pomoci
			cin >> n;
		} while (n < 1 || n>3);


		if (s[niz[i]].o1 == s[niz[i]].to)
			pom = 'A';
		if (s[niz[i]].o2 == s[niz[i]].to)
			pom = 'B';
		if (s[niz[i]].o3 == s[niz[i]].to)
			pom = 'C';
		if (s[niz[i]].o4 == s[niz[i]].to)
			pom = 'D';


		if (flags[0] == 0 && n == 1)							//Pomoc prijatelja
		{
			cout << "Prijatelj kaze da je tacan odgovor:" << endl;	
			cout << pom << endl;
			flags[0]++;
			k--;
			return --i;
		}
		else if (flags[1] == 0 && n == 2)						//Pomoc publike
		{
			int x, y, z, q;

			cout << "Odgovori publike: " << endl;
			x = rand() % 20 + 60;
			y = 80 - x;
			z = rand() % 20;
			q = 20 - z;

			if (pom == 'A')
			{
				cout << "Pod A: " << x << "%" << endl;
				cout << "Pod B: " << z << "%" << endl;
				cout << "Pod C: " << y << "%" << endl;
				cout << "Pod D: " << q << "%" << endl;
			}
			if (pom == 'B')
			{
				cout << "Pod A: " << z << "%" << endl;
				cout << "Pod B: " << x << "%" << endl;
				cout << "Pod C: " << y << "%" << endl;
				cout << "Pod D: " << q << "%" << endl;
			}
			if (pom == 'C')
			{
				cout << "Pod A: " << y << "%" << endl;
				cout << "Pod B: " << z << "%" << endl;
				cout << "Pod C: " << x << "%" << endl;
				cout << "Pod D: " << q << "%" << endl;
			}
			if (pom == 'D')
			{
				cout << "Pod A: " << q << "%" << endl;
				cout << "Pod B: " << z << "%" << endl;
				cout << "Pod C: " << y << "%" << endl;
				cout << "Pod D: " << x << "%" << endl;
			}
			
			flags[1]++;
			k--;
			return --i;

		}												
		else if (flags[2] == 0 && n == 3)							//Pomoc pola pola	
		{
			char odgovor;
			if (pom == 'A' || pom == 'D')
			{
				cout << s[niz[i]].pitanje << endl << endl;
				cout << "\t  A: " << s[niz[i]].o1 << endl;
				cout << "\t\t\t\tD: " << s[niz[i]].o4 << endl << endl;

				cout << "Unesite vas odgovor(A/D): ";
				cin >> odgovor;
				odgovor = toupper(odgovor);
				if (pom == odgovor)
				{
					cout << "\nVas odgovor je TACAN\n" << endl;
					flags[2]++;
					return i;
				}
				else
				{
					cout << "\nVas odgovor NIJE TACAN\n" << endl;
					flags[3]++;
				}
			}
			if (pom == 'B' || pom == 'C')
			{
				cout << s[niz[i]].pitanje << endl << endl;
				cout << "\t\t\t\tB: " << s[niz[i]].o2 << endl;
				cout << "\t  C: " << s[niz[i]].o3 << endl << endl;
				cout << "Unesite vas odgovor(B/C): ";
				cin >> odgovor;
				odgovor = toupper(odgovor);
				if (pom == odgovor)
				{
					cout << "\nVas odgovor je TACAN\n" << endl;
					flags[2]++;
				}
				else
				{
					cout << "\nVas odgovor NIJE TACAN\n" << endl;
					flags[3]++;
				}
			}
		}
		else
		{
			cout << "\nPomoc je iskoriscena\n" << endl;
			return --i;
		}
	}
}

void mesanje(int *niz)                                 //Stavlja pitanja na ralicita mesta
{
	int n = rand() % 6+1;
	string pom;
	for (int i=0; i < 5; i++) {
		for (int j = 0; j < n; j++)
		{
			pom = s[niz[i]].o1;
			s[niz[i]].o1 = s[niz[i]].o2;
			s[niz[i]].o2 = s[niz[i]].o3;
			s[niz[i]].o3 = s[niz[i]].o4;
			s[niz[i]].o4 = pom;
		}
	}
}

int skor()														//Broji rezultat
{
	
	int novac[15] = { 500,1000,1500,2500,5000,
						10000,20000,40000,80000,150000,
						300000,600000,1250000,2500000,5000000 };

	k++;

	return novac[k];
}

void brisanje(int kategorija) 
{
	ispis_pitanja(kategorija);
	
	int x;
	fstream temp1, temp2;
	int n=0;

	if (kategorija == 1)
	{
		f1.open("Pitanja1.txt", ios::in);				//Otvaranje datoteke za citanje
		f2.open("Odgovori1.txt", ios::in);
	}
	if (kategorija == 2)
	{
		f1.open("Pitanja2.txt", ios::in);
		f2.open("Odgovori2.txt", ios::in);
	}
	if (kategorija == 3)
	{
		f1.open("Pitanja3.txt", ios::in);
		f2.open("Odgovori3.txt", ios::in);
	}
	if (!f1 || !f2) {									//Provera 
		cout << "Greska pri otvaranju datoteke";
		exit(1);
	}
	temp1.open("Temp1.txt", ios::out | ios::app);		//Otvaranje pomocnih datoteka
	temp2.open("Temp2.txt", ios::out | ios::app);		
	if (!temp1 || !temp2) {								//Provera 
		cout << "Greska pri otvaranju datoteke";
		exit(1);
	}
	
	string pom;
	while (getline(f1,pom))
	{
		n++;
	}
	f1.clear();
	f1.seekg(0);
	
	if (n <= 5)											//Provera broja pitanja
	{
		cout << "Ne mozete da izbrisete pitanje" << endl;
		cout << "Program mora da ima minimum 5 pitanja u kategoriji" << endl;
		f1.close();
		f2.close();
		temp1.close();
		temp2.close();
	}
	else 
	{
		cout << "Unesite broj pitanja koje zelite da izbrisete: ";
		cin >> x;
		n = 0;
		while (getline(f1, pom))											//Smestanje podataka u privremene datoteke
		{
			n++;
			if (n != x)
				temp1 << pom << endl;
		}
		n = 0;
		while (getline(f2, pom))
		{
			n++;
			if (n != x)
				temp2 << pom << endl;
		}

		f1.close();
		f2.close();
		temp1.close();
		temp2.close();
		if (kategorija == 1)												//Zamena datoteka
		{
			remove("Pitanja1.txt");
			rename("Temp1.txt", "Pitanja1.txt");
			remove("Odgovori1.txt");
			rename("Temp2.txt", "Odgovori1.txt");
		}
		if (kategorija == 2)
		{
			remove("Pitanja2.txt");
			rename("Temp1.txt", "Pitanja2.txt");
			remove("Odgovori2.txt");
			rename("Temp2.txt", "Odgovori2.txt");
		}
		if (kategorija == 3)
		{
			remove("Pitanja3.txt");
			rename("Temp1.txt", "Pitanja3.txt");
			remove("Odgovori3.txt");
			rename("Temp2.txt", "Odgovori3.txt");
		}

	}
}