#include "creazioneDiAlbum.h"
#include "widgetDiCreazione.h"
#include <QLabel>

creazioneDiAlbum::creazioneDiAlbum(mediaManager* man, QWidget* parent) : widgetDiCreazione(man,parent), trackList(nullptr)
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
    QObject::connect(btnSalva, &QPushButton::clicked, this, &creazioneDiAlbum::crea);
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
        canzone *c = dynamic_cast<canzone*>(m);

        QString str = QString::fromStdString(c->getTitolo()) + "   " + toQString(c->getAutore()+ "   "  );
        str +=QString::number((c->getDurata())/60 ) + ":" + QString::number((c->getDurata())%60);
        QListWidgetItem *item = new QListWidgetItem(str, trackList);
        item->setData(Qt::UserRole, c->getId()); // Assegna l'ID all'elemento

        
        item->setFont(QFont("Mono",20));
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

void creazioneDiAlbum::crea()
{    
    if(!validaInput())
        return;

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
            if(c && dynamic_cast<canzone*>(c))
            {
                newAlbum->addCanzone(dynamic_cast<canzone*>(c));
            }
        }
    }

    manager->addMedia(newAlbum);
    windowEsterna->reloadMediaVisibili();


}
