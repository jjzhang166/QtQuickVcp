import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Window 2.0

Rectangle {
    /*! This property holds the title of the service window.
    */
    property string title: "Window"

    /*! \qmlproperty bool ready

        This property holds wheter the service window is ready or not.
        Per default this property is set using the internal services
        if you want to overwrite the services set this property to \c true.
    */
    property bool ready: false

    /*! \qmlproperty list<Service> services

        This property holds the services used by the application.
    */
    property var services: []

    /*! \internal */
    property var _requiredServices: {
        var required = []
        for (var i = 0; i < services.length; ++i) {
            if (services[i].required) {
                required.push(services[i])
                services[i].onReadyChanged.connect(_evaluateReady)
            }
        }

        return required
    }

    /*! \internal */
    function _evaluateReady() {
        for (var i = 0; i < _requiredServices.length; ++i) {
            if (!_requiredServices[i].ready) {
                ready = false
                return
            }
        }

        ready = true
        return
    }

    /*! \internal */
    function _recurseObjects(objects, name)
    {
        var list = []

        if (objects !== undefined) {
            for (var i = 0; i < objects.length; ++i)
            {
                if (objects[i].objectName === name) {
                    list.push(objects[i])
                }
                var nestedList = _recurseObjects(objects[i].data)
                if (nestedList.length > 0) {
                    list = list.concat(nestedList)
                }
            }
        }

        return list;
    }

    Component.onCompleted: {
        var list = main.services
        var nestedList = _recurseObjects(main.data, "Service")
        if (nestedList.length > 0) {
            list = list.concat(nestedList)
        }
        main.services = list
    }

    id: main
    color: systemPalette.window

    SystemPalette {
        id: systemPalette;
        colorGroup: enabled ? SystemPalette.Active : SystemPalette.Disabled
    }

    Label {
        id: dummyText
    }

    Rectangle {
        id: discoveryPage

        anchors.fill: parent
        visible: false
        z: 100
        color: systemPalette.window


        Label {
            id: connectingLabel

            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: connectingIndicator.top
            anchors.bottomMargin: Screen.logicalPixelDensity
            font.pointSize: dummyText.font.pointSize * 1.3
            text: qsTr("Waiting for services to appear...")
        }

        BusyIndicator {
            id: connectingIndicator

            anchors.centerIn: parent
            running: true
            height: parent.height * 0.15
            width: height
        }

        Column {
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: connectingIndicator.bottom
            anchors.topMargin: Screen.logicalPixelDensity

            Repeater {
                model: main._requiredServices.length

                CheckBox {
                    id: checkBox
                    text: _requiredServices[index].type + qsTr(" service")
                    checked: _requiredServices[index].ready
                }
            }
        }
    }

    /* This timer is a workaround to make the discoveryPage invisible in QML designer */
    Timer {
        interval: 10
        repeat: false
        running: true
        onTriggered: {
            discoveryPage.visible = true
        }
    }

    state: ready ? "connected" : "disconnected"

    states: [
        State {
            name: "disconnected"
            PropertyChanges { target: discoveryPage; opacity: 1.0; enabled: true }
        },
        State {
            name: "connected"
            PropertyChanges { target: discoveryPage; opacity: 0.0; enabled: false }
            PropertyChanges { target: main; enabled: true }
        }
    ]

    transitions: Transition {
            PropertyAnimation { duration: 500; properties: "opacity"; easing.type: Easing.InCubic}
        }
}