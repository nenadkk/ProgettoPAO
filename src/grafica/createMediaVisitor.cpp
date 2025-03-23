#include "createMediaVisitor.h"
#include "widgetCreazione.h"

#include <QWidget>
#include <QLabel>
#include <QFileDialog>
#include <QPushButton>
#include <QIntValidator>

createMediaVisitor::createMediaVisitor(mainWindow* m, QGridLayout* l, mediaManager* man) : 
    windowEsterna(m), layoutEsterno(l), managerEsterno(man){}

void createMediaVisitor::creaSottoOggettoMedia(QWidget **widgetBase, widgetCreazione* mainWidget )
{
    //---------- TITOLO ----------
    widgetBase[0] = new QWidget();

    QLabel *lableTitolo = new QLabel("Titolo: ");
    lableTitolo->setFont(QFont("Mono",14));
    lableTitolo->setFixedSize(120,30);

    mainWidget->insertLineEdit("titolo",new QLineEdit());
    (*mainWidget)["titolo"]->setFont(QFont("Mono",14));
    (*mainWidget)["titolo"]->setFixedSize(200,30);

    QHBoxLayout *layoutTitolo = new QHBoxLayout(widgetBase[0]);
    layoutTitolo->setContentsMargins(0,0,0,0);
    layoutTitolo->setSpacing(0);
    layoutTitolo->addWidget(lableTitolo,0,Qt::AlignRight);
    layoutTitolo->addWidget((*mainWidget)["titolo"],0, Qt::AlignLeft);

    //---------- AUTORE ----------
    widgetBase[1] = new QWidget();
   
    QLabel *lableAutore = new QLabel("Autore: ");
    lableAutore->setFont(QFont("Mono",14));
    lableAutore->setFixedSize(120,30);

    mainWidget->insertLineEdit("autore",new QLineEdit());
    (*mainWidget)["autore"]->setFont(QFont("Mono",14));
    (*mainWidget)["autore"]->setFixedSize(200,30);

    QHBoxLayout *layoutAutore = new QHBoxLayout(widgetBase[1]);
    layoutAutore->setContentsMargins(0,0,0,0);
    layoutAutore->setSpacing(0);
    layoutAutore->addWidget(lableAutore,0,Qt::AlignRight);
    layoutAutore->addWidget((*mainWidget)["autore"],0, Qt::AlignLeft);

    //---------- ANNO ----------
    widgetBase[2] = new QWidget();

    QLabel *lableAnno = new QLabel("Anno: ");
    lableAnno->setFont(QFont("Mono",14));
    lableAnno->setFixedSize(120,30);

    mainWidget->insertLineEdit("anno",new QLineEdit());
    (*mainWidget)["anno"]->setFont(QFont("Mono",14));
    (*mainWidget)["anno"]->setFixedSize(200,30);
    QIntValidator *validatorAnno = new QIntValidator((*mainWidget)["anno"]);
    (*mainWidget)["anno"]->setValidator(validatorAnno);

    QHBoxLayout *layoutAnno = new QHBoxLayout(widgetBase[2]);
    layoutAnno->setContentsMargins(0,0,0,0);
    layoutAnno->setSpacing(0);
    layoutAnno->addWidget(lableAnno,0,Qt::AlignRight);
    layoutAnno->addWidget((*mainWidget)["anno"],0, Qt::AlignLeft);

    //---------- COPERTINA ----------
    widgetBase[3] = new QWidget();
 
    QLabel *lableCopertina = new QLabel("Copertina: ");
    lableCopertina->setFont(QFont("Mono",14));
    lableCopertina->setFixedSize(120,30);

    mainWidget->insertLineEdit("copertina",new QLineEdit());
    (*mainWidget)["copertina"]->setFont(QFont("Mono",14));
    (*mainWidget)["copertina"]->setFixedSize(200,30);

    QHBoxLayout *layoutCopertina = new QHBoxLayout(widgetBase[3]);
    
    QPushButton* btnSfoglia = new QPushButton("Sfoglia");
    btnSfoglia->setFixedSize(120,30);
    btnSfoglia->setFont(QFont("Mono",15));
    QObject::connect(btnSfoglia, &QPushButton::clicked, mainWidget, &widgetCreazione::browseImage);

    layoutCopertina->setContentsMargins(0,0,0,0);
    layoutCopertina->setSpacing(0);
    layoutCopertina->addWidget(lableCopertina,0,Qt::AlignRight);
    layoutCopertina->addWidget((*mainWidget)["copertina"],0, Qt::AlignLeft);
    layoutCopertina->addWidget(btnSfoglia, 0, Qt::AlignLeft);
}

void createMediaVisitor::visit(libro* newLibro)
{
    widgetCreazione *mainWidget = new widgetCreazione(managerEsterno, newLibro, windowEsterna);

    QVBoxLayout *layout = new QVBoxLayout(mainWidget);    
    layout->setAlignment(Qt::AlignCenter);

    QWidget *widgetsBase[4];

    creaSottoOggettoMedia(widgetsBase, mainWidget);
    
    //---------- NUMERO PAGINE ----------
    QWidget *widgetNumPagine = new QWidget();
 
    QLabel *lableNumPagine = new QLabel("N° Pagine: ");
    lableNumPagine->setFont(QFont("Mono",14));
    lableNumPagine->setFixedSize(120,30);

    mainWidget->insertLineEdit("numeroPagine",new QLineEdit());
    (*mainWidget)["numeroPagine"]->setFont(QFont("Mono",14));
    (*mainWidget)["numeroPagine"]->setFixedSize(200,30);
    QIntValidator *validatorNumPag = new QIntValidator((*mainWidget)["numeroPagine"]);
    (*mainWidget)["numeroPagine"]->setValidator(validatorNumPag);

    QHBoxLayout *layoutNumPagine = new QHBoxLayout(widgetNumPagine);
    layoutNumPagine->setContentsMargins(0,0,0,0);
    layoutNumPagine->setSpacing(0);
    layoutNumPagine->addWidget(lableNumPagine,0,Qt::AlignRight);
    layoutNumPagine->addWidget((*mainWidget)["numeroPagine"],0, Qt::AlignLeft);

    //---------- ISBN ----------
    QWidget *widgetIsbn = new QWidget();

    QLabel *lableIsbn = new QLabel("ISBN: ");
    lableIsbn->setFont(QFont("Mono",14));
    lableIsbn->setFixedSize(120,30);

    mainWidget->insertLineEdit("isbn",new QLineEdit());
    (*mainWidget)["isbn"]->setFont(QFont("Mono",14));
    (*mainWidget)["isbn"]->setFixedSize(200,30);
    QIntValidator *validatorIsbn = new QIntValidator(0,INT_MAX,(*mainWidget)["isbn"]);
    (*mainWidget)["isbn"]->setValidator(validatorIsbn);

    QHBoxLayout *layoutIsbn = new QHBoxLayout(widgetIsbn);
    layoutIsbn->setContentsMargins(0,0,0,0);
    layoutIsbn->setSpacing(0);
    layoutIsbn->addWidget(lableIsbn,0,Qt::AlignRight);
    layoutIsbn->addWidget((*mainWidget)["isbn"],0, Qt::AlignLeft);

    //---------- GENERE ----------
    QWidget *widgetGenere = new QWidget();

    QLabel *lableGenere = new QLabel("Editore: ");
    lableGenere->setFont(QFont("Mono",14));
    lableGenere->setFixedSize(120,30);

    mainWidget->insertLineEdit("editore",new QLineEdit());
    (*mainWidget)["editore"]->setFont(QFont("Mono",14));
    (*mainWidget)["editore"]->setFixedSize(200,30);


    QHBoxLayout *layoutGenere = new QHBoxLayout(widgetGenere);
    layoutGenere->setContentsMargins(0,0,0,0);
    layoutGenere->setSpacing(0);
    layoutGenere->addWidget(lableGenere,0,Qt::AlignRight);
    layoutGenere->addWidget((*mainWidget)["editore"],0, Qt::AlignLeft);

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
    QObject::connect(btnSalva, &QPushButton::clicked, mainWidget, &widgetCreazione::crea);
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

    layoutEsterno->addWidget(mainWidget);


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
    windowEsterna->reloadMediaVisibili();
}








