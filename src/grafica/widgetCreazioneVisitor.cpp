#include "widgetCreazioneVisitor.h"
#include "widgetCreazione.h"

#include <QWidget>
#include <QLabel>
#include <QFileDialog>
#include <QPushButton>
#include <QIntValidator>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListWidget>
#include <QMessageBox>

widgetCreazioneVisitor::widgetCreazioneVisitor(widgetCreazione* w) : widget(w) {}


void widgetCreazioneVisitor::visit(libro* newLibro)
{
    widget->buildWidget(newLibro);
}

void widgetCreazioneVisitor::visit(canzone* newCanzone)
{
    widget->buildWidget(newCanzone);
}


void widgetCreazioneVisitor::visit(album* newAlbum)
{
    widget->buildWidget(newAlbum);
}
