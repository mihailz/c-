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

class IntArray{
private:
    int *broevi;
    int broj_broevi;
public:

    int getBroevi()
    {
    	return broj_broevi;
    }
    IntArray(int *broevi=NULL,int broj_broevi=0)
    {
        this->broevi=new int[broj_broevi];
        for(int i=0;i<broj_broevi;i++)
            this->broevi[i]=broevi[i];
        this->broj_broevi=broj_broevi;
    }

    IntArray(const IntArray &ia)
    {
        this->broevi=new int[ia.broj_broevi];
        for(int i=0;i<broj_broevi;i++)
            this->broevi[i]=ia.broevi[i];
        this->broj_broevi=ia.broj_broevi;
    }

    IntArray& operator=(const IntArray &ia)
    {
        if(this!=&ia)
        {
            delete [] this->broevi;
            this->broevi=new int[ia.broj_broevi];
        for(int i=0;i<broj_broevi;i++)
            this->broevi[i]=ia.broevi[i];
        this->broj_broevi=ia.broj_broevi;
        }
        return *this;
    }

    int& operator[](int indeks)
    {
        if(indeks>=0&&indeks<broj_broevi)
            return broevi[indeks];
        throw IndexOutOfBounds("Index out of bounds\n");
    }

    ~IntArray()
    {
        delete [] broevi;
    }

};

class IntRows{
private:
    IntArray *niza_broevi;
    int niza_golemina;
public:
    IntRows()
    {
        niza_broevi=NULL;
        niza_golemina=0;
    }

    IntRows(const IntRows &ir)
    {
        this->niza_broevi=new IntArray[ir.niza_golemina];
        for(int i=0;i<niza_golemina;i++)
            this->niza_broevi=ir.niza_broevi;
        this->niza_golemina=ir.niza_golemina;
    }

    IntRows& operator=(const IntRows &ir)
    {
        if(this!=&ir)
        {
            delete [] this->niza_broevi;
            this->niza_broevi=new IntArray[ir.niza_golemina];
        for(int i=0;i<niza_golemina;i++)
            this->niza_broevi=ir.niza_broevi;
        this->niza_golemina=ir.niza_golemina;
        }
        return *this;
    }

    IntRows& operator+=(const IntArray &ia)
    {
        IntArray *temp = new IntArray[niza_golemina+1];
        for(int i=0;i<niza_golemina;i++)
            temp[i] = niza_broevi[i];

        delete [] niza_broevi;
        niza_broevi=temp;
        niza_broevi[niza_golemina++]=ia;
        return *this;

    }

     friend ostream &operator<<(ostream &out, const IntRows &ir) {
        int maxArrayLength = ir.niza_broevi[0].getBroevi();
        for (int i = 1; i < ir.niza_golemina; ++i) {
            if (maxArrayLength < ir.niza_broevi[i].getBroevi())
                maxArrayLength = ir.niza_broevi[i].getBroevi();
        }

        for (int i = 0; i < ir.niza_golemina; ++i) {
            for (int j = 0; j < ir.niza_broevi[i].getBroevi(); ++j) {
                out << ir.niza_broevi[i][j] << " ";
            }
            if (ir.niza_broevi[i].getBroevi() < maxArrayLength) {
                for (int j = ir.niza_broevi[i].getBroevi(); j < maxArrayLength; ++j)
                    out << ". ";
            }
            out << endl;
        }
        return out;
     }

    ~IntRows()
    {
        delete [] niza_broevi;
    }


};
int main() {
    int n;
    cin >> n;
    if(n == 0) {
        cout << "IntArray constructors" << endl;
        int a[] = {1, 2, 3};
        IntArray ia(a, 3);
        cout << "OK" << endl;
    } else if(n == 1) {
        cout << "IntArray [] operator" << endl;
        int a[] = {1, 2, 3};
        IntArray ia(a, 3);
        cout << "a[0] = " << a[0] << endl;
        cout << "a[1] = " << a[1] << endl;
        cout << "a[2] = " << a[2] << endl;
    } else if(n == 2) {
        cout << "IntArray exception" << endl;
        int a[] = {1, 2, 3};
        IntArray ia(a, 3);
        // TRY - CATCH code here

        try{
        cout << ia[-1] << endl;
        }
        catch(IndexOutOfBounds &ib)
        {
            cout<<ib;
        }


    } else if(n == 3) {
        cout << "IntRows constructor" << endl;
        IntRows ir;
        cout << "OK" << endl;
    } else if(n == 4) {
        cout << "IntRows += and cout" << endl;
        IntRows ir;
        int a[] = {1, 2, 3};
        IntArray ia(a, 3);
        int b[] = {5, 4, 3, 2, 1};
        IntArray ib(b, 5);
        int c[] = {20};
        IntArray ic(c, 1);
        ir += ia;
        ir += ib;
        ir += ic;
        cout << ir << endl;
    }

    return 0;
}
