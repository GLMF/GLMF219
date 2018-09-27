
#include "main_win.h"

#include <QtDebug>
#include <QtWidgets/QApplication>
#include <QtWebSockets/QWebSocket>
#include <QtCore/QProcessEnvironment>

#include <cstdlib>

int main(int argc, char *argv[])
{
   QApplication app(argc, argv);

   Main_Win main_win;
   main_win.showMaximized();
   main_win.show();

   QWebSocket web_socket(QString(), QWebSocketProtocol::VersionLatest, &app);
   QObject::connect(
            &web_socket, &QWebSocket::connected,
            [&]()
   {
      qDebug() << "connected";
      QObject::connect(
               &main_win, &Main_Win::stringGiven,
               [&](QString const& s)
      {
         web_socket.sendBinaryMessage(s.toUtf8());
      });
      QObject::connect(
               &web_socket, &QWebSocket::binaryMessageReceived,
               [&](QByteArray ba)
      {
         QString const s = QString::fromUtf8(ba);
         main_win.appendString(s);
      });
      QObject::connect(
               &web_socket, &QWebSocket::disconnected,
               [&]()
      {
         qDebug() << "disconnected";
         app.quit();
      });
   });

   QString server = std::getenv("SERVER");
   if ( server.isEmpty() )
      server = "localhost";
   qDebug() << "Server =" << server;
   QString const server_url = QStringLiteral("ws://%1:7474").arg(server);
   qDebug() << "Connecting to" << server_url;
   web_socket.open(QUrl(server_url));

   return app.exec();
}
