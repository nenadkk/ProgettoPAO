#ifndef MEDIAMANAGER
#define MEDIAMANAGER
#include "../logica/media.h"
#include <list>

class mediaManager
{
    private:
        list<media*> LM;

    public:
        static unordered_map<string, string> save_file;

        mediaManager();
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

        static void loadFileDiSalvataggio();
};
#endif
