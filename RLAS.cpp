#pragma once
#include "RLAS.h"
#include "qstring.h"
RLAS::RLAS(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
}

//���� ��������� �����
void RLAS::importPoints(vector<Point>& points)
{
}

//���� ������������ �����
void RLAS::importAngles(Angle& angle, string angle_name)
{
}


double  RLAS::ctg(Angle angle)
{
	//������� �� grad.min.sec � � rad
}

//������ ���������� ���� Y
double  RLAS::setCtgY(vector<Point> points, Angle alpha, Angle beta)
{
}

//������ Z
double  RLAS::setZ(vector<Point> points, Angle alpha, Angle beta, double ctgY)
{
}

void  RLAS::getStationCoordinates(double x, double y)
{
}

//���������� ��������� ��������� ������
void  RLAS::setAndGetStationCoordinates(vector<Point> points, double z, double ctgY)
{
}

void RLAS::CalculateButton() 
{
}