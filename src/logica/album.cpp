#include "album.h"
#include "canzone.h"
#include <ostream>

album::album() : media("", "", 0, "./immagini/album.png",0) {}
album::album(const string& _titolo, const string& _autore, const int& _anno, const string& _copertina, const int& _id) :
        media(_titolo, _autore, _anno, _copertina, _id), durataTotale(0) {}

album::album(const string& _titolo, const string& _autore, const int& _anno, const string& _copertina, const int& _id,
             const list<canzone*>& tracks) : media(_titolo, _autore, _anno, _copertina, _id), durataTotale(0)
{
    for (canzone* t : tracks)
    {
        trackList.push_back(new canzone(t->getTitolo(),t->getAutore(),t->getAnno(),t->getCopertina(),t->getId(),t->getDurata(),t->getGenere()));
        durataTotale+=t->getDurata();
    }
}

int album::getDurataTotale() const { return durataTotale; }
int album::getNumCanzoni() const { return trackList.size(); };

void album::addCanzone(canzone* newCanzone)
{
    trackList.push_back(newCanzone);
    durataTotale+=newCanzone->getDurata();
}

void album::accept(visitor *_visitor)
{
    _visitor->visit(this);
}

canzone* album::operator[](size_t index)
{
    auto it = trackList.begin();
    advance(it, index);
    return *it;
}

const canzone* album::operator[](size_t index) const
{
    auto it = trackList.begin();
    advance(it, index);
    return *it;
}

std::ostream& operator << (std::ostream &out, const album& a)
{
    out<<"\nTITOLO: "<<a.getTitolo();
    out<<"\nAUTORE: "<<a.getAutore();
    out<<"\nANNO: "<<a.getAnno();
    out<<"\nCOPERTINA: "<<a.getCopertina();
    out<<"\nDURATA TOT: "<<a.getDurataTotale()/60<<" min, "<<a.getDurataTotale()%60<<" sec";
    out<<"\nID: "<<a.getId();

    out<<"\n\n----CANZONI----\n";
    for(canzone* c : a.trackList)
    {
        out<<(*c)<<"\n";
    }
    return out;
}
