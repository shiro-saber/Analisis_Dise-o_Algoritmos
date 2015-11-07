 HEADERS     = renderarea.h \
               window.h
 SOURCES     = main.cpp \
               renderarea.cpp \
               window.cpp

 QT       += core gui
 greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

 # install
 target.path = $$[QT_INSTALL_EXAMPLES]/painting/transformations
 sources.files = $$SOURCES $$HEADERS $$RESOURCES $$FORMS transformations.pro
 sources.path = $$[QT_INSTALL_EXAMPLES]/painting/transformations
 INSTALLS += target sources

 symbian {
     TARGET.UID3 = 0xA000A64D
     include($$QT_SOURCE_TREE/examples/symbianpkgrules.pri)
 }
