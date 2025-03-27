#ifndef MEDIAWIDGET
#define MEDIAWIDGET

#include "../logica/media.h"
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QEvent>


class mediaWidget : public QWidget
{
    Q_OBJECT

    private:
        QGridLayout* layoutEsterno;
        media* object;

    protected:
        void mousePressEvent(QMouseEvent* event) override;

    public:
        explicit mediaWidget(media*, QGridLayout*, QWidget* parent = nullptr);

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
