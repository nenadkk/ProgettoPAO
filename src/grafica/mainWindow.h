#ifndef MAINWINDOW
#define MAINWINDOW
#include "../logica/media.h"
#include "../listaMedia/listaMedia.h"
#include <QMainWindow>

class mainWindow : public QMainWindow 
{
    private:
        listamedia LM;

    public:
        mainWindow(QWidget* parent = nullptr);

};
#endif
