#include "album.h"
#include "canzone.h"
#include <ostream>


album::album(const string& t, const string& a, const int& d, const string& c) : media(t,a,d,c) {}
album::album(const string& t, const string& a, const int& d, const string& c,
             const list<canzone*>& tracks) : media(t,a,d,c), durataTotale(0)
{
    for (canzone* t : tracks)
    {
        trackList.push_back(t);
    }
}

int album::getDurataTotale() const { return durataTotale; }
int album::getNumCanzoni() const { return trackList.size(); };

void album::addCanzone(canzone* newCanzone)
{
    trackList.push_back(newCanzone);
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

    out<<"\n\n----CANZONI----\n";
    for(canzone* c : a.trackList)
    {
        out<<(*c)<<"\n";
    }
    return out;
}
