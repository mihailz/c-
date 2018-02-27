#include<iostream>
#include<cstring>
using namespace std;

class Ekskurzija{
protected:
    char ime[50];
    int prevoz;
    int mesec;
    int denovi;
    double cena;
    int patnici;
public:
    Ekskurzija(){}

    Ekskurzija(char* name,int  vehicle,int  month,int duration,double price,int tourists){
        strcpy(ime,name);
        prevoz=vehicle;
        mesec=month;
        denovi=duration;
        cena=price;
        patnici=tourists;
    }

    Ekskurzija& operator=(const Ekskurzija& e){
        strcpy(ime,e.ime);
        prevoz=e.prevoz;
        mesec=e.mesec;
        denovi=e.denovi;
        cena=e.cena;
        patnici=e.patnici;
        return *this;
    }

    int getPrevoz(){
        return prevoz;
    }

    int getMesec(){
        return mesec;
    }

    int getDenovi(){
        return denovi;
    }

    int getPatnici(){
        return patnici;
    }

    double getCena(){
        return cena;
    }





};


class TuristichkaAgencija{
protected:
    char ime[50];
    Ekskurzija e[5];
    int brEks;
public:
    TuristichkaAgencija(){}

    TuristichkaAgencija(char* agency,Ekskurzija* eks,int num){
        strcpy(ime,agency);
        brEks=num;
        for(int i=0;i<num;i++){
            e[i]=eks[i];
        }
    }

};

class OnlineTuristichkaAgencija : public TuristichkaAgencija{
protected:

public:
    OnlineTuristichkaAgencija():TuristichkaAgencija(){}

    OnlineTuristichkaAgencija(char* agency,Ekskurzija* online,int numOnlineE):TuristichkaAgencija(agency,online,numOnlineE){

    }

    double vkupnaDobivka(){
        double profit=0;
        for(int i=0;i<brEks;i++){
            double k;
            if(e[i].getMesec()==6 || e[i].getMesec()==7 || e[i].getMesec()==8) k=2.5;
            else if(e[i].getPrevoz()) k=2.2;
            else k=1.8;
            profit+=e[i].getDenovi()*e[i].getCena()*e[i].getPatnici()+20*k;
        }
        return profit;
    }

};

class TradicionalnaTuristichkaAgencija : public TuristichkaAgencija{
protected:

public:
    TradicionalnaTuristichkaAgencija():TuristichkaAgencija(){}

    TradicionalnaTuristichkaAgencija(char* agency,Ekskurzija* traditional,int numTradE):TuristichkaAgencija(agency, traditional, numTradE){

    }

    double vkupnaDobivka(){
        double profit=0;
        for(int i=0;i<brEks;i++){
            double k;
            if(e[i].getMesec()==6 || e[i].getMesec()==7 || e[i].getMesec()==8) k=1.8;
            else k=1.3;
            profit+=e[i].getDenovi()*e[i].getCena()*e[i].getPatnici()+30*k;
        }
        return profit;
    }



};

int main()
{

    	char agency[50];
    	double freq;
    	int numOnlineE, numTradE;
    	Ekskurzija online[5];
    	Ekskurzija traditional[5];
    	cin >> numOnlineE >> numTradE;
    	for(int i = 0; i < numOnlineE; i++){
    		char name[50];
            int vehicle, month, duration, price, tourists;
        	cin >> name >> vehicle >> month >> duration >> price >> tourists;
       		Ekskurzija e(name, vehicle, month, duration, price, tourists);
       		online[i] = e;
    	}
    	cin >> agency;
		OnlineTuristichkaAgencija onlineAgency(agency, online, numOnlineE);
		for(int i = 0; i < numTradE; i++){
    		char name[50];
        	int vehicle, month, duration, price, tourists;
        	cin >> name >> vehicle >> month >> duration >> price >> tourists;
       		Ekskurzija e(name, vehicle, month, duration, price, tourists);
       		traditional[i] = e;
    	}
    	cin >> agency;
		TradicionalnaTuristichkaAgencija traditionalAgency(agency, traditional, numTradE);
		cout << onlineAgency.vkupnaDobivka() << endl;
    	cout << traditionalAgency.vkupnaDobivka() << endl;

    return 0;
}
