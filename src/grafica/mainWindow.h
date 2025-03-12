#ifndef MAINWINDOW
#define MAINWINDOW
#include "../logica/media.h"
#include "../listaMedia/listaMedia.h"
#include <QMainWindow>
#include <QVBoxLayout>

class mainWindow : public QMainWindow 
{
    private:
        listamedia LM;
        QVBoxLayout *mediaVisibili;

    public:
        mainWindow(QWidget* parent = nullptr);

    public slots:
        void ricerca();

};
#endif
