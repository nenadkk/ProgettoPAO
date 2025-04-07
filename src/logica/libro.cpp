#include "libro.h"
#include "media.h"
#include <ostream>

libro::libro() : media("", "", 0, "./immagini/libro.png", 0), numPagine(0), isbn(0), editore("") {}
libro::libro(const string& _titolo, const string& _autore, const int& _anno, const string& _copertina, const int& _id,
             const int& _numPagine, const int& _isbn, const string& _editore) : 
            media(_titolo,_autore,_anno,_copertina,_id), numPagine(_numPagine), isbn(_isbn), editore(_editore) {};

int libro::getNumPagine() const { return numPagine; }
int libro::getIsbn() const { return isbn; }
string libro::getEditore() const { return editore; }

void libro::setNumPagine(const int& np) { numPagine = np; }
void libro::setIsbn(const int& i) { isbn = i; }
void libro::setEditore(const string& e) { editore = e; }

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
    out<<"\nID: "<<l.getId();

    return out;
}
