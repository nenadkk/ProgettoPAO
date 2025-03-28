#include "mediaWidget.h"
#include "../logica/libro.h"
#include "../logica/canzone.h"
#include "../logica/album.h"
#include "qboxlayout.h"
#include "qglobal.h"
#include "qwidget.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QMouseEvent>
#include <QListWidget>

mediaWidget::mediaWidget(media* obj, QGridLayout* l, QWidget* parent) : QWidget(parent), layoutEsterno(l), object(obj)  
{
        QVBoxLayout* mainLayout = new QVBoxLayout();
        mainLayout->setAlignment(Qt::AlignCenter);

        setFixedSize(250, 330);
        setAttribute(Qt::WA_StyledBackground);
        setStyleSheet("QWidget {background-color: #686868; border-radius: 10px;}");


        QLabel *imageLabel = new QLabel();
        imageLabel->setPixmap(QPixmap(toQString(object->getCopertina())).scaled(200, 300, Qt::KeepAspectRatio));
        imageLabel->setAlignment(Qt::AlignCenter);
        mainLayout->addWidget(imageLabel);

        QLabel *labelTitolo = new QLabel(toQString(object->getTitolo()));
        labelTitolo->setFont(QFont("Mono",13));
        labelTitolo->setAlignment(Qt::AlignCenter);
        mainLayout->addWidget(labelTitolo);

        QLabel *labelAutore = new QLabel(toQString(object->getTitolo()));
        labelAutore->setFont(QFont("Mono",13));
        labelAutore->setAlignment(Qt::AlignCenter);
        mainLayout->addWidget(labelAutore);

        this->setLayout(mainLayout);


/*
        // Pulsanti
        QPushButton *buttonModifica = new QPushButton("Modifica", this);
        QPushButton *buttonElimina = new QPushButton("Elimina", this);
        
        buttonLayout->addWidget(buttonModifica);
        buttonLayout->addWidget(buttonElimina);
        
        buttonModifica->setStyleSheet("color: black; background-color: #A8A8A8;");
        buttonElimina->setStyleSheet("color: black; background-color: #A8A8A8;");

        buttonModifica->setFixedSize(120, 40);
        buttonElimina->setFixedSize(120, 40);

        mainLayout->addLayout(buttonLayout);

        connect(buttonModifica, &QPushButton::clicked, this, &mediaWidget::modificaClicked);
        connect(buttonElimina, &QPushButton::clicked, this, &mediaWidget::eliminaClicked); 
        */
}
void mediaWidget::mousePressEvent(QMouseEvent* event)  
{
    if (event->button() == Qt::LeftButton) //se viene clickato con il tasto sx del mouse
        emit clicked(); 
                        
    QWidget::mousePressEvent(event);
}

void mediaWidget::resetSchermata()
{
    if (!layoutEsterno)
        return;


    // Rimuove tutti gli altri widget
    for (int i = layoutEsterno->count() - 1; i >= 0; --i) 
    {
        QLayoutItem* item = layoutEsterno->itemAt(i);
        if (item) 
        {
            QWidget* widget = item->widget();
            if (widget && widget != this) 
            {
                layoutEsterno->removeWidget(widget);
                delete widget;  
            }
        }
    }

    // Svuota questo widget
    if(layout())
    {
        QLayout *l =layout();
        for (int i = l->count() - 1; i >= 0; --i) 
        {
            QLayoutItem* item = l->itemAt(i);
            if (item) 
            {
                QWidget* widget = item->widget();

                l->removeWidget(widget);
                delete widget;  
            }
        }   
        delete layout(); //rimuove il corrente layout associato al widget
    }

    //rimuovo la formattazione precedente
    this->setMinimumSize(QSize(0, 0));  
    this->setMaximumSize(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    layoutEsterno->update();
}

void mediaWidget::dettagliLibro()
{
    resetSchermata();

    QVBoxLayout *layout = new QVBoxLayout();
    layout->setAlignment(Qt::AlignLeft);

    libro *objLibro = dynamic_cast<libro*>(object);

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
    info->setAlignment(Qt::AlignLeft);
    layout->addWidget(info);

    this->setStyleSheet("QWidget {background-color: #686868; border-radius: 10px; padding: 10px;}");
    this->setLayout(layout);

}

void mediaWidget::dettagliCanzone()
{
    resetSchermata();

    QVBoxLayout *layout = new QVBoxLayout();
    layout->setAlignment(Qt::AlignLeft);

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
    info->setAlignment(Qt::AlignLeft);
    layout->addWidget(info);

    this->setStyleSheet("QWidget {background-color: #686868; border-radius: 10px; padding: 10px;}");
    this->setLayout(layout);

}

void mediaWidget::dettagliAlbum()
{
    resetSchermata();

    this->setStyleSheet("QWidget {background-color: #686868; border-radius: 10px; padding: 10px;}");

    QHBoxLayout *layout = new QHBoxLayout();

    //PARTE DI SINISTRA
    QWidget *parteSx = new QWidget();
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

    layoutSX->addWidget(info);
    parteSx->setLayout(layoutSX);
    layout->addWidget(parteSx);

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

    this->setLayout(layout);

}


void mediaWidget::eliminaClicked()
{

}
void mediaWidget::modificaClicked()
{

}
