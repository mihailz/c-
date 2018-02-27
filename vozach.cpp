#include <iostream>
using namespace std;
#include <cstring>

class Vozac{
protected:
    char ime[100];
    int vozrast;
    int brojTrki;
    bool veteran;
public:
    Vozac(const char *ime = "",int vozrast=0,int brojTrki=0,bool veteran=false)
    {
        strcpy(this->ime,ime);
        this->vozrast=vozrast;
        this->brojTrki=brojTrki;
        this->veteran=veteran;
    }

    friend ostream& operator<<(ostream &out,const Vozac &v)
    {
        cout<<v.ime<<endl;
        cout<<v.vozrast<<endl;
        cout<<v.brojTrki<<endl;
        if(v.veteran)
            cout<<"VETERAN"<<endl;
            return out;
    }

    bool operator==( Vozac &v1)
    {
       return zarabotuvacka()==v1.zarabotuvacka();
    }

    virtual float zarabotuvacka() = 0;
    virtual float danok() = 0;
    virtual ~Vozac(){}

};

class Avtomobilist: public Vozac{
private:
    float cena;
public:
    Avtomobilist(const char *ime = "",int vozrast=0,int brojTrki=0,bool veteran=false,float cena=0.0):
        Vozac(ime,vozrast,brojTrki,veteran)
    {
        this->cena=cena;
    }

    float zarabotuvacka()
    {
        return cena/5;
    }

    float danok()
    {
        if(brojTrki>10)
        {
            return(zarabotuvacka()*0.15);
        }
        else{
            return(zarabotuvacka()*0.10);
        }
    }

};

class Motociklist:public Vozac{
private:
    int moknost;
public:
    Motociklist(const char *ime = "",int vozrast=0,int brojTrki=0,bool veteran=false,int moknost=0):
    Vozac(ime,vozrast,brojTrki,veteran)
    {
        this->moknost=moknost;
    }

    float zarabotuvacka()
    {
        return moknost * 20;
    }

    float danok()
    {
        if(veteran==true)
        {
            return zarabotuvacka()*0.25;
        }
        else
        {
            return zarabotuvacka()*0.2;
        }
    }

};

int soIstaZarabotuvachka(Vozac **vozaci,int brojVozaci,Vozac *v)
{
    int broj=0;
    for(int i=0;i<brojVozaci;i++)
    {
        if(*v==*vozaci[i])
        {
            broj ++;
        }
    }
    return broj;
}

int main() {
	int n, x;
	cin >> n >> x;
	Vozac **v = new Vozac*[n];
	char ime[100];
	int vozrast;
	int trki;
	bool vet;
	for(int i = 0; i < n; ++i) {
		cin >> ime >> vozrast >> trki >> vet;
		if(i < x) {
			float cena_avto;
			cin >> cena_avto;
			v[i] = new Avtomobilist(ime, vozrast, trki, vet, cena_avto);
		} else {
			int mokjnost;
			cin >> mokjnost;
			v[i] = new Motociklist(ime, vozrast, trki, vet, mokjnost);
		}
	}
	cout << "=== DANOK ===" << endl;
	for(int i = 0; i < n; ++i) {
		cout << *v[i];
		cout << v[i]->danok() << endl;
	}
	cin >> ime >> vozrast >> trki >> vet;
	int mokjnost;
	cin >> mokjnost;
	Vozac *vx = new Motociklist(ime, vozrast, trki, vet, mokjnost);
	cout << "=== VOZAC X ===" << endl;
	cout << *vx;
	cout << "=== SO ISTA ZARABOTUVACKA KAKO VOZAC X ===" << endl;
	cout << soIstaZarabotuvachka(v, n, vx);
    for(int i = 0; i < n; ++i) {
        delete v[i];
    }
    delete [] v;
    delete vx;
	return 0;
