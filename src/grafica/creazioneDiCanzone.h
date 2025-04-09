#ifndef CREAZIONEDICANZONE
#define CREAZIONEDICANZONE

#include "widgetDiCreazione.h"

class creazioneDiCanzone : public widgetDiCreazione
{
    protected:
        void crea() override;
    public:
        creazioneDiCanzone(mediaManager*, QWidget* parent=nullptr);
};
#endif
