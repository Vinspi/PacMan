#! /bin/sh
export PATH=/opt/qt-everywhere-opensource-src-5.7.0/bin:$PATH
cp -r ../../sources/PacMan/* ./
qmake
make
rm *.o
rm *.cpp
rm -r ressources
rm *.h
rm PacMan.pro
rm PacMan.pro.user
rm *.ui




