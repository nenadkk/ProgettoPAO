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
#include "createMediaVisitor.h"

mainWindow::mainWindow(QWidget* parent) : QMainWindow(parent)
{
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

    // Configurazione della finestra principale
    setWindowTitle("Interfaccia Qt");
    resize(1200, 800);
}

void mainWindow::ricerca()
{
    string daCercare = searchBar->text().toStdString();
    list<media*> query = mediaMan.search(daCercare);

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

    for (int i=0;i<mediaMan.size();i++) 
        mediaMan[i]->accept(&showvis);
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
    createMediaVisitor vis(this, mediaVisibili, &mediaMan);
    temp->accept(&vis);
}

void mainWindow::creaCanzone()
{
    svuotaMediaVisibili();

    //il seguente oggetto canzone viene deallocato una volta finita la procedura di creazione
    //all'interno di widgetCreazione::crea()
    canzone *temp = new canzone();
    createMediaVisitor vis(this, mediaVisibili, &mediaMan);
    temp->accept(&vis);
}

void mainWindow::creaAlbum()
{
    svuotaMediaVisibili();

    //il seguente oggetto album viene deallocato una volta finita la procedura di creazione
    //all'interno di widgetCreazione::crea()
    album *temp = new album();
    createMediaVisitor vis(this, mediaVisibili, &mediaMan);
    temp->accept(&vis);
}

void mainWindow::filtraLibri()
{
    svuotaMediaVisibili();
    showMediaVisitor vis(mediaVisibili,width());

    for(auto m : mediaMan.filtroSoloLibri())
        m->accept(&vis);
}

void mainWindow::filtraCanzoni()
{
    svuotaMediaVisibili();
    showMediaVisitor vis(mediaVisibili,width());

    for(auto m : mediaMan.filtroSoloCanzoni())
        m->accept(&vis);
}

void mainWindow::filtraAlbum()
{
    svuotaMediaVisibili();
    showMediaVisitor vis(mediaVisibili,width());

    for(auto m : mediaMan.filtroSoloAlbum())
        m->accept(&vis);
}











