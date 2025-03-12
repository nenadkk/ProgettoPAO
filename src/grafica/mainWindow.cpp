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
    cout<<"\nDIMENSIONE LM "<<LM.size();


    // Widget principale
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // Layout principale orizzontale
    QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);

    // Barra laterale sinistra con pulsanti
    QWidget *sideBar = new QWidget();
    QVBoxLayout *sideBarLayout = new QVBoxLayout(sideBar);
    for (int i = 1; i <= 5; ++i) {
        QPushButton *button = new QPushButton(tr("Pulsante %1").arg(i));
        sideBarLayout->addWidget(button);
    }
    sideBarLayout->addStretch();

    // Area centrale con barra di ricerca in alto
    QWidget *centralArea = new QWidget();
    QVBoxLayout *centralLayout = new QVBoxLayout(centralArea);

    QLineEdit *searchBar = new QLineEdit();
    searchBar->setPlaceholderText("Cerca...");
    connect(searchBar, &QLineEdit::returnPressed, this, &mainWindow::ricerca);
    centralLayout->addWidget(searchBar);

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
    resize(1000, 800);
}

void mainWindow::ricerca()
{
    string searchText = findChild<QLineEdit *>()->text().toStdString();

    for (int i = 1; i <= 20; ++i) {
        QPushButton *contentItem = new QPushButton(tr("Elemento %1").arg(i));
        contentItem->setFixedHeight(50);
        contentItem->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        mediaVisibili->addWidget(contentItem);
    }
}

void mainWindow::reloadMediaVisibili()
{
    showMediaVisitor showvis(mediaVisibili);

    int columns = 3; // Numero di colonne per riga
    int row = 0, col = 0;

    for (int i=0;i<<LM.size();i++) 
    {
        LM[i]->accept(&showvis);

        QWidget *itemWidget = new QWidget();
        QVBoxLayout *itemLayout = new QVBoxLayout(itemWidget);

        QLabel *imageLabel = new QLabel();
        imageLabel->setPixmap(QPixmap("./immagini/libro.png").scaled(100, 100, Qt::KeepAspectRatio));
        imageLabel->setAlignment(Qt::AlignCenter);

        QLabel *titleLabel = new QLabel(tr(LM[i]->getTitolo().c_str()).arg(i));
        titleLabel->setAlignment(Qt::AlignCenter);

        QLabel *descLabel = new QLabel(tr(to_string(LM[i]->getAnno()).c_str()).arg(i));
        descLabel->setAlignment(Qt::AlignCenter);

        itemLayout->addWidget(imageLabel);
        itemLayout->addWidget(titleLabel);
        itemLayout->addWidget(descLabel);
        itemWidget->setLayout(itemLayout);
        itemWidget->setFixedSize(150, 200);

        mediaVisibili->addWidget(itemWidget, row, col);

        col++;
        if (col >= columns) 
        {
            col = 0;
            row++;
        }
    }
}











