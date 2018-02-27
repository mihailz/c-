#include <iostream>
#include <stdlib.h>
#include <cstring>
using namespace std;

class PostoeckoLice{
private:
    char *error_msg;
public:
    PostoeckoLice(const char *error_msg)
    {
        this->error_msg=new char[strlen(error_msg)+1];
        strcpy(this->error_msg,error_msg);
    }

    PostoeckoLice(const PostoeckoLice &p)
    {
        this->error_msg=new char[strlen(p.error_msg)+1];
        strcpy(this->error_msg,p.error_msg);
    }

    PostoeckoLice& operator=(const PostoeckoLice &p)
    {
       if(this!=&p)
       {
           delete [] error_msg;
        this->error_msg=new char[strlen(p.error_msg)+1];
        strcpy(this->error_msg,p.error_msg);
       }
       return *this;
    }

    friend ostream& operator<<(ostream &out,const PostoeckoLice &p)
    {
        cout<<p.error_msg;

        return out;
    }

    ~PostoeckoLice()
    {
        delete [] error_msg;
    }

};

class Lice{
private:
    char ime[15];
    char prezime[15];
    char licna_karta[9];
    char datum[11];
public:
    Lice(const char *ime="",const char *prezime="",const char *licna_karta="",const char *datum="")
    {
        strcpy(this->ime,ime);
        strcpy(this->prezime,prezime);
        strcpy(this->licna_karta,licna_karta);
        strcpy(this->datum,datum);
    }
    char *getData()
    {
        return datum;
    }
    bool operator==(const Lice &l)
    {
        if(strcmp(licna_karta,l.licna_karta)==0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    friend ostream& operator<<(ostream &out,const Lice &l)
    {
        cout<<l.ime<<" "<<l.prezime<<" "<<l.licna_karta<<" "<<l.datum<<endl;

        return out;
    }

};

class Auditorium{
private:
    char ime[50];
    Lice *lica;
    int broj_lica;
public:
    Auditorium(const char *ime="")
    {
        strcpy(this->ime,ime);
        lica = NULL;
        broj_lica=0;
    }

    Auditorium(const Auditorium &a)
    {
        strcpy(this->ime,a.ime);
        this->lica = new Lice[a.broj_lica];
        for(int i=0;i<broj_lica;i++)
            this->lica[i]=a.lica[i];
        this->broj_lica=a.broj_lica;
    }

    Auditorium& operator=(const Auditorium &a)
    {
        if(this!=&a)
        {
            delete [] lica;
        strcpy(this->ime,a.ime);
        this->lica = new Lice[a.broj_lica];
        for(int i=0;i<broj_lica;i++)
            this->lica[i]=a.lica[i];
        this->broj_lica=a.broj_lica;
        }
        return *this;
    }

    Auditorium& operator+=(const Lice &a)
    {
    for(int i=0;i<broj_lica;i++){
        if(lica[i]==a){
            throw PostoeckoLice("Liceto e vekje prijaveno za nastanot!\n");
        }
    }

    Lice *temp = new Lice[broj_lica+1];
    for(int i=0;i<broj_lica;i++)
        temp[i] = lica[i];

    delete [] lica;
    lica = temp;
    lica[broj_lica++] = a;
    return *this;
}

friend ostream& operator<<(ostream &out,const Auditorium &a)
{
    cout<<a.ime<<endl;
    for(int i=0;i<a.broj_lica;i++){
        if(i%2==0){
            cout<<a.lica[i];
        }
    }

    return out;
}

void nagradeni(int m)
{
    char mesec[3];
    int k;
    for(int i=0;i<broj_lica;i++)
    {
        k=0;
        for(int j=3;j<5;j++){
            mesec[k++] = lica[i].getData() [j];
        }
        mesec[k]='\0';
        if(atoi(mesec)==m)
            cout<<lica[i];
        }
}

    ~Auditorium()
    {
        delete [] lica;
    }

};

int main(){

    char ime[15];
    char prezime[15];
    char lk[9];
    char datum[11];
    char naziv[50];
    int n;

    int tip;
    cin>>tip;

    if (tip==1){
        cout<<"-----Test Lice & operator <<-----" <<endl ;
        cin>>ime>>prezime>>lk>>datum;
        Lice l(ime, prezime, lk, datum);
        cout<<l;
    }
    else if (tip==2){
    	cout<<"-----Test Lice & operator == -----" <<endl ;
        cin>>ime>>prezime>>lk>>datum;
        Lice l1(ime, prezime, lk, datum);
        cin>>ime>>prezime>>lk>>datum;
        Lice l2(ime, prezime, lk, datum);
        if (l1==l2) cout<<"Isti se"<<endl;
        else cout<<"Ne se isti"<<endl;
    }
    else if (tip==3){
        cout<<"-----Test Auditorium, operator +=, operator << -----" <<endl ;
        cin.get();
		cin.getline(naziv,49);
        cin>>n;
        Auditorium a(naziv);
        for (int i = 0; i < n; i++){
            try{
            cin>>ime>>prezime>>lk>>datum;
        	Lice l(ime, prezime, lk, datum);
            a+=l;
            }catch(PostoeckoLice &p){
            cout<<p;
            }
        }
        cout<<a;
    }
    else if (tip==4){
      	cout<<"-----Test KorisnichkiProfil, operator +=, nagradeni -----" <<endl ;
      	cin.get();
		cin.getline(naziv,49);
        cin>>n;
        Auditorium a(naziv);
        for (int i = 0; i < n; i++){
            try{cin>>ime>>prezime>>lk>>datum;
        	Lice l(ime, prezime, lk, datum);
                a+=l;}
            catch(PostoeckoLice &p){
            cout<<p;
            }
        }
        cout<<"Nagradeni posetiteli:"<<endl;
      	a.nagradeni(8);

    }
    else if (tip==5){
    	cout<<"-----Test Exception -----" <<endl ;
      	cin.get();
		cin.getline(naziv,49);
        cin>>n;
        Auditorium a(naziv);
        for (int i = 0; i < n; i++){
            try {cin>>ime>>prezime>>lk>>datum;
        	Lice l(ime, prezime, lk, datum);
            a+=l;
                }
            catch(PostoeckoLice &p){
            cout<<p;
            }
        }
        cout<<a;

    }
    else if (tip==6){
    	cout<<"-----Test All -----" <<endl ;
      	cin.get();
		cin.getline(naziv,49);
        cin>>n;
        Auditorium a(naziv);
        for (int i = 0; i < n; i++){
            try {cin>>ime>>prezime>>lk>>datum;
        	Lice l(ime, prezime, lk, datum);
            a+=l;
                }
            catch(PostoeckoLice &p){
            cout<<p;
            }
        }
        cout<<a;

      	cout<<"Nagradeni posetiteli:"<<endl;
      	a.nagradeni(8);

    }

	return 0;
}
