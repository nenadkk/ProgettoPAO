#ifndef MAINWINDOW
#define MAINWINDOW
#include "../logica/media.h"
#include "../listaMedia/listaMedia.h"
#include <QMainWindow>
#include <QGridLayout>

class mainWindow : public QMainWindow 
{
    private:
        listamedia LM;
        QGridLayout *mediaVisibili;

    public:
        mainWindow(QWidget* parent = nullptr);

    public slots:
        void ricerca();
        void reloadMediaVisibili();

};
#endif
