#include "bottoneSfoglia.h"
#include <QFileDialog>
bottoneSfoglia::bottoneSfoglia(QLineEdit* _le, QWidget* parent) : imgLineEdit(_le), QPushButton("Sfoglia", parent)
{
    this->setFixedSize(120,30);
    this->setFont(QFont("Mono",15));
    connect(this, &QPushButton::clicked, this, &bottoneSfoglia::browseImage);
}

void bottoneSfoglia::browseImage()
{
    if(imgLineEdit)
    {
        QString filePath = QFileDialog::getOpenFileName(this, "Seleziona un'immagine", "", "Immagini (*.png *.jpg *.jpeg *.bmp *.gif)");
        if (!filePath.isEmpty() && isImageFile(filePath))    
            imgLineEdit->setText(filePath);       
    }
}

bool bottoneSfoglia::isImageFile(const QString &filePath) const 
{
    QFileInfo fileInfo(filePath);
    QString ext = fileInfo.suffix().toLower();
    return (ext == "png" || ext == "jpg" || ext == "jpeg" || ext == "jpeg" || ext == "bmp" || ext == "gif");
}
