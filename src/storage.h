#ifndef STORAGE_H
#define STORAGE_H

#include <QVariantMap>

class Storage
{
public:
    QVariantMap user(const QString &id);
    QVariantList users();
    void saveUser(QVariantMap user);

    QVariantMap channel(const QString &id);
    QVariantList channels();
    void saveChannel(QVariantMap channel);

    QVariantList channelMessages(const QString &channelId);
    bool channelMessagesExist(const QString &channelId);

    void prependChannelMessages(const QString &channelId, QVariantList messages);
    void appendChannelMessage(const QString &channelId, QVariantMap message);
    void clearChannelMessages();

    void appendThreadMessage(const QString &threadId, QVariantMap message);

    void clear();

protected:
    void setChannelMessages(const QString &channelId, QVariantList messages);

private:

    QVariantMap userMap;
    QVariantMap channelMap;
    QVariantMap channelMessageMap;
    QVariantMap threadMessageMap;
};

#endif // STORAGE_H
