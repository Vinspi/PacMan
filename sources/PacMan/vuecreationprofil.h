#ifndef VUECREATIONPROFIL_H
#define VUECREATIONPROFIL_H

#include <QWidget>

namespace Ui {
class vuecreationprofil;
}

class vuecreationprofil : public QWidget
{
    Q_OBJECT

public:
    explicit vuecreationprofil(QWidget *parent = 0);
    ~vuecreationprofil();

private:
    Ui::vuecreationprofil *ui;
};

#endif // VUECREATIONPROFIL_H
