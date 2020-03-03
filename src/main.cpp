#include "main.h"
#include <QApplication>
#include <QGuiApplication>
//For Debug
#include <QDebug>
//For Qml loading Method 1
#include <QQmlApplicationEngine>
//For Qml loading Method 2
#include <QQuickView>
#include <QQmlContext>
//For Qml loading Method 3
#include <QQuickWidget>
//For Qml loading Method 4
#include <QQmlComponent>
//For Qml loading Method 5
#include "EngineReloaderWrapper.h"
//For Debugging
#include <QQmlDebuggingEnabler>
//
#include <QQuickWindow>
#include <QQuickItem>
//For Multi-Screen
#include <QDesktopWidget>
//Others
#include <QLabel>

//For static link
#ifdef QT_STATIC
    //Qt
    #include <QtCore/QtPlugin>
    //QWindowsIntegrationPlugin "platforms/qwindows.dll" //Qt5Gui_QWindowsIntegrationPlugin.cmake
    Q_IMPORT_PLUGIN(QWindowsIntegrationPlugin)
    //Install Qml plugins
#include <QtQml/QQmlExtensionPlugin>
    //${QQMLDIR}QtQuick.2/qtquick2plugind.lib
    Q_IMPORT_PLUGIN(QtQuick2Plugin)
    //${QQMLDIR}QtQuick/Window.2/windowplugind.lib
    Q_IMPORT_PLUGIN(QtQuick2WindowPlugin)
    //${QQMLDIR}QtQuick/Controls.2/qtquickcontrols2plugind.lib
    //${QQMLDIR}QtQuick/Templates.2/qtquicktemplates2plugind.lib
    //${QLIBDIR}Qt5QuickTemplates2d.lib
    Q_IMPORT_PLUGIN(QtQuickControls2Plugin)
    //${QQMLDIR}QtQuick/Templates.2/qtquicktemplates2plugind.lib
    //${QLIBDIR}Qt5QuickTemplates2d.lib
    Q_IMPORT_PLUGIN(QtQuickTemplates2Plugin)
    //${QQMLDIR}QtQuick/Layouts/qquicklayoutsplugind.lib
    Q_IMPORT_PLUGIN(QtQuickLayoutsPlugin)
    //${QQMLDIR}QtQuick/Controls.2/Fusion/qtquickcontrols2fusionstyleplugin.lib
    //${QQMLDIR}QtQuick/Controls.2/Imagine/qtquickcontrols2imaginestyleplugin.lib
    //${QQMLDIR}QtQuick/Controls.2/Material/qtquickcontrols2materialstyleplugin.lib
    //${QQMLDIR}QtQuick/Controls.2/Universal/qtquickcontrols2universalstyleplugin.lib
    Q_IMPORT_PLUGIN(QtQuickControls2FusionStylePlugin)
    Q_IMPORT_PLUGIN(QtQuickControls2ImagineStylePlugin)
    Q_IMPORT_PLUGIN(QtQuickControls2MaterialStylePlugin)
    Q_IMPORT_PLUGIN(QtQuickControls2UniversalStylePlugin)
    //${QQMLDIR}QtQuick/Dialogs/dialogplugind.lib
    //QtQuick/Dialogs/Private/dialogsprivateplugind.lib
    Q_IMPORT_PLUGIN(QtQuick2DialogsPlugin)
    Q_IMPORT_PLUGIN(QtQuick2DialogsPrivatePlugin)
    //${QQMLDIR}Qt/labs/folderlistmodel/qmlfolderlistmodelplugind.lib
    Q_IMPORT_PLUGIN(QmlFolderListModelPlugin)
    //${QQMLDIR}Qt/labs/settings/qmlsettingsplugin.lib
    Q_IMPORT_PLUGIN(QmlSettingsPlugin)
    //${QQMLDIR}QtGraphicalEffects/qtgraphicaleffectsplugin.lib
    Q_IMPORT_PLUGIN(QtGraphicalEffectsPlugin)
    //${QQMLDIR}QtGraphicalEffects/private/qtgraphicaleffectsprivate.lib
    Q_IMPORT_PLUGIN(QtGraphicalEffectsPrivatePlugin)
    //${QQMLDIR}QtQml/Models.2/modelsplugin.lib
    Q_IMPORT_PLUGIN(QtQmlModelsPlugin)
    //${QQMLDIR}QtQuick/Extras/qtquickextrasplugin.lib
    Q_IMPORT_PLUGIN(QtQuickExtrasPlugin)
    //${QQMLDIR}QtQuick/PrivateWidgets/widgetsplugin.lib
    Q_IMPORT_PLUGIN(QtQuick2PrivateWidgetsPlugin)
    //QtQuick\Controls/qtquickcontrolsplugind.lib
    Q_IMPORT_PLUGIN(QtQuickControls1Plugin)

#endif

#if 0

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    //Settings
    QCoreApplication::setOrganizationName("Bizerba");
    QCoreApplication::setApplicationName("QmlLoader");
    QCoreApplication::setOrganizationDomain("Bizerba.com");
    //Engine
    EngineReloaderWrapper engine;
    qDebug() << "EngineReloaderWrapper";
    QUrl url = QUrl(QStringLiteral("qrc:/main.qml"));
    engine.load(url);

    return app.exec();
}

#elif 0

/*
* Call QML : Method 4
*
*/
int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QQmlEngine *engine = new QQmlEngine;
    QQmlComponent component(engine, QUrl(QStringLiteral("qrc:///method2.qml")));
//    QQmlComponent component(engine, QUrl::fromLocalFile("method2.qml "));

    if(component.isReady()){
        QObject *myObject = component.create();
        QQuickItem *item = qobject_cast<QQuickItem*>(myObject);
        int width = item->width();  // width = 200
        qDebug()<<width;
    }
    return app.exec();
}

#elif 0

/*
* Call QML : Method 3
* QQuickWidget是继承于 QWidget 控件，这种方式主要是用于在 QWidget 界面上加载 QML 界面。
*/
int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QQuickWidget *view = new QQuickWidget;
    view->setSource(QUrl::fromLocalFile("method2.qml"));
    view->show();

    return app.exec();
}

#elif 0

/*
* Call QML : Method 2
* 使用 QQuickView 显示 QML 文件，对窗口的控制权（标题、窗口尺寸）是在 C++代码中，QML 文件是以 Item （及 以Item为根的组件）作为根对象。
*/
int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);

    QQuickView *view = new QQuickView;
    view->setResizeMode(QQuickView::SizeRootObjectToView);
    view->setSource(QUrl(QStringLiteral("qrc:/method2.qml")));
    view->show();

    return app.exec();
}

#elif 1
/*
* Call QML : Method 1
* 这种方式是加载以 Window为跟对象的 QML 文件，QML 拥有窗口的完整控制权，可以直接设置标题、窗口尺寸等属性。
*/

/*
* Find Sub Object by Function
* Param : objectName
* Method : From QObject
*/
QObject * FindSubObjectByObjectName(QObject * objParent,QString qstr){
    QObject * objSub = objParent->findChild<QObject*>(qstr);
    if(objSub)
        qDebug() << "PName:" << objParent->objectName() << "SName:" << objSub->objectName() << endl;
    return objSub;
}

int main(int argc, char *argv[]) {
    //For Debugging
//    QQmlDebuggingEnabler enabler;
    //Application
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);
    //For Desktop
    QDesktopWidget * desktopWidget = QApplication::desktop();
    //count of screen
    int nScreenCount = desktopWidget->screenCount();
    qDebug() << "nScreenCount: " << nScreenCount;
    //primary scrren
    int nIndexOfPrimaryScreen = desktopWidget->primaryScreen();
    qDebug() << "nIndexOfPrimaryScreen: " << nIndexOfPrimaryScreen;  
    //rect of dual screen
    QRect rectPrimary = desktopWidget->screenGeometry(0);
    QRect rectSecondary = desktopWidget->screenGeometry(1);
    qDebug() << "rectPrimary wh: " << rectPrimary.width() << rectPrimary.height();  
    qDebug() << "rectSecondary wh: " << rectSecondary.width() << rectSecondary.height(); 
    //QWidget of dual scrren
    QWidget * widgetOfPrimary = desktopWidget->screen(0);
    QWidget * widgetOfSecondary = desktopWidget->screen(1);
    qDebug() << "widgetOfPrimary wh: " << widgetOfPrimary->width() << widgetOfPrimary->height();  
    qDebug() << "widgetOfSecondary wh: " << widgetOfSecondary->width() << widgetOfSecondary->height(); 
    //show something on secondary screen
#if 0
    //Method1 
    QLabel Label("this is Widget",widgetOfSecondary); //在widget中添加一个标签
    Label.setGeometry(100,100,340,340);   //标签属性设置
    Label.show();
    QRect screenres = QApplication::desktop()->screenGeometry(1/*screenNumber*/);
    Label.move(QPoint(screenres.x(), screenres.y()));
    //
#elif 0
    //Method2
    QLabel Label("this is Widget",widgetOfSecondary); //在widget中添加一个标签
    Label.setGeometry(QApplication::desktop()->availableGeometry(1));
    Label.showMaximized();
#elif 0
    //Method3
    QLabel Label("this is Widget",widgetOfPrimary); //在widget中添加一个标签
    QRect screen2 = QApplication::desktop()->screenGeometry(1);
    Label.setGeometry(screen2.x(),screen2.y(),340,340);   //标签属性设置
    qDebug() << "widgetOfSecondary xy: " << widgetOfSecondary->x() << widgetOfSecondary->y(); 
    qDebug() << "widgetOfSecondary xy: " << screen2.x() << screen2.y();
    Label.show();
#elif 0
    /*
     * Method4 qml on secondary screen
     * only can load window
     */
    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:///main.qml")));
    if (engine.rootObjects().isEmpty()) return -1;
#elif 1
    /*
     * Method5 : qml on secondary screen
     * load item with two windows
     */
    QQuickView *view = new QQuickView;
	view->setResizeMode(QQuickView::SizeViewToRootObject);//QQuickView::SizeRootObjectToView
	view->setSource(QUrl(QStringLiteral("qrc:///main.qml")));
    //
    QUrl url = view->source();
    qDebug() << "url: " << url;
    QSize size = view->initialSize();
    qDebug() << "size wh: " << size.width() << size.height();
    //!!!important,could hide unnecessary title bar
    view->setFlags(Qt::Window|Qt::FramelessWindowHint);
    //
	view->show();
    //
    qDebug() << "isWidgetType" << view->isWidgetType();
    qDebug() << "isWindowType" << view->isWindowType();
    
#endif

    return app.exec();
}

#elif 0
/*
* Find Sub Object(Button) by objectName
* Method : From QQuickWindow
*/
int main(int argc, char *argv[]){
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:///main.qml")));
    if (engine.rootObjects().isEmpty()) return -1;
    QQuickWindow * rootWindow = (QQuickWindow *)engine.rootObjects().first();
    if (rootWindow) {
        rootWindow->setProperty("width", 1024);
        rootWindow->setProperty("height", 768);
    }
    QObject * btn = Q_NULLPTR;
    auto list = rootWindow->contentItem()->childItems();
    for (QQuickItem *item : list) {
        qDebug() << item->objectName() << endl;
        if (item->objectName() == "objButton1") {
            qDebug() << "Found the button";
            btn = item;
        }
        if (btn) break;
    }
    if(btn)
        btn->setProperty("text", "textNew1");

    return app.exec();
}

#elif 0
/*
* Find Sub Object by objectName
* Method : From QObject
*/
int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:///main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;
    QObject* rootObject = engine.rootObjects().first();
    QObject * btn = rootObject->findChild<QObject*>("objButton1");

    btn->setProperty( "text", "textNew2" );

    return app.exec();
}

#elif 1

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;
    return app.exec();
}

#endif


