#pragma once
#include "RLAS.h"

RLAS::RLAS(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
}

//Ввод координат точек
void importPoints(vector<Point>& points)
{
	const int STATIONS_NUMBER = 3;
	for (size_t i = 0; i < STATIONS_NUMBER; ++i)
	{
		points.push_back(Point());
		cout << "Введите координаты " << i + 1 << "точки (x,y)\n";
		cout << "X: ";
		cin >> points.back().x;
		cout << "Y:";
		cin >> points.back().y;
	}
}

//Ввод дирекционных углов
void importAngles(Angle& angle, string angle_name)
{
	bool
		AngleIsCorrect = false, //Общий уровень корректности угла
		grad_is_correct = false,
		min_is_correct = false,
		sec_is_correct = false;
	while (AngleIsCorrect != true)
	{
		cout << "Введите угол " + angle_name << endl;

		cout << "grad: ";
		cin >> angle.grad;
		if (angle.grad <= 360.0)
		{
			grad_is_correct = true;
		}
		else
		{
			cout << "Дирекционный угол не может превышать 360 градусов\n";
			continue;
		}
		cout << "min: ";

		cin >> angle.min;
		if (angle.min <= 60.0)
		{
			min_is_correct = true;
		}
		else
		{
			cout << "Минуты угла не могут превышать 60\n";
			continue;
		}
		cout << "sec: ";

		cin >> angle.sec;
		if (angle.sec <= 60.0)
		{
			sec_is_correct = true;
		}
		else
		{
			cout << "Секунды угла не могут превышать 60\n";
			continue;
		}
		if (grad_is_correct == min_is_correct == sec_is_correct == true)
		{
			AngleIsCorrect = true;
		}
	}
}


double ctg(Angle angle)
{
	//Перевод из grad.min.sec в в rad
	double angle_in_rad = (angle.grad + angle.min / 60. + angle.sec / 3600.) * M_PI / 180.;
	return cos(angle_in_rad) / sin(angle_in_rad);
}

//Расчёт котангенса угла Y
double setCtgY(vector<Point> points, Angle alpha, Angle beta)
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
double setZ(vector<Point> points, Angle alpha, Angle beta, double ctgY)
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

void getStationCoordinates(double x, double y)
{
	cout << "X = " << x << " м\n";
	cout << "Y = " << y << " м\n";
}

//Вычисление координат исходного пункта
void setAndGetStationCoordinates(vector<Point> points, double z, double ctgY)
{
	double delta_x = z / (1. + pow(ctgY, 2));
	double delta_y = delta_x * ctgY;
	double x = points[1].x + delta_x;
	double y = points[1].y + delta_y;
	getStationCoordinates(x, y);
}

void RLAS::CalculateButton() 
{
	vector<Point> points;
	Angle
		alpha,
		beta;
	importPoints(points);
	importAngles(alpha, "alpha");
	importAngles(beta, "beta");
	double ctgY = setCtgY(points, alpha, beta);
	double z = setZ(points, alpha, beta, ctgY);
	setAndGetStationCoordinates(points, z, ctgY);
}