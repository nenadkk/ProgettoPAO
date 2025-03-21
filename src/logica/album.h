#ifndef ALBUM 
#define ALBUM
#include "media.h"
#include "canzone.h"
#include <list>
#include <ostream>
#include <string>

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

        void addCanzone(canzone*);

        virtual void accept(visitor *_visitor) override;

        friend std::ostream& operator << (std::ostream &o, const album&);
        canzone* operator[](size_t index);
        const canzone* operator[](size_t index) const;
};
#endif
