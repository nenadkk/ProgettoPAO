#include "bottoneSalva.h"
#include "qglobal.h"
#include "qpushbutton.h"

bottoneSalva::bottoneSalva(mediaManager* man, QMap<QString,QLineEdit*> map, media* tipo, mainWindow* windowEsterna, QPushButton* parent) : 
    QPushButton("SALVA",parent), manager(man), attributi(map), tipo(tipo), windowEsterna(windowEsterna)
{
    connect(this, &QPushButton::clicked, this, &bottoneSalva::crea);
}

void bottoneSalva::crea()
{
    if(dynamic_cast<libro*>(tipo))
    {
        manager->addMedia(new libro((attributi)["titolo"]->text().toStdString(),
                                    (attributi)["autore"]->text().toStdString(),
                                    (attributi)["anno"]->text().toInt(),
                                    (attributi)["copertina"]->text().toStdString(),
                                    0,
                                    (attributi)["numeroPagine"]->text().toInt(),
                                    (attributi)["isbn"]->text().toInt(),
                                    (attributi)["editore"]->text().toStdString()
                                    ));
    }
    windowEsterna->reloadMediaVisibili();
}
