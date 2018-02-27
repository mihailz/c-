#include <iostream>
#include <cstring>
using namespace std;

// vasiot kod tuka
#include <iostream>
#include <cstring>
using namespace std;

class Ticket{
protected:
    int seriski_broj;
    double koeficienti[16];
    int broj_koeficienti;
    double uplata;
    bool dobiten;
public:
    Ticket(int seriski_broj=0,double *koeficienti=0,int broj_koeficienti=0,double uplata =0,bool dobiten=false)
    {
        this->seriski_broj=seriski_broj;
        for(int i=0;i<broj_koeficienti;i++)
            this->koeficienti[i]=koeficienti[i];
        this->broj_koeficienti=broj_koeficienti;
        this->uplata=uplata;
        this->dobiten=dobiten;
    }
    int getSeriskiBroj()
    {
        return seriski_broj;
    }

     bool getDobiten(){
        return dobiten;
    }
    bool operator>( Ticket &t)
    {
        if(loss()>t.loss())
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    virtual double income()=0;
    virtual double loss()=0;
    virtual ~Ticket(){}
};


class ETicket:public Ticket{
private:
public:
    ETicket(int seriski_broj=0,double *koeficienti=0,int broj_koeficienti=0,double uplata =0,bool dobiten=false):
        Ticket(seriski_broj,koeficienti,broj_koeficienti,uplata,dobiten)
    {

    }

    double loss()
    {
        double sumaKoeficienti = 1;
        for(int i=0;i<broj_koeficienti;i++){
            sumaKoeficienti*=koeficienti[i];
        }
        return uplata * sumaKoeficienti;
    }

    double income()
    {
        return uplata;
    }

};

class OTCTicket:public Ticket{
private:
    static int provizija;
public:
    OTCTicket(int seriski_broj=0,double *koeficienti=0,int broj_koeficienti=0,double uplata =0,bool dobiten=false):
        Ticket(seriski_broj,koeficienti,broj_koeficienti,uplata,dobiten)
    {

    }

    static void setCommission(int prov)
    {
        provizija=prov;
    }

    double loss()
    {
        double sumaKoeficienti = 1;
        for(int i=0;i<broj_koeficienti;i++){
            sumaKoeficienti*=koeficienti[i];
        }
        return uplata * sumaKoeficienti;
    }

    double income()
    {
        return uplata + (provizija/100.00) * uplata;
    }

};
int OTCTicket::provizija=0;

double profit(Ticket **tickets,int broj_tiketi)
{
    double uplati=0,isplati=0;
    for(int i=0;i<broj_tiketi;i++){
        uplati+=tickets[i]->income();
    if(tickets[i]->getDobiten())
        isplati+=tickets[i]->loss();

    }
    return uplati - isplati;
}

int bestBet(Ticket **tickets,int broj_tiketi)
{
    Ticket *max = tickets[0];
    for(int i=0;i<broj_tiketi;i++)
    {
        if(*tickets[i]>*max)
            max=tickets[i];
    }
    return max->getSeriskiBroj();

}
int main(){

	int n, serialNumber, nn;
    double coef[16], payment;
    bool w;
    Ticket *tickets[10];
    cin >> n;
    for(int i = 0; i < n; i++){
    	cin >> serialNumber >> payment >> nn >> w;
        for(int j = 0; j < nn; j++){
        	cin >> coef[j];
        }
        if(i % 2){
        	tickets[i] = new ETicket(serialNumber, coef, nn, payment, w);
        }
        else{
        	tickets[i] = new OTCTicket(serialNumber, coef, nn, payment, w);
        }
    }
    OTCTicket::setCommission(2);
    cout << profit(tickets, n) << endl;
    cout << bestBet(tickets, n) << endl;
	return 0;
}
