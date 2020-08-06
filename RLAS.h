#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_RLAS.h"
#include "resources.h"

class RLAS : public QMainWindow
{
    Q_OBJECT

public:
    RLAS(QWidget *parent = Q_NULLPTR);

   void importPoints(vector<Point>&);
   void importAngles(Angle&, string);
   double ctg(Angle);
   double setCtgY(vector<Point>, Angle, Angle);
   double setZ(vector<Point>, Angle, Angle, double);
   void getStationCoordinates(double, double);
   void setAndGetStationCoordinates(vector<Point>, double, double);

   void CalculateButton();
private:
    Ui::RLASClass ui;
};

