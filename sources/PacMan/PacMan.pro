#-------------------------------------------------
#
# Project created by QtCreator 2017-10-20T09:08:48
#
#-------------------------------------------------

QT += widgets
QT += xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PacMan
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    #controleur.cpp \
  #  entite.cpp \
    gameview.cpp \
    graph.cpp \
  #  joueur.cpp \
    main.cpp \
    mainwindow.cpp \
    #modele.cpp \
    profil.cpp \
    #sommet.cpp \
    tilemanager.cpp \
    vuemenu.cpp \
    vueprofile.cpp \
    collectableitem.cpp \
    dotitem.cpp \
    gamescene.cpp \
    tilemap.cpp \
    superdotitem.cpp \
    entity.cpp \
    pacman.cpp \
    blocitem.cpp \
    muritem.cpp \
    blinky.cpp \
    clyde.cpp \
    ghost.cpp \
    afraidghost.cpp \
    flashafraidghost.cpp \
    inky.cpp \
    pinky.cpp \
    deadghost.cpp \
    spawnblocclyde.cpp \
    spawnblocblinky.cpp \
    spawnblocinky.cpp \
    spawnblocpinky.cpp \
    hud.cpp \
    mysteryitem.cpp \
    mysterybloc.cpp \
    vuecreationprofil.cpp \
    testmodulegraph.cpp \
    testmodulemap.cpp

HEADERS += \
    const.h \
    #controleur.h \
 #   entite.h \
    gameview.h \
    graph.h \
 #   joueur.h \
    mainwindow.h \
    #modele.h \
    profil.h \
    #sommet.h \
    tilemanager.h \
    vuemenu.h \
    vueprofile.h \
    collectableitem.h \
    dotitem.h \
    gamescene.h \
    tilemap.h \
    superdotitem.h \
    entity.h \
    pacman.h \
    blocitem.h \
    muritem.h \
    blinky.h \
    clyde.h \
    ghost.h \
    afraidghost.h \
    flashafraidghost.h \
    inky.h \
    pinky.h \
    deadghost.h \
    spawnblocclyde.h \
    spawnblocblinky.h \
    spawnblocinky.h \
    spawnblocpinky.h \
    hud.h \
    mysteryitem.h \
    mysterybloc.h \
    vuecreationprofil.h \
    testmodulegraph.h \
    testmodulemap.h


CONFIG += c++11

FORMS += \
    mainwindow.ui \
    vueprofile.ui \
    vuemenu.ui \
    vuecreationprofil.ui

RESOURCES += \
    resources.qrc
