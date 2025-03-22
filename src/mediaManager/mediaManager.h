#ifndef MEDIAMANAGER
#define MEDIAMANAGER
#include "../logica/canzone.h"
#include "../logica/album.h"
#include "../logica/libro.h"
class mediaManager
{
    private:
        list<media*> LM;
        static void rendiMaiuscolo(string&);

    public:
        void save() const;
        void load();

        void addMedia();
        void removeMedia();
        void editMedia();

        int size() const;

        list<media*> filtroSoloLibri() const;
        list<media*> filtroSoloCanzoni() const;
        list<media*> filtroSoloAlbum() const;

        list<media*> search(string) const;

        media* operator[](size_t index);
        const media* operator[](size_t index) const;
};
#endif
