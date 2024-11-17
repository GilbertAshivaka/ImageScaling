import QtQuick
import QtQuick.Window
import QtQuick.Controls.Material
import QtQuick.Dialogs
import QtQuick.Layouts
import com.images 1.0

ApplicationWindow {
    width: 640
    height: 480
    visible: true
    title: qsTr("Image Scaling")

    ImageDownloader{
        id: imageDownloader

    }

    Button{
        id: addUrlBtn
        text: "Add Urls"

        anchors{
            left: parent.left
            leftMargin: 5
            top: parent.top
            topMargin: 5
        }

        onClicked: {
            dowloadDialog.open()
        }
    }

    Button{
        id: cancelBtn
        text: "Cancel"
        anchors{
            left: addUrlBtn.right
            leftMargin: 5
            verticalCenter: addUrlBtn.verticalCenter
        }
        onClicked: {

        }
    }

    Dialog{
        id: dowloadDialog
        width: parent.width* .85
        height: parent.height * .8
        anchors.centerIn: parent

        TextField{
            id: urlInput
            height: 44
            width: parent.width* .8
            placeholderText: "Enter url...."
            placeholderTextColor: "gray"
            anchors{
                left: parent.left
                leftMargin: 5
                top: parent.top
                topMargin: 8
            }
        }

        Button{
            id: addBtn
            text: "Add"
            width: removeBtn.width
            anchors{
                left: urlInput.right
                leftMargin: 10
                verticalCenter: urlInput.verticalCenter
            }

            onClicked: {
                if (urlInput.text.trim() !== "") {
                    urlModel.append({ url: urlInput.text });
                    urlInput.text = ""; // clear the input after adding
                }
            }
        }

        Button{
            id: removeBtn
            text: "Remove"
            anchors{
                left: addBtn.left
                top: addBtn.bottom
                topMargin: 8
            }
        }

        Button{
            id: clearBtn
            text: "Clear"
            width: removeBtn.width
            anchors{
                left: addBtn.left
                top: removeBtn.bottom
                topMargin: 8
            }
        }

        ListModel{
            id: urlModel
        }

        ListView{
            id: urlsList
            width: urlInput.width
            clip: true
            anchors{
                left: parent.left
                leftMargin: 5
                top: urlInput.bottom
                topMargin: 8
                bottom: parent.bottom
            }

            ScrollBar.vertical: ScrollBar{}

            model: urlModel

            delegate: Rectangle {
                width: ListView.view.width
                height: 40
                color: index % 2 === 0 ? "#ffffff" : "#f8f8f8"

                RowLayout {
                    anchors.fill: parent
                    anchors.margins: 10
                    spacing: 10

                    Text {
                        id: urlText
                        text: model.url
                        font.family: "Segoe Script"
                        font.italic: true
                    }

                    Image {
                        id: removeImage
                        source: "assets/crossRed.png"
                        width: 20
                        height: 20
                        MouseArea{
                            id: removeMA
                            anchors.fill: parent
                            onClicked: {
                                urlModel.remove(index)
                            }
                        }
                    }
                }
            }
        }

        Button{
            id: dialogCancelBtn
            text: "Cancel"
            anchors{
                left: addBtn.left
                bottom: parent.bottom
                //                bottomMargin: 0
            }

            onClicked: {
                dowloadDialog.close()
            }
        }

        Button{
            id: okBtn
            text: "OK"
            anchors{
                right: dialogCancelBtn.left
                rightMargin: 10
                verticalCenter: dialogCancelBtn.verticalCenter
            }

            onClicked: {
                var urlList = [];
                for (var i = 0; i < urlModel.count; i++) {
                    urlList.push(urlModel.get(i).url);
                }
                imageDownloader.getUrls(urlList);
                imageDownloader.process();
                dowloadDialog.close();
            }
        }
    }

    //model to hold the images
    ListModel{
        id: imageModel
    }

    GridView {
        id: imageGrid
        anchors{
            top: addUrlBtn.bottom
            topMargin: 10
            left: parent.left
            right: parent.right
            bottom: parent.bottom
        }

        clip: true
        cellWidth: 110  // 100px image + 10px margin
        cellHeight: 110
        model: imageDownloader.imageList
        visible: false

        delegate: Rectangle {
            width: 100
            height: 100
            color: "#ffffff"
            border.color: "#dddddd"
            border.width: 1

            Image {
                anchors.centerIn: parent
                width: 90
                height: 90
                source: modelData
                fillMode: Image.PreserveAspectFit
            }
        }

        Rectangle {
            anchors.fill: parent
            color: "transparent"
            visible: imageModel.count === 0

            Text {
                anchors.centerIn: parent
                text: "No images loaded"
                color: "#666666"
            }
        }

        ScrollBar.vertical: ScrollBar {}
    }

    Rectangle{
        id: statusBar
        color: "#F5F5F5"
        width: statusBarText.width + 10
        height: 32
        anchors{
            left: parent.left
            leftMargin: 8
            bottom: parent.bottom
            bottomMargin: 8
        }

        Text{
            id: statusBarText
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignLeft
            text: imageDownloader.statusMessage
            anchors{
                left: parent.left
                verticalCenter: parent.verticalCenter
                leftMargin: 5
            }
        }
    }
}


















