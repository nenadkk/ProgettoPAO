#ifndef BOTTONESFOGLIA
#define BOTTONESFOGLIA

#include "qpushbutton.h"
#include <QPushButton>
#include <QString>
#include <QLineEdit>

class bottoneSfoglia : public QPushButton
{
    Q_OBJECT

    private:
        QLineEdit* imgLineEdit;

    private slots:
        void browseImage();

    public:
        bottoneSfoglia(QLineEdit*, QWidget* parent = nullptr);
};
#endif

