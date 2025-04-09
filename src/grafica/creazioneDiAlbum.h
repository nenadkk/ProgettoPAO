#ifndef CREAZIONEDIALBUM
#define CREAZIONEDIALBUM

#include "widgetDiCreazione.h"

class creazioneDiAlbum : public widgetDiCreazione
{
    private:
        QListWidget* trackList;

    protected:
        void crea() override;
    public:
        creazioneDiAlbum(mediaManager*, QWidget* parent=nullptr);
};
#endif
