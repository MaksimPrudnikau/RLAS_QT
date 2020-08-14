#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_RLAS.h"
#include "resources.h"

#define Q_SLOTS
#define Q_SIGNALS   protected
#define SLOT(a)     "1"#a
#define SIGNAL(a)   "2"#a

class RLAS : public QMainWindow
{
    Q_OBJECT

public:
    RLAS(QWidget *parent = Q_NULLPTR);

   void ifDouble();

   void importPoints(vector<Point>&);
   void importAngles(Angle&, Angle&);
   bool checkAngles(Angle);
   double ctg(Angle);
   double setCtgY(vector<Point>, Angle, Angle);
   double setZ(vector<Point>, Angle, Angle, double);
   Point setStationCoordinates(vector<Point>, double, double);
   void getStationCoordinates(Point, RLAS*);

private slots:
    void Calculate();
private:
    Ui::RLASClass ui;
    QLabel* Station_X;
    QLabel* Station_Y;
};

