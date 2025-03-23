#include "mediaWidget.h"
#include "qpushbutton.h"
#include <QVBoxLayout>
#include <QHBoxLayout>

mediaWidget::mediaWidget(media* obj, string* campoDati, QWidget* parent) : QWidget(parent), object(obj) 
{
        QVBoxLayout* mainLayout = new QVBoxLayout(this);
        QHBoxLayout* buttonLayout = new QHBoxLayout();
        mainLayout->setAlignment(Qt::AlignCenter);
        setFixedSize(270, 400);

        // Immagine
        QLabel *imageLabel = new QLabel();
        imageLabel->setPixmap(QPixmap(toQString(object->getCopertina())).scaled(200, 200, Qt::KeepAspectRatio));
        imageLabel->setAlignment(Qt::AlignCenter);
        mainLayout->addWidget(imageLabel);


        // Campi label
        for (int i = 0; i < 6; ++i) 
        {
            QLabel *label = new QLabel(toQString(campoDati[i]), this);
            label->setFont(QFont("Mono",13));
            label->setWordWrap(true);
            label->setAlignment(Qt::AlignCenter);
            mainLayout->addWidget(label);
        }

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
}

void mediaWidget::modificaClicked()
{
    
}

void mediaWidget::eliminaClicked()
{

}
