include(UI.pri)

TEMPLATE    = vcapp
LANGUAGE    = C++

CONFIG     += debug_and_release
CONFIG     += windows
CONFIG     += thread
CONFIG     -= app_bundle

build_pass:CONFIG(release, debug|release) {
	DESTDIR = $$RELEASE
	OBJECTS_DIR = $$RELEASE/obj
	RCC_DIR = $$RELEASE/rc

}

build_pass:CONFIG(debug, debug|release) {
	DESTDIR = $$DEBUG
	OBJECTS_DIR = $$DEBUG/obj
	RCC_DIR = $$DEBUG/rc
}

INCLUDEPATH  = $$QT_INCLUDE
INCLUDEPATH += $$QT_INCLUDE/QtCore
INCLUDEPATH += $$QT_INCLUDE/QtGui
INCLUDEPATH += $(QTDIR)/mkspecs/$(QMAKESPEC)
INCLUDEPATH += ./HEADER
INCLUDEPATH += ./UI
INCLUDEPATH += ./RESOURCE

equals(QT_MAJOR_VERSION, 4) {
//    QT          += gui
	
	INCLUDEPATH += $$QT_INCLUDE/ActiveQt
	
	LIBS         = $$QT_LIB/qtmaind.lib
	LIBS        += $$QT_LIB/QtGuid4.lib
	LIBS		+= $$QT_LIB/QtCored4.lib
}

equals(QT_MAJOR_VERSION, 5) {
	QT          += widgets

	INCLUDEPATH += $$QT_INCLUDE/QtWidgets
	INCLUDEPATH += $$QT_INCLUDE/QtANGLE	
	
	LIBS         = $$QT_LIB/qtmaind.lib
	LIBS        += $$QT_LIB/Qt5Guid.lib
	LIBS		+= $$QT_LIB/Qt5Cored.lib
	LIBS		+= $$QT_LIB/Qt5Widgetsd.lib	
}

MOC_DIR      = ./MOC
UI_DIR       = ./MOC
FORMS        = $$files("./UI/*.ui")
HEADERS      = $$files("./HEADER/*.h")
SOURCES      = $$files("./SOURCE/*.cpp")
RESOURCES    = $$files("./RESOURCE/*.qrc")
