#include "editorAlbum.h"
#include "../logica/album.h"
#include <QLabel>

editorAlbum::editorAlbum(mediaManager* man, mainWindow* mw, media* obj) : 
    widgetEditorMedia(man, mw, obj), trackList(nullptr)
{
    //---------- PARTE SINISTRA ----------
    trackList = new QListWidget();

    QVBoxLayout *layoutSinistra = new QVBoxLayout();    
    layoutSinistra->setAlignment(Qt::AlignCenter);

    //---------- PULSANTI ----------
    QWidget *widgetPulsanti = new QWidget();
    QHBoxLayout *layoutSinistraPulsanti = new QHBoxLayout(widgetPulsanti);

    //---------- PULSANTE ANNULLA ----------
    QPushButton *btnAnnulla = new QPushButton("ANNULLA",widgetPulsanti);
    btnAnnulla->setFixedSize(200,50);
    btnAnnulla->setFont(QFont("Mono",15));
    QObject::connect(btnAnnulla, &QPushButton::clicked, windowEsterna, &mainWindow::reloadMediaVisibili);
    layoutSinistraPulsanti->addWidget(btnAnnulla,0, Qt::AlignLeft);

    //---------- PULSANTE SALVA ----------
    QPushButton *btnSalva = new QPushButton("SALVA",widgetPulsanti);
    btnSalva->setFixedSize(200,50);
    btnSalva->setFont(QFont("Mono",15));
    if(object)
        QObject::connect(btnSalva, &QPushButton::clicked, this, &editorAlbum::modifica);
    else
        QObject::connect(btnSalva, &QPushButton::clicked, this, &editorAlbum::crea);

    layoutSinistraPulsanti->addWidget(btnSalva,0, Qt::AlignRight);

    //---------------------------------------------------
    layoutSinistra->addWidget(widgetBase[0]);
    layoutSinistra->addWidget(widgetBase[1]);
    layoutSinistra->addWidget(widgetBase[2]);
    layoutSinistra->addWidget(widgetBase[3]);
    layoutSinistra->addWidget(widgetPulsanti);


            //---------- PARTE DESTRA ----------
            
    for (const auto m : manager->filtroSoloCanzoni()) 
    {
        const canzone *c = dynamic_cast<const canzone*>(m);

        QString str = QString::fromStdString(c->getTitolo()) + "   " + toQString(c->getAutore()+ "   "  );
        str +=QString::number((c->getDurata())/60 ) + ":" + QString::number((c->getDurata())%60);
        QListWidgetItem *item = new QListWidgetItem(str, trackList);

        
        item->setData(Qt::UserRole, c->getId()); // Assegna l'ID all'elemento
        
        item->setFont(QFont("Mono",20));

        if(object)
        {
            if(dynamic_cast<album*>(object)->contieneCanzone(c->getId()))
                item->setCheckState(Qt::Checked);
            else
                item->setCheckState(Qt::Unchecked);
        }
        else
            item->setCheckState(Qt::Unchecked);
    }

    trackList->setStyleSheet(
            "QListWidget::item {"
            "    border-radius: 5px;"
            "    margin: 5px;"
            "    padding: 5px;"
            "    background-color: #323232;"
            "}"
            "QListWidget::item:selected {background-color: #595959;}"
            );

    
    QHBoxLayout *layout = new QHBoxLayout();    
    layout->addLayout(layoutSinistra);
    layout->addWidget(trackList);

    this->setLayout(layout);  
}

void editorAlbum::crea()
{    
    if(!validaInput())
        return;

    copiaImmagine();
    //creazione album
    album *newAlbum = new album(attributi["titolo"]->text().toStdString(),
            attributi["autore"]->text().toStdString(),
            attributi["anno"]->text().toInt(),
            attributi["copertina"]->text().toStdString(),
            manager->trovaIdLibero());

    //aggiunta canzoni ad album
    for(int i=0; i<trackList->count();++i)
    {
        QListWidgetItem *item = trackList->item(i);

        if (item->checkState() == Qt::Checked) 
        {
            int trackID = item->data(Qt::UserRole).toInt();
            media* c = manager->searchById(trackID);

            if(c)
                newAlbum->addCanzone(dynamic_cast<canzone*>(c));
        }
    }

    manager->addMedia(newAlbum);
    windowEsterna->reloadMediaVisibili();

}

void editorAlbum::modifica()
{
    object->setTitolo(attributi["titolo"]->text().toStdString());
    object->setAutore(attributi["autore"]->text().toStdString());
    object->setAnno(attributi["anno"]->text().toInt());

    string copertina=attributi["copertina"]->text().toStdString();
    if(copertina!=object->getCopertina())
        copiaImmagine();
    object->setCopertina(copertina);

    album* _album = dynamic_cast<album*>(object);
    //svuoto l'album
    while(_album->getNumCanzoni()!=0)
    {
        _album->removeCanzone((*_album)[0]->getId());
    }
    //ripopolo l'album
    for(int i=0; i<trackList->count();++i)
    {
        QListWidgetItem *item = trackList->item(i);

        if (item->checkState() == Qt::Checked) 
        {
            int trackID = item->data(Qt::UserRole).toInt();
            media* c = manager->searchById(trackID);

            if(c)
                _album->addCanzone(dynamic_cast<canzone*>(c));
        }
    }

    manager->saveAll();
    windowEsterna->reloadMediaVisibili();
}
