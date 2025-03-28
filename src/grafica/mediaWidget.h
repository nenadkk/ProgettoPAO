#ifndef MEDIAWIDGET
#define MEDIAWIDGET

#include "../logica/media.h"
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QEvent>
#include <QListWidget>


class mediaWidget : public QWidget
{
    Q_OBJECT

    private:
        QGridLayout* layoutEsterno;
        media* object;

        void resetSchermata();
        void aggiungiPulsanti(QHBoxLayout*);

    protected:
        void mousePressEvent(QMouseEvent* event) override;

    public:
        explicit mediaWidget(media*, QGridLayout*, QWidget* parent = nullptr);

        //le seguenti tre sono pubbliche per poter venir connesse da showMediaVisitor
        void dettagliLibro();
        void dettagliCanzone();
        void dettagliAlbum();

    private slots:
        void modificaClicked();
        void eliminaClicked(); 
        
    signals:
        void clicked();
};
#endif
