#include "canzone.h"
#include "media.h"
#include <ostream>

canzone::canzone() : media("","",0,"./immagini/canzone.png",0), durata(0), genere("") {}
canzone::canzone(const string& _titolo, const string& _autore, const int& _anno, const string& _copertina, const int& _id,
                 const int& _durata, const string& _genere): 
                 media(_titolo,_autore,_anno,_copertina,_id), durata(_durata), genere(_genere) {};

int canzone::getDurata() const { return durata; }
string canzone::getGenere() const { return genere; }

void canzone::setDurata(const int& d) { durata=d; }
void canzone::setGenere(const string& g) { genere=g; }

void canzone::accept(visitor *_visitor)
{
    _visitor->visit(this);
}

std::ostream& operator << (std::ostream &out, const canzone& c)
{
    out<<"\nTITOLO: "<<c.getTitolo();
    out<<"\nAUTORE: "<<c.getAutore();
    out<<"\nANNO: "<<c.getAnno();
    out<<"\nCOPERTINA: "<<c.getCopertina();
    out<<"\nDURATA: "<<c.getDurata()/60<<" min, "<<c.getDurata()%60<<" sec";
    out<<"\nGENERE: "<<c.getGenere();
    out<<"\nID: "<<c.getId();

    return out;
}
