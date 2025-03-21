#ifndef CREATEMEDIAVISITOR
#define CREATEMEDIAVISITOR
#include "../logica/visitor.h"

#include <QGridLayout>
#include <QLineEdit>

class createMediaVisitor : public visitor
{
    private:
        QGridLayout *layoutEsterno;

        void creaSottoOggettoMedia(QWidget**, QLineEdit**);
        bool isImageFile(const QString &filePath) const;

    public:
        createMediaVisitor(QGridLayout*);

        virtual void visit(libro *_libro) override; 
        virtual void visit(canzone *_canzone) override; 
        virtual void visit(album *_album) override;
    
    private slots:
        void confermaSalvataggio();
        void annullaSalvataggio();
};

#endif
