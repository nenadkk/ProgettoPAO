#include "listaMedia.h"
#include "../jsonHandler/jsonVisitor.h"
#include <string>
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

int listamedia::size() const { return LM.size();}

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

list<media*> listamedia::search(string& strDaCercare) const
{
    list<media*> listaTemp;
    for(auto m : LM)
    {
        if(m->getTitolo().find(strDaCercare) != string::npos ||
           m->getAutore().find(strDaCercare) != string::npos || 
           to_string(m->getAnno()).find(strDaCercare) != string::npos ||
           to_string(m->getId()).find(strDaCercare) != string::npos)
        {
            listaTemp.push_back(m);
        }
        else if (auto t = dynamic_cast<libro*>(m)) 
        {
            if(to_string(t->getIsbn()).find(strDaCercare) != string::npos || t->getEditore().find(strDaCercare) != string::npos)
                listaTemp.push_back(m);
        }
        else if (auto t = dynamic_cast<canzone*>(m)) 
        {
            if(t->getGenere().find(strDaCercare) != string::npos)
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














