#include <iostream>
#include <cstring>
using namespace std;

class Karticka{
public:

    bool operator<(Karticka &k)
    {
        if(vkupnaCena()<k.vkupnaCena())
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    friend ostream& operator<<(ostream &out, Karticka &k1)
    {
        cout<<"Vkupna cena: "<<k1.vkupnaCena()<<endl;
        cout<<"Broj na vozenja: "<<k1.brojVozenja()<<endl;

        return out;
    }
    virtual  int vkupnaCena()=0;
    virtual  int brojVozenja() =0;
    virtual ~Karticka(){}

};

class KartickaAvtobus:public Karticka{
private:
    int cena_karticka;
    int cena_vozenje;
    int broj_vozenja;
public:
    KartickaAvtobus(int cena_karticka=0,int cena_vozenje=0,int broj_vozenja=0):
        Karticka()
    {
        this->cena_karticka=cena_karticka;
        this->cena_vozenje=cena_vozenje;
        this->broj_vozenja=broj_vozenja;
    }

    int vkupnaCena()
    {
        return cena_karticka + (cena_vozenje*broj_vozenja);
    }
    int brojVozenja()
    {
        return broj_vozenja;
    }
    ~KartickaAvtobus(){}

};

class KartickaVoz:public Karticka{
private:
    int broj_vozenja;
    bool gradcka_oblast;
public:
    KartickaVoz(int broj_vozenja=0,bool gradcka_oblast=false):
        Karticka()
    {
        this->broj_vozenja=broj_vozenja;
        this->gradcka_oblast=gradcka_oblast;
    }

    int vkupnaCena()
    {
        if(gradcka_oblast==true)
        {
            return broj_vozenja*50;
        }
        else
        {
            return broj_vozenja*95;
        }
    }

    int brojVozenja()
    {
        return broj_vozenja;
    }
    ~KartickaVoz(){}
};


class AvtomatZaKarticki{
private:
public:

static int total(Karticka**karticki, int n)
{
    int sum=0;
    for(int i=0;i<n;i++){
        sum+=karticki[i]->vkupnaCena();
    }
    return sum;
}

};
int main() {
    int n;
    cin >> n;
    if(n == 0) {
		cout << "Constructors" << endl;
        KartickaAvtobus ds(150,35,2);
        KartickaVoz cs(15,false);
        cout << "OK" << endl;
    } else if(n == 1) {
  		cout << "operator <<" << endl;
        KartickaAvtobus ds(150,35,2);
        KartickaVoz cs(10,true);
        cout << ds << endl;
        cout << cs << endl;
    } else if(n == 2) {
  		cout << "<" << endl;
        KartickaAvtobus ds(150,35,2);
        KartickaVoz cs(20,true);
        KartickaVoz css(30, false);
        cout << (ds < cs) << endl;
        cout << (cs < ds) << endl;
        cout << (cs < css) << endl;
        cout << (cs < css) << endl;
    } else if(n == 3) {
  		cout << "Karticka total" << endl;
        KartickaAvtobus ds1(150,35,2);
        KartickaAvtobus ds2(100,80,5);
        KartickaAvtobus ds3(150,40,1);
        KartickaVoz cs1(15,false);
        KartickaVoz cs2(10,true);
        KartickaVoz cs3(20,true);
        Karticka** s = new Karticka*[6];
        s[0] = &ds1;
        s[1] = &ds2;
        s[2] = &ds3;
        s[3] = &cs1;
        s[4] = &cs2;
        s[5] = &cs3;
        cout<<AvtomatZaKarticki::total(s, 6);
        delete [] s;
    }

    return 0;
}
