#include "editorLibro.h"
#include <QLabel>

editorLibro::editorLibro(mediaManager* man, mainWindow* mw, media* obj) : 
    widgetEditorMedia(man, mw, obj)
{
    QVBoxLayout *layout = new QVBoxLayout();    

    layout->setAlignment(Qt::AlignCenter);

    //---------- NUMERO PAGINE ----------
    QWidget *widgetNumPagine = new QWidget();
    widgetNumPagine->setFixedWidth(350);
 
    QLabel *lableNumPagine = new QLabel("N° Pagine: ");
    lableNumPagine->setFont(QFont("Mono",14));
    lableNumPagine->setFixedSize(120,30);

    this->insertLineEdit("numeroPagine",new QLineEdit());
    (*this)["numeroPagine"]->setFont(QFont("Mono",14));
    (*this)["numeroPagine"]->setFixedSize(200,30);
    QIntValidator *validatorNumPag = new QIntValidator((*this)["numeroPagine"]);
    (*this)["numeroPagine"]->setValidator(validatorNumPag);

    if(object)
        (*this)["numeroPagine"]->setText(QString::number(dynamic_cast<libro*>(object)->getNumPagine()));

    QHBoxLayout *layoutNumPagine = new QHBoxLayout(widgetNumPagine);
    layoutNumPagine->setContentsMargins(0,0,0,0);
    layoutNumPagine->setSpacing(0);
    layoutNumPagine->addWidget(lableNumPagine,0,Qt::AlignRight);
    layoutNumPagine->addWidget((*this)["numeroPagine"],0, Qt::AlignLeft);

    //---------- ISBN ----------
    QWidget *widgetIsbn = new QWidget();
    widgetIsbn->setFixedWidth(350);

    QLabel *lableIsbn = new QLabel("ISBN: ");
    lableIsbn->setFont(QFont("Mono",14));
    lableIsbn->setFixedSize(120,30);

    this->insertLineEdit("isbn",new QLineEdit());
    (*this)["isbn"]->setFont(QFont("Mono",14));
    (*this)["isbn"]->setFixedSize(200,30);
    QIntValidator *validatorIsbn = new QIntValidator(0,INT_MAX,(*this)["isbn"]);
    (*this)["isbn"]->setValidator(validatorIsbn);

    if(object)
        (*this)["isbn"]->setText(QString::number(dynamic_cast<libro*>(object)->getIsbn()));

    QHBoxLayout *layoutIsbn = new QHBoxLayout(widgetIsbn);
    layoutIsbn->setContentsMargins(0,0,0,0);
    layoutIsbn->setSpacing(0);
    layoutIsbn->addWidget(lableIsbn,0,Qt::AlignRight);
    layoutIsbn->addWidget((*this)["isbn"],0, Qt::AlignLeft);

    //---------- EDITORE ----------
    QWidget *widgetEditore = new QWidget();
    widgetEditore->setFixedWidth(350);

    QLabel *lableEditore = new QLabel("Editore: ");
    lableEditore->setFont(QFont("Mono",14));
    lableEditore->setFixedSize(120,30);

    this->insertLineEdit("editore",new QLineEdit());
    (*this)["editore"]->setFont(QFont("Mono",14));
    (*this)["editore"]->setFixedSize(200,30);

    if(object)
        (*this)["editore"]->setText(QString::fromStdString(dynamic_cast<libro*>(object)->getEditore()));


    QHBoxLayout *layoutGenere = new QHBoxLayout(widgetEditore);
    layoutGenere->setContentsMargins(0,0,0,0);
    layoutGenere->setSpacing(0);
    layoutGenere->addWidget(lableEditore,0,Qt::AlignRight);
    layoutGenere->addWidget((*this)["editore"],0, Qt::AlignLeft);

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

    if(object)
        QObject::connect(btnSalva, &QPushButton::clicked, this, &editorLibro::modifica);
    else
        QObject::connect(btnSalva, &QPushButton::clicked, this, &editorLibro::crea);

    layoutPulsanti->addWidget(btnSalva,0, Qt::AlignRight);

    //---------------------------------------------------
    
    layout->addWidget(widgetBase[0]);
    layout->addWidget(widgetBase[1]);
    layout->addWidget(widgetBase[2]);
    layout->addWidget(widgetNumPagine);
    layout->addWidget(widgetIsbn);
    layout->addWidget(widgetEditore);
    layout->addWidget(widgetBase[3]);
    layout->addWidget(widgetPulsanti);

    this->setLayout(layout);

}

void editorLibro::crea()
{
    if(validaInput())
    {
        copiaImmagine();
        manager->addMedia(new libro(attributi["titolo"]->text().toStdString(),
                    attributi["autore"]->text().toStdString(),
                    attributi["anno"]->text().toInt(),
                    attributi["copertina"]->text().toStdString(),
                    manager->trovaIdLibero(),
                    attributi["numeroPagine"]->text().toInt(),
                    attributi["isbn"]->text().toInt(),
                    attributi["editore"]->text().toStdString()));

        windowEsterna->reloadMediaVisibili();
    }

}

void editorLibro::modifica()
{
    object->setTitolo(attributi["titolo"]->text().toStdString());
    object->setAutore(attributi["autore"]->text().toStdString());
    object->setAnno(attributi["anno"]->text().toInt());
    
    string copertina=attributi["copertina"]->text().toStdString();
    if(copertina!=object->getCopertina())
        copiaImmagine();
    object->setCopertina(copertina);

    dynamic_cast<libro*>(object)->setNumPagine(attributi["numeroPagine"]->text().toInt());
    dynamic_cast<libro*>(object)->setIsbn(attributi["isbn"]->text().toInt());
    dynamic_cast<libro*>(object)->setEditore(attributi["editore"]->text().toStdString());

    manager->save();
    windowEsterna->reloadMediaVisibili();
}
