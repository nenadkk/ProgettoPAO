#include <QFileInfo>
#include <QMessageBox>
#include <QFileDialog>
#include "widgetCreazione.h"
#include "qglobal.h"

widgetCreazione::widgetCreazione(mediaManager* man, media* tipo, mainWindow* windowEsterna, QListWidget* tracks, QWidget* parent) : 
    QWidget(parent), manager(man), tipo(tipo), windowEsterna(windowEsterna), trackList(tracks)
{}

QLineEdit*& widgetCreazione::operator[](const QString& key) 
{
    return attributi[key];
}

void widgetCreazione::insertLineEdit(QString str,QLineEdit* n)
{
    attributi.insert(str,n);
}
void widgetCreazione::crea()
{
    if(validaInput())
    {
        if(dynamic_cast<libro*>(tipo))
        {
            copiaImmagine();
            manager->addMedia(new libro(attributi["titolo"]->text().toStdString(),
                                        attributi["autore"]->text().toStdString(),
                                        attributi["anno"]->text().toInt(),
                                        attributi["copertina"]->text().toStdString(),
                                        manager->trovaIdLibero(),
                                        attributi["numeroPagine"]->text().toInt(),
                                        attributi["isbn"]->text().toInt(),
                                        attributi["editore"]->text().toStdString()));
        }
        else if(dynamic_cast<canzone*>(tipo))
        {
            copiaImmagine();
            int durata = (attributi["durataMin"]->text().toInt())*60+(attributi["durataSec"]->text().toInt());
            manager->addMedia(new canzone(attributi["titolo"]->text().toStdString(),
                                        attributi["autore"]->text().toStdString(),
                                        attributi["anno"]->text().toInt(),
                                        attributi["copertina"]->text().toStdString(),
                                        manager->trovaIdLibero(),
                                        durata,
                                        attributi["genere"]->text().toStdString()));
        }
        else if (dynamic_cast<album*>(tipo)) 
        {
            copiaImmagine();
            //creazione album
            album *newAlbum = new album(attributi["titolo"]->text().toStdString(),
                                        attributi["autore"]->text().toStdString(),
                                        attributi["anno"]->text().toInt(),
                                        attributi["copertina"]->text().toStdString(),
                                        manager->trovaIdLibero());

            //aggiunta canzoni ad album
            for(int i=0; i<trackList->count();++i)
            {
                QListWidgetItem *item = trackList->item(i);
                if (item->checkState() == Qt::Checked) 
                {
                    int trackID = item->data(Qt::UserRole).toInt();
                    media* c = manager->searchById(trackID);
                    if(c && dynamic_cast<canzone*>(c))
                    {
                        newAlbum->addCanzone(dynamic_cast<canzone*>(c));
                    }
                }
            }

            manager->addMedia(newAlbum);
        }
        delete tipo;
        windowEsterna->reloadMediaVisibili();
    }
}

bool widgetCreazione::validaInput()
{
    foreach(auto val, attributi.values())
    {
        if(val->text().isEmpty())
        {
            QMessageBox::warning(this, "Validazione", "Dati non validi o nulli. Compilare ogni campo con valori significativi.");
            return false;
        }
    }
    return true;
}

void widgetCreazione::copiaImmagine() 
{
    QFileInfo infoImmagine(attributi["copertina"]->text());
    if (!infoImmagine.exists()) {
        qDebug() << "L'immagine sorgente non esiste.";
        return;
    }

    QString nomeFile = infoImmagine.fileName();
    QString percorsoDestinazione = "./immagini/" + nomeFile;
    QFileInfo infoDestinazione(percorsoDestinazione);

    if (!infoDestinazione.exists()) 
    {
        if (!QFile::copy(attributi["copertina"]->text(), percorsoDestinazione)) 
        {
            qDebug() << "Errore durante la copia dell'immagine.";
            return;
        }
        attributi["copertina"]->setText(percorsoDestinazione);
    }


}

void widgetCreazione::browseImage()
{
    if(attributi["copertina"])
    {
        QString filePath = QFileDialog::getOpenFileName(this, "Seleziona un'immagine", "", "Immagini (*.png *.jpg *.jpeg *.bmp *.gif)");
        if (!filePath.isEmpty() && isImageFile(filePath))    
            attributi["copertina"]->setText(filePath);       
    }
}

bool widgetCreazione::isImageFile(const QString &filePath) const 
{
    QFileInfo fileInfo(filePath);
    QString ext = fileInfo.suffix().toLower();
    return (ext == "png" || ext == "jpg" || ext == "jpeg" || ext == "jpeg" || ext == "bmp" || ext == "gif");
}






