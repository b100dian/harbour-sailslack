#ifndef SLACKSTREAM_H
#define SLACKSTREAM_H

#include <QObject>
#include <QJsonObject>
#include <QPointer>
#include <QUrl>
#include <QTimer>
#include <QAtomicInteger>
#include <QtWebSockets/QWebSocket>

class SlackStream : public QObject
{
    Q_OBJECT
public:
    explicit SlackStream(QObject *parent = 0);
    ~SlackStream();

signals:
    void connected();
    void reconnecting();
    void disconnected();
    void messageReceived(QJsonObject message);

public slots:
    void disconnectFromHost();
    void listen(QUrl url);
    void send(QJsonObject message);
    void checkConnection();
    void handleListerStart();
    void handleListerEnd();
    void handleMessage(QString message);
    void handleError(QAbstractSocket::SocketError error);
    void handleStateChanged(QAbstractSocket::SocketState state);
    void pong(quint64 elapsedTime, const QByteArray &payload);
private:
    QPointer<QWebSocket> webSocket;
    QPointer<QTimer> checkTimer;

    bool isConnected;
    bool helloReceived;
    QAtomicInteger<int> lastMessageId;
};

#endif // SLACKSTREAM_H
