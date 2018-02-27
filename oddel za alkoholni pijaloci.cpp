#include <iostream>
using namespace std;
#include <cstring>

class Pijalok{
private:
    char naziv[20];
    char osnovna_sostojka[20];
    float kolicina_dl;
    static int cena_decilitar;
public:
    Pijalok(const char *naziv="",const char *osnovna_sostojka="",float kolicina_dl=0.0)
    {
        strcpy(this->naziv,naziv);
        strcpy(this->osnovna_sostojka,osnovna_sostojka);
        this->kolicina_dl=kolicina_dl;

    }

    char *getSostojka()
    {
        return osnovna_sostojka;
    }

    char *getNaziv()
    {
        return naziv;
    }
    static int getCenaDl()
    {
        return cena_decilitar;
    }

    static void setCenaDl(int cenaDL)
    {
        cena_decilitar=cenaDL;
    }

    virtual float cena()
    {
        return kolicina_dl * cena_decilitar;
    }



};
int Pijalok::cena_decilitar=3;


class AlkoholenPijalok:public Pijalok{
private:
    float stepen_alkohol;
    int godina;
public:
    AlkoholenPijalok(const char *naziv="",const char *osnovna_sostojka="",float kolicina_dl=0.0,float stepen_alkohol=0.0,int godina=0):
        Pijalok(naziv,osnovna_sostojka,kolicina_dl)
    {
        this->stepen_alkohol=stepen_alkohol;
        this->godina=godina;
    }

    float getStepen()
    {
        return stepen_alkohol;
    }

    float cena()
    {
        float c=Pijalok::cena();
        if(strcmp(getNaziv(),"Vino")==0){
            if(godina>2010){
                return c*=10;
            }
             if(godina<=2010)
            {
                return c*=15;
            }
        }
         if(strcmp(getSostojka(),"kompir")==0)
        {
            return c+=50;
        }
        if(strcmp(getSostojka(),"jacmen")==0)
        {
            return c+=70;
        }


           return c+=100;


    }

};

class AlkoholenOddel{
private:
    AlkoholenPijalok *pijaloci[50];
    int broj_pijaloci;
public:
    AlkoholenOddel()
    {
        broj_pijaloci=0;
    }

int primiAPijalok(char* naziv, char* osnovnaSostojka, float kolicina, float alkohol, int godina)
{
    pijaloci[broj_pijaloci]=new AlkoholenPijalok(naziv,osnovnaSostojka,kolicina,alkohol,godina);
    broj_pijaloci++;

    return broj_pijaloci;
}

void pecati(int alkohol)
{
    cout<<"Povisok stepen na alkohol od "<<alkohol<<" "<<"imaat:"<<endl;
    for(int i=0;i<broj_pijaloci;i++){
		if(pijaloci[i]->getStepen()>alkohol)
        {
        	cout<<pijaloci[i]->getNaziv() << " " << pijaloci[i]->cena() << endl;
        }
    }
}
};

int main(){

    int tip,n,novaCena;
    char naziv[20], osnovnaSostojka[20];
    int godina;
    float kolicina, alkohol;
    AlkoholenOddel ao;

    cin>>n;
    for (int i=0;i<n;i++){
        cin>>tip;
        if (tip==1){//Pijalok
        	cin>>naziv>>osnovnaSostojka>>kolicina;
        	Pijalok p1(naziv,osnovnaSostojka,kolicina);
        	cout<<"Kreiran e pijalok so naziv: "<<p1.getNaziv()<<endl;
        }
        else if (tip==2){//cena - Pijalok
        	cin>>naziv>>osnovnaSostojka>>kolicina;
        	Pijalok p1(naziv,osnovnaSostojka,kolicina);
        	cout<<"Osnovna cena na pijalokot so naziv "<<p1.getNaziv()<< " e: " <<p1.cena()<<endl;
        }
        else if (tip==3){//AlkoholenPijalok
            cin>>naziv>>osnovnaSostojka>>kolicina>>alkohol>>godina;
            AlkoholenPijalok p2(naziv,osnovnaSostojka,kolicina, alkohol, godina);
            cout<<"Kreiran e alkoholen pijalog so naziv "<<p2.getNaziv()<<" i stepen "<<p2.getStepen()<<endl;
        }
        else if (tip==4){//cena - AlkoholenPijalok
        	cin>>naziv>>osnovnaSostojka>>kolicina>>alkohol>>godina;
        	AlkoholenPijalok p2(naziv,osnovnaSostojka,kolicina, alkohol, godina);
            cout<<"Cenata na alkoholniot pijalog so naziv "<<p2.getNaziv()<<" e: "<<p2.cena()<<endl;
        }
        else if (tip==5) {//dodadi
        	cin>>naziv>>osnovnaSostojka>>kolicina>>alkohol>>godina;
        	cout<<ao.primiAPijalok(naziv,osnovnaSostojka,kolicina,alkohol,godina)<<endl;
        }
        else if (tip==6) {//pecati
        	cin>>alkohol;
            ao.pecati(alkohol);
        }
        else if (tip==7){//smeni cena
        	cin>>novaCena;
          	Pijalok::setCenaDl(novaCena);
            cout<<"Nova cena: "<<Pijalok::getCenaDl()<<endl;

            cin>>naziv>>osnovnaSostojka>>kolicina>>alkohol>>godina;
        	AlkoholenPijalok p2(naziv,osnovnaSostojka,kolicina, alkohol, godina);
            cout<<"Cenata na alkoholniot pijalog so naziv "<<p2.getNaziv()<<" e: "<<p2.cena()<<endl;
        }

    }

    return 0;
}
