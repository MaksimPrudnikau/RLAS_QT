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
   void checkAngles(Angle);
   double ctg(Angle);
   double setCtgY(vector<Point>, Angle, Angle);
   double setZ(vector<Point>, Angle, Angle, double);
   void getStationCoordinates(double, double);
   void setAndGetStationCoordinates(vector<Point>, double, double);


private slots:
    void Calculate();
private:
    Ui::RLASClass ui;
};

