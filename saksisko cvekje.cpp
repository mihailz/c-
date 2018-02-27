#include <iostream>
using namespace std;
#include <cstring>

class SaksiskoCveke{
protected:
    char ime[20];
    int osnovnaCena;
    char familija[20];
public:
    SaksiskoCveke(const char *ime="",int osnovnaCena=0,const char *familija="")
    {
        strcpy(this->ime,ime);
        this->osnovnaCena=osnovnaCena;
        strcpy(this->familija,familija);
    }

    char *getIme()
    {
        return ime;
    }

    char *getFamilija()
    {
        return familija;
    }

    bool operator==(SaksiskoCveke &s)
    {
        if(strcmp(familija,s.familija)==0)
        {
            return true;
        }else{
            return false;
        }
    }
    virtual int presmetajCena()=0;
    virtual ~SaksiskoCveke(){}

};

class BezCvet:public SaksiskoCveke{
private:
    int denoviStarost;
public:
    BezCvet(const char *ime="",int osnovnaCena=0,const char *familija="",int denoviStarost=0):
    SaksiskoCveke(ime,osnovnaCena,familija)
    {
        this->denoviStarost=denoviStarost;
    }

    int presmetajCena()
    {
        if(denoviStarost<=10)
        {
            return osnovnaCena + (osnovnaCena*0.2);
        }
        else if(denoviStarost<=35)
        {
            return osnovnaCena + (osnovnaCena*0.1);
        }
    }
};

class SoCvet: public SaksiskoCveke{
private:
    int brojCvetovi;
public:
    SoCvet(const char *ime="",int osnovnaCena=0,const char *familija="",int brojCvetovi=0):
        SaksiskoCveke(ime,osnovnaCena,familija)
    {
        this->brojCvetovi=brojCvetovi;
    }

    int presmetajCena()
    {
        return osnovnaCena + brojCvetovi;
    }
};

void pecatiMaxCena(SaksiskoCveke **cvekina,int brojCvekina,SaksiskoCveke &c)
{
    SaksiskoCveke *najskapoCveke =cvekina[0];
    for(int i=0;i<brojCvekina;i++)
    {
        if(strcmp(cvekina[i]->getFamilija(),c.getFamilija())==0)
        {
            if(cvekina[i]->presmetajCena()>najskapoCveke->presmetajCena())
            {
                najskapoCveke=cvekina[i];
            }
        }
    }
    cout<<najskapoCveke->getIme()<<" "<<najskapoCveke->getFamilija()<<" "<<najskapoCveke->presmetajCena()<<endl;
}
int main(){

char ime[10],familija[10];
int tip,starost,broj,cena;
int n;
cin>>n;
SaksiskoCveke **cvekinja;
cvekinja=new SaksiskoCveke*[n];

for (int i=0;i<n;i++){

    cin>>tip>>ime>>cena>>familija;
    if (tip==1) {
        cin>>starost;
        cvekinja[i]=new BezCvet(ime,cena,familija,starost);

    }
    else {
        cin>>broj;
        cvekinja[i]=new SoCvet(ime,cena,familija,broj);
    }


}

BezCvet nov("opuntia",90,"cactus",10);
pecatiMaxCena(cvekinja,n,nov);

for (int i=0;i<n;i++) delete cvekinja[i];
delete [] cvekinja;
return 0;
}
