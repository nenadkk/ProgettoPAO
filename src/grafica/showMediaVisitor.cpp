#include "showMediaVisitor.h"
#include "../logica/libro.h"
#include "../logica/canzone.h"
#include "../logica/album.h"
#include "mediaWidgetAnteprima.h"
#include <QGridLayout>
#include <algorithm>
#include <QResizeEvent>
#include <QWidget>

showMediaVisitor::showMediaVisitor(mainWindow* w, QGridLayout* _layout, int _width) : 
    windowEsterna(w), layoutDaRiempire(_layout), row(0), col(0) 
{ 
    maxCol = max(3,((_width-150)/(270+10)));
    if(maxCol>5)
        maxCol=5;
}

void showMediaVisitor::visit(libro* _libro)
{
    mediaWidgetAnteprima* item = new mediaWidgetAnteprima(_libro, windowEsterna,layoutDaRiempire);
    
    QObject::connect(item, &mediaWidgetAnteprima::clicked, item, &mediaWidgetAnteprima::mostraDettagli);

    layoutDaRiempire->addWidget(item, row, col);

    col++;
    if (col >= maxCol) 
    {
        col = 0;
        row++;
    }
}

void showMediaVisitor::visit(canzone* _canzone) 
{
    mediaWidgetAnteprima* item = new mediaWidgetAnteprima(_canzone, windowEsterna,layoutDaRiempire);

    QObject::connect(item, &mediaWidgetAnteprima::clicked, item, &mediaWidgetAnteprima::mostraDettagli);

    layoutDaRiempire->addWidget(item, row, col);

    col++;
    if (col >= maxCol) 
    {
        col = 0;
        row++;
    }     
}

void showMediaVisitor::visit(album* _album) 
{
    mediaWidgetAnteprima* item = new mediaWidgetAnteprima(_album, windowEsterna, layoutDaRiempire);

    QObject::connect(item, &mediaWidgetAnteprima::clicked, item, &mediaWidgetAnteprima::mostraDettagli);

    layoutDaRiempire->addWidget(item, row, col);

    col++;
    if (col >= maxCol) 
    {
        col = 0;
        row++;
    }   
}
