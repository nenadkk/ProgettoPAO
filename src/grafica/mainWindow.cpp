#include "mainWindow.h"
#include <QApplication>
#include <QMainWindow>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QScrollArea>
#include <QListWidget>
#include <QLabel>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QUrl>
#include <QMimeData>
#include <QFileDialog>
#include <QDebug>

#include "showMediaVisitor.h"
#include "bottoneSfoglia.h"

mainWindow::mainWindow(QWidget* parent) : QMainWindow(parent)
{
    //Caricamento dati 
    LM.load();

    // Widget principale
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // Layout principale orizzontale
    QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);

    // Barra laterale sinistra con pulsanti
    QWidget *sideBar = new QWidget();
    QVBoxLayout *sideBarLayout = new QVBoxLayout(sideBar);

    QWidget *space = new QWidget();
    space->setFixedHeight(40);
    sideBarLayout->addWidget(space);

    QPushButton *pulsanteCrea = new QPushButton("Crea");
    pulsanteCrea->setFixedHeight(40);
    sideBarLayout->addWidget(pulsanteCrea);
    connect(pulsanteCrea, &QPushButton::clicked, this, &mainWindow::sceltaCreazione);

    sideBarLayout->addStretch();

    // Area centrale con barra di ricerca in alto
    QWidget *centralArea = new QWidget();
    QVBoxLayout *centralLayout = new QVBoxLayout(centralArea);

    QWidget *searchWidget = new QWidget();
    QHBoxLayout *searchLayout = new QHBoxLayout(searchWidget);

    searchBar = new QLineEdit();
    searchBar->setPlaceholderText("Cerca...");
    searchBar->setFixedHeight(35);
    searchBar->setFont(QFont("Mono",16));
    connect(searchBar, &QLineEdit::returnPressed, this, &mainWindow::ricerca);
    searchLayout->addWidget(searchBar);

    QPushButton *clearButton = new QPushButton("✖");
    clearButton->setFixedSize(30, 30);
    clearButton->setStyleSheet("font-size: 18px; color: #555;");
    connect(clearButton, &QPushButton::clicked, [=, this]() {
            searchBar->clear();
            this->reloadMediaVisibili();
            });

    searchLayout->addWidget(clearButton);
    centralLayout->addWidget(searchWidget);

    // Area di contenuto con scroll
    QScrollArea *scrollArea = new QScrollArea();
    QWidget *contentWidget = new QWidget();
    mediaVisibili = new QGridLayout(contentWidget);

    reloadMediaVisibili();




    //mediaVisibili->addStretch();
    contentWidget->setLayout(mediaVisibili);
    scrollArea->setWidget(contentWidget);
    scrollArea->setWidgetResizable(true);

    centralLayout->addWidget(scrollArea);

    // Aggiunta delle aree al layout principale
    sideBar->setFixedWidth(150);
    mainLayout->addWidget(sideBar);
    mainLayout->addWidget(centralArea);

    // Configurazione della finestra principale
    setWindowTitle("Interfaccia Qt");
    resize(1200, 800);
}

void mainWindow::ricerca()
{
    string daCercare = searchBar->text().toStdString();
    list<media*> query = LM.search(daCercare);

    svuotaMediaVisibili();

    if(!query.empty())
    {
        //Ripopola con i valori filtrati
        showMediaVisitor showvis(mediaVisibili, width());

        for (auto m : query) 
            m->accept(&showvis);
    }
}


void mainWindow::reloadMediaVisibili()
{
    svuotaMediaVisibili();

    //Ripopola
    showMediaVisitor showvis(mediaVisibili,width());

    for (int i=0;i<LM.size();i++) 
        LM[i]->accept(&showvis);
}

void mainWindow::resizeEvent(QResizeEvent* event)
{
    QWidget::resizeEvent(event);
    updateLayoutAtResize();
}

void mainWindow::updateLayoutAtResize()
{
}

void mainWindow::svuotaMediaVisibili()
{
    if (mediaVisibili != nullptr)
    {
        while (QLayoutItem *item = mediaVisibili->takeAt(0)) 
        {
            if (QWidget *widget = item->widget()) 
                widget->deleteLater();

            delete item;
        }
    }    
}

void mainWindow::sceltaCreazione()
{
    svuotaMediaVisibili(); 
    
    QWidget* sezioneCrea = new QWidget();
    sezioneCrea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QVBoxLayout* layout = new QVBoxLayout(sezioneCrea);

    QLabel *titoloSezione = new QLabel("SELEZIONA IL TIPO DI MEDIA DA CREARE");
    titoloSezione->setAlignment(Qt::AlignCenter);
    titoloSezione->setFont(QFont("Mono",18));
    layout->addWidget(titoloSezione);

    QWidget *pulsantiTipoMedia = new QWidget();
    QHBoxLayout *layoutPulsanti = new QHBoxLayout(pulsantiTipoMedia);

    QPushButton *creaLibro = new QPushButton("Libro");
    creaLibro->setFixedHeight(40);
    layout->addWidget(creaLibro);
    connect(creaLibro, &QPushButton::clicked, this, &mainWindow::creaLibro);
    layoutPulsanti->addWidget(creaLibro);

    QPushButton *creaCanzone = new QPushButton("Canzone");
    creaCanzone->setFixedHeight(40);
    layout->addWidget(creaCanzone);
    connect(creaCanzone, &QPushButton::clicked, this, &mainWindow::creaCanzone);
    layoutPulsanti->addWidget(creaCanzone);

    QPushButton *creaAlbum = new QPushButton("Album");
    creaAlbum->setFixedHeight(40);
    layout->addWidget(creaAlbum);
    connect(creaAlbum, &QPushButton::clicked, this, &mainWindow::creaAlbum);
    layoutPulsanti->addWidget(creaAlbum);

    layout->addWidget(pulsantiTipoMedia);

    mediaVisibili->addWidget(sezioneCrea);
    
}

void mainWindow::creaSottoOggettoMedia(QWidget **widgetBase, QLineEdit **campiBase )
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
    

    QPushButton *browseButton = new QPushButton("Sfoglia", this);
    browseButton->setFixedSize(120,30);
    browseButton->setFont(QFont("Mono",12));

    copertinaTemp = campiBase[3];
    connect(browseButton, &QPushButton::clicked, this, &mainWindow::browseImage);

    layoutCopertina->setContentsMargins(0,0,0,0);
    layoutCopertina->setSpacing(0);
    layoutCopertina->addWidget(lableCopertina,0,Qt::AlignRight);
    layoutCopertina->addWidget(campiBase[3],0, Qt::AlignLeft);
    layoutCopertina->addWidget(browseButton, 0, Qt::AlignLeft);
}





void mainWindow::creaLibro()
{
    svuotaMediaVisibili();
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

    //---------------------------------------------------
    layout->addWidget(widgetsBase[0]);
    layout->addWidget(widgetsBase[1]);
    layout->addWidget(widgetsBase[2]);
    layout->addWidget(widgetNumPagine);
    layout->addWidget(widgetIsbn);
    layout->addWidget(widgetGenere);
    layout->addWidget(widgetsBase[3]);


    mediaVisibili->addWidget(widgetCreazione);
    
}

void mainWindow::creaCanzone()
{

}

void mainWindow::creaAlbum()
{

}

void mainWindow::browseImage()
{
        QString filePath = QFileDialog::getOpenFileName(this, "Seleziona un'immagine", "", "Immagini (*.png *.jpg *.jpeg *.bmp *.gif)");
        if (!filePath.isEmpty())    
            copertinaTemp->setText(filePath);
}

void mainWindow::confermaSalvataggio()
{

}

void mainWindow::annullaSalvataggio()
{

}

bool mainWindow::isImageFile(const QString &filePath) const 
{
    QFileInfo fileInfo(filePath);
    QString ext = fileInfo.suffix().toLower();
    return (ext == "png" || ext == "jpg" || ext == "jpeg" || ext == "bmp" || ext == "gif");
}














