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

#include "widgetCreazione.h"
#include "mediaWidgetAnteprima.h"

mainWindow::mainWindow(QWidget* parent) : QMainWindow(parent), rowGrid(0), colGrid(0)
{
    // Configurazione della finestra principale
    setWindowTitle("Interfaccia Qt");
    resize(1200, 800);

    //Caricamento dati 
    mediaMan.load();

    // Widget principale
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // Layout principale orizzontale
    QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);

    // Barra laterale sinistra con pulsanti
    QWidget *sideBar = new QWidget();
    QVBoxLayout *sideBarLayout = new QVBoxLayout(sideBar);

    QWidget *space = new QWidget();
    space->setFixedHeight(60);
    sideBarLayout->addWidget(space);

    QPushButton *pulsanteCrea = new QPushButton("Crea");
    pulsanteCrea->setFont(QFont("Mono",14));
    pulsanteCrea->setFixedHeight(40);
    sideBarLayout->addWidget(pulsanteCrea);
    connect(pulsanteCrea, &QPushButton::clicked, this, &mainWindow::sceltaCreazione);

    QPushButton *pulsanteFiltroLibri = new QPushButton("Filtra Libri");
    pulsanteFiltroLibri->setFont(QFont("Mono",14));
    pulsanteFiltroLibri->setFixedHeight(40);
    sideBarLayout->addWidget(pulsanteFiltroLibri);
    connect(pulsanteFiltroLibri, &QPushButton::clicked, this, &mainWindow::filtraLibri);

    QPushButton *pulsanteFiltroCanzoni = new QPushButton("Filtra Canzoni");
    pulsanteFiltroCanzoni->setFont(QFont("Mono",14));
    pulsanteFiltroCanzoni->setFixedHeight(40);
    pulsanteFiltroCanzoni->setStyleSheet("padding: 0 10px;");
    sideBarLayout->addWidget(pulsanteFiltroCanzoni);
    connect(pulsanteFiltroCanzoni, &QPushButton::clicked, this, &mainWindow::filtraCanzoni);

    QPushButton *pulsanteFiltroAlbum = new QPushButton("Filtra Album");
    pulsanteFiltroAlbum->setFont(QFont("Mono",14));
    pulsanteFiltroAlbum->setFixedHeight(40);
    sideBarLayout->addWidget(pulsanteFiltroAlbum);
    connect(pulsanteFiltroAlbum, &QPushButton::clicked, this, &mainWindow::filtraAlbum);
    
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

    contentWidget->setLayout(mediaVisibili);
    scrollArea->setWidget(contentWidget);
    scrollArea->setWidgetResizable(true);

    centralLayout->addWidget(scrollArea);

    // Aggiunta delle aree al layout principale
    sideBar->setFixedWidth(200);
    mainLayout->addWidget(sideBar);
    mainLayout->addWidget(centralArea);

}

void mainWindow::ricerca()
{
    string daCercare = searchBar->text().toStdString();
    list<media*> query = mediaMan.search(daCercare);

    svuotaMediaVisibili();

    if(!query.empty())
    {
        //Ripopola con i valori filtrati
        for (auto m : query) 
            addToMediaVisibili(m);
    }
}
void mainWindow::addToMediaVisibili(media* m)
{
    int maxCol = max(2,((this->width())/(270+10)));
    if(maxCol>5)
        maxCol=5;

    mediaWidgetAnteprima* item = new mediaWidgetAnteprima(m,mediaVisibili,this);

    mediaVisibili->addWidget(item, rowGrid, colGrid);

    colGrid++;
    if (colGrid >= maxCol) 
    {
        colGrid = 0;
        rowGrid++;
    }
}

void mainWindow::reloadMediaVisibili()
{
    svuotaMediaVisibili();

    for (int i=0;i<mediaMan.size();i++) 
        addToMediaVisibili(mediaMan[i]);
}

void mainWindow::svuotaMediaVisibili()
{
    rowGrid=0;
    colGrid=0;

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
    creaLibro->setFont(QFont("Mono",15));
    layout->addWidget(creaLibro);
    connect(creaLibro, &QPushButton::clicked, this, &mainWindow::creaLibro);
    layoutPulsanti->addWidget(creaLibro);

    QPushButton *creaCanzone = new QPushButton("Canzone");
    creaCanzone->setFixedHeight(40);
    creaCanzone->setFont(QFont("Mono",15));
    layout->addWidget(creaCanzone);
    connect(creaCanzone, &QPushButton::clicked, this, &mainWindow::creaCanzone);
    layoutPulsanti->addWidget(creaCanzone);

    QPushButton *creaAlbum = new QPushButton("Album");
    creaAlbum->setFixedHeight(40);
    creaAlbum->setFont(QFont("Mono",15));
    layout->addWidget(creaAlbum);
    connect(creaAlbum, &QPushButton::clicked, this, &mainWindow::creaAlbum);
    layoutPulsanti->addWidget(creaAlbum);

    layout->addWidget(pulsantiTipoMedia);

    QWidget *space = new QWidget();
    space->setFixedHeight(200);
    space->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    layout->addWidget(space);

    mediaVisibili->addWidget(sezioneCrea);
    
}

void mainWindow::creaLibro()
{
    svuotaMediaVisibili();

    //il seguente oggetto libro viene deallocato una volta finita la procedura di creazione
    //all'interno di widgetCreazione::crea()
    libro *temp = new libro();
    widgetCreazione *wid = new widgetCreazione(temp,&mediaMan,this);
    mediaVisibili->addWidget(wid);
}

void mainWindow::creaCanzone()
{
    svuotaMediaVisibili();

    //il seguente oggetto canzone viene deallocato una volta finita la procedura di creazione
    //all'interno di widgetCreazione::crea()
    canzone *temp = new canzone();
    widgetCreazione *wid = new widgetCreazione(temp,&mediaMan,this);
    mediaVisibili->addWidget(wid);
}

void mainWindow::creaAlbum()
{
    svuotaMediaVisibili();

    //il seguente oggetto album viene deallocato una volta finita la procedura di creazione
    //all'interno di widgetCreazione::crea()
    album *temp = new album();
    widgetCreazione *wid = new widgetCreazione(temp,&mediaMan,this);
    mediaVisibili->addWidget(wid);
}

void mainWindow::filtraLibri()
{
    svuotaMediaVisibili();

    for(auto m : mediaMan.filtroSoloLibri())
        addToMediaVisibili(m);
}

void mainWindow::filtraCanzoni()
{
    svuotaMediaVisibili();

    for(auto m : mediaMan.filtroSoloCanzoni())
        addToMediaVisibili(m);
}

void mainWindow::filtraAlbum()
{
    svuotaMediaVisibili();

    for(auto m : mediaMan.filtroSoloAlbum())
        addToMediaVisibili(m);
}











