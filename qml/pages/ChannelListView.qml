import QtQuick 2.0
import Sailfish.Silica 1.0
import harbour.slackfish 1.0 as Slack

import "ChannelList.js" as ChannelList
import "Channel.js" as Channel

SilicaListView {
    id: listView
    spacing: Theme.paddingMedium

    VerticalScrollDecorator {}

    header: PageHeader {
        title: Slack.Client.config.teamName
    }

    model: ListModel {
        id: channelListModel
    }

    section {
        property: "section"
        criteria: ViewSection.FullString
        delegate: SectionHeader {
            text: getSectionName(section)
        }
    }

    delegate: ListItem {
        id: delegate
        contentHeight: row.height + Theme.paddingLarge
        property color infoColor: delegate.highlighted ? Theme.secondaryHighlightColor : Theme.secondaryColor
        property color textColor: delegate.highlighted ? Theme.highlightColor : Theme.primaryColor
        property color currentColor: model.unreadCount > 0 ? textColor : infoColor

        Row {
            id: row
            width: parent.width - Theme.paddingLarge * (Screen.sizeCategory >= Screen.Large ? 4 : 2)
            anchors.verticalCenter: parent.verticalCenter
            x: Theme.paddingLarge * (Screen.sizeCategory >= Screen.Large ? 2 : 1)
            spacing: Theme.paddingMedium

            Image {
                id: icon
                source: "image://theme/" + Channel.getIcon(model) + "?" + (delegate.highlighted ? currentColor : Channel.getIconColor(model, currentColor))
                anchors.verticalCenter: parent.verticalCenter
            }

            Label {
                width: parent.width - icon.width - Theme.paddingMedium
                wrapMode: Text.Wrap
                anchors.verticalCenter: parent.verticalCenter
                font.pixelSize: Theme.fontSizeMedium
                font.bold: model.unreadCount > 0
                text: model.name
                color: currentColor
            }
        }

        onClicked: {
            pageStack.push(Qt.resolvedUrl("Channel.qml"), {"channelId": model.id})
        }

        menu: ContextMenu {
            hasContent: model.category === "channel" || model.type === "im"

            MenuItem {
                text: model.category === "channel" ? qsTr("Leave") : qsTr("Close")
                onClicked: {
                    switch (model.type) {
                        case "channel":
                            Slack.Client.leaveChannel(model.id)
                            break

                        case "group":
                            var dialog = pageStack.push(Qt.resolvedUrl("GroupLeaveDialog.qml"), {"name": model.name})
                            dialog.accepted.connect(function() {
                                Slack.Client.leaveGroup(model.id)
                            })
                            break

                        case "im":
                            Slack.Client.closeChat(model.id)
                    }
                }
            }
        }
    }

    Component.onCompleted: {
        ChannelList.init()
    }

    Component.onDestruction: {
        ChannelList.disconnect()
    }

    function getSectionName(section) {
        switch (section) {
            case "unread":
                return qsTr("Unreads")

            case "channel":
                return qsTr("Channels")

            case "chat":
                return qsTr("Direct messages")
        }
    }
}
