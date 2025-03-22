#include "showMediaVisitor.h"
#include "../logica/libro.h"
#include "../logica/canzone.h"
#include "../logica/album.h"
#include "mediaWidget.h"
#include <QGridLayout>
#include <algorithm>
#include <string>
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
    string campi[6] = {_libro->getTitolo(), 
        _libro->getAutore(), 
        to_string(_libro->getAnno()),
        _libro->getEditore(),
        to_string(_libro->getIsbn()),
        to_string(_libro->getNumPagine())+" pagine"};

    mediaWidget* item = new mediaWidget(static_cast<media*>(_libro), campi);

    item->setStyleSheet(
            "background-color: #686868;"
            "border-radius: 10px;"
            "margin: 5px;"
            );

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
    string durata = to_string(_canzone->getDurata()/60) + ":";
    if(_canzone->getDurata()%60 < 10)
        durata = durata + "0" + to_string(_canzone->getDurata()%60);
    else
        durata = durata + to_string(_canzone->getDurata()%60);

    string campi[6] = {_canzone->getTitolo(), 
        _canzone->getAutore(), 
        to_string(_canzone->getAnno()),
        _canzone->getGenere(),
        durata,
        " "};

    mediaWidget* item = new mediaWidget(static_cast<media*>(_canzone), campi);

    item->setStyleSheet(
            "background-color: #686868;"
            "border-radius: 10px;"
            "margin: 5px;"
            );

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
    string durata = to_string(_album->getDurataTotale()/60) + ":";
    if(_album->getDurataTotale()%60 < 10)
        durata = durata + "0" + to_string(_album->getDurataTotale()%60);
    else
        durata = durata + to_string(_album->getDurataTotale()%60);

    string campi[6] = {_album->getTitolo(), 
        _album->getAutore(), 
        to_string(_album->getAnno()),
        durata,
        " ",
        " "};

    mediaWidget* item = new mediaWidget(static_cast<media*>(_album), campi);

    item->setStyleSheet(
            "background-color: #686868;"
            "border-radius: 10px;"
            "margin: 5px;"
            );

    layoutDaRiempire->addWidget(item, row, col);

    col++;
    if (col >= maxCol) 
    {
        col = 0;
        row++;
    }   
}
