#include "mainWindow.h"
#include "qglobal.h"
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
#include <string>
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
    space->setFixedHeight(35);
    sideBarLayout->addWidget(space);

    for (int i = 1; i <= 5; ++i) 
    {
        QPushButton *button = new QPushButton(tr("Pulsante %1").arg(i));
        button->setFixedHeight(40);
        sideBarLayout->addWidget(button);
    }
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

    //Svuota
    if (mediaVisibili != nullptr)
    {
        while (QLayoutItem *item = mediaVisibili->takeAt(0)) 
        {
            if (QWidget *widget = item->widget()) 
                widget->deleteLater();

            delete item;
        }
    }    

    //Ripopola con i valori filtrati
    showMediaVisitor showvis(mediaVisibili);

    int row = 0, col = 0;

    for (auto m : query) 
    {

        QWidget *itemWidget = new QWidget();
        QVBoxLayout *itemLayout = new QVBoxLayout(itemWidget);

        QLabel *imageLabel = new QLabel();
        imageLabel->setPixmap(QPixmap("./immagini/libro.png").scaled(100, 100, Qt::KeepAspectRatio));
        imageLabel->setAlignment(Qt::AlignCenter);

        QLabel *titleLabel = new QLabel(m->getTitolo().c_str());
        titleLabel->setAlignment(Qt::AlignCenter);
        titleLabel->setFont(QFont("Mono",16));

        QLabel *annoLable = new QLabel(to_string(m->getAnno()).c_str());
        annoLable->setAlignment(Qt::AlignCenter);
        annoLable->setFont(QFont("Mono",12));

        itemLayout->addWidget(imageLabel);
        itemLayout->addWidget(titleLabel);
        itemLayout->addWidget(annoLable);
        itemWidget->setLayout(itemLayout);
        itemWidget->setFixedSize(200, 250);
        // Stile per bordi arrotondati e contrasto
        itemWidget->setStyleSheet(
                "background-color: #686868;"
                "border-radius: 10px;"
                "margin: 5px;"
                );
        mediaVisibili->addWidget(itemWidget, row, col);

        col++;
        if (col >= 3) 
        {
            col = 0;
            row++;
        }
    }


}


void mainWindow::reloadMediaVisibili()
{
    //Svuota
    if (mediaVisibili != nullptr)
    {
        while (QLayoutItem *item = mediaVisibili->takeAt(0)) 
        {
            if (QWidget *widget = item->widget()) 
                widget->deleteLater();

            delete item;
        }
    }    

    //Ripopola
    showMediaVisitor showvis(mediaVisibili);

    int row = 0, col = 0;

    for (int i=0;i<LM.size();i++) 
        LM[i]->accept(&showvis);
}











