QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    AbstractUI.cpp \
    Button.cpp \
    Character.cpp \
    DerivedTile.cpp \
    DungeonCrawler.cpp \
    Factory.cpp \
    Graphicalui.cpp \
    Level.cpp \
    PassiveAndActive.cpp \
    Tile.cpp \
    active.cpp \
    attackController.cpp \
    levelChanger.cpp \
    list.cpp \
    lootChest.cpp \
    main.cpp \
    mainwindow.cpp \
    node.cpp \
    passive.cpp \
    startscreen.cpp

HEADERS += \
    AbstractUI.h \
    Button.h \
    Character.h \
    DerivedTile.h \
    DungeonCrawler.h \
    Factory.h \
    Graphicalui.h \
    Level.h \
    Tile.h \
    active.h \
    attackController.h \
    levelChanger.h \
    list.h \
    lootChest.h \
    mainwindow.h \
    node.h \
    passive.h \
    startscreen.h

FORMS += \
    mainwindow.ui \
    startscreen.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    textures.qrc

DISTFILES += \
    textures/arrows/arrow_down.png \
    textures/arrows/arrow_down_left.png \
    textures/arrows/arrow_down_right.png \
    textures/arrows/arrow_left.png \
    textures/arrows/arrow_right.png \
    textures/arrows/arrow_skip.png \
    textures/arrows/arrow_up.png \
    textures/arrows/arrow_up_left.png \
    textures/arrows/arrow_up_right.png \
    textures/bloody_frame.png \
    textures/char/back/char_back_1.png \
    textures/char/back/char_back_2.png \
    textures/char/back/char_back_3.png \
    textures/char/char_complete.png \
    textures/char/front/char_front_1.png \
    textures/char/front/char_front_2.png \
    textures/char/front/char_front_3.png \
    textures/char/left/char_left_1.png \
    textures/char/left/char_left_2.png \
    textures/char/left/char_left_3.png \
    textures/char/right/char_right_1.png \
    textures/char/right/char_right_2.png \
    textures/char/right/char_right_3.png \
    textures/chest.png \
    textures/doors/door1.png \
    textures/doors/door2.png \
    textures/floor/floor1.png \
    textures/floor/floor2.png \
    textures/floor/floor3.png \
    textures/floor/floor4.png \
    textures/floor/floor5.png \
    textures/load-icon.png \
    textures/new_game_button.png \
    textures/pit.png \
    textures/portal/portal1.png \
    textures/portal/portal2.png \
    textures/portal/portal3.png \
    textures/ramp.png \
    textures/startscreen.png \
    textures/switch.png \
    textures/wall/wall1.png \
    textures/zombie/zombie_left.png \
    textures/zombie/zombie_right.png
