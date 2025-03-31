#ifndef MEDIAWIDGETANTEPRIMA    
#define MEDIAWIDGETANTEPRIMA

#include "../logica/media.h"
#include "mainWindow.h"

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QEvent>
#include <QListWidget>

class mediaWidgetAnteprima : public QWidget
{
    Q_OBJECT

    private:
        media* object;
        mainWindow* widowEsterna;
        QGridLayout* layoutEsterno;


    protected:
        void mousePressEvent(QMouseEvent* event) override;

    public:
        explicit mediaWidgetAnteprima(media*, mainWindow*, QGridLayout*, QWidget* parent = nullptr);

        void mostraDettagli();

    signals:
        void clicked();
};
#endif
