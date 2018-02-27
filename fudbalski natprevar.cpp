#include <iostream>
#include <stdlib.h>
#include <cstring>
using namespace std;

class InvalidTeamName{
private:
    char *error_msg;
public:
    InvalidTeamName(const char *error_msg)
    {
        this->error_msg=new char[strlen(error_msg)+1];
        strcpy(this->error_msg,error_msg);
    }

    InvalidTeamName(const InvalidTeamName &t)
    {
         this->error_msg=new char[strlen(t.error_msg)+1];
        strcpy(this->error_msg,t.error_msg);
    }

    InvalidTeamName& operator=(const InvalidTeamName &t)
    {
        if(this!=&t)
        {
            delete [] this->error_msg;
        this->error_msg=new char[strlen(t.error_msg)+1];
        strcpy(this->error_msg,t.error_msg);
        }
        return *this;
    }

    char *what()
    {
        return error_msg;
    }

    ~InvalidTeamName()
    {
        delete [] error_msg;
    }


};

class Gol{
private:
    char *strelec;
    int minuta;
    char tim[50];
public:
    Gol(const char *strelec="",int minuta=0,const char *tim="")
    {
        this->strelec=new char[strlen(strelec)+1];
        strcpy(this->strelec,strelec);
        this->minuta=minuta;
        strcpy(this->tim,tim);
    }

    char *getTim()
    {
        return tim;
    }
    Gol(const Gol &g)
    {
        this->strelec=new char[strlen(g.strelec)+1];
        strcpy(this->strelec,g.strelec);
        this->minuta=g.minuta;
        strcpy(this->tim,g.tim);
    }

    Gol& operator=(const Gol &g)
    {
        if(this!=&g)
        {
            delete [] this->strelec;
        this->strelec=new char[strlen(g.strelec)+1];
        strcpy(this->strelec,g.strelec);
        this->minuta=g.minuta;
        strcpy(this->tim,g.tim);
        }
        return *this;
    }

    friend ostream& operator<<(ostream &out,const Gol &g)
    {
        cout<<g.minuta<<" "<<g.strelec<<endl;

        return out;
    }
    Gol& operator++()
    {
        minuta++;
        return *this;
    }

    Gol& operator--()
    {
        --minuta;
        return *this;
    }

~Gol()
{
    delete [] strelec;
}
};

class Natprevar{
private:
    Gol *golovi;
    char team1[50];
    char team2[50];
    int broj_golovi;
public:
    Natprevar(const char *team1="",const char *team2="")
    {
        strcpy(this->team1,team1);
        strcpy(this->team2,team2);
        golovi=NULL;
        broj_golovi=0;
    }

    Natprevar(const Natprevar &n)
    {
        strcpy(this->team1,n.team1);
        strcpy(this->team2,n.team2);
        this->golovi = new Gol[n.broj_golovi];
        for(int i=0;i<broj_golovi;i++)
            this->golovi[i]=n.golovi[i];
        this->broj_golovi=n.broj_golovi;
    }

    Natprevar& operator=(const Natprevar &n)
    {
        if(this!=&n)
        {
            delete [] this->golovi;
        strcpy(this->team1,n.team1);
        strcpy(this->team2,n.team2);
        this->golovi = new Gol[n.broj_golovi];
        for(int i=0;i<broj_golovi;i++)
            this->golovi[i]=n.golovi[i];
        this->broj_golovi=n.broj_golovi;
        }
        return *this;
    }

    Natprevar& operator+=( Gol &g)
    {
        if((strcmp(g.getTim(),team1)!=0)&&strcmp(g.getTim(),team2)!=0){
            throw InvalidTeamName(g.getTim());
        }

        Gol *temp = new Gol[broj_golovi+1];
        for(int i=0;i<broj_golovi;i++)
            temp[i]=golovi[i];

        delete [] golovi;
        golovi=temp;
        golovi[broj_golovi++]=g;
        return *this;
    }


    friend ostream& operator<<(ostream &out,const Natprevar &n)
    {
        cout << n.team1 << " - " << n.team2 << endl;
        for(int i=0;i<n.broj_golovi;i++)
            cout<<n.golovi[i];

        return out;

    }
    ~Natprevar()
    {
        delete [] golovi;
    }
};


int main() {
    char team1[50];
    char team2[50];
    cin >> team1;
    cin >> team2;
    Natprevar n(team1, team2);
    int x;
    cin >> x;
    char player[100];
    int m;
    for(int i = 0; i < x; ++i) {
        cin >> player;
        cin >> m;
        cin >> team1;
        Gol g(player, m, team1);
        try {
    		n += g;
        } catch(InvalidTeamName &e) {
            cout << "Invalid team name: " << e.what() << endl;
        }
    }
    cout << n << endl;
    return 0;
}
