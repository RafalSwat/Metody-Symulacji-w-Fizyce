#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>

void Verlet();
void Verlet_predkosciowy();

void Verlet()
{
	std::ofstream file;
	file.open("./SKF_list2.zad1a.csv", std::ios::out);

	double h = 0.05;
	size_t n = 100;

	std::vector<double> vx;
	std::vector<double> vy;
	std::vector<double> t;
	std::vector<double> x;
	std::vector<double> y;
	std::vector<double> r;
	std::vector<double> ax;
	std::vector<double> ay;
	//inicjalizacja pierwszego kroku
	x.push_back(0.5);
	y.push_back(0.0001);
	r.push_back(sqrt(x[0] * x[0] + y[0] * y[0]));
	vx.push_back(0);
	vy.push_back(1.63);
	ax.push_back((-x[0]) / (r[0] * r[0] * r[0]));
	ay.push_back((-y[0]) / (r[0] * r[0] * r[0]));
	//inicjalizacja drugiego kroku
	x.push_back(x[0] - h * vx[0] * ax[0]);
	y.push_back(y[0] - h * vy[0] * ay[0]);
	r.push_back(sqrt(x[1] * x[1] + y[1] * y[1]));
	ax.push_back((-x[1]) / (r[1] * r[1] * r[1]));
	ay.push_back((-y[1]) / (r[1] * r[1] * r[1]));

	for (size_t i = 2; i < n; i++)
	{
		x.push_back(2 * x[i - 1] - x[i - 2] + h * ax[i - 1]);
		y.push_back(2 * y[i - 1] - y[i - 2] + h * ay[i - 1]);
		vx.push_back((x[i - 2] - x[i]) / (2 * h));
		vy.push_back((y[i - 2] - y[i]) / (2 * h));
		r.push_back(sqrt(x[1] * x[1] + y[1] * y[1]));
		ax.push_back((-x[i]) / (r[i] * r[i] * r[i]));
		ay.push_back((-y[i]) / (r[i] * r[i] * r[i]));
	}
	for (size_t i = 0; i < n; i++)
	{
		file << x[i] << ',' << y[i] << std::endl;
	}
}
void Verlet_predkosciowy()
{
	std::ofstream file;
	file.open("./SKF_list2.zad1b.csv", std::ios::out);

	double h = 0.05;
	size_t n = 10000;

	std::vector<double> vx;
	std::vector<double> vy;
	std::vector<double> t;
	std::vector<double> x;
	std::vector<double> y;
	std::vector<double> r;
	std::vector<double> ax;
	std::vector<double> ay;
	//inicjalizacja pierwszego kroku
	x.push_back(0.5);
	y.push_back(0);
	r.push_back(sqrt(x[0] * x[0] + y[0] * y[0]));
	vx.push_back(0);
	vy.push_back(1.63);
	ax.push_back((-x[0]) / (r[0] * r[0] * r[0]));
	ay.push_back((-y[0]) / (r[0] * r[0] * r[0]));

	for (size_t i = 1; i < n; i++)
	{
		x.push_back(x[i - 1] + h*vx[i - 1] + (h*h*ax[i - 1]));
		y.push_back(y[i - 1] + h*vy[i - 1] + (h*h*ay[i - 1]));
		r.push_back(sqrt(x[i] * x[i] + y[i] * y[i]));
		ax.push_back((-x[i]) / (r[i] * r[i] * r[i]));
		ay.push_back((-y[i]) / (r[i] * r[i] * r[i]));
		vx.push_back(vx[i-1] * (h / 2)*(ax[i] + ax[i - 1]));
		vy.push_back(vy[i-1] * (h / 2)*(ay[i] + ay[i - 1]));
	}
	for (size_t i = 0; i < n; i++)
	{
		file << x[i] << ',' << y[i] << std::endl;
	}

}


int main()
{
	//Verlet();
	Verlet_predkosciowy();

	system("pause");
	return 0;
}
