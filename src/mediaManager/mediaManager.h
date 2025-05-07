#ifndef MEDIAMANAGER
#define MEDIAMANAGER
#include "../logica/canzone.h"
#include "../logica/album.h"
#include "../logica/libro.h"

class mediaManager
{
    private:
        list<media*> LM;

    public:
        ~mediaManager();
        void saveAll() const;
        void load();

        void addMedia(media*);
        void removeMedia(int);// rimuove in base all'id

        int trovaIdLibero() const;
        media* searchById(int) const;

        int size() const;

        list<media*> filtroSoloLibri() const;
        list<media*> filtroSoloCanzoni() const;
        list<media*> filtroSoloAlbum() const;

        list<media*> search(string) const; 

        media* operator[](size_t index);
        const media* operator[](size_t index) const;
};
#endif
