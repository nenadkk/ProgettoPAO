#include "listaMedia.h"
#include "../jsonHandler/jsonVisitor.h"
#include <string>
#include <algorithm> // Per std::transform
#include <cctype>    // Per std::toupper
                     
void listamedia::save() const
{
    jsonVisitor jVisitor; 
    jVisitor.clearAll();
    
    for(auto m : LM)
        m->accept(&jVisitor);
}

void listamedia::load()
{
    jsonVisitor jVisitor;
    jVisitor.readAllLibri(LM);
    jVisitor.readAllCanzoni(LM);
    jVisitor.readAllAlbum(LM);
}

int listamedia::size() const { return LM.size(); }

list<media*> listamedia::filtroSoloLibri() const
{
    list<media*> listaTemp;
    for(auto m : LM)
    {
        if(dynamic_cast<libro*>(m))
            listaTemp.push_back(m);
    }
    return listaTemp;
}

list<media*> listamedia::filtroSoloCanzoni() const
{
    list<media*> listaTemp;
    for(auto m : LM)
    {
        if(dynamic_cast<canzone*>(m))
            listaTemp.push_back(m);
    }
    return listaTemp;
}

list<media*> listamedia::filtroSoloAlbum() const
{
    list<media*> listaTemp;
    for(auto m : LM)
    {
        if(dynamic_cast<album*>(m))
            listaTemp.push_back(m);
    }
    return listaTemp;
}

void listamedia::rendiMaiuscolo(string& str)
{
    transform(str.begin(), str.end(), str.begin(), [](unsigned char c) { return std::toupper(c); }); 
}

list<media*> listamedia::search(string strDaCercare) const
{
    list<media*> listaTemp;
    for(auto m : LM)
    {
        //Trasformo tutto in maiuscolo per evitare ricerca case sensitive 
        rendiMaiuscolo(strDaCercare);

        string titoloMaiuscolo = m->getTitolo(), 
               autoreMaiuscolo = m->getAutore(), 
               annoMaiuscolo = to_string(m->getAnno()), 
               idMaiuscolo = to_string(m->getId());
        
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
            listaTemp.push_back(m);
        }
        else if (auto t = dynamic_cast<libro*>(m)) 
        {
            //Trasformo tutto in maiuscolo per evitare ricerca case sensitive 
            string isbnMaiuscolo = to_string(t->getIsbn()), 
                   editoreMaiuscolo = t->getEditore();

            rendiMaiuscolo(isbnMaiuscolo);
            rendiMaiuscolo(editoreMaiuscolo);

            //ricerca
            if(isbnMaiuscolo.find(strDaCercare) != string::npos || editoreMaiuscolo.find(strDaCercare) != string::npos)
                listaTemp.push_back(m);
        }
        else if (auto t = dynamic_cast<canzone*>(m)) 
        {
            //Trasformo tutto in maiuscolo per evitare ricerca case sensitive 
            string genereMaiuscolo = t->getGenere();
            rendiMaiuscolo(genereMaiuscolo);

            //ricerca
            if(genereMaiuscolo.find(strDaCercare) != string::npos)
                listaTemp.push_back(m);
        }

    }

    return listaTemp;
}

media* listamedia::operator[](size_t index)
{
    auto it = LM.begin();
    advance(it, index);
    return *it;
}
const media* listamedia::operator[](size_t index) const
{
    auto it = LM.begin();
    advance(it, index);
    return *it;

}














