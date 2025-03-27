#include "mediaWidget.h"
#include "qglobal.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QMouseEvent>

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

        QLabel *labelTitolo = new QLabel(toQString(obj->getTitolo()));
        labelTitolo->setFont(QFont("Mono",13));
        labelTitolo->setAlignment(Qt::AlignCenter);
        mainLayout->addWidget(labelTitolo);

        QLabel *labelAutore = new QLabel(toQString(obj->getTitolo()));
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

void mediaWidget::dettagliLibro()
{
    

}

void mediaWidget::dettagliCanzone()
{

}

void mediaWidget::dettagliAlbum()
{

}

void mediaWidget::modificaClicked()
{
    
}

void mediaWidget::eliminaClicked()
{

}
