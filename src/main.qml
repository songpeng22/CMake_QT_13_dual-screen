import QtQuick 2.9
import QtQuick.Window 2.3
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.2
import QtQuick.Controls.Material 2.0
//import QtQuick.Controls.Universal 2.0
import QtQuick.Dialogs 1.1

Item{
	visible: false
	x: 10
	y: 10
	width: 1
	height: 1
	implicitWidth: 1
	implicitHeight: 1
/**/
	Window {
		id:win1
		objectName: "objWindow1"
		visible: true
		title: qsTr("Hello World")
		//	because screen 2 is at diffrient xy on a combined frame buffer
		screen: Qt.application.screens[1]
		x: 0
		y: 0
		width: 100
		height:100
/*
		x: screen.virtualX
		y: screen.virtualY
		width: screen.width
		height:screen.height
*/
		flags: Qt.FramelessWindowHint
		Rectangle{
			id:idRect1
			objectName : "objRect1"
			color: "teal"
			height: parent.height
			anchors.left : parent.left
			anchors.right : parent.right

		}

		Component.onCompleted:{
			console.log( "screen1 xy: ",screen.virtualX, screen.virtualY);
			console.log( "screen1 wh: ",screen.width, screen.height);
		}
	}

	Window {
		id:win2
		objectName: "objWindow2"
		visible: true
		title: qsTr("window on primary screen")
		x: Qt.application.screens[0].width
		y: Qt.application.screens[0].height
		width: 100
		height:100
/*
		screen: Qt.application.screens[0]
		x: screen.virtualX
		y: screen.virtualY
		width: screen.width
		height:screen.height
*/
		flags: Qt.FramelessWindowHint
		Rectangle{
			id:idRect2
			objectName : "objRect2"
			color: "red"
			height: parent.height
			anchors.left : parent.left
			anchors.right : parent.right

		}
		Component.onCompleted:{
			console.log( "screen0 xy: ",screen.virtualX, screen.virtualY);
			console.log( "screen0 wh: ",screen.width, screen.height);
		}
	}

}

