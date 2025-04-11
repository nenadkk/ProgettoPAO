#ifndef EDITORCANZONE
#define EDITORCANZONE

#include "widgetEditorMedia.h"

class editorCanzone : public widgetEditorMedia
{
    protected:
        void crea() override;
        void modifica() override;
    public:
        editorCanzone(mediaManager*, QWidget* parent=nullptr, media* obj=nullptr);
};
#endif
