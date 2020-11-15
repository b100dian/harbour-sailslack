#include "storage.h"

#include <QDebug>
#include <QSequentialIterable>

void Storage::saveUser(QVariantMap user) {
    userMap.insert(user.value("id").toString(), user);
}

QVariantMap Storage::user(const QString &id) {
    return userMap.value(id).toMap();
}

QVariantList Storage::users() {
    return userMap.values();
}

void Storage::saveChannel(QVariantMap channel) {
    channelMap.insert(channel.value("id").toString(), channel);
}

QVariantMap Storage::channel(const QString &id) {
    return channelMap.value(id).toMap();
}

QVariantList Storage::channels() {
    return channelMap.values();
}

QVariantList Storage::channelMessages(const QString &channelId) {
    return channelMessageMap.value(channelId).toList();
}

bool Storage::channelMessagesExist(const QString &channelId) {
    return channelMessageMap.contains(channelId);
}

void Storage::setChannelMessages(const QString &channelId, QVariantList messages) {
    channelMessageMap.insert(channelId, messages); // FIXME
}

void Storage::prependChannelMessages(const QString &channelId, QVariantList messages) {
    // TODO check for thread messages
    QVariantList existing = channelMessages(channelId);
    messages.append(existing);
    setChannelMessages(channelId, messages);
}

QString messageThread(const QVariantMap& message) {
    return message.contains("thread_ts")
            ? message.value("thread_ts").toString()
            : QString();
}

bool isThreadStarter(const QVariantMap& message) {
    return message.value("thread_ts") == message.value("timestamp");
}

void Storage::appendChannelMessage(const QString &channelId, QVariantMap message) {
    QVariantList messages = channelMessages(channelId);
    auto thread = messageThread(message);
    if (thread.isEmpty() || isThreadStarter(message)) {
        messages.append(message);
        setChannelMessages(channelId, messages);
    }
    if (!thread.isEmpty()) {
        appendThreadMessage(thread, message);
    }
}

void Storage::clearChannelMessages() {
    channelMessageMap.clear();
}

void Storage::appendThreadMessage(const QString &threadId, QVariantMap message) {
    if(isThreadStarter(message)) {
        if (!threadMessageMap.contains(threadId)) {
            threadMessageMap.insert(threadId, QVariantList({message}));
        } else {
            qDebug() << "Thread already exists:" << threadId;
        }
    }

    auto messages = threadMessageMap.value(threadId).toList();
    if (messages.size()) {
        if (isThreadStarter(message)) {
            // TODO replace in channel
            qDebug() << "Updated thread starter for:" << threadId;
        } else {
            messages.push_back(message);
        }
    } else {
        qDebug("Thread without thread starter?");
        Q_ASSERT(false);
        return;
    }

    // Update replies count
    auto threadStarter = messages.first().toMap();
    threadStarter.insert("thread_replies", messages.size() - 1);

    threadMessageMap.insert(threadId, messages);
}

void Storage::clear() {
    userMap.clear();
    channelMap.clear();
    channelMessageMap.clear();
    threadMessageMap.clear();
}
