#include "canzone.h"
#include <ostream>

canzone::canzone(const string& t, const string& a, const int& d, const string& c,
                 const int& _durata, const string& _genere, const int& _id): 
                 media(t,a,d,c), durata(_durata), genere(_genere), id(_id) {};

int canzone::getDurata() const { return durata; }
string canzone::getGenere() const { return genere; }
int canzone::getId() const { return id; }


void canzone::setDurata(const int& d) { durata=d; }
void canzone::setGenere(const string& g) { genere=g; }
void canzone::setId(const int& _id) { id=_id; }

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
