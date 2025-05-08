#ifndef SEARCHVISITOR
#define SEARCHVISITOR
#include "../logica/visitor.h"
#include "../logica/libro.h"
#include "../logica/canzone.h"
#include "../logica/album.h"
#include <list>
#include <string>
using std::list;
using std::string;

class searchVisitor : public visitor
{
    private:
        string strDaCercare; 
        list<int> *idRisultati;
        static void rendiMaiuscolo(string&);
        bool ricercaAttributiStandard(media*);

    public:
        searchVisitor(string, list<int>*);
        ~searchVisitor();

        virtual void visit(libro *_libro) override; 
        virtual void visit(canzone *_canzone) override; 
        virtual void visit(album *_album) override; 

};

#endif
