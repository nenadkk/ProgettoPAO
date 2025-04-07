#ifndef MEDIA
#define MEDIA
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
        int id;
        
    public:
        media(const string&, const string&, const int&, const string&, const int&);
        virtual ~media();

        string getTitolo() const;
        string getAutore() const;
        int getAnno() const;
        string getCopertina() const;
        int getId() const;

        void setTitolo(const string&);
        void setAutore(const string&);
        void setAnno(const int&);
        void setCopertina(const string&);
        void setId(const int&);

        virtual void accept(visitor *_visitor)=0;



};

#endif

