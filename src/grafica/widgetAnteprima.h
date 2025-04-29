#ifndef WIDGETANTEPRIMA    
#define WIDGETANTEPRIMA

#include "../logica/media.h"
#include "mainWindow.h"

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QEvent>
#include <QListWidget>

class widgetAnteprima : public QWidget
{
    Q_OBJECT

    private:
        media* object;
        mainWindow* windowEsterna;
        QGridLayout* layoutEsterno;


    protected:
        void mousePressEvent(QMouseEvent* event) override;

    public:
        explicit widgetAnteprima(media*, QGridLayout*, mainWindow*);

    signals:
        void clicked();
};
#endif
