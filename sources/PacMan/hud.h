#ifndef HUD_H
#define HUD_H
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QTime>
#include "const.h"
#include "mysteryitem.h"
#include "superdotitem.h"



class HUD : public QWidget
{
public:
    HUD();
    HUD(int nb_vie);
    void addToScore(int points);
    int updateTime();
    int nb_vie();
    void perd_une_vie();
    void setMysteryItem(MysteryItem *mi);
    void resetMysteryItem();

private:
    QLabel *m_score_label;
    QLabel *vie[NB_VIE_MAX];
    QLabel *m_chrono;
    QLabel *m_mystery_item;
    QTime *time;
    int m_nb_vie;
    int m_score;
    QTime timeout;
};

#endif // HUD_H
