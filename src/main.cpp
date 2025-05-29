#include "grafica/mainWindow.h"
#include <QApplication>
#include <QJsonDocument>

using namespace std;
int main(int argc, char *argv[])
{
    qputenv("QT_QPA_PLATFORM", "xcb;windows:darkmode=1");//per evitare warning dell'ambiente grafico
    QApplication app(argc, argv);
    mainWindow window;
    window.show();
    return app.exec();
    return 0;
}
