#include "mediaManager.h"
#include "../jsonHandler/jsonHandler.h"
#include "filtraVisitor.h"
#include "searchVisitor.h"
#include <cctype>    // Per std::toupper
                     
mediaManager::~mediaManager()
{
    for(auto m : LM)
        delete m;
}

void mediaManager::save() const
{
    jsonHandler jHandler; 
    jHandler.clearAll();
    
    for(auto m : LM)
        jHandler.saveMedia(m);
}

void mediaManager::addMedia(media* newMedia)
{
    LM.push_back(newMedia);
    save();
}

void mediaManager::removeMedia(int _id)
{
    auto i = LM.begin();
    while(i != LM.end())
    {
        if((*i)->getId()==_id)
        {
            delete *i;
            i = LM.erase(i);
            save();
        }
        else
            i++;
    }
}

void mediaManager::load()
{
    jsonHandler jHandler;
    jHandler.readAllLibri(LM);
    jHandler.readAllCanzoni(LM);
    jHandler.readAllAlbum(LM);
}

int mediaManager::size() const { return LM.size(); }

list<media*> mediaManager::filtroSoloLibri() const
{
    filtraVisitor vis(LM);
    return vis.getSoloLibri();
}

list<media*> mediaManager::filtroSoloCanzoni() const
{
    filtraVisitor vis(LM);
    return vis.getSoloCanzoni();
}

list<media*> mediaManager::filtroSoloAlbum() const
{ 
    filtraVisitor vis(LM);
    return vis.getSoloAlbum();
}

list<media*> mediaManager::search(string strDaCercare) const
{
    list<media*> listaTemp;
    list<int> idRisultati;
    searchVisitor vis(strDaCercare, &idRisultati);

    for(auto m : LM)
        m->accept(&vis);
    
    for(int _id : idRisultati)
        listaTemp.push_back(this->searchById(_id));
         
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

int mediaManager::trovaIdLibero() const
{
    list<media*> copiaLM = this->LM; // copia non profonda!! (perchè non necessaria)

    if(copiaLM.empty())
        return 0;
    else
    {
        copiaLM.sort([](const media* a, const media* b) 
        { return a->getId() < b->getId(); });


        int last=0;
        for(auto i : copiaLM)
        {
            if(i->getId()>last)
                return last;

            else if (i->getId()==last)
                last++;
        }
        return ++last;
    }
}

media* mediaManager::searchById(int _id) const
{
    for(auto m : LM)
    {
        if(m->getId()==_id)
            return m;
    }
    return nullptr;
}








