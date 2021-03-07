#include "networkaccessmanagerfactory.h"

#include <QDebug>
#include <QObject>

#include "networkaccessmanager.h"

void configurationChanged(QNetworkConfiguration& configuration) {
    qDebug() << "Valid:" << configuration.isValid() << "State:" << configuration.state();

}

NetworkAccessManagerFactory::NetworkAccessManagerFactory() noexcept
    : session(nullptr)
{
    qDebug() << "Capabilities: " << configManager.capabilities();

    connect(&configManager, SIGNAL(configurationAdded(const QNetworkConfiguration &)), this, (SLOT(configurationAdded(const QNetworkConfiguration &))));
    connect(&configManager, SIGNAL(configurationChanged(const QNetworkConfiguration &)), this, (SLOT(configurationChanged(const QNetworkConfiguration &))));
    connect(&configManager, SIGNAL(configurationRemoved(const QNetworkConfiguration &)), this, (SLOT(configurationRemoved(const QNetworkConfiguration &))));

    auto configuration = configManager.defaultConfiguration();
    qDebug() << "Config is valid:" << configuration.isValid() << "State:" << configuration.state() << " roamingAvailable:" << configuration.isRoamingAvailable();
    session = new QNetworkSession(configuration, nullptr);

    connect(session, SIGNAL(preferredConfigurationChanged(const QNetworkConfiguration&, bool)), this, SLOT(preferredConfigurationChanged(const QNetworkConfiguration&, bool)));
    connect(session, SIGNAL(stateChanged(QNetworkSession::State)), this, SLOT(stateChanged(QNetworkSession::State)));
    connect(session, SIGNAL(error(QNetworkSession::SessionError)), this, SLOT(sessionError(QNetworkSession::SessionError)));
//    session->open();
//    auto activeConfig = session->configuration();
//    qDebug() << "active networkConfiguration " << activeConfig.identifier();
//    if (!session->waitForOpened(5000)) {
//        qDebug() << "Session open error: " << session->error();
//    }
}

NetworkAccessManagerFactory::~NetworkAccessManagerFactory() {
    qDebug();
}

void NetworkAccessManagerFactory::preferredConfigurationChanged(const QNetworkConfiguration &configuration, bool isSeamless) {
    qDebug() << "New Cfg is valid:" << configuration.isValid() << "State:" << configuration.state() << " isSeamless:" << isSeamless;
}

void NetworkAccessManagerFactory::stateChanged(QNetworkSession::State state) {
    qDebug() << state;
}

void NetworkAccessManagerFactory::sessionError(QNetworkSession::SessionError error) {
    qDebug() << error << " as string: " << session->errorString();
}

void NetworkAccessManagerFactory::configurationAdded(const QNetworkConfiguration &config) {
    qDebug() << config.name() << " " << config.identifier() << " " << config.bearerType() << " " << config.bearerTypeName() << " " << config.bearerTypeFamily();
}

void NetworkAccessManagerFactory::configurationChanged(const QNetworkConfiguration &config) {
//    qDebug() << config.name() << " " << config.identifier() << " " << config.bearerType() << " " << config.bearerTypeName() << " " << config.bearerTypeFamily();
}

void NetworkAccessManagerFactory::configurationRemoved(const QNetworkConfiguration &config) {
    qDebug() << config.name() << " " << config.identifier() << " " << config.bearerType() << " " << config.bearerTypeName() << " " << config.bearerTypeFamily();
}

void NetworkAccessManagerFactory::newConfigurationActivated() {
    qDebug();
}


QNetworkAccessManager *NetworkAccessManagerFactory::create(QObject *parent)
{
    NetworkAccessManager *manager = new NetworkAccessManager(parent);
    managers.append(manager);
    return manager;
}
