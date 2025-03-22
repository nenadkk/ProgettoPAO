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
        bool isImageFile(const QString &filePath) const;

    public:
        bottoneSfoglia(QLineEdit*, QWidget* parent = nullptr);
};
#endif

