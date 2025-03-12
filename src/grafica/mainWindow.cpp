#include "mainWindow.h"
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

mainWindow::mainWindow(QWidget* parent) : QMainWindow(parent)
{
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
        QVBoxLayout *contentLayout = new QVBoxLayout(contentWidget);
        mediaVisibili = contentLayout;

        contentLayout->addStretch();
        contentWidget->setLayout(contentLayout);
        scrollArea->setWidget(contentWidget);
        scrollArea->setWidgetResizable(true);

        centralLayout->addWidget(scrollArea);

        // Aggiunta delle aree al layout principale
        sideBar->setFixedWidth(150);
        mainLayout->addWidget(sideBar);
        mainLayout->addWidget(centralArea);

        // Configurazione della finestra principale
        setWindowTitle("Interfaccia Qt");
        resize(800, 600);
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
