#include "createMediaVisitor.h"
#include "bottoneSalva.h"
#include "bottoneSfoglia.h"

#include <QWidget>
#include <QLabel>
#include <QFileDialog>
#include <QPushButton>
createMediaVisitor::createMediaVisitor(mainWindow* m, QGridLayout* l, mediaManager* man) : 
    windowEsterna(m), layoutEsterno(l), managerEsterno(man){}

void createMediaVisitor::creaSottoOggettoMedia(QWidget **widgetBase, QMap<QString,QLineEdit*>*campiBase )
{
    //---------- TITOLO ----------
    QLabel *lableTitolo = new QLabel("Titolo: ");
    lableTitolo->setFont(QFont("Mono",14));
    lableTitolo->setFixedSize(120,30);

    campiBase->insert("titolo",new QLineEdit());
    (*campiBase)["titolo"]->setFont(QFont("Mono",14));
    (*campiBase)["titolo"]->setFixedSize(200,30);

    widgetBase[0] = new QWidget();

    QHBoxLayout *layoutTitolo = new QHBoxLayout(widgetBase[0]);
    layoutTitolo->setContentsMargins(0,0,0,0);
    layoutTitolo->setSpacing(0);
    layoutTitolo->addWidget(lableTitolo,0,Qt::AlignRight);
    layoutTitolo->addWidget((*campiBase)["titolo"],0, Qt::AlignLeft);

    //---------- AUTORE ----------
    QLabel *lableAutore = new QLabel("Autore: ");
    lableAutore->setFont(QFont("Mono",14));
    lableAutore->setFixedSize(120,30);

    campiBase->insert("autore",new QLineEdit());
    (*campiBase)["autore"]->setFont(QFont("Mono",14));
    (*campiBase)["autore"]->setFixedSize(200,30);

    widgetBase[1] = new QWidget();

    QHBoxLayout *layoutAutore = new QHBoxLayout(widgetBase[1]);
    layoutAutore->setContentsMargins(0,0,0,0);
    layoutAutore->setSpacing(0);
    layoutAutore->addWidget(lableAutore,0,Qt::AlignRight);
    layoutAutore->addWidget((*campiBase)["autore"],0, Qt::AlignLeft);

    //---------- ANNO ----------
    QLabel *lableAnno = new QLabel("Anno: ");
    lableAnno->setFont(QFont("Mono",14));
    lableAnno->setFixedSize(120,30);

    campiBase->insert("anno",new QLineEdit());
    (*campiBase)["anno"]->setFont(QFont("Mono",14));
    (*campiBase)["anno"]->setFixedSize(200,30);

    widgetBase[2] = new QWidget();

    QHBoxLayout *layoutAnno = new QHBoxLayout(widgetBase[2]);
    layoutAnno->setContentsMargins(0,0,0,0);
    layoutAnno->setSpacing(0);
    layoutAnno->addWidget(lableAnno,0,Qt::AlignRight);
    layoutAnno->addWidget((*campiBase)["anno"],0, Qt::AlignLeft);

    //---------- COPERTINA ----------
    QLabel *lableCopertina = new QLabel("Copertina: ");
    lableCopertina->setFont(QFont("Mono",14));
    lableCopertina->setFixedSize(120,30);

    campiBase->insert("copertina",new QLineEdit());
    (*campiBase)["copertina"]->setFont(QFont("Mono",14));
    (*campiBase)["copertina"]->setFixedSize(200,30);

    widgetBase[3] = new QWidget();

    QHBoxLayout *layoutCopertina = new QHBoxLayout(widgetBase[3]);
    
    bottoneSfoglia* btnSfoglia = new bottoneSfoglia((*campiBase)["copertina"]);

    layoutCopertina->setContentsMargins(0,0,0,0);
    layoutCopertina->setSpacing(0);
    layoutCopertina->addWidget(lableCopertina,0,Qt::AlignRight);
    layoutCopertina->addWidget((*campiBase)["copertina"],0, Qt::AlignLeft);
    layoutCopertina->addWidget(btnSfoglia, 0, Qt::AlignLeft);
}

void createMediaVisitor::visit(libro* newLibro)
{
    QWidget *widgetCreazione = new QWidget();

    QVBoxLayout *layout = new QVBoxLayout(widgetCreazione);    
    layout->setAlignment(Qt::AlignCenter);

    QWidget *widgetsBase[4];
    QMap<QString, QLineEdit*> campi;
    creaSottoOggettoMedia(widgetsBase, &campi);
    
    //---------- NUMERO PAGINE ----------
    QLabel *lableNumPagine = new QLabel("N° Pagine: ");
    lableNumPagine->setFont(QFont("Mono",14));
    lableNumPagine->setFixedSize(120,30);

    campi.insert("numeroPagine",new QLineEdit());
    campi["numeroPagine"]->setFont(QFont("Mono",14));
    campi["numeroPagine"]->setFixedSize(200,30);

    QWidget *widgetNumPagine = new QWidget();

    QHBoxLayout *layoutNumPagine = new QHBoxLayout(widgetNumPagine);
    layoutNumPagine->setContentsMargins(0,0,0,0);
    layoutNumPagine->setSpacing(0);
    layoutNumPagine->addWidget(lableNumPagine,0,Qt::AlignRight);
    layoutNumPagine->addWidget(campi["numeroPagine"],0, Qt::AlignLeft);

    //---------- ISBN ----------
    QLabel *lableIsbn = new QLabel("ISBN: ");
    lableIsbn->setFont(QFont("Mono",14));
    lableIsbn->setFixedSize(120,30);

    campi.insert("isbn",new QLineEdit());
    campi["isbn"]->setFont(QFont("Mono",14));
    campi["isbn"]->setFixedSize(200,30);

    QWidget *widgetIsbn = new QWidget();

    QHBoxLayout *layoutIsbn = new QHBoxLayout(widgetIsbn);
    layoutIsbn->setContentsMargins(0,0,0,0);
    layoutIsbn->setSpacing(0);
    layoutIsbn->addWidget(lableIsbn,0,Qt::AlignRight);
    layoutIsbn->addWidget(campi["isbn"],0, Qt::AlignLeft);

    //---------- GENERE ----------
    QLabel *lableGenere = new QLabel("Editore: ");
    lableGenere->setFont(QFont("Mono",14));
    lableGenere->setFixedSize(120,30);

    campi.insert("editore",new QLineEdit());
    campi["editore"]->setFont(QFont("Mono",14));
    campi["editore"]->setFixedSize(200,30);

    QWidget *widgetGenere = new QWidget();

    QHBoxLayout *layoutGenere = new QHBoxLayout(widgetGenere);
    layoutGenere->setContentsMargins(0,0,0,0);
    layoutGenere->setSpacing(0);
    layoutGenere->addWidget(lableGenere,0,Qt::AlignRight);
    layoutGenere->addWidget(campi["editore"],0, Qt::AlignLeft);

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
    bottoneSalva *btnSalva = new bottoneSalva(managerEsterno, campi, newLibro, windowEsterna);

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























