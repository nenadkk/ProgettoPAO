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
        QString fileSalvataggio;
        mediaManager mediaMan;
        QGridLayout *areaContenuti;
        QLineEdit *searchBar;

        void ricerca();
        void addToAreaContenuti(list<media*>);//aggiunge l'anteprima del media al layout principale
        bool loadFileSalvataggio(); //true se la selezione del file avviene correttamente, false altrimenti
        
    private slots:
        void sceltaCreazione();//scegli che tipo di media creare
        void avviaCreazioneLibro();
        void avviaCreazioneCanzone();
        void avviaCreazioneAlbum();

        void filtraLibri();
        void filtraCanzoni();
        void filtraAlbum();

    public:
        mainWindow(QWidget* parent = nullptr);
        void mostraDettagli(media*);
        void svuotaAreaContenuti();
        void addToAreaContenuti(QWidget*);//permette di visualizzare un'altro widget
                                          //rimuove il contenuto precedente

    public slots:
        void reloadAreaContenuti();
};
#endif

//NB: la differenza tra addToAreaContenuti(QWidget*) e addToAreaContenuti(media*) è che la prima fa si che
//ci sia un solo widget visualizzabile all'interno di mediaVisibili, mentre la seconda serve a disporre più
//widget anteprima in griglia
