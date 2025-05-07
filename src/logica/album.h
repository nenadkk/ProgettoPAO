#ifndef ALBUM 
#define ALBUM
#include "media.h"
#include "canzone.h"
#include <list>
#include <ostream>
#include <string>

//la classe album non implementa un distruttore per la delete degli oggetti puntati nella tracklist
//perché gli stssi oggetti canzone potrebbero essere puntati da più album

using namespace std;
class album : public media
{
    private:
        int durataTotale;
        list<canzone*> trackList; 

    public:

        album();
        album(const string&, const string&, const int&, const string&, const int&);//album vuoto 
        //costruttore di copia
        album(const string&, const string&, const int&, const string&, const int&, //per il sotto-oggetto MEDIA
              const list<canzone*>&); //trackList
        
        int getDurataTotale() const;
        int getNumCanzoni() const;

        bool contieneCanzone(int) const;//prende in input un id e restituisce true 
                                        //se la canzone è contenuta nell'album 

        void addCanzone(canzone*);
        void removeCanzone(int); //rimozione in base all'id

        virtual void accept(visitor *_visitor) override;

        friend std::ostream& operator << (std::ostream &o, const album&);
        canzone* operator[](size_t index);
        const canzone* operator[](size_t index) const;
};
#endif
