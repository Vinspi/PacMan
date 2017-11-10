#include "entity.h"

Entity::Entity(QString skin) : QGraphicsPixmapItem()
{
    QPixmap pixmap(skin);
    m_vitesse = 1;
    m_direction = UP;
    int width = pixmap.width();

    moveUp.resize(width);
    moveDown.resize(width);
    moveLeft.resize(width);
    moveRight.resize(width);

    for(int c=0;c<pixmap.width()/T_SIZE;c++){
        for(int l=0;l<4;l++){
            if(l == 0){
                /* ajout a move Right */
                moveRight[c] = pixmap.copy(c*T_SIZE,l*T_SIZE,c*T_SIZE+T_SIZE,l*T_SIZE+T_SIZE);
            }
            if(l == 1){
                /* ajout a move Left */
                moveLeft[c] = pixmap.copy(c*T_SIZE,l*T_SIZE,c*T_SIZE+T_SIZE,l*T_SIZE+T_SIZE);
            }
            if(l == 2){
                /* ajout a move Up */
                moveUp[c] = pixmap.copy(c*T_SIZE,l*T_SIZE,c*T_SIZE+T_SIZE,l*T_SIZE+T_SIZE);
            }
            if(l == 3){
                /* ajout a move Down */
                moveDown[c] = pixmap.copy(c*T_SIZE,l*T_SIZE,c*T_SIZE+T_SIZE,l*T_SIZE+T_SIZE);
            }
        }
    }
    setPixmap(QPixmap(skin).copy(32,0,32,32));
}

int Entity::vitesse(){
    return m_vitesse;
}

void Entity::setDirection(int dir){
    m_direction = dir;
}

void Entity::avance(){
    switch (direction()) {
    case UP:
        this->setOffset(this->offset()+QPointF(0,vitesse()));
        break;
    case DOWN:
        this->setOffset(this->offset()+QPointF(0,-vitesse()));
        break;
    case LEFT:
        this->setOffset(this->offset()+QPointF(-vitesse(),0));
        break;
    case RIGHT:
        this->setOffset(this->offset()+QPointF(vitesse(),0));
        break;
    default:
        break;
    }
}

int Entity::direction(){
    return m_direction;
}
