#include <iostream>
#include <algorithm>

using namespace std;

class Vectoras
{
    int nr_elem;

public:

    int *start;

    friend class Matrice;
    //friend bool verific(const Matrice &A, const Vectoras &x, const Vectoras &y);

    friend istream& operator>>(istream &in, Vectoras &v);
    //friend std::ifstream& operator>>(std::ifstream &in, Vectoras &v);
    friend ostream& operator<<(ostream &out, const Vectoras &v);

    friend bool operator ==(const Vectoras &v1, const Vectoras &v2);
    friend bool operator !=(const Vectoras &v1, const Vectoras &v2);

    friend int operator *(const Vectoras &v1, const Vectoras &v2);

    bool operator<( const Vectoras& v ) const {
        return nr_elem < v.nr_elem;
    }

    int& operator[](const int index);

    Vectoras &operator =(const Vectoras &v)
    {
        if(this->start!=v.start)
        {
            delete []this->start;
            this->nr_elem=v.nr_elem;
            this->start = new int[this->nr_elem];
            for(int i=0; i<this->nr_elem; i++)
            {
                this->start[i]=v.start[i];
            }

            return *this;
        }
    }

    Vectoras()
    {
        start=new int[0];
        nr_elem=0;
    }

    Vectoras(const Vectoras &v)
    {
        start=new int[v.nr_elem];
        nr_elem=v.nr_elem;
        for(int i=0; i<nr_elem; i++)
            {
                start[i]=v.start[i];
            }
    }

    ~Vectoras()
    {
        delete this->start;
    }

    void suma(Vectoras &v)
    {
        int s=0;
        for(int i=0; i<v.nr_elem; i++)
        {
            s=s+v.start[i];
        }

        cout<<"Suma este "<<s<<endl<<endl;
    }

    void maxim(Vectoras &v)
    {
        int m = v.start[0], poz = 0;
        for(int i=1; i<v.nr_elem; i++)
        {
            if(v.start[i]>m)
            {
                m=v.start[i];
                poz=i;
            }
        }

        cout<<"Maximul se afla pe pozitia "<<poz<<" si are valorea "<<m<<endl<<endl;
    }

    void sortez(Vectoras &v)
    {
        for(int i=0; i<v.nr_elem-1; i++)
        {
            for(int j=i+1; j<v.nr_elem; j++)
            {
                if(v.start[j]<v.start[i])swap(v.start[i], v.start[j]);
            }
        }
    }
};

int& Vectoras::operator[](const int index)
{
    return this->start[index];
}

ostream& operator<<(ostream &out, const Vectoras &v)
{
    for(int i=0; i<v.nr_elem; i++)
    {
        out << v.start[i] <<" ";
    }

    return out;
}

istream& operator>>(istream &in, Vectoras &v)
{
    cout<<"Cate elemente are vectorul?";
    in>>v.nr_elem;
    v.start = new int[v.nr_elem];
    cout<<"Cititi elementele :"<<endl;
    for(int i=0; i<v.nr_elem; i++)
    {
        in>>v.start[i];
    }

    cout<<endl<<endl;
    return in;
}

/*std::ifstream& operator>>(std::ifstream &in, Vectoras &v)
{
    in>>v.nr_elem;
    v.start = new int[v.nr_elem];
    for(int i=0; i<v.nr_elem; i++)
    {
        in>>v.start[i];
    }

    return in;
}*/


int operator *(const Vectoras &v1, const Vectoras &v2)
{

    int rez=0;
    if(v1.nr_elem==v2.nr_elem)
    {
        for(int i=0; i<v1.nr_elem; i++)
        {
            rez=rez+(v1.start[i]*v2.start[i]);
        }

        return rez;
    }
    else
    {
        throw 11;
        cout<<endl;
    }

}

bool operator == (const Vectoras &v1, const Vectoras &v2)
{
    return (v1.nr_elem==v2.nr_elem);
}

bool operator != (const Vectoras &v1, const Vectoras &v2)
{
    return !(v1.nr_elem==v2.nr_elem);
}


///////////////////////////////////////////////////////////

class Matrice
{
    int linii;
    int col;
    Vectoras *m;

public:

    friend istream& operator>>(istream &in, Matrice &mat);
    friend ostream& operator<<(ostream &out, const Matrice &mat);
    friend Matrice operator +(const Matrice &m1, const Matrice &m2);

    friend bool verific( const Matrice &A, const Vectoras &x, const Vectoras &y);

};

istream& operator>>(istream &in, Matrice &mat)
{
    cout<<"Cate linii are matricea?";
    in>>mat.linii;
    cout<<"Cate coloane are matricea?";
    in>>mat.col;
    mat.m = new Vectoras[mat.linii];
    for(int i=0; i<mat.linii; i++)
    {
        mat.m[i].start=new int[mat.col];
        cin>>mat.m[i];
    }
    cout<<endl;
    return in;
}

ostream& operator<<(ostream &out, const Matrice &mat)
{
    for(int i=0;i<mat.linii; i++)
    {
        cout<<mat.m[i];
        cout<<endl;
    }
    return out;
}

Matrice operator +(const Matrice &m1, const Matrice &m2)
    {
        if(m1.col==m2.col && m1.linii==m2.linii)
        {
            Matrice rez;
            rez.col=m1.col;
            rez.linii=m1.linii;
            rez.m=new Vectoras[rez.linii];
            for(int i=0; i<rez.linii; i++)
            {
                rez.m[i].start=new int[rez.col];
            }

            cout<<endl<<"Rezultatul este :"<<endl;

            for(int i=0; i<rez.linii; i++)
            {
                for(int j=0; j<rez.col; j++)
                {
                    rez.m[i][j]=m1.m[i][j]+m2.m[i][j];
                    cout<<rez.m[i][j]<<" ";
                }
                cout<<endl;
            }

            return rez;
        }
        else
        {
            throw 111;
            cout<<endl;
        }
    }

bool verific(const Matrice &A, const Vectoras &x, const Vectoras &y)
{

    bool t=1;
    int rez;
    for(int i=0; i<A.linii && t==1; i++)
    {
        rez=A.m[i]*x;
        if(rez!=y.start[i])t=0;
    }

    return t;
}

int main()
{
    int optiune;
    do
    {
        cout<<" --!--!-- V E C T O R   S I M U L A T O R   2 0 1 8 --!--!--";
        cout<<endl<<"-------------------------------"<<endl;
        cout<<"1. Suma Elementelor"<<endl;
        cout<<"2. Maximul"<<endl;
        cout<<"3. Sortare"<<endl;
        cout<<"4. BONUS! Sorteaza un Vector de Vectori Dupa Nr. de Elemente"<<endl;
        cout<<"5. Produs Scalar"<<endl;
        cout<<"0. EXIT"<<endl;
        cout<<"-------------------------------";

        cout<<endl<<"Alegeti optiunea : ";
        cin>>optiune;
        cout<<endl<<endl;

        switch(optiune)
        {

        case 1:
            {
                Vectoras v;
                cin>>v;
                v.suma(v);
                break;
            }
        case 2:
            {
                Vectoras v;
                cin>>v;
                v.maxim(v);
                break;
            }
        case 3:
            {
                Vectoras v;
                cin>>v;
                v.sortez(v);
                cout<<"Voila! Vectorul e sortat : "<<v<<endl<<endl;
                break;
            }
        case 4:
            {
                cout<<"Cati vectori doriti sa sortati?"<<endl;
                int n; cin>>n;
                Vectoras *vect = new Vectoras[n];
                cout<<"Se vor citi vectorii :"<<endl;
                for(int i=0; i<n; i++)
                    {
                        cin>>vect[i];
                    }

                cout<<"Acestia sunt vectorii :"<<endl;
                for(int i=0; i<n; i++)
                    {
                        cout<<vect[i];
                        cout<<endl;
                    }

                cout<<endl;
                sort(vect, vect+n);
                cout<<endl;

                cout<<"Dupa sortare, stimati invitati..."<<endl;
                for(int i=0; i<n; i++)
                    {
                        cout<<vect[i];
                        cout<<endl;
                    }
                cout<<endl<<endl;
                delete vect;
                break;
            }
        case 5:
            {
                cout<<"Cititi primul vector : "<<endl;
                Vectoras v1,v2;
                cin>>v1;
                cout<<"Cititi al doilea vector : "<<endl;
                cin>>v2;
                int rez;
                try
                {
                    rez=v1*v2;
                    cout<<"Rezultatul produsului scalar este..."<<rez<<endl<<endl;
                }
                catch(int eroare)
                {
                    if(eroare==11)
                    {
                        cout<<"Vectorii nu au aceeasi lungime. Repetati comanda..."<<endl;
                    }
                }
                break;
            }
        }
    }while(optiune>0 && optiune<6);

    do{
        cout<<" M A T R I C E A    2 0 1 8 "<<endl;
        cout<<"------------------------------------"<<endl;
        cout<<"1. Citire si afisare"<<endl;
        cout<<"2. Suma a doua matrici"<<endl;
        cout<<"3. Verificare Ax=y"<<endl;
        cout<<"0. EXIT"<<endl;
        cout<<"------------------------------------"<<endl;

        cout<<endl<<"Alegeti optiunea..."; cin>>optiune;

        switch(optiune)
        {
        case 1:
            {
                Matrice m;
                cin>>m;
                cout<<"Matricea este..."<<endl<<endl<<m<<endl;
                break;
            }
        case 2:
            {
                Matrice m1, m2, rez;
                cout<<"Cititi prima matrice..."<<endl;
                cin>>m1;
                cout<<"Cititi a doua matrice..."<<endl;
                cin>>m2;
                cout<<"Rezultatul sumei este..."<<endl<<endl;
                try{
                    rez=m1+m2;
                }
                catch(int eroare)
                {
                    if(eroare==111)cout<<"Dimensiunile matricelor nu sunt egale. Repetati comanda..."<<endl;
                }
                cout<<endl<<endl;
                break;
            }
        case 3:
            {
                Vectoras x,y;
                Matrice A;
                int adev;
                cout<<"Cititi matricea A..."<<endl;
                cin>>A;
                cout<<"Cititi vectorul x..."<<endl;
                cin>>x;
                cout<<"Cititi vectorul y..."<<endl;
                cin>>y;
                cout<<"Se verifica Ax=y..."<<endl;
                adev=verific(A,x,y);
                if(adev==1)cout<<"Conditia se respecta."<<endl<<endl;
                    else cout<<"Conditia NU se respecta."<<endl<<endl;
                break;
            }
        }


    }while(optiune>0 && optiune<4);

    return 0;

};
