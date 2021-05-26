QT          += core gui multimedia sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    call_window.cpp \
    call_window.cpp \
    contact_editor.cpp \
    contact_window.cpp \
    database.cpp \
    main.cpp \
    main_window.cpp \
    sip_adapter.cpp

HEADERS += \
    call_window.h \
    contact_editor.h \
    contact_window.h \
    database.h \
    main_window.h \
    sip_adapter.h

FORMS += \
    call_window.ui \
    contact_editor.ui \
    contact_window.ui \
    main_window.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

#Pjproject libs including.

INCLUDEPATH += \
    $$PWD/../../libs/pjproject_2.10/pjlib/include \
    $$PWD/../../libs/pjproject_2.10/pjlib-util/include \
    $$PWD/../../libs/pjproject_2.10/pjmedia/include \
    $$PWD/../../libs/pjproject_2.10/pjnath/include \
    $$PWD/../../libs/pjproject_2.10/pjsip/include \

LIBS += \
    -L"$$PWD/../../libs/pjproject_2.10/lib" \
    -L"$$PWD/../../libs/pjproject_2.10/pjlib" \
    -L"$$PWD/../../libs/pjproject_2.10/pjlib-util" \
    -L"$$PWD/../../libs/pjproject_2.10/pjmedia" \
    -L"$$PWD/../../libs/pjproject_2.10/pjnath" \
    -L"$$PWD/../../libs/pjproject_2.10/pjsip" \
    -llibpjproject-x86_64-x64-vc14-Release \
    -lpjlib-x86_64-x64-vc14-Release \
    -lpjlib-util-x86_64-x64-vc14-Release \
    -lpjmedia-audiodev-x86_64-x64-vc14-Release \
    -lpjmedia-codec-x86_64-x64-vc14-Release \
    -lpjmedia-x86_64-x64-vc14-Release \
    -lpjnath-x86_64-x64-vc14-Release \
    -lpjsip-core-x86_64-x64-vc14-Release \
    -lpjsip-simple-x86_64-x64-vc14-Release \
    -lpjsip-ua-x86_64-x64-vc14-Release \
    -lpjsua2-lib-x86_64-x64-vc14-Release \
    -lpjsua-lib-x86_64-x64-vc14-Release \
    -lWs2_32 \
    -lOle32 \
    -lMsdmo \
    -lDmoguids \
    -lwmcodecdspuuid \
    -lamstrmid
