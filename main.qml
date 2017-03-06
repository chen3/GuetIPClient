import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

import cn.qiditu 1.0

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    ComboBox {
        id: comnoBox;
        anchors.left: parent.left;
        anchors.top: parent.top;
        anchors.leftMargin: 20;
        anchors.topMargin: 20;
        textRole: "IPV4";
        model: ListModel {
            id: listModel;
        }
        Component.onCompleted: {
            var array = CPPHelper.networkList();
            if(array.length > 0) {
                listModel.append(array);
                currentIndex = 0;
            }
        }
    }

    Server {
        id: server;
    }

}
