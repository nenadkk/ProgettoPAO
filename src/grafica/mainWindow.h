#ifndef MAINWINDOW
#define MAINWINDOW
#include "../logica/media.h"
#include "../mediaManager/mediaManager.h"
#include <QMainWindow>
#include <QGridLayout>
#include <QLineEdit>

class mainWindow : public QMainWindow 
{
    Q_OBJECT

    private:
        mediaManager mediaMan;
        QGridLayout *mediaVisibili;
        QLineEdit *searchBar;

        int rowGrid; //serve per disposizione anteprime nel layout pricipale
        int colGrid; //serve per disposizione anteprime nel layout pricipale

        void ricerca();
        void addToMediaVisibili(media*);//aggiunge l'anteprima del media al layout principale
        
    private slots:
        void sceltaCreazione();//scegli che tipo di media creare
        void creaLibro();
        void creaCanzone();
        void creaAlbum();

        void filtraLibri();
        void filtraCanzoni();
        void filtraAlbum();

    public:
        mainWindow(QWidget* parent = nullptr);
        void mostraDettagli(media*);
        void svuotaMediaVisibili();

    public slots:
        void reloadMediaVisibili();
};
#endif
