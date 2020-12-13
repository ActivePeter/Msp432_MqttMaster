import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.3
import QtQuick.Dialogs 1.2
//import PathPainter 1.0
import pa.qmlTypes 1.0
Window {
    id:window
    visible: true
    width: 320
    height: 480
    minimumWidth:width
    maximumWidth:width
    minimumHeight:height
    maximumHeight:height
    title: qsTr("Hello World")

    Column {
        id: column
        anchors.fill: parent
        padding: 10

        Row {
            id: row
            height: 200

            Text {
                id: attiText
                text: qsTr("陀螺仪姿态")
                font.pixelSize: 12
            }

        }
    }
    QmlCppInterface{
        id:qmlCppInterface
        onAttitudeChange:{
            attiText.text=qmlCppInterface.getAttitude()
//            canvas.j=canvas.j+1;
//            canvas.j=canvas.j%3;
            canvas.requestPaint();
        }
    }
//    PathPainter{
//        id:pathPainter
//        x: 10
//        y: 10
//        contentsScale: 1
//        anchors.fill: parent
//    }

    FileDialog {
        id:fds
        title: "选择文件"
        folder: shortcuts.desktop
        selectExisting: true
        selectFolder: false
        selectMultiple: false
        nameFilters: ["图像文件(*.gif;*.jpg;*.jpeg;*.png;)"]
        onAccepted: {

            //            labels.text = fds.fileUrl;
            console.log("You chose: " + fds.fileUrl);
//            pathPainter.transmitImagePath(fds.fileUrl)
            viewImage.source=fds.fileUrl
            viewImage.visible=true
            button.anchors.verticalCenter=undefined
            button.anchors.bottom= button.parent.bottom
            picPathText.text=fds.fileUrl
        }

        onRejected: {
        }

    }

    Button {
        id: button
        x: 246
        y: 416
        text: qsTr("链接")
        onClicked: {
            qmlCppInterface.startMqtt()
        }
    }
    Canvas{
            id:canvas
            width: 300
            height: 300
            anchors.centerIn: parent
            property int j: 0
//            onJChanged: canvas.requestPaint()
            onPaint: {
                var ctx = getContext("2d");

//                ctx.save();
//                ctx.strokeStyle = "#148014";
//                ctx.lineWidth = 10
//                ctx.strokeRect(0,0,width,height);

                ctx.beginPath();
                ctx.moveTo(0,0);
//                if(j==0){
                    ctx.clearRect(0,0,width,height);
//                    ctx.restore();
                    ctx.strokeStyle = "#FF7F50";
                    ctx.moveTo(0,qmlCppInterface.getAttitudes(0,0)/2);
                    for(var i=1;i < 299;i+=1)
                    {
                        ctx.lineTo(i,qmlCppInterface.getAttitudes(0,i)/2);
                    }
                    ctx.stroke();
//                    j=j+1;
//                    canvas.requestPaint();
//                }
//                else if(j==1){
    //                ctx.restore();
                    ctx.beginPath();
                    ctx.strokeStyle = "#00BFFF";
                    ctx.moveTo(0,150+qmlCppInterface.getAttitudes(1,0)/2);
                    for(var i=1;i < 299;i+=1)
                    {
                        ctx.lineTo(i,150+qmlCppInterface.getAttitudes(1,i)/2);
                    }
                    ctx.stroke();
//                    j=j+1;
                    canvas.requestPaint();
//                }
//                else if(j==2){
    //                ctx.restore();
                    ctx.beginPath();
                    ctx.strokeStyle = "#148014";
                    ctx.moveTo(0,150+qmlCppInterface.getAttitudes(2,0)/2);
                    for(var i=1;i < 299;i+=1)
                    {
                        ctx.lineTo(i,150+qmlCppInterface.getAttitudes(2,i)/2);
                    }
                    ctx.stroke();
//                }





//                j=j+1;
//                ctx.fillStyle = "green"
//                ctx.fill();
            }

//            Timer{
//                repeat: true
//                interval: 20
//                running: true
//                onTriggered: {
//                    canvas.j+=5;
//                    canvas.requestPaint();
//                }
//            }
        }

}






















































