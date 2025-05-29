#include <QFileInfo>
#include <QMessageBox>
#include <QFileDialog>
#include <QLabel>
#include "widgetEditorMedia.h"
#include "qglobal.h"

widgetEditorMedia::widgetEditorMedia(mediaManager* man, mainWindow* mw, media* obj) : 
    manager(man), windowEsterna(mw), object(obj)
{
    //---------- TITOLO ----------
    widgetBase[0] = new QWidget();
    widgetBase[0]->setFixedWidth(350);

    QLabel *lableTitolo = new QLabel("Titolo: ");
    lableTitolo->setFont(QFont("Mono",14));
    lableTitolo->setFixedSize(120,30);

    this->insertLineEdit("titolo",new QLineEdit());
    (*this)["titolo"]->setFont(QFont("Mono",14));
    (*this)["titolo"]->setFixedSize(200,30);
    
    if(object)
        (*this)["titolo"]->setText(QString::fromStdString(object->getTitolo()));

    QHBoxLayout *layoutTitolo = new QHBoxLayout(widgetBase[0]);
    layoutTitolo->setContentsMargins(0,0,0,0);
    layoutTitolo->setSpacing(0);
    layoutTitolo->addWidget(lableTitolo,0,Qt::AlignRight);
    layoutTitolo->addWidget((*this)["titolo"],0, Qt::AlignLeft);

    //---------- AUTORE ----------
    widgetBase[1] = new QWidget();
    widgetBase[1]->setFixedWidth(350);
   
    QLabel *lableAutore = new QLabel("Autore: ");
    lableAutore->setFont(QFont("Mono",14));
    lableAutore->setFixedSize(120,30);

    this->insertLineEdit("autore",new QLineEdit());
    (*this)["autore"]->setFont(QFont("Mono",14));
    (*this)["autore"]->setFixedSize(200,30);    

    if(object)
        (*this)["autore"]->setText(QString::fromStdString(object->getAutore()));

    QHBoxLayout *layoutAutore = new QHBoxLayout(widgetBase[1]);
    layoutAutore->setContentsMargins(0,0,0,0);
    layoutAutore->setSpacing(0);
    layoutAutore->addWidget(lableAutore,0,Qt::AlignRight);
    layoutAutore->addWidget((*this)["autore"],0, Qt::AlignLeft);

    //---------- ANNO ----------
    widgetBase[2] = new QWidget();
    widgetBase[2]->setFixedWidth(350);

    QLabel *lableAnno = new QLabel("Anno: ");
    lableAnno->setFont(QFont("Mono",14));
    lableAnno->setFixedSize(120,30);

    this->insertLineEdit("anno",new QLineEdit());
    (*this)["anno"]->setFont(QFont("Mono",14));
    (*this)["anno"]->setFixedSize(200,30);
    QIntValidator *validatorAnno = new QIntValidator((*this)["anno"]);
    (*this)["anno"]->setValidator(validatorAnno);

    if(object)
        (*this)["anno"]->setText(QString::number(object->getAnno()));

    QHBoxLayout *layoutAnno = new QHBoxLayout(widgetBase[2]);
    layoutAnno->setContentsMargins(0,0,0,0);
    layoutAnno->setSpacing(0);
    layoutAnno->addWidget(lableAnno,0,Qt::AlignRight);
    layoutAnno->addWidget((*this)["anno"],0, Qt::AlignLeft);

    //---------- COPERTINA ----------
    widgetBase[3] = new QWidget();
 
    QLabel *lableCopertina = new QLabel("Copertina: ");
    lableCopertina->setFont(QFont("Mono",14));
    lableCopertina->setFixedSize(120,30);

    this->insertLineEdit("copertina",new QLineEdit());
    (*this)["copertina"]->setFont(QFont("Mono",14));
    (*this)["copertina"]->setFixedSize(200,30);

    if(object)
        (*this)["copertina"]->setText(QString::fromStdString(object->getCopertina()));

    QHBoxLayout *layoutCopertina = new QHBoxLayout(widgetBase[3]);
    
    QPushButton* btnSfoglia = new QPushButton("Sfoglia");
    btnSfoglia->setFixedSize(120,30);
    btnSfoglia->setFont(QFont("Mono",15));
    QObject::connect(btnSfoglia, &QPushButton::clicked, this, &widgetEditorMedia::browseImage);

    layoutCopertina->setContentsMargins(0,0,0,0);
    layoutCopertina->setSpacing(0);
    layoutCopertina->addWidget(lableCopertina,0,Qt::AlignRight);
    layoutCopertina->addWidget((*this)["copertina"],0, Qt::AlignLeft);
    layoutCopertina->addWidget(btnSfoglia, 0, Qt::AlignLeft);
}

QLineEdit*& widgetEditorMedia::operator[](const QString& key) 
{
    return attributi[key];
}

void  widgetEditorMedia::insertLineEdit(QString str,QLineEdit* n)
{
    attributi.insert(str,n);
}

bool widgetEditorMedia::validaInput()
{
    foreach(auto val, attributi.values())
    {
        if(val->text().isEmpty())
        {
            QMessageBox::warning(this, "Validazione", "Dati non validi o nulli. Compilare ogni campo con valori significativi.");
            return false;
        }
    }
    return true;
}

void widgetEditorMedia::copiaImmagine() 
{
    QFileInfo infoImmagine(attributi["copertina"]->text());
    if (!infoImmagine.exists()) {
        qDebug() << "L'immagine sorgente non esiste.";
        return;
    }

    QString folderImmagine = infoImmagine.absolutePath();
    QString targetFolder = QDir::currentPath() + QString("/immagini");

    //se l'immagine è stata selezionata nella cartella /immagini dell'applicazione
    if(folderImmagine.startsWith(targetFolder))
    {
        QString pathDestinazione = "./immagini/" + infoImmagine.fileName();
        attributi["copertina"]->setText(pathDestinazione);

    }
    else //altrimenti
    {
        //se esiste già un file con lo stesso nome
        if(QFileInfo("./immagini/" + infoImmagine.fileName()).exists())
        {
            //controllo e prendo il primo nome libero
            int N=1;
            while(QFileInfo("./immagini/" + infoImmagine.baseName() +
                            "("+ QString::number(N)+")." + 
                            infoImmagine.completeSuffix()).exists())
            {
                N++;
            }

            //copio il file e aggiorno l'attributo
            QString pathDestinazione = "./immagini/" + infoImmagine.baseName() +
                                       "("+ QString::number(N)+")." + 
                                       infoImmagine.completeSuffix();

            if(!QFile::copy(attributi["copertina"]->text(), pathDestinazione))
            {
                qDebug()<<"Errore durante la copia dell'immagine.";
                return;
            }
            attributi["copertina"]->setText(pathDestinazione);

        }
        else //se invece non esistono altri file con lo stesso nome 
        { 
            QString pathDestinazione = "./immagini/" + infoImmagine.fileName();

            if(!QFile::copy(attributi["copertina"]->text(), pathDestinazione))
            {
                qDebug()<<"Errore durante la copia dell'immagine.";
                return;
            }
            attributi["copertina"]->setText(pathDestinazione);

        }
    }
}

void widgetEditorMedia::browseImage()
{
    if(attributi["copertina"])
    {
        QString dirIniziale = QDir::currentPath() + QString("/immagini/");
        QString filePath = QFileDialog::getOpenFileName(this, "Seleziona un'immagine", dirIniziale, "Immagini (*.png *.jpg *.jpeg *.bmp *.gif)");
        if (!filePath.isEmpty() && isImageFile(filePath))    
            attributi["copertina"]->setText(filePath);       
    }
}

bool widgetEditorMedia::isImageFile(const QString &filePath) const 
{
    QFileInfo fileInfo(filePath);
    QString ext = fileInfo.suffix().toLower();
    return (ext == "png" || ext == "jpg" || ext == "jpeg" || ext == "jpeg" || ext == "bmp" || ext == "gif");
}










