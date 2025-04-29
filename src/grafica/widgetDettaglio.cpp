#include "widgetDettaglio.h"
#include "editorLibro.h"
#include "editorCanzone.h"
#include "editorAlbum.h"
#include "qglobal.h"
#include "qnamespace.h"
#include "sceltaDettaglioVisitor.h"
#include <QWidget>
#include <QPushButton>
#include <QMessageBox>

widgetDettaglio::widgetDettaglio(media* obj, mediaManager* man, mainWindow* parent): 
    object(obj),manager(man), windowEsterna(parent) 
{
    sceltaDettaglioVisitor vis(this);
    obj->accept(&vis);
}

void widgetDettaglio::buildDettaglio(libro* object)
{
    QVBoxLayout *layout = new QVBoxLayout(); 
    layout->setAlignment(Qt::AlignCenter);

    QLabel *imageLabel = new QLabel();
    imageLabel->setPixmap(QPixmap(toQString(object->getCopertina())).scaled(300, 400, Qt::KeepAspectRatio));
    imageLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(imageLabel);

    QString str = "Titolo: " + QString::fromStdString(object->getTitolo()) + "\n" +
                  "Autore: " + QString::fromStdString(object->getAutore()) + "\n" +
                  "Anno: " + QString::number(object->getAnno()) + "\n" +
                  "ID: " + QString::number(object->getId()) + "\n" +
                  "Numero Pagine: " + QString::number(object->getNumPagine()) + "\n" +
                  "ISBN: " + QString::number(object->getIsbn()) + "\n" +
                  "Editore: " + QString::fromStdString(object->getEditore()) + "\n";
                    
    QLabel *info = new QLabel(str);
    info->setFont(QFont("Mono",20));
    info->setAlignment(Qt::AlignCenter);
    layout->addWidget(info);

    // Pulsanti
    QHBoxLayout *layoutPulsanti = new QHBoxLayout();

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

    connect(buttonModifica, &QPushButton::clicked, this, &widgetDettaglio::modificaLibro);
    connect(buttonElimina, &QPushButton::clicked, this, &widgetDettaglio::removeMedia);

    layout->addLayout(layoutPulsanti);



    this->setStyleSheet("QWidget {background-color: #686868; border-radius: 10px; padding: 10px;}");
    this->setLayout(layout);

}

void widgetDettaglio::buildDettaglio(canzone* object)
{
    QVBoxLayout *layout = new QVBoxLayout();
    layout->setAlignment(Qt::AlignCenter);

    QLabel *imageLabel = new QLabel();
    imageLabel->setPixmap(QPixmap(toQString(object->getCopertina())).scaled(300, 400, Qt::KeepAspectRatio));
    imageLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(imageLabel);


    QString str = "Titolo: " + QString::fromStdString(object->getTitolo()) + "\n" +
                  "Autore: " + QString::fromStdString(object->getAutore()) + "\n" +
                  "Anno: " + QString::number(object->getAnno()) + "\n" +
                  "ID: " + QString::number(object->getId()) + "\n" +
                  "Durata: " + QString::number(object->getDurata()/60) +":";

    if(object->getDurata()%60 > 9)
        str += QString::number(object->getDurata()%60);  
    else
        str += "0"+QString::number(object->getDurata()%60);   

    str += "\nGenere: " + QString::fromStdString(object->getGenere()) + "\n";

    QLabel *info = new QLabel(str);
    info->setFont(QFont("Mono",20));
    info->setAlignment(Qt::AlignCenter);
    layout->addWidget(info);    


    // Pulsanti
    QHBoxLayout *layoutPulsanti = new QHBoxLayout();
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

    connect(buttonModifica, &QPushButton::clicked, this, &widgetDettaglio::modificaCanzone);
    connect(buttonElimina, &QPushButton::clicked, this, &widgetDettaglio::removeMedia);

    layout->addLayout(layoutPulsanti);


    this->setStyleSheet("QWidget {background-color: #686868; border-radius: 10px; padding: 10px;}");
    this->setLayout(layout);


}

void widgetDettaglio::buildDettaglio(album* object)
{
    QHBoxLayout *layout = new QHBoxLayout();

    //PARTE DI SINISTRA
    QVBoxLayout *layoutSX = new QVBoxLayout();
    layoutSX->setAlignment(Qt::AlignLeft);

    QLabel *imageLabel = new QLabel();
    imageLabel->setPixmap(QPixmap(toQString(object->getCopertina())).scaled(300, 400, Qt::KeepAspectRatio));
    imageLabel->setAlignment(Qt::AlignCenter);
    layoutSX->addWidget(imageLabel);

    QString str = "Titolo: " + QString::fromStdString(object->getTitolo()) + "\n" +
                  "Autore: " + QString::fromStdString(object->getAutore()) + "\n" +
                  "Anno: " + QString::number(object->getAnno()) + "\n" +
                  "ID: " + QString::number(object->getId()) + "\n" +
                  "Durata: " + QString::number(object->getDurataTotale()/60) +":";

    if(object->getDurataTotale()%60 > 9)
        str += QString::number(object->getDurataTotale()%60);  
    else
        str += "0"+QString::number(object->getDurataTotale()%60);  


    QLabel *info = new QLabel(str);
    info->setFont(QFont("Mono",20));
    info->setAlignment(Qt::AlignLeft);

    // Pulsanti
    QHBoxLayout *layoutPulsanti = new QHBoxLayout();

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

    connect(buttonModifica, &QPushButton::clicked, this, &widgetDettaglio::modificaAlbum);
    connect(buttonElimina, &QPushButton::clicked, this, &widgetDettaglio::removeMedia);



    layoutSX->addWidget(info);
    layoutSX->addLayout(layoutPulsanti);
    layout->addLayout(layoutSX);

    //PARTE DI DESTRA
    QVBoxLayout *layoutDX = new QVBoxLayout();
    QWidget *parteDx = new QWidget();
    parteDx->setStyleSheet("border: 1px solid white");

    QLabel *lableTracklist = new QLabel("LISTA CANZONI");
    lableTracklist->setFont(QFont("Mono",20));
    lableTracklist->setAlignment(Qt::AlignCenter);   
    lableTracklist->setFixedHeight(50);

    layoutDX->addWidget(lableTracklist);

    QListWidget *tracklist = new QListWidget();

    for (int i=0; i<object->getNumCanzoni();i++)
    {
        QString txt = QString::fromStdString((*object)[i]->getTitolo()) +"    "+ 
                      QString::fromStdString((*object)[i]->getAutore()) +"    "+
                      QString::number((*object)[i]->getDurata()/60) +":"+
                      QString::number((*object)[i]->getDurata()%60);

        
        QListWidgetItem* track = new QListWidgetItem(txt);
        track->setFont(QFont("Mono",20));
        tracklist->addItem(track);

    }

    if(object->getNumCanzoni()==0)
    {
        QListWidgetItem* lableZeroCanzoni = new QListWidgetItem("Non ci sono canzoni\nin questo album.");
        lableZeroCanzoni->setFont(QFont("Mono",20));
        lableZeroCanzoni->setTextAlignment(Qt::AlignCenter);

        tracklist->addItem(lableZeroCanzoni);
    }
    
    layoutDX->addWidget(tracklist);

    parteDx->setLayout(layoutDX);
    layout->addWidget(parteDx);

    this->setStyleSheet("QWidget {background-color: #686868; border-radius: 10px; padding: 10px;}");
    this->setLayout(layout);


}


void widgetDettaglio::removeMedia()
{
    QString str = "L'elemento verrà eliminato definitivamente. Vuoi procedere?";
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Conferma azione",str,QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) 
    {
        manager->removeMedia(object->getId());
        windowEsterna->reloadMediaVisibili();
    }
    
}

void widgetDettaglio::modificaLibro()
{
    editorLibro *temp = new editorLibro(manager,windowEsterna,object);
    windowEsterna->addToMediaVisibili(temp);  
}

void widgetDettaglio::modificaCanzone()
{
    editorCanzone *temp = new editorCanzone(manager,windowEsterna,object);
    windowEsterna->addToMediaVisibili(temp);   
}

void widgetDettaglio::modificaAlbum()
{
    editorAlbum *temp = new editorAlbum(manager,windowEsterna,object);
    windowEsterna->addToMediaVisibili(temp);
}















