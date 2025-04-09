#ifndef CREAZIONEDIALBUM
#define CREAZIONEDIALBUM

#include "widgetDiCreazione.h"

class creazioneDiAlbum : public widgetDiCreazione
{
    protected:
        void crea() override;
        QListWidget* trackList;
    public:
        creazioneDiAlbum(mediaManager*, QWidget* parent=nullptr);
};
#endif
