#include "mainWindow.h"
#include "qboxlayout.h"
#include "qglobal.h"
#include "qlabel.h"
#include "qlineedit.h"
#include "qmainwindow.h"
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
#include "qnamespace.h"
#include "qpushbutton.h"
#include "showMediaVisitor.h"

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
    connect(pulsanteCrea, &QPushButton::clicked, this, &mainWindow::creaMedia);

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

void mainWindow::creaMedia()
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

void mainWindow::creaLibro()
{
    svuotaMediaVisibili();
    QVBoxLayout *layout = new QVBoxLayout();    
    layout->setAlignment(Qt::AlignCenter);
    
    QLabel *lableTitle = new QLabel("Titolo: ");
    QLineEdit *titolo = new QLineEdit();
    QWidget *widgetTitolo = new QWidget();
    QHBoxLayout *layoutTitolo = new QHBoxLayout(widgetTitolo);

}

void mainWindow::creaCanzone()
{

}

void mainWindow::creaAlbum()
{

}















