import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Dialogs 1.2



ApplicationWindow {
    id: applicationWindow1
    x: -1280
    y: 800
    visible: true
    width: 408
    height: 70
    minimumWidth: 408
    minimumHeight: 70
    maximumWidth: 408
    maximumHeight: 70
    title: qsTr("DualCam Tracker")

    menuBar: MenuBar {
        Menu {
            title: qsTr("File")
            MenuItem {
                text: qsTr("&Open")
                onTriggered: console.log("Open action triggered");
            }
            MenuItem {
                text: qsTr("Exit")
                onTriggered: Qt.quit();
            }
        }
    }

    FileDialog {
        id: fileDialog
        folder: "~/Desktop"
        visible: fileDialogVisible.checked
        modality: fileDialogModal.checked ? Qt.WindowModal : Qt.NonModal
        title: fileDialogSelectFolder.checked ? "Choose a folder" :
                                                (fileDialogSelectMultiple.checked ? "Choose some files" : "Choose a file")
        selectExisting: fileDialogSelectExisting.checked
        selectMultiple: fileDialogSelectMultiple.checked
        selectFolder: fileDialogSelectFolder.checked
        nameFilters: [ "Image files (*.mp4)", "All files (*)" ]
        selectedNameFilter: "Image files (*.mp4)"
        sidebarVisible: fileDialogSidebarVisible.checked
        onAccepted: {
            console.log("Accepted: " + fileUrls)
            if (fileDialogOpenFiles.checked)
                for (var i = 0; i < fileUrls.length; ++i)
                    Qt.openUrlExternally(fileUrls[i])
        }
        onRejected: { console.log("Rejected") }

    }

    CheckBox {
        id: chkbxLeftHand
        x: 133
        y: 11
        text: qsTr("Left Hand")
        checked: true
        transformOrigin: Item.Right
        onClicked: capture.toggleDisplayLeftHand()
    }

    ToolButton {
        id: btnRecord
        x: 25
        y: 11
        width: 48
        height: 46
        checkable: true
        isDefault: true
        iconSource: checked? "ic_stop.png" : "ic_record.png"
        onClicked: capture.startRecording()
    }

    CheckBox {
        id: chkbxRightHand
        x: 133
        y: 37
        text: qsTr("Right Hand")
        checked: true
        transformOrigin: Item.Right
        onClicked: capture.toggleDisplayRightHand()
    }

    CheckBox {
        id: chkbxLeftTrack
        x: 232
        y: 11
        text: qsTr("Left Track")
        checked: true
        transformOrigin: Item.Right
        onClicked: capture.toggleDisplayLeftTrack()
    }

    CheckBox {
        id: chkbxRightTrack
        x: 232
        y: 37
        text: qsTr("Right Track")
        checked: true
        transformOrigin: Item.Right
        onClicked: capture.toggleDisplayRightTrack()
    }

    CheckBox {
        id: chkbxGrid
        x: 326
        y: 11
        text: qsTr("Grid")
        transformOrigin: Item.Right
        onClicked: capture.toggleDisplayGrid()
    }

    ToolButton {
        id: btnOpen
        x: 79
        y: 11
        width: 48
        height: 46
        iconSource: "ic_folder_open.png"
        onClicked: fileDialog.open()
    }

}

