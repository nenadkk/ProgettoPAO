#ifndef MEDIA
#define MEDIA
#include <strstream>
#include <iostream>
#include "visitor.h"
using std::string;
using namespace std;

class media
{
    private:
        string titolo;
        string autore;
        int anno;
        string copertina;//si intende il path in cui è salvata l'immagine della copertina
        
    public:
        media(const string&, const string&, const int&, const string&);

        string getTitolo() const;
        string getAutore() const;
        int getAnno() const;
        string getCopertina() const;

        void setTitolo(const string&);
        void setAutore(const string&);
        void setAnno(const int&);
        void setCopertina(const string&);

        virtual void accept(visitor *_visitor)=0;



};

#endif

