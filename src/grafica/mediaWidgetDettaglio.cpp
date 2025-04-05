#include "mediaWidgetDettaglio.h"
#include "sceltaDettaglioVisitor.h"
#include <QWidget>
#include <QPushButton>
#include <QMessageBox>

mediaWidgetDettaglio::mediaWidgetDettaglio(media* obj): QWidget(nullptr), object(obj)
{
    sceltaDettaglioVisitor vis(this);
    obj->accept(&vis);
}

void mediaWidgetDettaglio::buildDettaglio(libro* object)
{
    QVBoxLayout *layout = new QVBoxLayout();
    layout->setAlignment(Qt::AlignCenter);

    libro *objLibro = dynamic_cast<libro*>(object); //sono sicuro che funzioni perché questa
                                                    //funzione è richiamata dal visitor

    QLabel *imageLabel = new QLabel();
    imageLabel->setPixmap(QPixmap(toQString(objLibro->getCopertina())).scaled(300, 400, Qt::KeepAspectRatio));
    imageLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(imageLabel);

    QString str = "Titolo: " + QString::fromStdString(objLibro->getTitolo()) + "\n" +
                  "Autore: " + QString::fromStdString(objLibro->getAutore()) + "\n" +
                  "Anno: " + QString::number(objLibro->getAnno()) + "\n" +
                  "ID: " + QString::number(objLibro->getId()) + "\n" +
                  "Numero Pagine: " + QString::number(objLibro->getNumPagine()) + "\n" +
                  "ISBN: " + QString::number(objLibro->getIsbn()) + "\n" +
                  "Editore: " + QString::fromStdString(objLibro->getEditore()) + "\n";
                    
    QLabel *info = new QLabel(str);
    info->setFont(QFont("Mono",20));
    info->setAlignment(Qt::AlignCenter);
    layout->addWidget(info);

    QHBoxLayout *layoutPulsanti = new QHBoxLayout();
    aggiungiPulsanti(layoutPulsanti);
    layout->addLayout(layoutPulsanti);

    this->setStyleSheet("QWidget {background-color: #686868; border-radius: 10px; padding: 10px;}");
    this->setLayout(layout);

}

void mediaWidgetDettaglio::buildDettaglio(canzone* object)
{
    QVBoxLayout *layout = new QVBoxLayout();
    layout->setAlignment(Qt::AlignCenter);

    canzone *objCanzone = dynamic_cast<canzone*>(object);

    QLabel *imageLabel = new QLabel();
    imageLabel->setPixmap(QPixmap(toQString(objCanzone->getCopertina())).scaled(300, 400, Qt::KeepAspectRatio));
    imageLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(imageLabel);


    QString str = "Titolo: " + QString::fromStdString(objCanzone->getTitolo()) + "\n" +
                  "Autore: " + QString::fromStdString(objCanzone->getAutore()) + "\n" +
                  "Anno: " + QString::number(objCanzone->getAnno()) + "\n" +
                  "ID: " + QString::number(objCanzone->getId()) + "\n" +
                  "Durata: " + QString::number(objCanzone->getDurata()/60) +":";

    if(objCanzone->getDurata()%60 > 9)
        str += QString::number(objCanzone->getDurata()%60);  
    else
        str += "0"+QString::number(objCanzone->getDurata()%60);   

    str += "\nGenere: " + QString::fromStdString(objCanzone->getGenere()) + "\n";

    QLabel *info = new QLabel(str);
    info->setFont(QFont("Mono",20));
    info->setAlignment(Qt::AlignCenter);
    layout->addWidget(info);    

    QHBoxLayout *layoutPulsanti = new QHBoxLayout();
    aggiungiPulsanti(layoutPulsanti);
    layout->addLayout(layoutPulsanti);

    this->setStyleSheet("QWidget {background-color: #686868; border-radius: 10px; padding: 10px;}");
    this->setLayout(layout);


}

void mediaWidgetDettaglio::buildDettaglio(album* object)
{
    QHBoxLayout *layout = new QHBoxLayout();

    //PARTE DI SINISTRA
    QVBoxLayout *layoutSX = new QVBoxLayout();
    layoutSX->setAlignment(Qt::AlignLeft);

    album *objAlbum = dynamic_cast<album*>(object);

    QLabel *imageLabel = new QLabel();
    imageLabel->setPixmap(QPixmap(toQString(objAlbum->getCopertina())).scaled(300, 400, Qt::KeepAspectRatio));
    imageLabel->setAlignment(Qt::AlignCenter);
    layoutSX->addWidget(imageLabel);

    QString str = "Titolo: " + QString::fromStdString(objAlbum->getTitolo()) + "\n" +
                  "Autore: " + QString::fromStdString(objAlbum->getAutore()) + "\n" +
                  "Anno: " + QString::number(objAlbum->getAnno()) + "\n" +
                  "ID: " + QString::number(objAlbum->getId()) + "\n" +
                  "Durata: " + QString::number(objAlbum->getDurataTotale()/60) +":";

    if(objAlbum->getDurataTotale()%60 > 9)
        str += QString::number(objAlbum->getDurataTotale()%60);  
    else
        str += "0"+QString::number(objAlbum->getDurataTotale()%60);  


    QLabel *info = new QLabel(str);
    info->setFont(QFont("Mono",20));
    info->setAlignment(Qt::AlignLeft);

    QHBoxLayout *layoutPulsanti = new QHBoxLayout();
    aggiungiPulsanti(layoutPulsanti);

    layoutSX->addWidget(info);
    layoutSX->addLayout(layoutPulsanti);
    layout->addLayout(layoutSX);

    //PARTE DI DESTRA
    QVBoxLayout *layoutDX = new QVBoxLayout();
    QWidget *parteDx = new QWidget();
    parteDx->setStyleSheet("border: 1px solid white");

    QListWidget *tracklist = new QListWidget();

    for (int i=0; i<objAlbum->getNumCanzoni();i++)
    {
        QString txt = QString::fromStdString((*objAlbum)[i]->getTitolo()) +"    "+ 
                      QString::fromStdString((*objAlbum)[i]->getAutore()) +"    "+
                      QString::number((*objAlbum)[i]->getDurata()/60) +":"+
                      QString::number((*objAlbum)[i]->getDurata()%60);

        
        QListWidgetItem* track = new QListWidgetItem(txt);
        track->setFont(QFont("Mono",20));
        tracklist->addItem(track);

    }

    QLabel *lableTracklist = new QLabel("LISTA CANZONI");
    lableTracklist->setFont(QFont("Mono",20));
    lableTracklist->setAlignment(Qt::AlignCenter);   
    lableTracklist->setFixedHeight(50);

    layoutDX->addWidget(lableTracklist);

    if(objAlbum->getNumCanzoni()==0)
    {
        QLabel *lableZeroCanzoni = new QLabel("Non ci sono canzoni\nin questo album.");
        lableZeroCanzoni->setFont(QFont("Mono",20));
        lableZeroCanzoni->setAlignment(Qt::AlignCenter);   

        layoutDX->addWidget(lableZeroCanzoni);

    }
    else
        layoutDX->addWidget(tracklist);

    parteDx->setLayout(layoutDX);
    layout->addWidget(parteDx);

    this->setStyleSheet("QWidget {background-color: #686868; border-radius: 10px; padding: 10px;}");
    this->setLayout(layout);


}

void mediaWidgetDettaglio::aggiungiPulsanti(QHBoxLayout* layoutPulsanti)
{
        // Pulsanti
        QPushButton *buttonModifica = new QPushButton("Modifica");
        QPushButton *buttonElimina = new QPushButton("Elimina");
        
        layoutPulsanti->addWidget(buttonModifica);
        layoutPulsanti->addWidget(buttonElimina);
        
        buttonModifica->setFont(QFont("Mono",18));
        buttonElimina->setFont(QFont("Mono",18));

        buttonModifica->setStyleSheet("color: black; background-color: #A8A8A8; padding: 10px");
        buttonElimina->setStyleSheet("color: black; background-color: #A8A8A8; padding: 10px");

        buttonModifica->setFixedSize(150, 60);
        buttonElimina->setFixedSize(150, 60);

        connect(buttonElimina, &QPushButton::clicked, this, &mediaWidgetDettaglio::removeMedia);

}

void mediaWidgetDettaglio::removeMedia()
{
    QString str = "L'elemento verrà eliminato definitivamente. Vuoi procedere?";
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Conferma azione",str,QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) 
    {

    }
    
}
















