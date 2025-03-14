#ifndef MEDIAWIDGET
#define MEDIAWIDGET

#include "../logica/media.h"
#include <QWidget>
#include <QLabel>
#include <QPushButton>


class mediaWidget : public QWidget
{
    private:
        media* object;

    public:
        explicit mediaWidget(media*, string*, QWidget* parent = nullptr);

        
    private slots:
        void modificaClicked();
        void eliminaClicked(); 
};
#endif
