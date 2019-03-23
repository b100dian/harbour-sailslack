# NOTICE:
#
# Application name defined in TARGET has a corresponding QML filename.
# If name defined in TARGET is changed, the following needs to be done
# to match new name:
#   - corresponding QML filename must be changed
#   - desktop icon filename must be changed
#   - desktop filename must be changed
#   - icon definition filename in desktop file must be changed
#   - translation filenames have to be changed

# App config
TARGET = harbour-slackfish
CONFIG += sailfishapp
SAILFISHAPP_ICONS = 86x86 108x108 128x128 256x256

# Translations
CONFIG += sailfishapp_i18n
TRANSLATIONS += translations/harbour-slackfish-fi.ts

# Notifications
QT += dbus
PKGCONFIG += nemonotifications-qt5

# Includes
INCLUDEPATH += ./QtWebsocket

QT += concurrent

include(vendor/vendor.pri)

VERSION = "1.4.2"
DEFINES += APP_VERSION=\\\"$${VERSION}\\\"

# Check slack config
CLIENT_ID = $$slack_client_id
CLIENT_SECRET = $$slack_client_secret
if(isEmpty(CLIENT_ID)) {
    error("No client id defined")
}

if(isEmpty(CLIENT_SECRET)) {
    error("No client secret defined")
}
DEFINES += SLACK_CLIENT_ID=\\\"$${CLIENT_ID}\\\"
DEFINES += SLACK_CLIENT_SECRET=\\\"$${CLIENT_SECRET}\\\"

SOURCES += src/harbour-slackfish.cpp \
    src/slackclient.cpp \
    src/slackconfig.cpp \
    src/QtWebsocket/QWsSocket.cpp \
    src/QtWebsocket/QWsFrame.cpp \
    src/QtWebsocket/functions.cpp \
    src/QtWebsocket/QWsHandshake.cpp \
    src/networkaccessmanagerfactory.cpp \
    src/networkaccessmanager.cpp \
    src/slackstream.cpp \
    src/storage.cpp \
    src/messageformatter.cpp \
    src/notificationlistener.cpp \
    src/dbusadaptor.cpp \
    src/filemodel.cpp

OTHER_FILES += qml/harbour-slackfish.qml \
    qml/cover/CoverPage.qml \
    rpm/harbour-slackfish.changes.in \
    rpm/harbour-slackfish.spec \
    rpm/harbour-slackfish.yaml \
    translations/*.ts \
    harbour-slackfish.desktop \
    harbour-slackfish.png

HEADERS += \
    src/slackclient.h \
    src/slackconfig.h \
    src/QtWebsocket/QWsSocket.h \
    src/QtWebsocket/QWsFrame.h \
    src/QtWebsocket/functions.h \
    src/QtWebsocket/QWsHandshake.h \
    src/networkaccessmanagerfactory.h \
    src/networkaccessmanager.h \
    src/slackstream.h \
    src/storage.h \
    src/messageformatter.h \
    src/notificationlistener.h \
    src/dbusadaptor.h \
    src/filemodel.h

DISTFILES += \
    qml/pages/LoginPage.qml \
    qml/pages/Loader.qml \
    qml/pages/ChannelList.qml \
    qml/pages/ChannelList.js \
    qml/pages/Channel.qml \
    qml/pages/MessageListItem.qml \
    qml/pages/MessageInput.qml \
    qml/pages/Image.qml \
    qml/pages/ConnectionPanel.qml \
    qml/pages/ChannelListView.qml \
    qml/pages/MessageListView.qml \
    qml/pages/About.qml \
    qml/pages/RichTextLabel.qml \
    qml/pages/AttachmentFieldGrid.qml \
    qml/pages/Attachment.qml \
    qml/pages/Spacer.qml \
    qml/pages/ChannelSelect.qml \
    qml/pages/Channel.js \
    qml/pages/GroupLeaveDialog.qml \
    qml/pages/ChatSelect.qml \
    qml/dialogs/ImagePicker.qml \
    qml/pages/FileSend.qml \
    data/emoji.json

RESOURCES += \
    data.qrc
