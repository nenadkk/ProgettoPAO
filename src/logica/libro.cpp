#include "libro.h"
#include <ostream>

libro::libro(const string& t, const string& a, const int& d, const string& c,
             const int& np, const int& i, const string& ce) : media(t,a,d,c), numPagine(np), isbn(i), editore(ce) {};

int libro::getNumPagine() const { return numPagine; }
int libro::getIsbn() const { return isbn; }
string libro::getEditore() const { return editore; }

void libro::setNumPagine(const int& np) { numPagine = np; }
void libro::setIsbn(const int& i) { isbn = i; }
void libro::setEditore(const string& ce) { editore = ce; }

void libro::accept(visitor *_visitor)
{
    _visitor->visit(this);
}

std::ostream& operator << (std::ostream &out, const libro& l)
{
    out<<"\nTITOLO: "<<l.getTitolo();
    out<<"\nAUTORE: "<<l.getAutore();
    out<<"\nANNO: "<<l.getAnno();
    out<<"\nCOPERTINA: "<<l.getCopertina();
    out<<"\nN° PAGINE: "<<l.getNumPagine();
    out<<"\nISBN: "<<l.getIsbn();
    out<<"\nEDITORE: "<<l.getEditore();

    return out;
}
