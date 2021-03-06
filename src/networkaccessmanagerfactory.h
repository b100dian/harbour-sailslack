#ifndef NETWORKACCESSMANAGERFACTORY_H
#define NETWORKACCESSMANAGERFACTORY_H

#include <QQmlNetworkAccessManagerFactory>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkConfigurationManager>
#include <QtNetwork/QNetworkSession>
#include <QPointer>

class NetworkAccessManagerFactory : public QObject, public QQmlNetworkAccessManagerFactory
{
    Q_OBJECT

    QNetworkConfigurationManager configManager;
    QPointer<QNetworkSession> session;

    QList<QPointer<QNetworkAccessManager>> managers;
public slots:
    void preferredConfigurationChanged(const QNetworkConfiguration &configuration, bool isSeamless);
    void stateChanged(QNetworkSession::State state);
    void sessionError(QNetworkSession::SessionError error);
    void newConfigurationActivated();
    void configurationAdded(const QNetworkConfiguration &config);
    void configurationChanged(const QNetworkConfiguration &config);
    void configurationRemoved(const QNetworkConfiguration &config);
public:
    NetworkAccessManagerFactory() noexcept;
    virtual QNetworkAccessManager *create(QObject *parent);
    virtual ~NetworkAccessManagerFactory();

};

#endif // NETWORKACCESSMANAGERFACTORY_H
