#include "showMediaVisitor.h"
#include "../logica/libro.h"
#include "../logica/canzone.h"
#include "../logica/album.h"
#include "mediaWidget.h"
#include <QGridLayout>
#include <string>

showMediaVisitor::showMediaVisitor(QGridLayout* _layout) : layoutDaRiempire(_layout), col(0), row(0) {}

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
    if (col >= 3) 
    {
        col = 0;
        row++;
    }
}

void showMediaVisitor::visit(canzone* _canzone) 
{
    string durata = to_string(_canzone->getDurata()/60) + ":" + to_string(_canzone->getDurata()%60);
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
    if (col >= 3) 
    {
        col = 0;
        row++;
    }    
}

void showMediaVisitor::visit(album* _album) 
{
    string durata = to_string(_album->getDurataTotale()/60) + ":" + to_string(_album->getDurataTotale()%60);
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
    if (col >= 3) 
    {
        col = 0;
        row++;
    }   
}
