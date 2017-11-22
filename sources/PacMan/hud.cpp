#include "hud.h"
#include <QDebug>


HUD::HUD(int nb_vie) : QWidget()
{

    m_mystery_item = new QLabel();
    //m_mystery_item->setGeometry(0,0,200,200);

    m_mystery_item->setPixmap(QPixmap("../PacMan/graphics_pacman/mystery_box.png").copy(0,0,32,32).scaled(180,180));
    m_mystery_item->setStyleSheet("background-color: #061c29;"
                                  "border: none;"
                                  "color: white;");

    time = new QTime();
    time->start();
    setGeometry(0,0,200,200);
    setStyleSheet("background-color: #061c29;"
                  "border: 5px solid #157ab5;"
                  "color: white;");


    m_chrono = new QLabel("chrono : ");
    m_chrono->setStyleSheet("border: none;");
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(m_chrono);
    m_nb_vie = nb_vie;
    m_score = 0;
    m_score_label = new QLabel("score : 0");

    m_score_label->setStyleSheet("border: none;"
                                 "opacity: 0.3;");

    layout->addWidget(m_score_label);

    QHBoxLayout *layout_vie = new QHBoxLayout();
    QFrame *frame_vie = new QFrame();

    for(int i=0;i<nb_vie;i++){
        vie[i] = new QLabel();
        vie[i]->setPixmap(QPixmap("../PacMan/graphics_pacman/Pacman.png").copy(32,0,32,32).scaled(20,20));
        layout_vie->addWidget(vie[i]);
        vie[i]->setStyleSheet("border: none;");

    }

    QLabel *tmp = new QLabel("lives : ");
    tmp->setStyleSheet("border: none;");
    layout->addWidget(tmp);

    frame_vie->setStyleSheet("border: none;");
    frame_vie->setLayout(layout_vie);

    layout->addWidget(frame_vie);

    layout->addWidget(m_mystery_item);

    setLayout(layout);
    timeout = QTime(0,5,0,0);


}


HUD::HUD() : QWidget()
{

}

void HUD::perd_une_vie(){
    if(m_nb_vie > 0){
        m_nb_vie--;
        vie[m_nb_vie]->setVisible(false);
    }

}

int HUD::nb_vie(){
    return m_nb_vie;
}

int HUD::updateTime(){


    timeout = timeout.addMSecs(-40);

    int total = time->elapsed();
    int milisec = timeout.msec();
    int seconds = timeout.second();
    int minute = timeout.minute();
    m_chrono->setText(QString("chrono : %1:%2:%3").arg(minute).arg(seconds).arg(milisec));

    if(milisec == 0 && seconds == 0 && minute == 0){
        qDebug() << milisec << seconds << minute;
        return 0;
    }
    return 1;
}

void HUD::addToScore(int points){
    m_score += points;
    m_score_label->setText(QString("score : %1").arg(m_score));
}

void HUD::setMysteryItem(MysteryItem *mi){
    m_mystery_item->setPixmap(mi->pixmap().scaled(180,180));
}

void HUD::resetMysteryItem(){
    m_mystery_item->setPixmap(QPixmap("../PacMan/graphics_pacman/mystery_box.png").copy(0,0,32,32).scaled(180,180));
}
