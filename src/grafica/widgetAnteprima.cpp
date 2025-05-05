#include "widgetAnteprima.h"
#include "mainWindow.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QMouseEvent>
#include <QListWidget>

widgetAnteprima::widgetAnteprima(media* obj, QGridLayout* l, mainWindow* m) : 
    object(obj), windowEsterna(m), layoutEsterno(l)
{
    QVBoxLayout* mainLayout = new QVBoxLayout();
    mainLayout->setAlignment(Qt::AlignCenter);

    setFixedSize(250, 330);
    setAttribute(Qt::WA_StyledBackground);
    setStyleSheet("QWidget {background-color: #3F4454; border-radius: 10px;}");

    QLabel *imageLabel = new QLabel();
    imageLabel->setPixmap(QPixmap(toQString(object->getCopertina())).scaled(200, 300, Qt::KeepAspectRatio));
    imageLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(imageLabel);

    QString str = QString::fromStdString(object->getTitolo()) + "\n" +
        QString::fromStdString(object->getAutore());

    QLabel *labelTesto = new QLabel(str);
    labelTesto->setFont(QFont("Mono",13));
    labelTesto->setAlignment(Qt::AlignCenter);
    labelTesto->setWordWrap(true);

    mainLayout->addWidget(labelTesto);

    QObject::connect(this, &widgetAnteprima::clicked, [=,this](){
            windowEsterna->mostraDettagli(object);
            });
    
    this->setLayout(mainLayout);

}
void widgetAnteprima::mousePressEvent(QMouseEvent* event)  
{
    if (event->button() == Qt::LeftButton) //se viene clickato con il tasto sx del mouse
        emit clicked(); 

    QWidget::mousePressEvent(event);
}

