#include <iostream>
using namespace std;
#include <cstring>

class TimRakomet{
protected:
    char ime[30];
    float prosek;
public:
    TimRakomet(const char *ime="",float prosek=0.0)
    {
        strcpy(this->ime,ime);
        this->prosek=prosek;
    }

    char *getIme()
    {
        return ime;
    }
virtual float dostignuvanje() = 0;
virtual ~TimRakomet(){}

};

class Klub:public TimRakomet{
private:
    int brojTituli;
public:
    Klub(const char *ime="",float prosek=0.0,int brojTituli=0):
        TimRakomet(ime,prosek)
    {
        this->brojTituli=brojTituli;
    }


    float dostignuvanje()
    {
        return (prosek * 5) + (brojTituli*50);
    }
};

class Reprezentacija:public TimRakomet{
protected:
    int rank[3];
public:
    Reprezentacija(const char *ime="",float prosek=0.0,int *rank=0):
        TimRakomet(ime,prosek)
        {
            for(int i=0;i<3;i++)
                this->rank[i]=rank[i];
        }


        float dostignuvanje()
        {
            float p = prosek * 5;

            for(int i=0;i<3;i++)
            {
                if(rank[i]==1)
                {
                    p+=60;
                }
                else if(rank[i]==2)
                {
                    p+=40;
                }
                else if(rank[i]==3)
                {
                    p+=20;
                }
            }
            return p;
        }

};

void najdobar(TimRakomet **timovi,int brojTimovi)
{
    TimRakomet *najdostignuvanje = timovi[0];
    for(int i=0;i<brojTimovi;i++){
        if(timovi[i]->dostignuvanje()>najdostignuvanje->dostignuvanje())
        {
            najdostignuvanje=timovi[i];
        }
    }
    cout<<najdostignuvanje->getIme()<<endl;
    cout<<najdostignuvanje->dostignuvanje()<<endl;
}
int main() {
	int n;
	cin >> n;
	TimRakomet** timovi = new TimRakomet*[n];
	for(int i = 0; i < n; ++i) {
		char ime[30];
		float prosekGolovi;
		cin >> ime >> prosekGolovi;
		if(i % 2) {
			int tituli;
			cin >> tituli;
			timovi[i] = new Klub(ime, prosekGolovi, tituli);
		} else {
			int rank[] = {0, 0, 0};
			cin >> rank[0] >> rank[1] >> rank[2];
			timovi[i] = new Reprezentacija(ime, prosekGolovi, rank);
		}
	}

	najdobar(timovi, n);

	for(int i = 0; i < n; ++i) {
		delete timovi[i];
	}
	delete [] timovi;
	return 0;
}
