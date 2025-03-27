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

        void resizeEvent(QResizeEvent* event) override;
        void updateLayoutAtResize();
        void svuotaMediaVisibili();
        void ricerca();
        
    private slots:
        void sceltaCreazione();
        void creaLibro();
        void creaCanzone();
        void creaAlbum();

        void filtraLibri();
        void filtraCanzoni();
        void filtraAlbum();

    public:
        mainWindow(QWidget* parent = nullptr);

    public slots:
        void reloadMediaVisibili();
};
#endif
