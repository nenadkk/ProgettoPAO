#include "mediaManager.h"
#include "../jsonHandler/jsonVisitor.h"
#include <string>
#include <algorithm> // Per std::transform
#include <cctype>    // Per std::toupper
                     
void mediaManager::addMedia(media* newMedia)
{
    LM.push_back(newMedia);
    save();
}
void mediaManager::save() const
{
    jsonVisitor jVisitor; 
    jVisitor.clearAll();
    
    for(auto m : LM)
        m->accept(&jVisitor);
}

void mediaManager::load()
{
    jsonVisitor jVisitor;
    jVisitor.readAllLibri(LM);
    jVisitor.readAllCanzoni(LM);
    jVisitor.readAllAlbum(LM);
}

int mediaManager::size() const { return LM.size(); }

list<media*> mediaManager::filtroSoloLibri() const
{
    list<media*> listaTemp;
    for(auto m : LM)
    {
        if(dynamic_cast<libro*>(m))
            listaTemp.push_back(m);
    }
    return listaTemp;
}

list<media*> mediaManager::filtroSoloCanzoni() const
{
    list<media*> listaTemp;
    for(auto m : LM)
    {
        if(dynamic_cast<canzone*>(m))
            listaTemp.push_back(m);
    }
    return listaTemp;
}

list<media*> mediaManager::filtroSoloAlbum() const
{
    list<media*> listaTemp;
    for(auto m : LM)
    {
        if(dynamic_cast<album*>(m))
            listaTemp.push_back(m);
    }
    return listaTemp;
}

void mediaManager::rendiMaiuscolo(string& str)
{
    transform(str.begin(), str.end(), str.begin(), [](unsigned char c) { return std::toupper(c); }); 
}

list<media*> mediaManager::search(string strDaCercare) const
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

media* mediaManager::operator[](size_t index)
{
    auto it = LM.begin();
    advance(it, index);
    return *it;
}
const media* mediaManager::operator[](size_t index) const
{
    auto it = LM.begin();
    advance(it, index);
    return *it;

}














