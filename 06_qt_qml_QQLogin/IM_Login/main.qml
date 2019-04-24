import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3



ApplicationWindow{
    id:im_Login
    visible: true
    width: 430   //483
    height: 330  //458
    title: qsTr("QQ登录界面")
    flags:Qt.FramelessWindowHint   //添加了这一句  隐藏了标题栏


    MouseArea{  //设置可以拖动没有标题的登录界面.  /*这个要放在上面，放在最下面的话，会把上面全部屏蔽掉的*/
        anchors.fill:parent
        property point clickPos: "0,0"  //定义一个点

        onPressed: {
            clickPos = Qt.point(mouseX, mouseY)
            winMenu.visible = false

        }

        onPositionChanged: {  //属性的改变
            var delta = Qt.point(mouseX-clickPos.x, mouseY-clickPos.y)
            im_Login.setX(im_Login.x+delta.x)
            im_Login.setY(im_Login.y+delta.y)
        }
    }



    //================================================
    //最上面的部分
    AnimatedImage {  //加载顶部背景的gif
        id: top_back
        source: "qrc:/images/back.gif"

    }


    Rectangle{  //右上角的关闭按钮
        id:rect_close
        width: 30   //3*30 *30
        height: 30
        color: "transparent"  //透明颜色
        anchors.right: parent.right
        anchors.top: parent.top
        clip: true  //剪切
        state: "close_Gary"  //初始状态，还没有进入会变得灰

        Image {
            id: picture_close
            width:rect_close.width*3
            height:rect_close.height
            fillMode: Image.Stretch  //图片扩展方式填充
            source: "qrc:/images/closeback.png"
            x:0
            y:0
        }


        MouseArea{
            hoverEnabled: true  //悬停使用
            anchors.fill:parent
            onEntered: rect_close.state = "close_Black"  //进入会变得黑
            onExited: rect_close.state = "close_Gary"  //离开会变得灰
            onPressed: rect_close.state = "close_Blue"  //按下不松开会变蓝色
            onReleased: rect_close.state = "close_Gary"  //松开会变灰

        }

        states:[  //必须在rectangle里面定义使用
            State {
                name: "close_Gary"
                PropertyChanges {
                    target: picture_close
                    x:-0*rect_close.width

                }
            },

            State {
                name: "close_Black"
                PropertyChanges {
                    target: picture_close
                    x:-1*rect_close.width

                }
            },
            State {
                name: "close_Blue"
                PropertyChanges {
                    target: picture_close
                    x:-2*rect_close.width

                }
            }
        ]
    }

    Rectangle{  //右上角的最小化
        id:rect_min
        width: 30   //3*30 *30
        height: 30
        color: "transparent"  //透明颜色
        anchors.right: rect_close.left
        anchors.top: parent.top
        clip: true  //剪切
        state: "min_Gary"  //初始状态，还没有进入会变得灰

        Image {
            id: picture_min
            width:rect_min.width*3
            height:rect_min.height
            fillMode: Image.Stretch  //图片扩展方式填充
            source: "qrc:/images/minback.png"
            x:0
            y:0
        }


        MouseArea{
            hoverEnabled: true  //悬停使用
            anchors.fill:parent
            onEntered: rect_min.state = "min_Black"  //进入会变得黑
            onExited: rect_min.state = "min_Gary"  //离开会变得灰
            onPressed: rect_min.state = "min_Blue"  //按下不松开会变蓝色
            onReleased: rect_min.state = "min_Gary"  //松开会变灰

        }

        states:[  //必须在rectangle里面定义使用
            State {
                name: "min_Gary"
                PropertyChanges {
                    target: picture_min
                    x:-0*rect_min.width

                }
            },

            State {
                name: "min_Black"
                PropertyChanges {
                    target: picture_min
                    x:-1*rect_min.width

                }
            },
            State {
                name: "min_Blue"
                PropertyChanges {
                    target: picture_min
                    x:-2*rect_min.width

                }
            }
        ]
    }


    Rectangle{  //右上角的菜单栏
        id:rect_arrowback
        width: 30   //3*30 *30
        height: 30
        color: "transparent"  //透明颜色
        anchors.right: rect_min.left
        anchors.top: parent.top
        clip: true  //剪切
        state: "arrowback_Gary"  //初始状态，还没有进入会变得灰

        Image {
            id: picture_arrowback
            width:rect_arrowback.width*3
            height:rect_arrowback.height
            fillMode: Image.Stretch  //图片扩展方式填充
            source: "qrc:/images/arrowback.png"
            x:0
            y:0
        }


        MouseArea{
            hoverEnabled: true  //悬停使用
            anchors.fill:parent
            onEntered: rect_arrowback.state = "arrowback_Black"  //进入会变得黑
            onExited: rect_arrowback.state = "arrowback_Gary"  //离开会变得灰
            onPressed: rect_arrowback.state = "arrowback_Blue"  //按下不松开会变蓝色
            onReleased: rect_arrowback.state = "arrowback_Gary"  //松开会变灰

        }

        states:[  //必须在rectangle里面定义使用
            State {
                name: "arrowback_Gary"
                PropertyChanges {
                    target: picture_arrowback
                    x:-0*rect_arrowback.width

                }
            },

            State {
                name: "arrowback_Black"
                PropertyChanges {
                    target: picture_arrowback
                    x:-1*rect_arrowback.width

                }
            },
            State {
                name: "arrowback_Blue"
                PropertyChanges {
                    target: picture_arrowback
                    x:-2*rect_arrowback.width

                }
            }
        ]
    }


    //================================================
    //中间的部分

    Image {  //加载登录头像
        id: body_HeadImage
        anchors.left: parent.left
        anchors.top: top_back.bottom
        anchors.leftMargin:  40
        anchors.topMargin: 10
        source: "qrc:/images/HeadImage.png"
    }

    Image {  //一开始的在线图标，用来进行点击出现弹窗的使用
        id:body_state_OnLine
        anchors.right: body_HeadImage.right
        anchors.bottom: body_HeadImage.bottom
        source: "qrc:/images/state_online.png"
        MouseArea {
            anchors.fill: parent
            acceptedButtons: Qt.LeftButton | Qt.RightButton
            onClicked: {
                if(mouse.button == Qt.LeftButton){
                    winMenu.visible = true
                    menu.open();
                }
                else if(mouse.button == Qt.RightButton){
                    winMenu.visible = false
                }
                else{
                    //no TODO
                }
            }
        }
    }


    Window{  //在线登陆的状态
            id: winMenu
            width: 80
            height: menu.height
            flags: Qt.FramelessWindowHint
            x: im_Login.x + body_state_OnLine.x + 13
            y: im_Login.y + body_state_OnLine.y

            Menu{
                id: menu

                MenuItem {
                    id: menuItem1
                    anchors.left: parent.left
                    anchors.leftMargin: 6
                    text: qsTr("在线")

                    height: 24   //避免只显示16的大小  看起来不美观，有点偏小
                    indicator:  //标志??  从最左边到这里会有一个叫宽度
                    Image {
                        id: image1
                        height: 16
                        width: 16
                        anchors.verticalCenter: parent.verticalCenter   //水平对齐
                        source: "qrc:/images/state_online.png"
                    }
                    contentItem: Text {  //内容容器
                        id: text1
                        text: menuItem1.text
                        font: menuItem1.font
                        opacity: enabled ? 1.0 : 0.3   //不透明度
                        color: menuItem1.down ? "#AA0000" : "#148014"    //字体的颜色： 按键按下改变
                        horizontalAlignment: Text.AlignLeft  //左对齐
                        verticalAlignment: Text.AlignVCenter  //居中对齐
                        leftPadding: menuItem1.indicator.width  //内容填充
                    }
                    onTriggered: {  //触发
                        body_state_OnLine.source = image1.source;
                        winMenu.visible = false;
                    }
                }

                MenuItem {
                    id: menuItem2
                    anchors.left: parent.left
                    anchors.leftMargin: 6
                    text: qsTr("离开")

                    height: 24  //让其看起来稍微宽一点点  只是16的话  显得比较窄了
                    indicator:  //标志??  实干毛线是用的？？   隔离开图片和文字的？？
                    Image {
                        id: image2
                        height: 16
                        width: 16
                        anchors.verticalCenter: parent.verticalCenter
                        source: "qrc:/images/state_away.png"
                    }
                    contentItem: Text {  //内容容器
                        id: text2
                        text: menuItem2.text
                        font: menuItem2.font
                        opacity: enabled ? 1.0 : 0.3   //不透明度： 开启
                        color: menuItem2.down ? "#FF6AAD" : "#6A83FF"  //文字按下， 颜色的改变
                        horizontalAlignment: Text.AlignLeft
                        verticalAlignment: Text.AlignVCenter
                        leftPadding: menuItem2.indicator.width   //左侧填充
                    }
                    onTriggered: {  //触发
                        body_state_OnLine.source = image2.source;
                        winMenu.visible = false;
                    }
                }

                MenuItem {
                    id: menuItem3
                    anchors.left: parent.left
                    anchors.leftMargin: 6
                    text: qsTr("忙碌")

                    height: 24
                    indicator:  //标志??  实干毛线是用的？？
                    Image {
                        id: image3
                        height: 16
                        width: 16
                        anchors.verticalCenter: parent.verticalCenter
                        source: "qrc:/images/state_busy.png"
                    }
                    contentItem: Text {  //内容容器
                        id: text3
                        text: menuItem3.text
                        font: menuItem3.font
                        opacity: enabled ? 1.0 : 0.3   //透明度
                        color: menuItem3.down ? "#AA0000" : "#148014"
                        horizontalAlignment: Text.AlignLeft
                        verticalAlignment: Text.AlignVCenter
                        leftPadding: menuItem3.indicator.width
                    }
                    onTriggered: {
                        body_state_OnLine.source = image3.source;
                        winMenu.visible = false;
                    }
                }

                MenuItem {
                    id: menuItem4
                    anchors.left: parent.left
                    anchors.leftMargin: 6
                    text: qsTr("隐身")

                    height: 24  //让其看起来稍微宽一点点  只是16的话  显得比较窄了
                    indicator:  //标志??  实干毛线是用的？？   隔离开图片和文字的？？
                    Image {
                        id: image4
                        height: 16
                        width: 16
                        anchors.verticalCenter: parent.verticalCenter
                        source: "qrc:/images/state_hide.png"
                    }
                    contentItem: Text {  //内容容器
                        id: text4
                        text: menuItem4.text
                        font: menuItem4.font
                        opacity: enabled ? 1.0 : 0.3   //不透明度： 开启
                        color: menuItem4.down ? "#FF6AAD" : "#6A83FF"  //文字按下， 颜色的改变
                        horizontalAlignment: Text.AlignLeft
                        verticalAlignment: Text.AlignVCenter
                        leftPadding: menuItem4.indicator.width   //左侧填充
                    }
                    onTriggered: {  //触发
                        body_state_OnLine.source = image4.source;
                        winMenu.visible = false;
                    }
                }

                MenuItem {
                    id: menuItem5
                    anchors.left: parent.left
                    anchors.leftMargin: 6
                    text: qsTr("请勿打扰")

                    height: 24
                    indicator:  //标志??  实干毛线是用的？？
                    Image {
                        id: image5
                        height: 16
                        width: 16
                        anchors.verticalCenter: parent.verticalCenter
                        source: "qrc:/images/state_notdisturb.png"
                    }
                    contentItem: Text {  //内容容器
                        id: text5
                        text: menuItem5.text
                        font: menuItem5.font
                        opacity: enabled ? 1.0 : 0.3   //透明度
                        color: menuItem5.down ? "#AA0000" : "#148014"
                        horizontalAlignment: Text.AlignLeft
                        verticalAlignment: Text.AlignVCenter
                        leftPadding: menuItem5.indicator.width
                    }
                    onTriggered: {
                        body_state_OnLine.source = image5.source;
                        winMenu.visible = false;
                    }
                }

                MenuItem {
                    id: menuItem6
                    anchors.left: parent.left
                    anchors.leftMargin: 6
                    text: qsTr("Q我吧")

                    height: 24  //让其看起来稍微宽一点点  只是16的话  显得比较窄了
                    indicator:  //标志??  实干毛线是用的？？   隔离开图片和文字的？？
                    Image {
                        id: image6
                        height: 16
                        width: 16
                        anchors.verticalCenter: parent.verticalCenter
                        source: "qrc:/images/state_Qme.png"
                    }
                    contentItem: Text {  //内容容器
                        id: text6
                        text: menuItem6.text
                        font: menuItem6.font
                        opacity: enabled ? 1.0 : 0.3   //不透明度： 开启
                        color: menuItem6.down ? "#FF6AAD" : "#6A83FF"  //文字按下， 颜色的改变
                        horizontalAlignment: Text.AlignLeft
                        verticalAlignment: Text.AlignVCenter
                        leftPadding: menuItem6.indicator.width   //左侧填充
                    }
                    onTriggered: {  //触发
                        body_state_OnLine.source = image6.source;
                        winMenu.visible = false;
                    }
                }


            }
    }

    TextField {  //账号输入栏， 组合框，下拉列表框的
        id:body_Id
        width: 190
        height: 30
        anchors.left: body_HeadImage.right
        anchors.top: top_back.bottom
        anchors.leftMargin:  10
        anchors.topMargin: 10
    }

    TextField {  //密码输入栏， 组合框，下拉列表框的
        id:body_Password
        width: 190
        height: 30
        anchors.left: body_HeadImage.right
        anchors.top: body_Id.bottom
        anchors.leftMargin:  10
    }

    Text {  //链接：注册账号
        id: body_Regeist_Id
        width: 50
        height: 20
        anchors.left: body_Id.right
        anchors.leftMargin: 10
        anchors.verticalCenter: body_Id.verticalCenter
        text: '<html></style><a href="http://www.baidu.com">注册账号</a></html>'
        MouseArea {
            anchors.fill: parent;
            hoverEnabled: true;
            cursorShape:
                (containsMouse? Qt.PointingHandCursor: Qt.ArrowCursor);
            onClicked: Qt.openUrlExternally("http://www.baidu.com")
        }
    }

    Text {  //链接：找回密码
        id: body_Find_Password
        width: 50
        height: 20
        anchors.left: body_Password.right
        anchors.leftMargin: 10
        anchors.verticalCenter: body_Password.verticalCenter
        text: '<html></style><a href="http://www.baidu.com">找回密码</a></html>'
        MouseArea {
            anchors.fill: parent;
            hoverEnabled: true;
            cursorShape:
                (containsMouse? Qt.PointingHandCursor: Qt.ArrowCursor);
            onClicked: Qt.openUrlExternally("http://www.baidu.com")
        }
    }

    ColumnLayout {  //复选框: 记住密码, 自动登录

        //width: 190
        //height: 30
        //作为一个整体必须在这里面定义复选框的位置
        id:bottom_checkBox
        anchors.left: body_HeadImage.right
        anchors.leftMargin: 5
        anchors.top:body_Password.bottom

        CheckBox{
            id:bottom_Remember_Password
            text:qsTr("记住密码")
        }

        CheckBox{
            id:bottom_Automatic_Lonin
            anchors.left: bottom_Remember_Password.right
            anchors.leftMargin: 10
            anchors.verticalCenter: bottom_Remember_Password.verticalCenter
            text:qsTr("自动登录")
        }

    }


    //================================================
    //最下面的部分
    Rectangle{  //左下角的新建账号头像
        id:bottom_New_ID
        width: 23.7   //3*23.7 *20
        height: 20
        color: "transparent"  //透明颜色
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        clip: true  //剪切
        state: "new_ID_Gary"  //初始状态，还没有进入会变得灰

        Image {
            id: picture_new_ID
            width:bottom_New_ID.width*3
            height:bottom_New_ID.height
            //fillMode: Image.Stretch  //图片扩展方式填充
            source: "qrc:/images/more_accountlogin.png"
            x:0
            y:0
        }


        MouseArea{
            hoverEnabled: true  //悬停使用
            anchors.fill:parent
            onEntered: bottom_New_ID.state = "new_ID_Black"  //进入会变得黑
            onExited: bottom_New_ID.state = "new_ID_Gary"  //离开会变得灰
            onPressed: bottom_New_ID.state = "new_ID_Blue"  //按下不松开会变蓝色
            onReleased: bottom_New_ID.state = "new_ID_Gary"  //松开会变灰

        }

        states:[  //必须在rectangle里面定义使用
            State {
                name: "new_ID_Gary"
                PropertyChanges {
                    target: picture_new_ID
                    x:-0*bottom_New_ID.width

                }
            },

            State {
                name: "new_ID_Black"
                PropertyChanges {
                    target: picture_new_ID
                    x:-1*bottom_New_ID.width

                }
            },
            State {
                name: "new_ID_Blue"
                PropertyChanges {
                    target: picture_new_ID
                    x:-2*bottom_New_ID.width

                }
            }
        ]
    }

    Rectangle{  //右下角的使用二维码登录
        id:bottom_Quick_Mark
        width: 22   //3*22 *22
        height: 22
        color: "transparent"  //透明颜色
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        clip: true  //剪切
        state: "new_ID_Gary"  //初始状态，还没有进入会变得灰

        Image {
            id: picture_Quick_Mark
            width:bottom_Quick_Mark.width*3
            height:bottom_Quick_Mark.height
            //fillMode: Image.Stretch  //图片扩展方式填充
            source: "qrc:/images/flicker.png"
            x:0
            y:0
        }


        MouseArea{
            hoverEnabled: true  //悬停使用
            anchors.fill:parent
            onEntered: bottom_Quick_Mark.state = "new_ID_Black"  //进入会变得黑
            onExited: bottom_Quick_Mark.state = "new_ID_Gary"  //离开会变得灰
            onPressed: bottom_Quick_Mark.state = "new_ID_Blue"  //按下不松开会变蓝色
            onReleased: bottom_Quick_Mark.state = "new_ID_Gary"  //松开会变灰

        }

        states:[  //必须在rectangle里面定义使用
            State {
                name: "new_ID_Gary"
                PropertyChanges {
                    target: picture_Quick_Mark
                    x:-0*bottom_Quick_Mark.width

                }
            },

            State {
                name: "new_ID_Black"
                PropertyChanges {
                    target: picture_Quick_Mark
                    x:-1*bottom_Quick_Mark.width

                }
            },
            State {
                name: "new_ID_Blue"
                PropertyChanges {
                    target: picture_Quick_Mark
                    x:-2*bottom_Quick_Mark.width

                }
            }
        ]
    }

    /*无需展开代码，改变按钮背景尝试
    //    Rectangle{
    //        width: 190
    //        height: 30
    //        color:"#05BAFB"
    //        anchors.bottom: parent.bottom
    //        anchors.bottomMargin: 10
    //        anchors.horizontalCenter: body_Id.horizontalCenter

    //        Button{  //最下面的登录按钮
    //            id:bottom_Login
    //            ColorAnimation:"green"
    //            text: qsTr("登录")
    //        }

    //    }
    */

    Button{  //最下面的登录按钮
        id:bottom_Login
        width: 190
        height: 30

        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        anchors.horizontalCenter: body_Id.horizontalCenter
        text: qsTr("登录")
    }

}


