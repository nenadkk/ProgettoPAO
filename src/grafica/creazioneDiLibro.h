#ifndef CREAZIONEDILIBRO
#define CREAZIONEDILIBRO

#include "widgetDiCreazione.h"

class creazioneDiLibro : public widgetDiCreazione
{
    protected:
        void crea() override;
    public:
        creazioneDiLibro(mediaManager*, QWidget* parent=nullptr);
};
#endif
