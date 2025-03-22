#include "createMediaVisitor.h"
#include "bottoneSfoglia.h"
#include "qpushbutton.h"
#include "qwidget.h"

#include <QWidget>
#include <QLabel>
#include <QFileDialog>
#include <QPushButton>
createMediaVisitor::createMediaVisitor(mainWindow* m, QGridLayout* l) : windowEsterna(m), layoutEsterno(l){}

void createMediaVisitor::creaSottoOggettoMedia(QWidget **widgetBase, QLineEdit **campiBase )
{
    //---------- TITOLO ----------
    QLabel *lableTitolo = new QLabel("Titolo: ");
    lableTitolo->setFont(QFont("Mono",14));
    lableTitolo->setFixedSize(120,30);

    campiBase[0] = new QLineEdit();
    campiBase[0]->setFont(QFont("Mono",14));
    campiBase[0]->setFixedSize(200,30);

    widgetBase[0] = new QWidget();

    QHBoxLayout *layoutTitolo = new QHBoxLayout(widgetBase[0]);
    layoutTitolo->setContentsMargins(0,0,0,0);
    layoutTitolo->setSpacing(0);
    layoutTitolo->addWidget(lableTitolo,0,Qt::AlignRight);
    layoutTitolo->addWidget(campiBase[0],0, Qt::AlignLeft);

    //---------- AUTORE ----------
    QLabel *lableAutore = new QLabel("Autore: ");
    lableAutore->setFont(QFont("Mono",14));
    lableAutore->setFixedSize(120,30);

    campiBase[1] = new QLineEdit();
    campiBase[1]->setFont(QFont("Mono",14));
    campiBase[1]->setFixedSize(200,30);

    widgetBase[1] = new QWidget();

    QHBoxLayout *layoutAutore = new QHBoxLayout(widgetBase[1]);
    layoutAutore->setContentsMargins(0,0,0,0);
    layoutAutore->setSpacing(0);
    layoutAutore->addWidget(lableAutore,0,Qt::AlignRight);
    layoutAutore->addWidget(campiBase[1],0, Qt::AlignLeft);

    //---------- ANNO ----------
    QLabel *lableAnno = new QLabel("Anno: ");
    lableAnno->setFont(QFont("Mono",14));
    lableAnno->setFixedSize(120,30);

    campiBase[2] = new QLineEdit();
    campiBase[2]->setFont(QFont("Mono",14));
    campiBase[2]->setFixedSize(200,30);

    widgetBase[2] = new QWidget();

    QHBoxLayout *layoutAnno = new QHBoxLayout(widgetBase[2]);
    layoutAnno->setContentsMargins(0,0,0,0);
    layoutAnno->setSpacing(0);
    layoutAnno->addWidget(lableAnno,0,Qt::AlignRight);
    layoutAnno->addWidget(campiBase[2],0, Qt::AlignLeft);

    //---------- COPERTINA ----------
    QLabel *lableCopertina = new QLabel("Copertina: ");
    lableCopertina->setFont(QFont("Mono",14));
    lableCopertina->setFixedSize(120,30);

    campiBase[3] = new QLineEdit();
    campiBase[3]->setFont(QFont("Mono",14));
    campiBase[3]->setFixedSize(200,30);

    widgetBase[3] = new QWidget();

    QHBoxLayout *layoutCopertina = new QHBoxLayout(widgetBase[3]);
    
    bottoneSfoglia* btnSfoglia = new bottoneSfoglia(campiBase[3]);

    layoutCopertina->setContentsMargins(0,0,0,0);
    layoutCopertina->setSpacing(0);
    layoutCopertina->addWidget(lableCopertina,0,Qt::AlignRight);
    layoutCopertina->addWidget(campiBase[3],0, Qt::AlignLeft);
    layoutCopertina->addWidget(btnSfoglia, 0, Qt::AlignLeft);
}

void createMediaVisitor::visit(libro* newLibro)
{
    QWidget *widgetCreazione = new QWidget();

    QVBoxLayout *layout = new QVBoxLayout(widgetCreazione);    
    layout->setAlignment(Qt::AlignCenter);

    QWidget *widgetsBase[4];
    QLineEdit *campiBase[4];
    creaSottoOggettoMedia(widgetsBase, campiBase);
    
    //---------- NUMERO PAGINE ----------
    QLabel *lableNumPagine = new QLabel("N° Pagine: ");
    lableNumPagine->setFont(QFont("Mono",14));
    lableNumPagine->setFixedSize(120,30);

    QLineEdit *numPagine = new QLineEdit();
    numPagine->setFont(QFont("Mono",14));
    numPagine->setFixedSize(200,30);

    QWidget *widgetNumPagine = new QWidget();

    QHBoxLayout *layoutNumPagine = new QHBoxLayout(widgetNumPagine);
    layoutNumPagine->setContentsMargins(0,0,0,0);
    layoutNumPagine->setSpacing(0);
    layoutNumPagine->addWidget(lableNumPagine,0,Qt::AlignRight);
    layoutNumPagine->addWidget(numPagine,0, Qt::AlignLeft);

    //---------- ISBN ----------
    QLabel *lableIsbn = new QLabel("ISBN: ");
    lableIsbn->setFont(QFont("Mono",14));
    lableIsbn->setFixedSize(120,30);

    QLineEdit *isbn = new QLineEdit();
    isbn->setFont(QFont("Mono",14));
    isbn->setFixedSize(200,30);

    QWidget *widgetIsbn = new QWidget();

    QHBoxLayout *layoutIsbn = new QHBoxLayout(widgetIsbn);
    layoutIsbn->setContentsMargins(0,0,0,0);
    layoutIsbn->setSpacing(0);
    layoutIsbn->addWidget(lableIsbn,0,Qt::AlignRight);
    layoutIsbn->addWidget(isbn,0, Qt::AlignLeft);

    //---------- GENERE ----------
    QLabel *lableGenere = new QLabel("Genere: ");
    lableGenere->setFont(QFont("Mono",14));
    lableGenere->setFixedSize(120,30);

    QLineEdit *genere = new QLineEdit();
    genere->setFont(QFont("Mono",14));
    genere->setFixedSize(200,30);

    QWidget *widgetGenere = new QWidget();

    QHBoxLayout *layoutGenere = new QHBoxLayout(widgetGenere);
    layoutGenere->setContentsMargins(0,0,0,0);
    layoutGenere->setSpacing(0);
    layoutGenere->addWidget(lableGenere,0,Qt::AlignRight);
    layoutGenere->addWidget(genere,0, Qt::AlignLeft);

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
    QPushButton *btnSalva = new QPushButton("SALVA");
    btnSalva->setFixedSize(200,50);
    btnSalva->setFont(QFont("Mono",15));
    layoutPulsanti->addWidget(btnSalva,0, Qt::AlignRight);

 

    //---------------------------------------------------
    layout->addWidget(widgetsBase[0]);
    layout->addWidget(widgetsBase[1]);
    layout->addWidget(widgetsBase[2]);
    layout->addWidget(widgetNumPagine);
    layout->addWidget(widgetIsbn);
    layout->addWidget(widgetGenere);
    layout->addWidget(widgetsBase[3]);
    layout->addWidget(widgetPulsanti);

    layoutEsterno->addWidget(widgetCreazione);


}

void createMediaVisitor::visit(canzone* newCanzone)
{

}

void createMediaVisitor::visit(album* newAlbum)
{

}

void createMediaVisitor::confermaSalvataggio()
{

}

void createMediaVisitor::annullaSalvataggio()
{
    qDebug()<<"ds";
    windowEsterna->reloadMediaVisibili();
}























