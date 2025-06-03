#include "mainWindow.h"
#include <QApplication>
#include <QMessageBox>
#include <QMainWindow>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QScrollArea>
#include <QListWidget>
#include <QLabel>
#include <QDir>
#include <QFileDialog>

#include <list>

#include "editorLibro.h"
#include "editorCanzone.h"
#include "editorAlbum.h"
#include "qglobal.h"
#include "widgetAnteprima.h"
#include "widgetDettaglio.h"

mainWindow::mainWindow(QWidget* parent) : 
    QMainWindow(parent)
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

    QPushButton *pulsanteHome = new QPushButton();
    pulsanteHome->setIcon(QIcon(QPixmap("./immagini/.icons/iconaHome.png")));
    pulsanteHome->setFixedHeight(60);
    pulsanteHome->setIconSize(QSize(60,60));
    sideBarLayout->addWidget(pulsanteHome);
    connect(pulsanteHome, &QPushButton::clicked, this, &mainWindow::reloadAreaContenuti);
    

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
            this->reloadAreaContenuti();
            });

    searchLayout->addWidget(clearButton);
    centralLayout->addWidget(searchWidget);

    // Area di contenuto con scroll
    QScrollArea *scrollArea = new QScrollArea();
    QWidget *contentWidget = new QWidget();
    areaContenuti = new QGridLayout(contentWidget);

    reloadAreaContenuti();

    contentWidget->setLayout(areaContenuti);
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

    svuotaAreaContenuti();

    if(!query.empty())
        addToAreaContenuti(query); //Ripopola con i valori filtrati

}

void mainWindow::addToAreaContenuti(list<media*> listaMedia)
{
    int colGrid=0;
    int rowGrid=0;

    int maxCol = max(2,((this->width() - 200)/(270)));

    for(auto m : listaMedia)
    {
        widgetAnteprima* item = new widgetAnteprima(m,areaContenuti,this);
        areaContenuti->addWidget(item, rowGrid, colGrid);
        colGrid++;

        if (colGrid >= maxCol) 
        {
            colGrid = 0;
            rowGrid++;
        }
    }

}
void mainWindow::addToAreaContenuti(QWidget* w)
{
    svuotaAreaContenuti();
    areaContenuti->addWidget(w);
}

void mainWindow::reloadAreaContenuti()
{
    svuotaAreaContenuti();
    
    list<media*> temp; //non faccio eliminazione profonda perché questi ogetti sono
                       //condivisi con il mediaManager
    for (int i=0;i<mediaMan.size();i++) 
        temp.push_back(mediaMan[i]);
        
    addToAreaContenuti(temp);
}

void mainWindow::svuotaAreaContenuti()
{
    if (areaContenuti != nullptr)
    {
        while (QLayoutItem *item = areaContenuti->takeAt(0)) 
        {
            if (QWidget *widget = item->widget()) 
                widget->deleteLater();

            delete item;
        }
    }    
}

void mainWindow::sceltaCreazione()
{
    svuotaAreaContenuti(); 
    
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
    connect(creaLibro, &QPushButton::clicked, this, &mainWindow::avviaCreazioneLibro);
    layoutPulsanti->addWidget(creaLibro);

    QPushButton *creaCanzone = new QPushButton("Canzone");
    creaCanzone->setFixedHeight(40);
    creaCanzone->setFont(QFont("Mono",15));
    layout->addWidget(creaCanzone);
    connect(creaCanzone, &QPushButton::clicked, this, &mainWindow::avviaCreazioneCanzone);
    layoutPulsanti->addWidget(creaCanzone);

    QPushButton *creaAlbum = new QPushButton("Album");
    creaAlbum->setFixedHeight(40);
    creaAlbum->setFont(QFont("Mono",15));
    layout->addWidget(creaAlbum);
    connect(creaAlbum, &QPushButton::clicked, this, &mainWindow::avviaCreazioneAlbum);
    layoutPulsanti->addWidget(creaAlbum);

    layout->addWidget(pulsantiTipoMedia);

    QWidget *space = new QWidget();
    space->setFixedHeight(200);
    space->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    layout->addWidget(space);

    areaContenuti->addWidget(sezioneCrea);
    
}

void mainWindow::avviaCreazioneLibro()
{
    svuotaAreaContenuti();

    editorLibro *wid = new editorLibro(&mediaMan,this);
    areaContenuti->addWidget(wid);
}

void mainWindow::avviaCreazioneCanzone()
{
    svuotaAreaContenuti();

    editorCanzone *wid = new editorCanzone(&mediaMan,this);
    areaContenuti->addWidget(wid);
}

void mainWindow::avviaCreazioneAlbum()
{
    svuotaAreaContenuti();

    editorAlbum *wid = new editorAlbum(&mediaMan,this);
    areaContenuti->addWidget(wid);
}

void mainWindow::filtraLibri()
{
    svuotaAreaContenuti();
    addToAreaContenuti(mediaMan.filtroSoloLibri());
}

void mainWindow::filtraCanzoni()
{
    svuotaAreaContenuti();
    addToAreaContenuti(mediaMan.filtroSoloCanzoni());
}

void mainWindow::filtraAlbum()
{
    svuotaAreaContenuti();
    addToAreaContenuti(mediaMan.filtroSoloAlbum());
}

void mainWindow::mostraDettagli(media* obj)
{
    widgetDettaglio *item = new widgetDettaglio(obj,&mediaMan,this); 
    svuotaAreaContenuti();
    areaContenuti->addWidget(item);
}

bool mainWindow::loadFileSalvataggio()
{
    QString str = "Scegliere il file .json che si vuole usare per salvare i dati dell'applicazione";
    QMessageBox::information(this,"Salvataggio",str);

    QString dirIniziale = QDir::currentPath() + QString("/src/jsonHandler/data/");
    fileSalvataggio = QFileDialog::getOpenFileName(this, "Seleziona il file .json di salvataggio", dirIniziale, "Json (*.json)");
        
    qDebug()<<fileSalvataggio<<fileSalvataggio.isEmpty();

    if(fileSalvataggio.isEmpty() || QFileInfo(fileSalvataggio).suffix().toLower()!=".json")
        return false;
 
    return true;
}








