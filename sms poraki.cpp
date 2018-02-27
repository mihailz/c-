#include <iostream>
#include <stdlib.h>
#include <cstring>
using namespace std;

class SMS{
protected:
    int osnovna_cena;
    char *sodrzina;
    char broj[20];
public:
    SMS(const char *broj="",const char *sodrzina="",int osnovna_cena=0)
    {
        strcpy(this->broj,broj);
        this->sodrzina=new char[strlen(sodrzina)+1];
        strcpy(this->sodrzina,sodrzina);
        this->osnovna_cena=osnovna_cena;
    }

    SMS(const SMS &s)
    {
        strcpy(this->broj,s.broj);
        this->sodrzina=new char[strlen(s.sodrzina)+1];
        strcpy(this->sodrzina,s.sodrzina);
        this->osnovna_cena=s.osnovna_cena;
    }

    SMS& operator=(const SMS &s)
    {
        if(this!=&s)
        {
            delete [] this->sodrzina;
        strcpy(this->broj,s.broj);
        this->sodrzina=new char[strlen(s.sodrzina)+1];
        strcpy(this->sodrzina,s.sodrzina);
        this->osnovna_cena=s.osnovna_cena;
        }
        return *this;
    }

    bool operator<( SMS &s)
    {
        if(SMS_cena()<s.SMS_cena())
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    friend ostream& operator<<(ostream &out, SMS &s)
    {
        cout<<s.broj<<": "<<s.sodrzina<<" - "<<s.SMS_cena()<<endl;

        return out;
    }
    virtual ~SMS()
    {
        delete [] sodrzina;
    }
    virtual float SMS_cena()=0;

};

class RegularSMS:public SMS{
private:
    bool roaming;
public:
    RegularSMS(const char *broj="",const char *sodrzina="",int osnovna_cena=0,bool roaming=false):
        SMS(broj,sodrzina,osnovna_cena)
    {
        this->roaming=roaming;
    }

    float SMS_cena()
    {
        float broj_poraki = 1;
        int golemina_poraka = strlen(sodrzina);
        if(golemina_poraka>16)
            broj_poraki = golemina_poraka / 16 + 1;
        if(roaming)
            return ((2*osnovna_cena) + ((20/float(100))*osnovna_cena)) * broj_poraki;
        return osnovna_cena + ((18/float(100)*osnovna_cena)) * broj_poraki;
    }

};

class SpecialSMS:public SMS{
private:
    bool humanitarni;
public:
    SpecialSMS(const char *broj="",const char *sodrzina="",int osnovna_cena=0,bool humanitarni=false):
        SMS(broj,sodrzina,osnovna_cena)
    {
        this->humanitarni=humanitarni;
    }

    float SMS_cena()
    {
        if(humanitarni)
            return osnovna_cena;
        return osnovna_cena + (18/float(100))*osnovna_cena;


    }


};

void najskapaSMS (SMS** sms, int n)
{
    int sum_reg=0,sum_spec=0;
    SMS *max = sms[0];
    for(int i=0;i<n;i++){
        SMS *regularni = dynamic_cast<RegularSMS *> (sms[i]);
        if(regularni){
            sum_reg+=sms[i]->SMS_cena();
        }
        else{
            sum_spec+=sms[i]->SMS_cena();
        }

        if(*max<*sms[i])
            max=sms[i];
    }
    cout<<"Vkupnata cena na regularni SMS poraki: "<<sum_reg<<endl;
    cout<<"Vkupnata cena na specijalni SMS poraki: "<<sum_spec<<endl;
    cout<<"Najskapa poraka e: "<<endl;
    cout<<*max;
}


int main(){

	char tel[20], msg[1000];
	int cena;
	float price;
	bool roam, hum;
	SMS  **sms;
	int n;
	int tip;

	int testCase;
	cin >> testCase;

	if (testCase == 1){
		cout << "====== Testing RegularSMS class ======" << endl;
		cin >> n;
		sms = new SMS *[n];

		for (int i = 0; i < n; i++){
			cin >> tel;
			cin.get();
			cin.getline(msg, 1000);
			cin >> cena;
			cin >> roam;
			cout << "CONSTRUCTOR" << endl;
			sms[i] = new RegularSMS(tel, msg, cena, roam);
			cout << "OPERATOR <<" << endl;
			cout << *sms[i];
		}
		cout << "OPERATOR <" << endl;
		cout << "Rezultat od sporedbata e: " << endl;
		if (*sms[0] < *sms[1])
			cout << *sms[0];
		else
			cout << *sms[1];
	}
	if (testCase == 2){
		cout << "====== Testing SpecialSMS class ======" << endl;
		cin >> n;
		sms = new SMS *[n];

		for (int i = 0; i < n; i++){
			cin >> tel;
			cin.get();
			cin.getline(msg, 1000);
			cin >> cena;
			cin >> hum;
			cout << "CONSTRUCTOR" << endl;
			sms[i] = new SpecialSMS(tel, msg, cena, hum);
			cout << "OPERATOR <<" << endl;
			cout << *sms[i];
		}
		cout << "OPERATOR <" << endl;
		cout << "Rezultat od sporedbata e: " << endl;
		if (*sms[0] < *sms[1])
			cout << *sms[0];
		else
			cout << *sms[1];
	}
	if (testCase == 3){
		cout << "====== Testing method najskapaSMS() ======" << endl;
		cin >> n;
		sms = new SMS *[n];

		for (int i = 0; i<n; i++){

			cin >> tip;
			cin >> tel;
			cin.get();
			cin.getline(msg, 1000);
			cin >> cena;
			if (tip == 1) {

				cin >> roam;

				sms[i] = new RegularSMS(tel, msg, cena, roam);

			}
			else {
				cin >> hum;

				sms[i] = new SpecialSMS(tel, msg, cena, hum);
			}
		}

		najskapaSMS(sms, n);
	}
	for (int i = 0; i<n; i++) delete sms[i];
	delete[] sms;
	return 0;
}
