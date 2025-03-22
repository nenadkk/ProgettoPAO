#include "grafica/mainWindow.h"
#include <QApplication>
#include <QJsonDocument>

using namespace std;
int main(int argc, char *argv[])
{
   QApplication app(argc, argv);
    mainWindow window;
    window.show();
    return app.exec();
    return 0;
}
