#include "creazioneDiCanzone.h"
#include "widgetDiCreazione.h"
#include <QLabel>

creazioneDiCanzone::creazioneDiCanzone(mediaManager* man, QWidget* parent) : widgetDiCreazione(man,parent)
{
    QVBoxLayout *layout = new QVBoxLayout();    

    layout->setAlignment(Qt::AlignCenter);

    //---------- DURATA ----------
    QWidget *widgetDurata = new QWidget();
    widgetDurata->setFixedWidth(350);
 
    QLabel *lableDurata = new QLabel("Durata: ");
    lableDurata->setFont(QFont("Mono",14));
    lableDurata->setFixedSize(120,30);

    this->insertLineEdit("durataMin",new QLineEdit());
    (*this)["durataMin"]->setFont(QFont("Mono",14));
    (*this)["durataMin"]->setFixedSize(40,30);
    QIntValidator *validatorDurataMin = new QIntValidator((*this)["durataMin"]);
    (*this)["durataMin"]->setValidator(validatorDurataMin);

    QLabel *lableMin = new QLabel("min");
    lableMin->setFont(QFont("Mono",14));
    
    this->insertLineEdit("durataSec",new QLineEdit());
    (*this)["durataSec"]->setFont(QFont("Mono",14));
    (*this)["durataSec"]->setFixedSize(40,30);
    QIntValidator *validatorDurataSec = new QIntValidator((*this)["durataSec"]);
    (*this)["durataSec"]->setValidator(validatorDurataSec);

    QLabel *lableSec = new QLabel("sec");
    lableSec->setFont(QFont("Mono",14));

    QHBoxLayout *layoutDurata = new QHBoxLayout(widgetDurata);
    layoutDurata->setContentsMargins(0,0,0,0);
    layoutDurata->setSpacing(0);
    layoutDurata->addWidget(lableDurata,0,Qt::AlignLeft);
    layoutDurata->addWidget((*this)["durataMin"],0, Qt::AlignRight);
    layoutDurata->addWidget(lableMin,0,Qt::AlignRight);
    layoutDurata->addWidget((*this)["durataSec"],0, Qt::AlignRight);
    layoutDurata->addWidget(lableSec,0,Qt::AlignRight);

    //---------- GENERE ----------
    QWidget *widgetGenere = new QWidget();
    widgetGenere->setFixedWidth(350);

    QLabel *lableGenere = new QLabel("Genere: ");
    lableGenere->setFont(QFont("Mono",14));
    lableGenere->setFixedSize(120,30);

    this->insertLineEdit("genere",new QLineEdit());
    (*this)["genere"]->setFont(QFont("Mono",14));
    (*this)["genere"]->setFixedSize(200,30);


    QHBoxLayout *layoutGenere = new QHBoxLayout(widgetGenere);
    layoutGenere->setContentsMargins(0,0,0,0);
    layoutGenere->setSpacing(0);
    layoutGenere->addWidget(lableGenere,0,Qt::AlignRight);
    layoutGenere->addWidget((*this)["genere"],0, Qt::AlignLeft);

    //---------- PULSANTI ----------
    QWidget *widgetPulsanti = new QWidget();
    QHBoxLayout *layoutPulsanti = new QHBoxLayout(widgetPulsanti);

    //---------- PULSANTE ANNULLA ----------
    QPushButton *btnAnnulla = new QPushButton("ANNULLA",widgetPulsanti);
    btnAnnulla->setFixedSize(200,50);
    btnAnnulla->setFont(QFont("Mono",15));
    QObject::connect(btnAnnulla, &QPushButton::clicked, windowEsterna, &mainWindow::reloadMediaVisibili);
    layoutPulsanti->addWidget(btnAnnulla,0, Qt::AlignLeft);

    //---------- PULSANTE SALVA ----------
    QPushButton *btnSalva = new QPushButton("SALVA",widgetPulsanti);
    btnSalva->setFixedSize(200,50);
    btnSalva->setFont(QFont("Mono",15));
    QObject::connect(btnSalva, &QPushButton::clicked, this, &creazioneDiCanzone::crea);
    layoutPulsanti->addWidget(btnSalva,0, Qt::AlignRight);

    //---------------------------------------------------
    layout->addWidget(widgetBase[0]);
    layout->addWidget(widgetBase[1]);
    layout->addWidget(widgetBase[2]);
    layout->addWidget(widgetDurata);
    layout->addWidget(widgetGenere);
    layout->addWidget(widgetBase[3]);
    layout->addWidget(widgetPulsanti);

    this->setLayout(layout);
}

void creazioneDiCanzone::crea()
{    
    if(validaInput())
    {
        int durata = (attributi["durataMin"]->text().toInt())*60+(attributi["durataSec"]->text().toInt());
        manager->addMedia(new canzone(attributi["titolo"]->text().toStdString(),
                    attributi["autore"]->text().toStdString(),
                    attributi["anno"]->text().toInt(),
                    attributi["copertina"]->text().toStdString(),
                    manager->trovaIdLibero(),
                    durata,
                    attributi["genere"]->text().toStdString()));

        windowEsterna->reloadMediaVisibili();
    }

}
