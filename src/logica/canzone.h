#ifndef CANZONE
#define CANZONE
#include "media.h"
#include <ostream>
#include <string>

class canzone: public media
{
    private:
        int durata; //in secondi
        string genere;

    public:
        canzone();
        canzone(const string&, const string&, const int&, const string&, const int&, //per il sotto-oggetto MEDIA
                const int&, const string&); //durata genere 

        int getDurata() const;
        string getGenere() const;

        void setDurata(const int&);
        void setGenere(const string&);

        virtual void accept(visitor *_visitor) override;

        friend std::ostream& operator << (std::ostream &o, const canzone&);
};

#endif
