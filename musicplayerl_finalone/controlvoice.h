#ifndef CONTROLVOICE_H
#define CONTROLVOICE_H
#include<QtMultimedia>
#include <QSlider>
#include <QDialog>

namespace Ui {
class Controlvoice;
}

class Controlvoice : public QDialog
{
    Q_OBJECT

public:
    explicit Controlvoice(QWidget *parent = 0);
    ~Controlvoice();

private:
    Ui::Controlvoice *ui;
     QPoint dragPos;
private slots:

    void positionChanged(qint64);

   void durationChanged(qint64);


   void on_horizontalSlider_valueChanged(int value);

protected:
   void mousePressEvent(QMouseEvent*);

    void mouseMoveEvent(QMouseEvent*);
signals:
    void send(int);
};

#endif // CONTROLVOICE_H
