#include "jsonHandler/writeJsonVisitor.h"
#include "logica/album.h"
#include "logica/libro.h"
#include <QJsonDocument>

using namespace std;
int main()
{
    libro l1("aaaa","bbbb",2000,"path",100,898989,"Mondadori");
    album a("kkkk","llll",2010,"path1");

    canzone c1("ioio","yeye",2020,"path",188,"rapp",1);
    canzone c2("carr","bbro",2023,"path",199,"rapp",2);
    canzone c3("skkkrt","yeye",2020,"path",188,"rapp",3);
    a.addCanzone(&c1);
    a.addCanzone(&c2);
    a.addCanzone(&c3);

    cout<<a;

    writeJsonVisitor JsonVisitor; 
    
    l1.accept(&JsonVisitor);

    return 0;
}
