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
        void save() const;
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

        void rimuoviDaAlbum(int); //rimuove un canzone dagli album;
                                  //questo metodo viene richiamato nel distruttore 
                                  //delle canzoni per assicurarsi che nessun album
                                  //punti a quella canzone prima che venga distrutta

        media* operator[](size_t index);
        const media* operator[](size_t index) const;
};
#endif
