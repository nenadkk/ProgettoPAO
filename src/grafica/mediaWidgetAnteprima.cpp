#include "mediaWidgetAnteprima.h"
#include "mediaWidgetDettaglio.h"
#include "mainWindow.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QMouseEvent>
#include <QListWidget>

mediaWidgetAnteprima::mediaWidgetAnteprima(media* obj, QGridLayout* l, QWidget* parent) : 
    QWidget(parent), object(obj) ,layoutEsterno(l)
{
    windowEsterna = (dynamic_cast<mainWindow*>(parent));

    QVBoxLayout* mainLayout = new QVBoxLayout();
    mainLayout->setAlignment(Qt::AlignCenter);

    setFixedSize(250, 330);
    setAttribute(Qt::WA_StyledBackground);
    setStyleSheet("QWidget {background-color: #686868; border-radius: 10px;}");

    QLabel *imageLabel = new QLabel();
    imageLabel->setPixmap(QPixmap(toQString(object->getCopertina())).scaled(200, 300, Qt::KeepAspectRatio));
    imageLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(imageLabel);

    QString str = QString::fromStdString(object->getTitolo()) + 
        QString::fromStdString(object->getAutore());

    QLabel *labelTesto = new QLabel(str);
    labelTesto->setFont(QFont("Mono",13));
    labelTesto->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(labelTesto);

    QObject::connect(this, &mediaWidgetAnteprima::clicked,
                     this, &mediaWidgetAnteprima::mostraDettagli);

    this->setLayout(mainLayout);

}
void mediaWidgetAnteprima::mousePressEvent(QMouseEvent* event)  
{
    if (event->button() == Qt::LeftButton) //se viene clickato con il tasto sx del mouse
        emit clicked(); 

    QWidget::mousePressEvent(event);
}

void mediaWidgetAnteprima::mostraDettagli()
{
    mediaWidgetDettaglio *item = new mediaWidgetDettaglio(object); 
    windowEsterna->svuotaMediaVisibili();
    layoutEsterno->addWidget(item);
}

