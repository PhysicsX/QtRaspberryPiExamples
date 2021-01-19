import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 1.4
import com.ulasdikme.mqtt 1.0
import QtQuick.Controls.Styles 1.4
import QtQuick.Extras 1.4

Window {
    visible: true
    width: 640
    height: 480
    visibility: "FullScreen"

    Mqtt
    {
    id:mqtt

    value:0

        onValueChanged:
        {
            gauge.value = value
        }

        onStatuChanged:
        {
            if(statu)
            {

                connect.text = "connect"
            }
            else
            {
                connect.text = "disconnect"
            }
        }
    }


    Gauge {
        id: gauge

        height: 300

        x: 400
        y: 20

        tickmarkStepSize: 100
        minimumValue: 0
        maximumValue: 1000
        minorTickmarkCount: 1
        value: 15
     }

    TextField {
        id: host
        placeholderText: qsTr("host name")
        x:20
        y:20
    }

    TextField {
        id: port
        placeholderText: qsTr(" port")
        x:20
        y:50
    }

    TextField {
        id: user
        placeholderText: qsTr("User name")
        x:20
        y:80
    }

    TextField {
        id: pass
        placeholderText: qsTr("Password")
        x:20
        y:110
    }

    Button {
        x:70
        y:150
        text: "connect"
        id: connect
        onClicked:
        {
            mqtt.connect_a(host.text, port.text, user.text, pass.text);
        }
    }

    TextField {
        id: topic
        placeholderText: qsTr("topic")
        x:20
        y:210
    }

    Button {
        x:70
        y:240
        text: "subs"
        onClicked:
        {
            mqtt.subs_a(topic.text);
        }
    }
}
