#include <iostream>
using namespace std;
#include <cstring>


class Book{
protected:
    char ISBN[20];
    char naslov[50];
    char avtor[30];
    float osnovna_cena;
public:
    Book(const char *ISBN="",const char *naslov="",const char *avtor="",float osnovna_cena=0.0)
    {
      strcpy(this->ISBN,ISBN);
      strcpy(this->naslov,naslov);
      strcpy(this->avtor,avtor);
      this->osnovna_cena=osnovna_cena;
    }
    char *getAvtor()
    {
        return avtor;
    }
    char *getNaslov()
    {
        return naslov;
    }
    char *getISBN()
    {
        return ISBN;
    }
     virtual void setISBN(char *ISBN)
    {
        strcpy(this->ISBN,ISBN);
    }
    bool operator>(Book &b)
    {
        if(bookPrice()>b.bookPrice())
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    friend ostream& operator<<(ostream &out,Book &b1)
    {
        cout<<b1.ISBN<<": "<<b1.naslov<<", "<<b1.avtor<<" "<<b1.bookPrice()<<endl;


        return out;
    }

    virtual float bookPrice() = 0;
    virtual ~Book(){}

};

class OnlineBook: public Book{
private:
    char *url;
    int golemina_MB;
public:
    OnlineBook(const char *ISBN="",const char *naslov="",const char *avtor="",float osnovna_cena=0.0,const char *url="",int golemina_MB=0):
        Book(ISBN,naslov,avtor,osnovna_cena)
    {
      this->url = new char[strlen(url)+1];
      strcpy(this->url,url);
      this->golemina_MB=golemina_MB;
    }

    OnlineBook(const OnlineBook &ob)
    {
      this->url = new char[strlen(ob.url)+1];
      strcpy(this->url,ob.url);
      this->golemina_MB=ob.golemina_MB;
      strcpy(this->ISBN,ob.ISBN);
      strcpy(this->naslov,ob.naslov);
      strcpy(this->avtor,ob.avtor);
      this->osnovna_cena=ob.osnovna_cena;
    }

    OnlineBook& operator=(const OnlineBook &ob1)
    {
        if(this!=&ob1)
        {
      delete [] url;
      this->url = new char[strlen(ob1.url)+1];
      strcpy(this->url,ob1.url);
      this->golemina_MB=ob1.golemina_MB;
      strcpy(this->ISBN,ob1.ISBN);
      strcpy(this->naslov,ob1.naslov);
      strcpy(this->avtor,ob1.avtor);
      this->osnovna_cena=ob1.osnovna_cena;
            return *this;
        }
    }


    float bookPrice()
    {
        if(golemina_MB>20)
        {
            return osnovna_cena + (osnovna_cena*0.20);
        }
        else
        {
            return osnovna_cena;
        }
    }



    ~OnlineBook()
    {
        delete [] url;
    }
};

class PrintBook: public Book{
private:
    float masa_kg;
    bool zaliha;
public:
    PrintBook(const char *ISBN="",const char *naslov="",const char *avtor="",float osnovna_cena=0.0,float masa_kg=0.0,bool zaliha=false):
        Book(ISBN,naslov,avtor,osnovna_cena)
    {
        this->masa_kg=masa_kg;
        this->zaliha=zaliha;
    }

    float bookPrice()
    {
        if(masa_kg>0.7)
        {
            return osnovna_cena + (osnovna_cena*0.15);
        }
        else{
            return osnovna_cena;
        }

    }

};

void mostExpensiveBook (Book** books, int n)
{
    int online=0;
    int pecateni=0;

    Book *max = books[0];

    for(int i=0;i<n;i++){

            Book *tmp =dynamic_cast<OnlineBook *>(books[i]);
            if(tmp)
            {
                online++;
            }else{
            pecateni++;
            }
        if(books[i]->bookPrice()>max->bookPrice())
        {
            max=books[i];
        }
    }


    cout<<"FINKI-Education"<<endl;
    cout<<"Total number of online books: "<<online<<endl;
    cout<<"Total number of print books: "<<pecateni<<endl;
    cout<<"The most expensive book is: "<<endl;
    cout<<max->getISBN()<<": "<<max->getNaslov()<<", "<<max->getAvtor()<<" "<<max->bookPrice();
}

int main(){

	char isbn[20], title[50], author[30], url[100];
	int size, tip;
	float price, weight;
	bool inStock;
	Book  **books;
	int n;

	int testCase;
	cin >> testCase;

	if (testCase == 1){
		cout << "====== Testing OnlineBook class ======" << endl;
		cin >> n;
		books = new Book *[n];

		for (int i = 0; i < n; i++){
			cin >> isbn;
			cin.get();
			cin.getline(title, 50);
			cin.getline(author, 30);
			cin >> price;
			cin >> url;
			cin >> size;
			cout << "CONSTRUCTOR" << endl;
			books[i] = new OnlineBook(isbn, title, author, price, url, size);
			cout << "OPERATOR <<" << endl;
			cout << *books[i];
		}
		cout << "OPERATOR >" << endl;
		cout << "Rezultat od sporedbata e: " << endl;
		if (*books[0] > *books[1])
			cout << *books[0];
		else
			cout << *books[1];
	}
	if (testCase == 2){
		cout << "====== Testing OnlineBook CONSTRUCTORS ======" << endl;
		cin >> isbn;
		cin.get();
		cin.getline(title, 50);
		cin.getline(author, 30);
		cin >> price;
		cin >> url;
		cin >> size;
		cout << "CONSTRUCTOR" << endl;
		OnlineBook ob1(isbn, title, author, price, url, size);
		cout << ob1 << endl;
		cout << "COPY CONSTRUCTOR" << endl;
		OnlineBook ob2(ob1);
		cin >> isbn;
		ob2.setISBN(isbn);
		cout << ob1 << endl;
		cout << ob2 << endl;
		cout << "OPERATOR =" << endl;
		ob1 = ob2;
		cin >> isbn;
		ob2.setISBN(isbn);
		cout << ob1 << endl;
		cout << ob2 << endl;
	}
	if (testCase == 3){
		cout << "====== Testing PrintBook class ======" << endl;
		cin >> n;
		books = new Book *[n];

		for (int i = 0; i < n; i++){
			cin >> isbn;
			cin.get();
			cin.getline(title, 50);
			cin.getline(author, 30);
			cin >> price;
			cin >> weight;
			cin >> inStock;
			cout << "CONSTRUCTOR" << endl;
			books[i] = new PrintBook(isbn, title, author, price, weight, inStock);
			cout << "OPERATOR <<" << endl;
			cout << *books[i];
		}
		cout << "OPERATOR >" << endl;
		cout << "Rezultat od sporedbata e: " << endl;
		if (*books[0] > *books[1])
			cout << *books[0];
		else
			cout << *books[1];
	}
	if (testCase == 4){
		cout << "====== Testing method mostExpensiveBook() ======" << endl;
		cin >> n;
		books = new Book *[n];

		for (int i = 0; i<n; i++){

			cin >> tip >> isbn;
			cin.get();
			cin.getline(title, 50);
			cin.getline(author, 30);
			cin >> price;
			if (tip == 1) {

				cin >> url;
				cin >> size;

				books[i] = new OnlineBook(isbn, title, author, price, url, size);

			}
			else {
				cin >> weight;
				cin >> inStock;

				books[i] = new PrintBook(isbn, title, author, price, weight, inStock);
			}
		}

		mostExpensiveBook(books, n);
	}

	for (int i = 0; i<n; i++) delete books[i];
		delete[] books;
	return 0;
