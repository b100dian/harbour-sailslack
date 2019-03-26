#include "storage.h"

#include <QDebug>

void Storage::saveUser(QVariantMap user) {
    userMap.insert(user.value("id").toString(), user);
}

QVariantMap Storage::user(QVariant id) {
    return userMap.value(id.toString()).toMap();
}

QVariantList Storage::users() {
    return userMap.values();
}

void Storage::saveChannel(QVariantMap channel) {
    channelMap.insert(channel.value("id").toString(), channel);
}

QVariantMap Storage::channel(QVariant id) {
    return channelMap.value(id.toString()).toMap();
}

QVariantList Storage::channels() {
    return channelMap.values();
}

QVariantList Storage::channelMessages(QVariant channelId) {
    return channelMessageMap.value(channelId.toString()).toList();
}

bool Storage::channelMessagesExist(QVariant channelId) {
    return channelMessageMap.contains(channelId.toString());
}

void Storage::setChannelMessages(QVariant channelId, QVariantList messages) {
    channelMessageMap.insert(channelId.toString(), messages);
}

void Storage::prependChannelMessages(QVariant channelId, QVariantList messages) {
    QVariantList existing = channelMessages(channelId);
    messages.append(existing);
    setChannelMessages(channelId, messages);
}

void Storage::appendChannelMessage(QVariant channelId, QVariantMap message) {
    QVariantList messages = channelMessages(channelId);
    messages.append(message);
    setChannelMessages(channelId, messages);
}

void Storage::clearChannelMessages() {
    channelMessageMap.clear();
}

void Storage::clear() {
    userMap.clear();
    channelMap.clear();
    channelMessageMap.clear();
}
