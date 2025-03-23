#include <QFileInfo>
#include <QFileDialog>
#include "widgetCreazione.h"
widgetCreazione::widgetCreazione(mediaManager* man, media* tipo, mainWindow* windowEsterna, QPushButton* parent) : 
    QWidget(parent), manager(man), tipo(tipo), windowEsterna(windowEsterna)
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
    if(dynamic_cast<libro*>(tipo))
    {
        string titolo = (attributi)["titolo"]->text().toStdString(),
               autore = (attributi)["autore"]->text().toStdString(),
               copertina = (attributi)["copertina"]->text().toStdString(),
               editore = (attributi)["editore"]->text().toStdString();

        int anno = (attributi)["anno"]->text().toInt(),
            numeroPagine = (attributi)["numeroPagine"]->text().toInt(),
            isbn = (attributi)["isbn"]->text().toInt();
    }
    delete tipo;
    windowEsterna->reloadMediaVisibili();
}
void widgetCreazione::copiaImmagine(QString& pathImmagine) 
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






