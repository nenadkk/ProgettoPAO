#include <QFileInfo>
#include <QMessageBox>
#include <QFileDialog>
#include <QLabel>
#include "widgetCreazione.h"
#include "qglobal.h"
#include "widgetCreazioneVisitor.h"

widgetCreazione::widgetCreazione(media* tipo, mediaManager* man, QWidget* parent, QListWidget* tracks) : 
    QWidget(parent), manager(man), tipo(tipo), trackList(tracks)
{
    windowEsterna = dynamic_cast<mainWindow*>(parent);
    widgetCreazioneVisitor vis(this);
    tipo->accept(&vis);
}

QLineEdit*& widgetCreazione::operator[](const QString& key) 
{
    return attributi[key];
}

void widgetCreazione::insertLineEdit(QString str,QLineEdit* n)
{
    attributi.insert(str,n);
}

void widgetCreazione::crea()
{
    if(validaInput())
    {
        if(dynamic_cast<libro*>(tipo))
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
        }
        else if(dynamic_cast<canzone*>(tipo))
        {
            copiaImmagine();
            int durata = (attributi["durataMin"]->text().toInt())*60+(attributi["durataSec"]->text().toInt());
            manager->addMedia(new canzone(attributi["titolo"]->text().toStdString(),
                                        attributi["autore"]->text().toStdString(),
                                        attributi["anno"]->text().toInt(),
                                        attributi["copertina"]->text().toStdString(),
                                        manager->trovaIdLibero(),
                                        durata,
                                        attributi["genere"]->text().toStdString()));
        }
        else if (dynamic_cast<album*>(tipo)) 
        {
            copiaImmagine();
            //creazione album
            album *newAlbum = new album(attributi["titolo"]->text().toStdString(),
                                        attributi["autore"]->text().toStdString(),
                                        attributi["anno"]->text().toInt(),
                                        attributi["copertina"]->text().toStdString(),
                                        manager->trovaIdLibero());

            //aggiunta canzoni ad album
            for(int i=0; i<trackList->count();++i)
            {
                QListWidgetItem *item = trackList->item(i);

                if (item->checkState() == Qt::Checked) 
                {
                    int trackID = item->data(Qt::UserRole).toInt();
                    media* c = manager->searchById(trackID);
                    if(c && dynamic_cast<canzone*>(c))
                    {
                        newAlbum->addCanzone(dynamic_cast<canzone*>(c));
                    }
                }
            }

            manager->addMedia(newAlbum);
        }
        delete tipo;
        windowEsterna->reloadMediaVisibili();
    }
}

bool widgetCreazione::validaInput()
{
    foreach(auto val, attributi.values())
    {
        if(val->text().isEmpty())
        {
            QMessageBox::warning(this, "Validazione", "Dati non validi o nulli. Compilare ogni campo con valori significativi.");
            return false;
        }
    }
    return true;
}

void widgetCreazione::copiaImmagine() 
{
    QFileInfo infoImmagine(attributi["copertina"]->text());
    if (!infoImmagine.exists()) {
        qDebug() << "L'immagine sorgente non esiste.";
        return;
    }

    QString nomeFile = infoImmagine.fileName();
    QString percorsoDestinazione = "./immagini/" + nomeFile;
    QFileInfo infoDestinazione(percorsoDestinazione);

    if (!infoDestinazione.exists()) 
    {
        if (!QFile::copy(attributi["copertina"]->text(), percorsoDestinazione)) 
        {
            qDebug() << "Errore durante la copia dell'immagine.";
            return;
        }
        attributi["copertina"]->setText(percorsoDestinazione);
    }


}

void widgetCreazione::browseImage()
{
    if(attributi["copertina"])
    {
        QString filePath = QFileDialog::getOpenFileName(this, "Seleziona un'immagine", "", "Immagini (*.png *.jpg *.jpeg *.bmp *.gif)");
        if (!filePath.isEmpty() && isImageFile(filePath))    
            attributi["copertina"]->setText(filePath);       
    }
}

bool widgetCreazione::isImageFile(const QString &filePath) const 
{
    QFileInfo fileInfo(filePath);
    QString ext = fileInfo.suffix().toLower();
    return (ext == "png" || ext == "jpg" || ext == "jpeg" || ext == "jpeg" || ext == "bmp" || ext == "gif");
}

void widgetCreazione::creaSottoOggettoMedia(QWidget **widgetBase, widgetCreazione* mainWidget )
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

void widgetCreazione::buildWidget(libro* newLibro)
{
    QVBoxLayout *layout = new QVBoxLayout();    

    layout->setAlignment(Qt::AlignCenter);

    QWidget *widgetsBase[4];

    creaSottoOggettoMedia(widgetsBase, this);
    
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
    QObject::connect(btnSalva, &QPushButton::clicked, this, &widgetCreazione::crea);
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

    this->setLayout(layout);
}



void widgetCreazione::buildWidget(canzone* newCanzone)
{
    QVBoxLayout *layout = new QVBoxLayout();    

    layout->setAlignment(Qt::AlignCenter);

    QWidget *widgetsBase[4];

    creaSottoOggettoMedia(widgetsBase, this);
    
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
    QObject::connect(btnSalva, &QPushButton::clicked, this, &widgetCreazione::crea);
    layoutPulsanti->addWidget(btnSalva,0, Qt::AlignRight);

    //---------------------------------------------------
    layout->addWidget(widgetsBase[0]);
    layout->addWidget(widgetsBase[1]);
    layout->addWidget(widgetsBase[2]);
    layout->addWidget(widgetDurata);
    layout->addWidget(widgetGenere);
    layout->addWidget(widgetsBase[3]);
    layout->addWidget(widgetPulsanti);

    this->setLayout(layout);
}

void widgetCreazione::buildWidget(album* newAlbum)
{
            //---------- PARTE SINISTRA ----------
    trackList = new QListWidget();

    QVBoxLayout *layoutSinistra = new QVBoxLayout();    
    layoutSinistra->setAlignment(Qt::AlignCenter);

    QWidget *widgetsBase[4];

    creaSottoOggettoMedia(widgetsBase, this);
    
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
    QObject::connect(btnSalva, &QPushButton::clicked, this, &widgetCreazione::crea);
    layoutSinistraPulsanti->addWidget(btnSalva,0, Qt::AlignRight);

    //---------------------------------------------------
    layoutSinistra->addWidget(widgetsBase[0]);
    layoutSinistra->addWidget(widgetsBase[1]);
    layoutSinistra->addWidget(widgetsBase[2]);
    layoutSinistra->addWidget(widgetsBase[3]);
    layoutSinistra->addWidget(widgetPulsanti);


            //---------- PARTE DESTRA ----------
            
    for (const auto m : manager->filtroSoloCanzoni()) 
    {
        canzone *c = dynamic_cast<canzone*>(m);

        QString str = QString::fromStdString(c->getTitolo()) + "   " + toQString(c->getAutore()+ "   "  );
        str +=QString::number((c->getDurata())/60 ) + ":" + QString::number((c->getDurata())%60);
        QListWidgetItem *item = new QListWidgetItem(str, trackList);
        item->setData(Qt::UserRole, c->getId()); // Assegna l'ID all'elemento

        
        item->setFont(QFont("Mono",20));
        item->setCheckState(Qt::Unchecked);
    }

    trackList->setStyleSheet(
            "QListWidget::item {"
            "    border-radius: 5px;"
            "    margin: 5px;"
            "    padding: 5px;"
            "    background-color: #323232;"
            "}"
            "QListWidget::item:selected {background-color: #595959;}"
            );

    
    QHBoxLayout *layout = new QHBoxLayout();    
    layout->addLayout(layoutSinistra);
    layout->addWidget(trackList);

    this->setLayout(layout);
}








