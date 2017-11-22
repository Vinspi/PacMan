#include "entity.h"

Entity::Entity() : QGraphicsPixmapItem()
{

}

void Entity::setLastPos(QPointF lastpos){
    m_last_position = lastpos;
}

Entity::Entity(QString skin) : QGraphicsPixmapItem()
{
    QPixmap pixmap(skin);

    m_vitesse = 0;
    m_direction = RIGHT;
    m_last_direction = RIGHT;
    m_frame = 0;
    m_last_frame = 0;
    int width = pixmap.width();
    moveUp.resize(width);
    moveDown.resize(width);
    moveLeft.resize(width);
    moveRight.resize(width);

    m_max_frame = pixmap.width()/T_SIZE;

    for(int c=0;c<pixmap.width()/T_SIZE;c++){
        for(int l=0;l<4;l++){
            if(l == 0){
                /* ajout a move Right */
                moveRight[c] = pixmap.copy(c*T_SIZE,l*T_SIZE,T_SIZE,T_SIZE);
            }
            if(l == 1){
                /* ajout a move Left */
                moveLeft[c] = pixmap.copy(c*T_SIZE,l*T_SIZE,T_SIZE,T_SIZE);
            }
            if(l == 2){
                /* ajout a move Up */
                moveUp[c] = pixmap.copy(c*T_SIZE,l*T_SIZE,T_SIZE,T_SIZE);
            }
            if(l == 3){
                /* ajout a move Down */
                moveDown[c] = pixmap.copy(c*T_SIZE,l*T_SIZE,T_SIZE,T_SIZE);
            }
        }
    }
    setPixmap(QPixmap(skin).copy(0,0,32,32));
}

void Entity::paint(QPainter *painter,
                          const QStyleOptionGraphicsItem *option,
                          QWidget *widget){
    painter->drawPixmap(0,0,this->pixmap());

}

void Entity::setVitesse(int v){
    m_vitesse = v;
}

int Entity::vitesse(){
    return m_vitesse;
}


void Entity::setDirection(int dir){
    m_last_direction = m_direction;
    m_direction = dir;
}

void Entity::annule_deplacement(){
    setPos(m_last_position);
    m_direction = m_last_direction;
    m_frame=m_last_frame;
}

void Entity::avance(){

        m_last_position = pos();

        //qDebug() << m_vitesse << " " << CYCLE_VITESSE << " " << m_vitesse*CYCLE_VITESSE << endl;

        switch (direction()) {
        case UP:
            this->setPixmap(moveUp[m_frame]);

            this->setPos(this->pos()+QPointF(0,-1));
            break;
        case DOWN:
            this->setPixmap(moveDown[m_frame]);

            this->setPos(this->pos()+QPointF(0,1));
            break;
        case LEFT:
            this->setPixmap(moveLeft[m_frame]);

            this->setPos(this->pos()+QPointF(-1,0));
            break;
        case RIGHT:
            this->setPixmap(moveRight[m_frame]);

            this->setPos(this->pos()+QPointF(1,0));
            break;
        default:
            break;


    }
    m_last_frame=m_frame;

}

void Entity::nextTile(){
    m_frame=(m_frame+1)%(m_max_frame);
}

QRectF Entity::boundingRect() const {
    return QRectF(0,0,32,32);
}

int Entity::direction(){
    return m_direction;
}

QPainterPath Entity::shape() const {
    QPainterPath path;
    path.addRect(QRectF(1,1,30,30));
    return path;
}

QPoint Entity::current_tile_pos(){
    QPoint p((pos().x()+T_SIZE/2)/T_SIZE,(pos().y()+T_SIZE/2)/T_SIZE);
    return p;
}

void Entity::setMode(int mode){
    m_mode = mode;
}


