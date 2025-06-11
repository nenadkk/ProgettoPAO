#include "mediaManager.h"
#include "../jsonHandler/jsonHandler.h"
#include "filtraVisitor.h"
#include "qglobal.h"
#include "searchVisitor.h"
#include <cctype>    // Per std::toupper
#include <QMessageBox>
#include <QFileDialog>
                     

unordered_map<string, string> mediaManager::save_file= {
    {"libro" , ""},
    {"canzone" , ""},
    {"album" , ""}
};


mediaManager::mediaManager()
{
    load();
}
mediaManager::~mediaManager()
{
    for(auto m : LM)
        delete m;
}

void mediaManager::saveAll() const
{
    jsonHandler::clearAll();
    
    for(auto m : LM)
        jsonHandler::saveMedia(m);
}

void mediaManager::addMedia(media* newMedia)
{
    LM.push_back(newMedia);
    saveAll();
}

void mediaManager::removeMedia(int _id)
{
    auto i = LM.begin();
    while(i != LM.end())
    {
        if((*i)->getId()==_id)
        {
            //controllo se il media da eliminare è una canzone ed presente in qualche 
            //album, in caso la elimino dall'album.
            for(auto m : filtroSoloAlbum())
            {
                album* a = dynamic_cast<album*>(m);
                if(a->contieneCanzone(_id))//solo le canzoni possono essere 
                                           //contenute in un album. 
                    a->removeCanzone(_id);
            }

            delete *i;
            i = LM.erase(i);
            saveAll();
        }
        else
            i++;
    }
}

void mediaManager::load()
{    
    //svuoto il contenuto prima di ricaricare la lista
    for(auto m : LM)
        delete m;

    //nota: non posso fare tutto in una funzione perché loadFileDiSalvataggio 
    //è un metodo statico e tale deve rimenere
    mediaManager::loadFileDiSalvataggio();

    //ricarico la lista, solo se ho un file effettivamente caricato
    if(save_file.find("libro")->second != "")
        jsonHandler::readAllLibri(LM);

    if(save_file.find("canzone")->second != "")
        jsonHandler::readAllCanzoni(LM);

    if(save_file.find("album")->second != "")
        jsonHandler::readAllAlbum(LM);
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

void mediaManager::loadFileDiSalvataggio()
{
    QString dirIniziale = QDir::currentPath() + QString("/src/jsonHandler/data/");

    QString str = "Adesso verra chiesto di selezionare i file .json di salvataggio nel seguente ordine:\n- LIBRI\n- CANZONI\n- ALBUM";
    QMessageBox::information(nullptr,"Salvataggio",str);

    // SCELTA FILE LIBRI

    QString temp = QFileDialog::getOpenFileName(nullptr, "Seleziona il file .json di salvataggio LIBRI", dirIniziale, "Json (*.json)");

    if(QFileInfo(temp).suffix().toLower()!="json")
        temp="";
    save_file["libro"] = temp.toStdString();

    // SCELTA FILE CANZONI

    temp = QFileDialog::getOpenFileName(nullptr, "Seleziona il file .json di salvataggio CANZONI", dirIniziale, "Json (*.json)");
        
    if(QFileInfo(temp).suffix().toLower()!="json")
        temp="";
    save_file["canzone"] = temp.toStdString();

    // SCELTA FILE ALBUM

    temp = QFileDialog::getOpenFileName(nullptr, "Seleziona il file .json di salvataggio ALBUM", dirIniziale, "Json (*.json)");

    if(QFileInfo(temp).suffix().toLower()!="json")
        temp="";
    save_file["album"] = temp.toStdString();


}







