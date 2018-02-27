#include <iostream>
#include <cstring>
using namespace std;

class IndexOutOfBounds{
private:
    char *error_msg;
public:
    IndexOutOfBounds(const char *error_msg)
    {
        this->error_msg=new char[strlen(error_msg)+1];
        strcpy(this->error_msg,error_msg);
    }

    IndexOutOfBounds(const IndexOutOfBounds &ib)
    {
        this->error_msg=new char[strlen(ib.error_msg)+1];
        strcpy(this->error_msg,ib.error_msg);
    }

    IndexOutOfBounds& operator=(const IndexOutOfBounds &ib)
    {
        if(this!=&ib)
        {
            delete [] this->error_msg;
        this->error_msg=new char[strlen(ib.error_msg)+1];
        strcpy(this->error_msg,ib.error_msg);
        }
        return *this;
    }

    friend ostream& operator<<(ostream &out,const IndexOutOfBounds &ib)
    {
        out<<ib.error_msg;

        return out;
    }

    ~IndexOutOfBounds()
    {
        delete [] error_msg;
    }

};

class Kontakt{
private:
    char *ime;
    char prezime[30];
public:
    Kontakt(const char *ime="",const char *prezime="")
    {
        this->ime=new char[strlen(ime)+1];
        strcpy(this->ime,ime);
        strcpy(this->prezime,prezime);
    }

    char *getIme()
    {
        return ime;
    }
    char *getPrezime()
    {
        return prezime;
    }
    Kontakt(const Kontakt &k)
    {
        this->ime=new char[strlen(k.ime)+1];
        strcpy(this->ime,k.ime);
        strcpy(this->prezime,k.prezime);
    }

    Kontakt& operator=(const Kontakt &k)
    {
        if(this!=&k)
        {
            delete [] this->ime;
        this->ime=new char[strlen(k.ime)+1];
        strcpy(this->ime,k.ime);
        strcpy(this->prezime,k.prezime);
        }
        return *this;
    }

    char& operator[](const int indeks)
    {
        if(indeks>=0&&indeks<strlen(prezime))
            return prezime[indeks];
        throw IndexOutOfBounds("Index out of bounds\n");
    }


    ~Kontakt()
    {
        delete [] ime;
    }
};

class Imenik{
private:
    Kontakt *kontakti;
    int broj_kontakti;
public:
    Imenik()
    {
        kontakti=NULL;
        broj_kontakti=0;
    }

    Imenik(const Imenik &im)
    {
        this->kontakti = new Kontakt[im.broj_kontakti];
        for(int i=0;i<broj_kontakti;i++)
            this->kontakti[i]=im.kontakti[i];
        this->broj_kontakti=im.broj_kontakti;
    }

    Imenik& operator=(const Imenik &im)
    {
        if(this!=&im)
        {
            delete [] this->kontakti;
            this->kontakti = new Kontakt[im.broj_kontakti];
        for(int i=0;i<broj_kontakti;i++)
            this->kontakti[i]=im.kontakti[i];
        this->broj_kontakti=im.broj_kontakti;
        }
        return *this;
    }

    Imenik& operator+=(const Kontakt &k)
    {
        Kontakt *temp = new Kontakt[broj_kontakti+1];
        for(int i=0;i<broj_kontakti;i++)
            temp[i] = kontakti[i];

        delete [] kontakti;
        kontakti = temp;
        kontakti[broj_kontakti++]=k;
        return *this;
    }

    friend ostream& operator<<(ostream &out,const Imenik &im)
    {
        for(int i=0;i<im.broj_kontakti;i++)
        {
            out<<im.kontakti[i].getIme()<<" ";
            for(int j=0;j<strlen(im.kontakti[i].getPrezime());j++){
                if(j==0)
                out<< (char) toupper(im.kontakti[i][j]);
                else
                    out<< (char) tolower(im.kontakti[i][j]);

        }
        out<<endl;
        }
        return out;
    }


    ~Imenik()
    {
        delete [] kontakti;
    }

};
int main() {
    char ime[20],prezime[30];
    int n;
    cin >> n;
    if(n == 0) {
        cout << "Konstruktori na Kontakt" << endl;

        cin>>ime>>prezime;

        Kontakt k1(ime, prezime);
        cout << "OK" << endl;
    } else if(n == 1) {
        cout << "[] operator" << endl;
         cin>>ime>>prezime;
        Kontakt k1(ime, prezime);
        cout << "a[0] = " << k1[0] << endl;
        cout << "a[1] = " << k1[1] << endl;
        cout << "a[2] = " << k1[2] << endl;
    } else if(n == 2) {
        cout << "Isklucok" << endl;
        cin>>ime>>prezime;
        Kontakt k1(ime, prezime);

        //vashiot kod tuka
        try{
        cout << k1[-1] << endl;
        }
        catch (IndexOutOfBounds &i)
        {
            cout<<i;
        }
    } else if(n == 3) {
        cout << "Imenik constructor" << endl;
        Imenik im;
        cout << "OK" << endl;
    } else if(n == 4) {
        cout << "Imenik += and cout" << endl;
        Imenik im;
         cin>>ime>>prezime;
        Kontakt k1(ime, prezime);
         cin>>ime>>prezime;
        Kontakt k2(ime, prezime);
         cin>>ime>>prezime;
        Kontakt k3(ime, prezime);
        im += k1;
        im += k2;
        im += k3;
        cout << im << endl;

    }

    return 0;
}
