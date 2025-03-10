#include "media.h"

media::media(const string& _titolo, const string& _autore, const int& _anno, const string& _copertina, const int& _id ) : 
    titolo(_titolo), autore(_autore), anno(_anno), copertina(_copertina), id(_id) {};

string media::getTitolo() const { return titolo; }
string media::getAutore() const { return autore; }
int media::getAnno() const { return anno; }
string media::getCopertina() const { return copertina; }
int media::getId() const { return id; }

void media::setTitolo(const string& t) { titolo=t; }
void media::setAutore(const string& a) { autore=a; }
void media::setAnno(const int& a) { anno=a; }
void media::setCopertina(const string& c) { copertina=c; }
void media::setId(const int& i) { anno=i; }

