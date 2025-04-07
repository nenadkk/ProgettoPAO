#ifndef LIBRO
#define LIBRO
#include "media.h"
#include <ostream>

class libro: public media
{
    private:
        int numPagine;
        int isbn;
        string editore;
    
    public:
        libro();
        libro(const string&, const string&, const int&, const string&, const int&, //per il sotto-oggetto MEDIA
              const int&, const int&, const string&); //numpagine isbn editore

        int getNumPagine() const;
        int getIsbn() const;
        string getEditore() const;

        void setNumPagine(const int&);
        void setIsbn(const int&);
        void setEditore(const string&);

        virtual void accept(visitor *_visitor) override;

        friend std::ostream& operator << (std::ostream &o, const libro&);
};
#endif
