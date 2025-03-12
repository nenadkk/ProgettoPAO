#include "showMediaVisitor.h"
#include "../logica/libro.h"
#include "../logica/canzone.h"
#include "../logica/album.h"
#include <QGridLayout>

showMediaVisitor::showMediaVisitor(QGridLayout* _layout) : layoutDaRiempire(_layout) {}

void showMediaVisitor::visit(libro* _libro) 
{
    
}

void showMediaVisitor::visit(canzone* _canzone) 
{
    
}

void showMediaVisitor::visit(album* _album) 
{
    
}
