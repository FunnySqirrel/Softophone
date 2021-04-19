QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    call_window.cpp \
    main.cpp \
    main_window.cpp \
    settings_window.cpp \
    sip_adapter.cpp

HEADERS += \
    call_window.h \
    main_window.h \
    settings_window.h \
    sip_adapter.h

FORMS += \
    call_window.ui \
    main_window.ui \
    settings_window.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

#Pjproject libs including.

INCLUDEPATH += \
    $$PWD/../../libs/pjproject/pjsip/include \
    $$PWD/../../libs/pjproject/pjlib/include \
    $$PWD/../../libs/pjproject/pjlib-util/include \
    $$PWD/../../libs/pjproject/pjmedia/include \
    $$PWD/../../libs/pjproject/pjnath/include \

LIBS += \
    -L"$$PWD/../../libs/pjproject/lib" \
    -L"$$PWD/../../libs/pjproject/pjsip/lib" \
    -L"$$PWD/../../libs/pjproject/pjlib/lib" \
    -L"$$PWD/../../libs/pjproject/pjlib-util/lib" \
    -L"$$PWD/../../libs/pjproject/pjmedia/lib" \
    -L"$$PWD/../../libs/pjproject/pjnath/lib" \
    -L"$$PWD/../../libs/pjproject/third_party/lib" \
    -L"$$PWD/../../libs/pjproject/WebRTC/Debug" \
    -llibpjproject-x86_64-x64-vc14-Debug \
    -lpjsip-core-x86_64-x64-vc14-Debug \
    -lpjsip-simple-x86_64-x64-vc14-Debug \
    -lpjsip-ua-x86_64-x64-vc14-Debug \
    -lpjsua2-lib-x86_64-x64-vc14-Debug \
    -lpjsua-lib-x86_64-x64-vc14-Debug \
    -lpjlib-x86_64-x64-vc14-Debug \
    -lpjlib-util-x86_64-x64-vc14-Debug \
    -lpjmedia-audiodev-x86_64-x64-vc14-Debug \
    -lpjmedia-codec-x86_64-x64-vc14-Debug \
    -lpjmedia-videodev-x86_64-x64-vc14-Debug \
    -lpjmedia-x86_64-x64-vc14-Debug \
    -lpjnath-x86_64-x64-vc14-Debug \
    -llibgsmcodec-x86_64-x64-vc14-Debug \
    -llibspeex-x86_64-x64-vc14-Debug \
    -llibsrtp-x86_64-x64-vc14-Debug \
    -llibilbccodec-x86_64-x64-vc14-Debug \
    -llibresample-x86_64-x64-vc14-Debug \
    -llibbaseclasses-x86_64-x64-vc14-Debug \
    -llibg7221codec-x86_64-x64-vc14-Debug \
    -llibmilenage-x86_64-x64-vc14-Debug \
    -llibresample-x86_64-x64-vc14-Debug \
    -llibspeex-x86_64-x64-vc14-Debug \
    -llibsrtp-x86_64-x64-vc14-Debug \
    -llibwebrtc-x86_64-x64-vc14-Debug \
    -llibyuv-x86_64-x64-vc14-Debug \
    -lWs2_32 \
    -lOle32 \
    -lMsdmo \
    -lDmoguids \
    -lwmcodecdspuuid \
    -lamstrmid
