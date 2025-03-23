#include "bottoneSalva.h"

#include <QFileInfo>
bottoneSalva::bottoneSalva(mediaManager* man, QMap<QString,QLineEdit*> map, media* tipo, mainWindow* windowEsterna, QPushButton* parent) : 
    QPushButton("SALVA",parent), manager(man), attributi(map), tipo(tipo), windowEsterna(windowEsterna)
{
    connect(this, &QPushButton::clicked, this, &bottoneSalva::crea);
}

void bottoneSalva::crea()
{
    


    if(dynamic_cast<libro*>(tipo))
    {
        string titolo,autore,copertina,editore;
        int  anno,numeroPagine,isbn;

        manager->addMedia(new libro((attributi)["titolo"]->text().toStdString(),
                                    (attributi)["autore"]->text().toStdString(),
                                    (attributi)["anno"]->text().toInt(),
                                    (attributi)["copertina"]->text().toStdString(),
                                    0,
                                    (attributi)["numeroPagine"]->text().toInt(),
                                    (attributi)["isbn"]->text().toInt(),
                                    (attributi)["editore"]->text().toStdString()
                                    ));
    }
    delete tipo;
    windowEsterna->reloadMediaVisibili();
}
void bottoneSalva::copiaImmagine(QString& pathImmagine) 
{
    QFileInfo infoImmagine(pathImmagine);
    if (!infoImmagine.exists()) {
        qDebug() << "L'immagine sorgente non esiste.";
        return;
    }

    QString nomeFile = infoImmagine.fileName();
    QString percorsoDestinazione = "./immagini/" + nomeFile;
    QFileInfo infoDestinazione(percorsoDestinazione);

    if (!infoDestinazione.exists()) 
    {
        if (!QFile::copy(pathImmagine, percorsoDestinazione)) 
        {
            qDebug() << "Errore durante la copia dell'immagine.";
            return;
        }
        pathImmagine = percorsoDestinazione;
    }


}







