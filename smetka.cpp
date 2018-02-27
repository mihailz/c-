#include <iostream>
#include <cstring>
#include <stdlib.h>
using namespace std;

class PostoeckaSmetka{
private:
    char *errorMsg;
public:
    PostoeckaSmetka(const char *errorMsg)
    {
        this->errorMsg=new char[strlen(errorMsg)+1];
        strcpy(this->errorMsg,errorMsg);
    }

    PostoeckaSmetka(const PostoeckaSmetka &ps)
    {
        this->errorMsg=new char[strlen(ps.errorMsg)+1];
        strcpy(this->errorMsg,ps.errorMsg);
    }

    PostoeckaSmetka& operator=(const PostoeckaSmetka &ps)
    {
        if(this!=&ps)
        {
            delete [] errorMsg;
        this->errorMsg=new char[strlen(ps.errorMsg)+1];
        strcpy(this->errorMsg,ps.errorMsg);
        }
        return *this;
    }

    friend ostream& operator<<(ostream &out,const PostoeckaSmetka &ps)
    {
        cout<<ps.errorMsg;

        return out;
    }

    ~PostoeckaSmetka()
    {
        delete [] errorMsg;
    }


};

class Smetka{
private:
    char *br_smetki;
    int cena_naplata;
    char data[8];
    bool status;
public:
    Smetka(const char *br_smetki="",int cena_naplata=0,const char *data="",bool status=false)
    {
        this->br_smetki=new char[strlen(br_smetki)+1];
        strcpy(this->br_smetki,br_smetki);
        this->cena_naplata=cena_naplata;
        strcpy(this->data,data);
        this->status=status;
    }
    char *getDatum()
    {
    	return data;
    }
    int getCena()
    {
        return cena_naplata;
    }

    bool getStatus()
    {
    	return status;
    }
    char *getSmetki()
    {
        return br_smetki;
    }
    Smetka(const Smetka &s)
    {
        this->br_smetki=new char[strlen(s.br_smetki)+1];
        strcpy(this->br_smetki,s.br_smetki);
        this->cena_naplata=s.cena_naplata;
        strcpy(this->data,s.data);
        this->status=s.status;
    }

    Smetka& operator=(const Smetka &s)
    {
        if(this!=&s)
        {
            delete [] br_smetki;
        this->br_smetki=new char[strlen(s.br_smetki)+1];
        strcpy(this->br_smetki,s.br_smetki);
        this->cena_naplata=s.cena_naplata;
        strcpy(this->data,s.data);
        this->status=s.status;
        }
        return *this;
    }

    bool operator==(const Smetka &s)
    {
        if(strcmp(br_smetki,s.br_smetki)==0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    friend ostream& operator<<(ostream &out,const Smetka &s)
    {
        cout<<s.br_smetki<<"("<<s.data<<")"<<" - "<<s.cena_naplata<<endl;

        return out;
    }

    ~Smetka()
    {
        delete [] br_smetki;
    }
};

class KorisnichkiProfil{
private:
    char ime[30];
    Smetka smetki[30];
    int broj_smetki;
public:
    KorisnichkiProfil(const char *ime="")
    {
        strcpy(this->ime,ime);
        broj_smetki=0;
    }

    KorisnichkiProfil& operator+=(const Smetka &s)
    {
        for(int i=0;i<broj_smetki;i++)
        {
            if(smetki[i]==s){
                throw PostoeckaSmetka("Smetkata vekje postoi\n");

        }
        }

        smetki[broj_smetki++]=s;
        return *this;
    }

     friend ostream& operator<<(ostream &out, KorisnichkiProfil &kp)
    {
        cout<<"Neplateni smetki na korisnikot "<<kp.ime<<" "<<"se:"<<endl;
        for(int i=0;i<kp.broj_smetki;i++){
                if(!kp.smetki[i].getStatus())
            cout<<kp.smetki[i];
        }

        return out;
    }

int vkupnaCena(int m,int y)
{
	char mesec[3],godina[5];
    int k,sum=0;

    for(int i=0;i<broj_smetki;i++)
    {
    	for(k=0;k<2;k++)
            mesec[k] = smetki[i].getDatum() [k];
        mesec[k]='\0';
        k=0;
        for(int j=3;j<strlen(smetki[i].getDatum());j++)
            godina[k++] = smetki[i].getDatum() [j];
        godina[k]='\0';

        if(atoi(mesec)==m&&atoi(godina)==y)
            sum+=smetki[i].getCena();


    }

    return sum;


}
};

int main(){
char broj[50],mesec[8],ime[50];
int cena,n;
bool status;


int tip;
cin>>tip;

if (tip==1){
   cout<<"-----Test Smetka & operator <<-----" <<endl ;
   cin>>broj>>cena>>mesec>>status;
   Smetka s(broj,cena,mesec,status);
   cout<<s;
}else if (tip==2){
   cout<<"-----Test Smetka & operator == -----" <<endl ;
   cin>>broj>>cena>>mesec>>status;
   Smetka s1(broj,cena,mesec,status);
   cin>>broj>>cena>>mesec>>status;
   Smetka s2(broj,cena,mesec,status);
   if (s1==s2) cout<<"Isti se"<<endl;
   else cout<<"Ne se isti"<<endl;

}else if (tip==3){
   cout<<"-----Test KorisnichkiProfil & operator += & << -----" <<endl ;
   cin>>ime>>n;
   KorisnichkiProfil kp(ime);
   for (int i=0;i<n;i++){
       try{cin>>broj>>cena>>mesec>>status;
      Smetka s(broj,cena,mesec,status);
           kp+=s;
          }
       catch(PostoeckaSmetka &ps){
            cout<<ps;
            }
   }
   cout<<kp;
}else if (tip==4){
   cout<<"-----Test KorisnichkiProfil & operator += & vkupnaCena -----" <<endl ;
   cin>>ime>>n;
   KorisnichkiProfil kp(ime);
   for (int i=0;i<n;i++){
       try {cin>>broj>>cena>>mesec>>status;
      Smetka s(broj,cena,mesec,status);
      kp+=s;
           }
       catch(PostoeckaSmetka &ps){
            cout<<ps;
            }
   }
   int m,y;
   cin>>m>>y;
   cout<<"Vkupnata cena za mesec "<<m<<" i godina "<<y<<" e:";
   cout<<kp.vkupnaCena(m,y)<<endl;
} else if (tip==5){
  cout<<"-----Test Exception -----" <<endl ;
  cin>>ime>>n;
  KorisnichkiProfil kp(ime);
  for (int i=0;i<n;i++){
      try {cin>>broj>>cena>>mesec>>status;
    Smetka s(broj,cena,mesec,status);
    kp+=s;
          }
      catch(PostoeckaSmetka &ps){
            cout<<ps;
            }
  }
  cout<<kp;

}
  else if (tip==6){
  cout<<"-----Test all -----" <<endl ;
  cin>>ime>>n;
  KorisnichkiProfil kp(ime);
  for (int i=0;i<n;i++){
      try{ cin>>broj>>cena>>mesec>>status;
    Smetka s(broj,cena,mesec,status);
    kp+=s;
         }
      catch(PostoeckaSmetka &ps){
            cout<<ps;
            }
  }
  cout<<kp;
  int m,y;
  cin>>m>>y;
  cout<<"Vkupnata cena za mesec "<<m<<" i godina "<<y<<" e:";
  cout<<kp.vkupnaCena(m,y)<<endl;

}

return 0;
}
