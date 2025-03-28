#include "showMediaVisitor.h"
#include "../logica/libro.h"
#include "../logica/canzone.h"
#include "../logica/album.h"
#include "mediaWidget.h"
#include <QGridLayout>
#include <algorithm>
#include <QResizeEvent>
#include <QWidget>

showMediaVisitor::showMediaVisitor(QGridLayout* _layout, int _width) : layoutDaRiempire(_layout), row(0), col(0) 
{ 
    maxCol = max(3,((_width-150)/(270+10)));
    if(maxCol>5)
        maxCol=5;
}

void showMediaVisitor::visit(libro* _libro)
{
    mediaWidget* item = new mediaWidget(_libro,layoutDaRiempire);
    
    QObject::connect(item, &mediaWidget::clicked, item, &mediaWidget::dettagliLibro);

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
    mediaWidget* item = new mediaWidget(_canzone,layoutDaRiempire);

    QObject::connect(item, &mediaWidget::clicked, item, &mediaWidget::dettagliCanzone);

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
    mediaWidget* item = new mediaWidget(_album, layoutDaRiempire);

    QObject::connect(item, &mediaWidget::clicked, item, &mediaWidget::dettagliAlbum);

    layoutDaRiempire->addWidget(item, row, col);

    col++;
    if (col >= maxCol) 
    {
        col = 0;
        row++;
    }   
}
