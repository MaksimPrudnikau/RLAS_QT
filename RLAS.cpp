#pragma once
#include "RLAS.h"
#include "qstring.h"
RLAS::RLAS(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
}

//Ввод координат точек
void RLAS::importPoints(vector<Point>& points)
{
}

//Ввод дирекционных углов
void RLAS::importAngles(Angle& angle, string angle_name)
{
}


double  RLAS::ctg(Angle angle)
{
	//Перевод из grad.min.sec в в rad
}

//Расчёт котангенса угла Y
double  RLAS::setCtgY(vector<Point> points, Angle alpha, Angle beta)
{
}

//Расчёт Z
double  RLAS::setZ(vector<Point> points, Angle alpha, Angle beta, double ctgY)
{
}

void  RLAS::getStationCoordinates(double x, double y)
{
}

//Вычисление координат исходного пункта
void  RLAS::setAndGetStationCoordinates(vector<Point> points, double z, double ctgY)
{
}

void RLAS::CalculateButton() 
{
}