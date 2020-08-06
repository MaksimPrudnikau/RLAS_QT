#pragma once
#include "RLAS.h"
#include "qstring.h"
RLAS::RLAS(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
	connect(ui.CalculateButton, SIGNAL(clicked()), this, SLOT(Calculate));
}

void RLAS::ifDouble()
{
}

//���� ��������� �����
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

//���� ������������ �����
void RLAS::checkAngles(Angle angle)
{
	bool
		AngleIsCorrect = false, //����� ������� ������������ ����
		grad_is_correct = false,
		min_is_correct = false,
		sec_is_correct = false;

	while (AngleIsCorrect != true)
	{
		if (angle.grad <= 360.0)
		{
			grad_is_correct = true;
		}
		else
		{
			ui.statusBar->showMessage("������� �� ����� ��������� ������ 360");
			continue;
		}
		if (angle.min <= 60.0)
		{
			min_is_correct = true;
		}
		else
		{
			ui.statusBar->showMessage("������ �� ����� ��������� ������ 360");
			continue;
		}
		if (angle.sec <= 60.0)
		{
			sec_is_correct = true;
		}
		else
		{
			ui.statusBar->showMessage("������� �� ����� ��������� ������ 360");
			continue;
		}
		if (grad_is_correct == min_is_correct == sec_is_correct == true)
		{
			AngleIsCorrect = true;
		}
	}
}


double  RLAS::ctg(Angle angle)
{
	//������� �� grad.min.sec � � rad
	return NULL;
}

//������ ���������� ���� Y
double  RLAS::setCtgY(vector<Point> points, Angle alpha, Angle beta)
{
	return NULL;
}

//������ Z
double  RLAS::setZ(vector<Point> points, Angle alpha, Angle beta, double ctgY)
{
	return NULL;
}

void  RLAS::getStationCoordinates(double x, double y)
{
}

//���������� ��������� ��������� ������
void  RLAS::setAndGetStationCoordinates(vector<Point> points, double z, double ctgY)
{
}

void RLAS::Calculate()
{
	vector<Point> points;
	importPoints(points);
	Angle
		alpha,
		beta;
	importAngles(alpha, beta);
	checkAngles(alpha);
	checkAngles(beta);
}