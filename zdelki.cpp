#include <iostream>
#include <cstring>
using namespace std;

class NegativnaVrednost{
private:
    char *message;
public:
     NegativnaVrednost(const char *message)
    {
        this->message=new char[strlen(message)+1];
        strcpy(this->message,message);
    }
    NegativnaVrednost(const NegativnaVrednost &m)
    {
        this->message=new char[strlen(m.message)+1];
        strcpy(this->message,m.message);
    }
    NegativnaVrednost& operator=(const NegativnaVrednost &m1)
    {
        if(this!=&m1)
        {
            delete [] this->message;
        this->message=new char[strlen(m1.message)+1];
        strcpy(this->message,m1.message);
        }
        return *this;
    }
    friend ostream& operator<<(ostream &out,const NegativnaVrednost &nv)
    {
        cout<<nv.message<<endl;

        return out;
    }

    ~NegativnaVrednost()
    {
        delete [] message;
    }


};

class Zdelka{
private:
char ime[100];
float osnovna_cena;
char traenje[50];
static int popust;
int dopolnitelen_popust;
int broj_kuponi;
public:
    Zdelka(const char *ime="",float osnovna_cena=0.0,const char *traenje="",int dopolnitelen_popust=0,int broj_kuponi=0)
    {
       strcpy(this->ime,ime);
       this->osnovna_cena=osnovna_cena;
       strcpy(this->traenje,traenje);
       this->dopolnitelen_popust=dopolnitelen_popust;
       this->broj_kuponi=broj_kuponi;
    }
    const int getDopolnitelenPopust() const {
        return dopolnitelen_popust;
    }
    int getKuponi()
    {
        return broj_kuponi;
    }
    static void setPopust1(int pp)
    {
        popust=pp;
    }

    friend ostream& operator<<(ostream &out,const Zdelka &z)
    {
        cout<<z.ime<<endl;
        cout<<"Trae do: "<<z.traenje<<", "<<"prodadeni kuponi: "<<z.broj_kuponi<<", "<<"cena: "<<z.osnovna_cena<<", "<<"cena so popust: "<<z.osnovna_cena - ((z.popust + z.dopolnitelen_popust)/100.00) * z.osnovna_cena<<endl;
        return out;
    }
};
int Zdelka::popust=10;

class FINKI_Zdelki{
private:
    Zdelka *zdelki;
    int broj_zdelki;
public:
    FINKI_Zdelki()
    {
        zdelki=NULL;
        broj_zdelki=0;
    }

    FINKI_Zdelki(const FINKI_Zdelki &fz)
    {
        this->broj_zdelki=fz.broj_zdelki;
        this->zdelki=new Zdelka[broj_zdelki];
        for(int i=0;i<broj_zdelki;i++)
            this->zdelki[i]=fz.zdelki[i];
    }

    FINKI_Zdelki& operator=(const FINKI_Zdelki &fz1)
    {
        if(this!=&fz1)
        {
            delete [] this->zdelki;
        this->broj_zdelki=fz1.broj_zdelki;
        this->zdelki=new Zdelka[broj_zdelki];
        for(int i=0;i<broj_zdelki;i++)
            this->zdelki[i]=fz1.zdelki[i];
        }
        return *this;
    }

    FINKI_Zdelki& operator+=(const Zdelka &z)
    {
        if(z.getDopolnitelenPopust()<0)
            throw NegativnaVrednost("Vnesena e negativna vrednost za popustot!");

        Zdelka *temp = new Zdelka[broj_zdelki+1];

        for(int i=0;i<broj_zdelki;i++)
            temp[i]=zdelki[i];

        delete [] zdelki;
        zdelki = temp;
        zdelki[broj_zdelki++]=z;
        return *this;
    }


    friend ostream& operator<<(ostream &out,const FINKI_Zdelki &fz)
    {
        for(int i=0;i<fz.broj_zdelki;i++)
        {
            cout<<fz.zdelki[i];
        }

        return out;
    }

    void najprodavaniZdelki()
    {
        float prosek=0.0;
        for(int i=0;i<broj_zdelki;i++)
            prosek+=zdelki[i].getKuponi();

        prosek = prosek / broj_zdelki;
        for(int i=0;i<broj_zdelki;i++){
            if(zdelki[i].getKuponi()>prosek)
            {
                cout<<zdelki[i];
            }
        }
    }

};

int main(){
	int testCase;
	cin >> testCase;

	char ime[100];
    float cena;
	char traeDo[50];
    int popust;
    int prodKuponi;

	if (testCase == 1){
		cout << "===== Testiranje na klasata Zdelka ======" << endl;
        cin.get();
		cin.getline(ime,100);
        cin >> cena;
        cin.get();
        cin.getline(traeDo,50);
        cin >> popust;
		cin >> prodKuponi;
        cout << "===== CONSTRUCTOR ======" << endl;
		Zdelka z(ime, cena, traeDo, popust, prodKuponi);
		cout << z;

	}
    if (testCase == 2){
		cout << "===== Testiranje na static clenovi ======" << endl;
		cin.get();
		cin.getline(ime,100);
        cin >> cena;
        cin.get();
        cin.getline(traeDo,50);
        cin >> popust;
		cin >> prodKuponi;
        cout << "===== CONSTRUCTOR ======" << endl;
		Zdelka z(ime, cena, traeDo, popust, prodKuponi);
		cout << z;

		z.setPopust1(15);

        cout << z;
	}
	if (testCase == 3){
		cout << "===== Testiranje na klasata FINKI-Zdelki ======" << endl;
		cout << "CONSTRUCTOR" << endl;
        FINKI_Zdelki fz;
        int n;
        cin >> n;
        cout << "OPERATOR +=" << endl;
        for(int i = 0; i < n; ++i) {
            try{cin.get();
			cin.getline(ime,100);
        	cin >> cena;
        	cin.get();
        	cin.getline(traeDo,50);
        	cin >> popust;
			cin >> prodKuponi;
            Zdelka z(ime, cena, traeDo, popust, prodKuponi);
            fz += z;
               }
            catch(NegativnaVrednost &nv){
            cout<<nv;
            }
        }
        cout << fz <<endl;

        Zdelka x("Pica po izbor", 250, "01.10.2016", 42, 15);
        FINKI_Zdelki fz1 = fz;
        fz+=x;
        cout << fz << endl;
        cout << fz1 << endl;
	}
	if (testCase == 4){
		cout << "===== Testiranje na operatorot += (celosna verzija) ======" << endl;
		FINKI_Zdelki fz;
        int n;
        cin >> n;
        cout << "OPERATOR +=" << endl;
        for(int i = 0; i < n; ++i) {
            try{cin.get();
			cin.getline(ime,100);
        	cin >> cena;
        	cin.get();
        	cin.getline(traeDo,50);
        	cin >> popust;
			cin >> prodKuponi;
            Zdelka z(ime, cena, traeDo, popust, prodKuponi);
            fz += z;
               }
             catch(NegativnaVrednost &nv){
            cout<<nv;
            }

        }
        cout << fz;
	}

	if (testCase == 5){
		cout << "===== Testiranje na metodot najprodavaniZdelki ======" << endl << endl;
		FINKI_Zdelki fz;
        int n;
        cin >> n;
        for(int i = 0; i < n; ++i) {
            try{ cin.get();
            cin.getline(ime,100);
            cin >> cena;
            cin.get();
            cin.getline(traeDo,50);
            cin >> popust;
            cin >> prodKuponi;
            Zdelka z(ime, cena, traeDo, popust, prodKuponi);
            fz += z;
               }
             catch(NegativnaVrednost &nv){
            cout<<nv;
            }
        }
        cout << "Site zdelki:" << endl;
        cout << fz << endl;

        cout << "Najprodavani zdelki:" << endl;
        fz.najprodavaniZdelki();
	}


	return 0;
}
