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
        QLineEdit *copertinaTemp;

        libro* tempLibro;
        canzone* tempCanzone;
        album* tempAlbum;

        void resizeEvent(QResizeEvent* event) override;
        void updateLayoutAtResize();
        void svuotaMediaVisibili();
        void ricerca();
        void deleteTemp();
        
    private slots:
        void sceltaCreazione();
        void creaLibro();
        void creaCanzone();
        void creaAlbum();

    public:
        mainWindow(QWidget* parent = nullptr);

    public slots:
        void reloadMediaVisibili();
};
#endif
