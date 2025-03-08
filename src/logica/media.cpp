#include "media.h"

media::media(const string& t, const string& a, const int& d, const string& c ) : titolo(t), autore(a), anno(d), copertina(c) {};

string media::getTitolo() const { return titolo; }
string media::getAutore() const { return autore; }
int media::getAnno() const { return anno; }
string media::getCopertina() const { return copertina; }

void media::setTitolo(const string& t) { titolo=t; }
void media::setAutore(const string& a) { autore=a; }
void media::setAnno(const int& d) { anno=d; }
void media::setCopertina(const string& c) { copertina=c; }
