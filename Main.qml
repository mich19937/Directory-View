import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Window {
    width: 640
    height: 480
    visible: true
    title: "Directory View"

    TextField {
        id: dirPathTextField
        anchors.top: parent.top
        width: parent.width
        focus: true
        placeholderText: "Directory path"
        onTextChanged: controller.dirPath = text
    }

    Loader {
        sourceComponent: controller.isDirPathValid ? dirTableComponent : pathInvalidTextComponent
        anchors.top: dirPathTextField.bottom
        anchors.bottom: parent.bottom
        width: parent.width
        Component {
            id: pathInvalidTextComponent
            Item {
                Text {
                    text: "Path is invalid."
                    anchors.centerIn: parent
                    font.pointSize: 16
                    color: "red"
                }
            }
        }
        Component {
            id: dirTableComponent
            Item {
                anchors.fill: parent
                HorizontalHeaderView {
                    id: dirTableHeader
                    anchors.top: parent.top
                    syncView: dirTable
                    height: 30
                    clip: true
                    delegate: Rectangle {
                        implicitWidth: dirTableHeader.width
                        implicitHeight: dirTableHeader.height
                        color: "#404040"
                        Text {
                            anchors.centerIn: parent
                            text: display
                            color: "white"
                            font.pointSize: 11
                        }
                    }
                }

                TableView {
                    id: dirTable
                    anchors {
                        top: dirTableHeader.bottom
                        bottom: parent.bottom
                        left: parent.left
                        right: dirTableVertScrollBar.right
                    }

                    clip: true
                    ScrollBar.vertical: dirTableVertScrollBar
                    model: controller.dirTableModel
                    columnWidthProvider: function(col) {
                        // make zeroth column fill available space
                        if(col === 0 && isColumnLoaded(1))
                            return dirTable.width - dirTableVertScrollBar.width - implicitColumnWidth(1);
                        else
                            return -1;
                    }

                    delegate: Rectangle {
                        implicitWidth: text.paintedWidth + text.anchors.leftMargin + text.anchors.rightMargin
                        implicitHeight: 20
                        border.width: 1
                        Text {
                            id: text
                            text: display
                            verticalAlignment: Text.AlignVCenter
                            anchors {
                                fill: parent
                                leftMargin: 4
                                rightMargin: 4
                            }
                        }
                    }
                }

                ScrollBar {
                    id: dirTableVertScrollBar
                    anchors {
                        top: parent.top
                        bottom: parent.bottom
                        right: parent.right
                    }
                    policy: ScrollBar.AlwaysOn
                }
            }
        }
    }
}
