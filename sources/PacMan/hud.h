#ifndef HUD_H
#define HUD_H
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QTime>
#include "const.h"



class HUD : public QWidget
{
public:
    HUD();
    HUD(int nb_vie);
    void addToScore(int points);
    int updateTime();
    int nb_vie();
    void perd_une_vie();

private:
    QLabel *m_score_label;
    QLabel *vie[NB_VIE_MAX];
    QLabel *m_chrono;
    QTime *time;
    int m_nb_vie;
    int m_score;
    QTime timeout;
};

#endif // HUD_H
