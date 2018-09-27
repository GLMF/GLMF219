
#include <QtDebug>
#include <QtCore/QCoreApplication>
#include <QtWebSockets/QWebSocketServer>
#include <QtWebSockets/QWebSocket>
#include <QtPlugin>

#include <unordered_set>

int main(int argc, char *argv[])
{
   QCoreApplication a(argc, argv);
   std::unordered_set<QWebSocket*> clients;

   QWebSocketServer server(QStringLiteral("server"),
                           QWebSocketServer::NonSecureMode,
                           &a);

   QObject::connect(
            &server, &QWebSocketServer::closed,
            [&]()
   {
      for(QWebSocket* client: clients)
         client->deleteLater();
   });

   QObject::connect(
            &server, &QWebSocketServer::newConnection,
            [&]()
   {
      QWebSocket* client = server.nextPendingConnection();
      while ( client != nullptr )
      {
         qDebug() << "New client from" << client->peerName() << client->peerAddress();
         clients.insert(client);
         QObject::connect(
                  client, &QWebSocket::binaryMessageReceived,
                  [&,client](QByteArray ba)
         {
            qDebug() << "Received binary from" << client->peerName() << client->peerAddress();
            QString const source = QString::fromUtf8(ba);
            QString const upper = source.toUpper();
            client->sendBinaryMessage(upper.toUtf8());
         });

         QObject::connect(
                  client, &QWebSocket::disconnected,
                  [&,client]()
         {
            qDebug() << "Lost client" << client->peerName() << client->peerAddress();
            clients.erase(client);
            client->deleteLater();
         });

         client = server.nextPendingConnection();
      }
   });

   server.listen(QHostAddress::Any, 7474);

   return a.exec();
}
