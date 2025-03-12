#include "jsonHandler/jsonVisitor.h"
#include "logica/album.h"
#include "grafica/mainWindow.h"
#include <QApplication>
#include <QJsonDocument>

using namespace std;
int main(int argc, char *argv[])
{
    /*
       libro l1("aaaa","bbbb",2000,"path",1,100,898989,"Mondadori");
       album a("kkkk","llll",2010,"path1",1);

       canzone c1("ioio","yeye",2020,"path",1,188,"rapp");
       canzone c2("carr","bbro",2023,"path",2,199,"rapp");
       canzone c3("skkkrt","yeye",2020,"path",3,188,"rapp");
       a.addCanzone(&c1);
       a.addCanzone(&c2);
       a.addCanzone(&c3);

       cout<<a;
    jsonVisitor JsonVisitor; 

    list<media*> listaMedia;
    JsonVisitor.readAllLibri(listaMedia);

    JsonVisitor.readAllCanzoni(listaMedia);

    JsonVisitor.readAllAlbum(listaMedia);
    cout<<listaMedia.size();
    for(auto temp : listaMedia)
    {
        if(dynamic_cast<album*>(temp))
        {   
            auto a = dynamic_cast<album*>(temp);
            cout<<*a<<"\n";
        }
    }
       c1.accept(&JsonVisitor);
       c2.accept(&JsonVisitor);
       c3.accept(&JsonVisitor);
       a.accept(&JsonVisitor);
       */
    QApplication app(argc, argv);
    mainWindow window;
    window.show();
    return app.exec();
    return 0;
}
