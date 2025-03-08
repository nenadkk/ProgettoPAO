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
        int id;

    public:
        canzone(const string&, const string&, const int&, const string&, //per il sotto-oggetto MEDIA
                const int&, const string&, const int&); //durata genere id

        int getDurata() const;
        string getGenere() const;
        int getId() const;

        void setDurata(const int&);
        void setGenere(const string&);
        void setId(const int&);

        virtual void accept(visitor *_visitor) override;

        friend std::ostream& operator << (std::ostream &o, const canzone&);
};

#endif
