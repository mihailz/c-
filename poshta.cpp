#include <iostream>
using namespace std;
#include <cstring>

class Pratka{
private:
    int ID;
    static int cenaProcesiranje;
public:
    Pratka(int ID=0)
    {
        this->ID=ID;
    }

    int getId()
    {
        return ID;
    }
    static void setCenaProcesiranje(int cena)
    {
        cenaProcesiranje=cena;
    }

    static int getCenaProcesiranje()
    {
        return cenaProcesiranje;
    }



};
int Pratka::cenaProcesiranje=150;

class Pliko: public Pratka{
private:
    int shirina;
    int visina;
    char primach[50];
public:
    Pliko(int ID=0,const char *primach="",int shirina=0,int visina=0):
        Pratka(ID)
    {
        strcpy(this->primach,primach);
        this->shirina=shirina;
        this->visina=visina;
    }
    char *getPrimach()
    {
        return primach;
    }

    int cena()
    {
        return Pratka::getCenaProcesiranje() + 0.3*(shirina*visina);
    }
};

class Poshta{
private:
    Pliko plikoa[100];
    int brojPlikoa;
    Pratka p1;
public:
    Poshta()
    {
        brojPlikoa=0;
    }

     int pratiPliko(int id, char* primach, int d, int w){
        Pliko p(id,primach,d,w);
         plikoa[brojPlikoa++]=p;
         return p.cena();
    }

    void pecatiPlikoaDo(char * primach)
    {
         cout<<"Za"<<" "<<primach<<" "<<"se plikoata so id-a: ";

        for(int i=0;i<brojPlikoa;i++)
        {
            if(strcmp(plikoa[i].getPrimach(),primach)==0)
            {
                cout<<plikoa[i].getId()<<" ";
            }
        }
        cout<<endl;
    }

};
int main(){

int tip,n,novaCena,id,visina,shirina;
char primach[50];

Poshta p;

cin>>n;
for (int i=0;i<n;i++){
   cin>>tip;
    if (tip==1) {//pratiPliko
        cin>>id>>primach>>shirina>> visina;
        cout<<"Cenata za prakjanje na pliko so id "<<id<<" e:"<<p.pratiPliko(id,primach,shirina,visina)<<endl;
    } else if (tip==2) {//pecatiPlikoaDo
        cin>>primach;
        p.pecatiPlikoaDo(primach);
    } else if (tip==3){//setCenaProcesiranje
        cin>>novaCena;
        Pratka::setCenaProcesiranje(novaCena);
    } else if (tip==4){//Pratka
        cin>>id;
        Pratka p1(id);
        cout<<"Kreirana e pratka so ID: "<<p1.getId()<<endl;
    } else {//Pliko
        cin>>id>>primach>>shirina>> visina;
        Pliko p2(id,primach,shirina,visina);
        cout<<"Cena na pratka so ID: "<<p2.getId()<<" Do: "<<p2.getPrimach()<<" e: "<<p2.cena()<<endl;
    }
}
return 0;
}
