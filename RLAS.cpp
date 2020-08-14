#pragma once
#define _USE_MATH_DEFINES
#include "RLAS.h"
#include "qstring.h"
#include <qlocale.h>
#include <cmath>
RLAS::RLAS(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
	connect(ui.CalculateButton, SIGNAL(clicked()), this, SLOT(Calculate));
}

void RLAS::ifDouble()
{
}

//Ввод координат точек
void RLAS::importPoints(vector<Point>& points)
{
	const int STATIONS_NUMBER = 3;
	for (size_t i = 0; i < STATIONS_NUMBER; ++i)
	{
		points.push_back(Point());
	}
	points[0].x = ui.Point1_X->text().toDouble();
	points[0].y = ui.Point1_Y->text().toDouble();
	points[1].x = ui.Point2_X->text().toDouble();
	points[1].y = ui.Point2_Y->text().toDouble();
	points[2].x = ui.Point3_X->text().toDouble();
	points[2].y = ui.Point3_Y->text().toDouble();
}

void RLAS::importAngles(Angle& alpha, Angle& beta)
{
	alpha.grad = ui.Alpha_Degrees->text().toDouble();
	alpha.min = ui.Alpha_Minutes->text().toDouble();
	alpha.sec = ui.Alpha_Seconds->text().toDouble();
	beta.grad = ui.Beta_Degrees->text().toDouble();
	beta.min =  ui.Beta_Minutes->text().toDouble();
	beta.sec =  ui.Beta_Seconds->text().toDouble();
}

//Ввод дирекционных углов
bool RLAS::checkAngles(Angle angle)
{
	bool
		AngleIsCorrect = false, //Общий уровень корректности угла
		grad_is_correct = false,
		min_is_correct = false,
		sec_is_correct = false;
		if (angle.grad <= 360.0)
		{
			grad_is_correct = true;
		}
		else
		{
			statusBar()->showMessage(QString::fromLocal8Bit("Градусы не могут превышать больше 360"));
		}
		if (angle.min <= 60)
		{
			min_is_correct = true;
		}
		else
		{
			statusBar()->showMessage(QString::fromLocal8Bit("Минуты не могут превышать больше 60"));
		}
		if (angle.sec <= 60.0)
		{
			sec_is_correct = true;
		}
		else
		{
			statusBar()->showMessage(QString::fromLocal8Bit("Секунды не могут превышать больше 60"));
		}
		if (grad_is_correct == min_is_correct == sec_is_correct == true)
		{
			AngleIsCorrect = true;
		}
		return AngleIsCorrect;
}


double  RLAS::ctg(Angle angle)
{
	//Перевод из grad.min.sec в в rad
	double angle_in_rad = (angle.grad + angle.min / 60. + angle.sec / 3600.) * M_PI / 180.;
	return cos(angle_in_rad) / sin(angle_in_rad);
}

//Расчёт котангенса угла Y
double  RLAS::setCtgY(vector<Point> points, Angle alpha, Angle beta)
{
	double
		numerator, //числитель
		denominator; // знаменатель
	numerator =
		(points[1].y - points[0].y) * ctg(alpha)
		- (points[2].y - points[1].y) * ctg(beta)
		+ (points[0].x - points[2].x);
	denominator =
		(points[1].x - points[0].x) * ctg(alpha)
		- (points[2].x - points[1].x) * ctg(beta)
		- (points[0].y - points[2].y);
	return numerator / denominator;
}

//Расчёт Z
double  RLAS::setZ(vector<Point> points, Angle alpha, Angle beta, double ctgY)
{
	double
		Z1,
		Z2;
	Z1 =
		(points[1].y - points[0].y) * (ctg(alpha) - ctgY)
		- (points[1].x - points[0].x) * (1 + ctg(alpha) * ctgY);
	Z2 =
		(points[2].y - points[1].y) * (ctg(beta) + ctgY)
		+ (points[2].x - points[1].x) * (1 - ctg(beta) * ctgY);
	return (Z1 + Z2) / 2.;
}


//Вычисление координат исходного пункта
Point  RLAS::setStationCoordinates(vector<Point> points, double z, double ctgY)
{
	double delta_x = z / (1. + pow(ctgY, 2));
	double delta_y = delta_x * ctgY;
	double x = points[1].x + delta_x;
	double y = points[1].y + delta_y;
	return Point({ x,y });
}


void  RLAS::getStationCoordinates(Point station, RLAS* Window)
{
	//Window->ui.Station_X->setText(QString::number(station.x, 'f', 3));
	//Window->ui.Station_Y->setText(QString::number(station.y, 'f', 3));
	setStatusBar(nullptr);
	Station_X = new QLabel(this);
	Station_Y = new QLabel(this);
	statusBar()->addWidget(Station_X);
	statusBar()->addWidget(Station_Y);
	Station_X->setText("X = " + QString::number(station.x, 'f', 4));
	Station_Y->setText("Y = " + QString::number(station.y, 'f', 4));
	
	
}
void RLAS::Calculate()
{
	vector<Point> points;
	importPoints(points);
	Angle
		alpha,
		beta;
	importAngles(alpha, beta);
	if (checkAngles(alpha) && checkAngles(beta))
	{
		double ctgY = setCtgY(points, alpha, beta);
		double z = setZ(points, alpha, beta, ctgY);
		getStationCoordinates(setStationCoordinates(points, z, ctgY),this);
	}
}