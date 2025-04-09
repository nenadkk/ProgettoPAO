#include "searchVisitor.h"

searchVisitor::searchVisitor(string str, list<int>* l) : strDaCercare(str), idRisultati(l) 
{
    rendiMaiuscolo(strDaCercare);
}

void searchVisitor::rendiMaiuscolo(string& str)
{
    transform(str.begin(), str.end(), str.begin(), [](unsigned char c) { return std::toupper(c); }); 
}

void searchVisitor::ricercaAttributiStandard(media* obj)
{
    string titoloMaiuscolo = obj->getTitolo(), 
           autoreMaiuscolo = obj->getAutore(), 
           annoMaiuscolo = to_string(obj->getAnno()), 
           idMaiuscolo = to_string(obj->getId());

    rendiMaiuscolo(titoloMaiuscolo);
    rendiMaiuscolo(autoreMaiuscolo);
    rendiMaiuscolo(annoMaiuscolo);
    rendiMaiuscolo(idMaiuscolo);

    //ricerca
    if(titoloMaiuscolo.find(strDaCercare) != string::npos ||
            autoreMaiuscolo.find(strDaCercare) != string::npos || 
            annoMaiuscolo.find(strDaCercare) != string::npos ||
            idMaiuscolo.find(strDaCercare) != string::npos)
    {
        idRisultati->push_back(obj->getId());
    }   
}

void searchVisitor::visit(libro *_libro)
{
    ricercaAttributiStandard(_libro);

    string isbnMaiuscolo = to_string(_libro->getIsbn()); 
    string editoreMaiuscolo = _libro->getEditore();

    rendiMaiuscolo(isbnMaiuscolo);
    rendiMaiuscolo(editoreMaiuscolo);

    //ricerca
    if(isbnMaiuscolo.find(strDaCercare) != string::npos || editoreMaiuscolo.find(strDaCercare) != string::npos)
        idRisultati->push_back(_libro->getId());

}

void searchVisitor::visit(canzone *_canzone)
{
    ricercaAttributiStandard(_canzone);

    string genereMaiuscolo = _canzone->getGenere();
    rendiMaiuscolo(genereMaiuscolo);

    //ricerca
    if(genereMaiuscolo.find(strDaCercare) != string::npos)
        idRisultati->push_back(_canzone->getId());
}

void searchVisitor::visit(album *_album)
{
    ricercaAttributiStandard(_album);
    //la classe album non ha altri attributi su cui poter fare ricerca al di fuori di quelli base
    //quindi basta solo la ricerca standard comune a tutti
}
