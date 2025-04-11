#ifndef EDITORALBUM
#define EDITORALBUM

#include "widgetEditorMedia.h"

class editorAlbum : public widgetEditorMedia
{
    private:
        QListWidget* trackList;

    protected:
        void crea() override;
        void modifica() override;
    public:
        editorAlbum(mediaManager*, QWidget* parent=nullptr, media* obj=nullptr);
};
#endif
