#include "createMediaVisitor.h"
#include "widgetCreazione.h"

#include <QWidget>
#include <QLabel>
#include <QFileDialog>
#include <QPushButton>
#include <QIntValidator>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListWidget>
#include <QMessageBox>

createMediaVisitor::createMediaVisitor(mainWindow* m, QGridLayout* l, mediaManager* man) : 
    windowEsterna(m), layoutEsterno(l), managerEsterno(man){}

void createMediaVisitor::creaSottoOggettoMedia(QWidget **widgetBase, widgetCreazione* mainWidget )
{
    //---------- TITOLO ----------
    widgetBase[0] = new QWidget();
    widgetBase[0]->setFixedWidth(350);

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
    widgetBase[1]->setFixedWidth(350);
   
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
    widgetBase[2]->setFixedWidth(350);

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
    widgetNumPagine->setFixedWidth(350);
 
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
    widgetIsbn->setFixedWidth(350);

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

    //---------- EDITORE ----------
    QWidget *widgetEditore = new QWidget();
    widgetEditore->setFixedWidth(350);

    QLabel *lableEditore = new QLabel("Editore: ");
    lableEditore->setFont(QFont("Mono",14));
    lableEditore->setFixedSize(120,30);

    mainWidget->insertLineEdit("editore",new QLineEdit());
    (*mainWidget)["editore"]->setFont(QFont("Mono",14));
    (*mainWidget)["editore"]->setFixedSize(200,30);


    QHBoxLayout *layoutGenere = new QHBoxLayout(widgetEditore);
    layoutGenere->setContentsMargins(0,0,0,0);
    layoutGenere->setSpacing(0);
    layoutGenere->addWidget(lableEditore,0,Qt::AlignRight);
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
    layout->addWidget(widgetEditore);
    layout->addWidget(widgetsBase[3]);
    layout->addWidget(widgetPulsanti);

    layoutEsterno->addWidget(mainWidget);
}

void createMediaVisitor::visit(canzone* newCanzone)
{
    widgetCreazione *mainWidget = new widgetCreazione(managerEsterno, newCanzone, windowEsterna);

    QVBoxLayout *layout = new QVBoxLayout(mainWidget);    
    layout->setAlignment(Qt::AlignCenter);

    QWidget *widgetsBase[4];

    creaSottoOggettoMedia(widgetsBase, mainWidget);
    
    //---------- DURATA ----------
    QWidget *widgetDurata = new QWidget();
    widgetDurata->setFixedWidth(350);
 
    QLabel *lableDurata = new QLabel("Durata: ");
    lableDurata->setFont(QFont("Mono",14));
    lableDurata->setFixedSize(120,30);

    mainWidget->insertLineEdit("durataMin",new QLineEdit());
    (*mainWidget)["durataMin"]->setFont(QFont("Mono",14));
    (*mainWidget)["durataMin"]->setFixedSize(40,30);
    QIntValidator *validatorDurataMin = new QIntValidator((*mainWidget)["durataMin"]);
    (*mainWidget)["durataMin"]->setValidator(validatorDurataMin);

    QLabel *lableMin = new QLabel("min");
    lableMin->setFont(QFont("Mono",14));
    
    mainWidget->insertLineEdit("durataSec",new QLineEdit());
    (*mainWidget)["durataSec"]->setFont(QFont("Mono",14));
    (*mainWidget)["durataSec"]->setFixedSize(40,30);
    QIntValidator *validatorDurataSec = new QIntValidator((*mainWidget)["durataSec"]);
    (*mainWidget)["durataSec"]->setValidator(validatorDurataSec);

    QLabel *lableSec = new QLabel("sec");
    lableSec->setFont(QFont("Mono",14));

    QHBoxLayout *layoutDurata = new QHBoxLayout(widgetDurata);
    layoutDurata->setContentsMargins(0,0,0,0);
    layoutDurata->setSpacing(0);
    layoutDurata->addWidget(lableDurata,0,Qt::AlignLeft);
    layoutDurata->addWidget((*mainWidget)["durataMin"],0, Qt::AlignRight);
    layoutDurata->addWidget(lableMin,0,Qt::AlignRight);
    layoutDurata->addWidget((*mainWidget)["durataSec"],0, Qt::AlignRight);
    layoutDurata->addWidget(lableSec,0,Qt::AlignRight);

    //---------- GENERE ----------
    QWidget *widgetGenere = new QWidget();
    widgetGenere->setFixedWidth(350);

    QLabel *lableGenere = new QLabel("Genere: ");
    lableGenere->setFont(QFont("Mono",14));
    lableGenere->setFixedSize(120,30);

    mainWidget->insertLineEdit("genere",new QLineEdit());
    (*mainWidget)["genere"]->setFont(QFont("Mono",14));
    (*mainWidget)["genere"]->setFixedSize(200,30);


    QHBoxLayout *layoutGenere = new QHBoxLayout(widgetGenere);
    layoutGenere->setContentsMargins(0,0,0,0);
    layoutGenere->setSpacing(0);
    layoutGenere->addWidget(lableGenere,0,Qt::AlignRight);
    layoutGenere->addWidget((*mainWidget)["genere"],0, Qt::AlignLeft);

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
    layout->addWidget(widgetDurata);
    layout->addWidget(widgetGenere);
    layout->addWidget(widgetsBase[3]);
    layout->addWidget(widgetPulsanti);

    layoutEsterno->addWidget(mainWidget);
}

void createMediaVisitor::visit(album* newAlbum)
{
            //---------- PARTE SINISTRA ----------
    QListWidget *listWidget = new QListWidget();
    widgetCreazione *mainWidget = new widgetCreazione(managerEsterno, newAlbum, windowEsterna, listWidget);

    QVBoxLayout *layoutSinistra = new QVBoxLayout(mainWidget);    
    layoutSinistra->setAlignment(Qt::AlignCenter);

    QWidget *widgetsBase[4];

    creaSottoOggettoMedia(widgetsBase, mainWidget);
    
    //---------- PULSANTI ----------
    QWidget *widgetPulsanti = new QWidget();
    QHBoxLayout *layoutSinistraPulsanti = new QHBoxLayout(widgetPulsanti);

    //---------- PULSANTE ANNULLA ----------
    QPushButton *btnAnnulla = new QPushButton("ANNULLA",widgetPulsanti);
    btnAnnulla->setFixedSize(200,50);
    btnAnnulla->setFont(QFont("Mono",15));
    QObject::connect(btnAnnulla, &QPushButton::clicked, windowEsterna, &mainWindow::reloadMediaVisibili);
    layoutSinistraPulsanti->addWidget(btnAnnulla,0, Qt::AlignLeft);

    //---------- PULSANTE SALVA ----------
    QPushButton *btnSalva = new QPushButton("SALVA",widgetPulsanti);
    btnSalva->setFixedSize(200,50);
    btnSalva->setFont(QFont("Mono",15));
    QObject::connect(btnSalva, &QPushButton::clicked, mainWidget, &widgetCreazione::crea);
    layoutSinistraPulsanti->addWidget(btnSalva,0, Qt::AlignRight);

    //---------------------------------------------------
    layoutSinistra->addWidget(widgetsBase[0]);
    layoutSinistra->addWidget(widgetsBase[1]);
    layoutSinistra->addWidget(widgetsBase[2]);
    layoutSinistra->addWidget(widgetsBase[3]);
    layoutSinistra->addWidget(widgetPulsanti);


            //---------- PARTE DESTRA ----------
            
    for (const auto m : managerEsterno->filtroSoloCanzoni()) 
    {
        canzone *c = dynamic_cast<canzone*>(m);

        QString str = QString::fromStdString(c->getTitolo()) + "   " + toQString(c->getAutore()+ "   "  );
        str +=QString::number((c->getDurata())/60 ) + ":" + QString::number((c->getDurata())%60);
        QListWidgetItem *item = new QListWidgetItem(str, listWidget);
        item->setData(Qt::UserRole, c->getId()); // Assegna l'ID all'elemento

        
        item->setFont(QFont("Mono",20));
        item->setCheckState(Qt::Unchecked);
    }

    listWidget->setStyleSheet(
            "QListWidget::item {"
            "    border-radius: 5px;"
            "    margin: 5px;"
            "    padding: 5px;"
            "    background-color: #323232;"
            "}"
            "QListWidget::item:selected {background-color: #595959;}"
            );
    layoutEsterno->addWidget(mainWidget,0,0);
    layoutEsterno->addWidget(listWidget,0,1);

}
