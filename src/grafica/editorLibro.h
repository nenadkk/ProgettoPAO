#ifndef EDITORLIBRO
#define EDITORLIBRO

#include "widgetEditorMedia.h"

class editorLibro : public widgetEditorMedia
{
    protected:
        void crea() override;
        void modifica() override;
    public:
        editorLibro(mediaManager*, QWidget* parent=nullptr, media* obj=nullptr);
};
#endif
