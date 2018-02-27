#include <iostream>
using namespace std;
#include <cstring>

class Vleznica{
protected:
    char natprevar[50];
    float osnovna_cena;
public:
    Vleznica(const char *natprevar="",float osnovna_cena=0.0)
    {
        strcpy(this->natprevar,natprevar);
        this->osnovna_cena=osnovna_cena;
    }
    char *getIme()
    {
        return natprevar;
    }

    virtual float cena() = 0;
    virtual ~Vleznica(){}

};

class VleznicaSedenje:public Vleznica{
private:
    int blok;
    int red;
public:
    VleznicaSedenje(const char *natprevar="",float osnovna_cena=0.0,int blok=0,int red=0):
        Vleznica(natprevar,osnovna_cena)
        {
            this->blok=blok;
            this->red=red;
        }

        float cena()
        {
            if(red<8)
            {
                return osnovna_cena + (osnovna_cena * 0.4);
            }
            else if(red>=8&&red <=15)
            {
                return osnovna_cena + (osnovna_cena * 0.2);
            }
            else
            {
                return osnovna_cena;
            }
        }
};

class VleznicaStoenje:public Vleznica{
private:
    char tribina;
public:
    VleznicaStoenje(const char *natprevar="",float osnovna_cena=0.0,const char tribina='S'):
        Vleznica(natprevar,osnovna_cena)
        {
            this->tribina=tribina;
        }


        float cena()
        {
            if(tribina=='S')
            {
                return osnovna_cena + (osnovna_cena*0.3);
            }
            else{
                return osnovna_cena;
            }
        }

};

void najmalaCena(Vleznica **vleznici,int brojVleznici)
{
    Vleznica *najmalacena = vleznici[0];
    for(int i=0;i<brojVleznici;i++){
        if(vleznici[i]->cena()<najmalacena->cena())
        {
            najmalacena=vleznici[i];
        }
    }
    cout<<najmalacena->getIme()<<endl;
    cout<<najmalacena->cena()<<endl;
}

int main() {
	int n;
	cin >> n;
	Vleznica** vleznici = new Vleznica*[n];
	for(int i = 0; i < n; ++i) {
		char ime[30];
		float osnovnaCena;
		cin >> ime >> osnovnaCena;
		if(i % 2) {
			int blok, red;
			cin >> blok >> red;
			vleznici[i] = new VleznicaSedenje(ime, osnovnaCena, blok, red);
		} else {
			char tribina;
			cin >> tribina;
			vleznici[i] = new VleznicaStoenje(ime, osnovnaCena, tribina);
		}
	}

	najmalaCena(vleznici, n);

	for(int i = 0; i < n; ++i) {
		delete vleznici[i];
	}
	delete [] vleznici;
	return 0;
}
