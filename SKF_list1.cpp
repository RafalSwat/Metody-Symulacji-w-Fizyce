#include <iostream>
#include <cmath>
#include <fstream>

void Zadanie1()
{
	std::ofstream file;
	file.open("./data.csv", std::ios::out);

	const int n = 10000;
	double h = 0.05;
	double kx1, kx2, kx3, kx4, kvx1, kvx2, kvx3, kvx4;
	double ky1, ky2, ky3, ky4, kvy1, kvy2, kvy3, kvy4;;
	double x[n], y[n], vx[n], vy[n], Ek[n], Ep[n], E[n], t[n];
	x[0] = 0.5;
	y[0] = 0;
	vx[0] = 0;
	vy[0] = 1.63;
	t[0] = 0;
	
	double r = sqrt(x[0] * x[0] + y[0] * y[0]);
	double x_temp, y_temp, vx_temp, vy_temp;

	Ek[0] = 0.5 * (vx[0] * vx[0] + vy[0] * vy[0]);
	Ep[0] = 1 /(r * r);
	E[0] = Ek[0] + Ep[0];

	for (int i = 0; i<n - 1; i++)
	{
		// K1s
		kvx1 = -x[i] / pow(r, 3);
		kx1 = vx[i];
		kvy1 = -y[i] / pow(r, 3);
		ky1 = vy[i];

		// auxilliary
		vx_temp = vx[i] + 0.5*h*kvx1;
		x_temp = x[i] + 0.5*kx1*h;
		vy_temp = vy[i] + 0.5*h*kvy1;
		y_temp = y[i] + 0.5*ky1*h;
		r = sqrt(x_temp*x_temp + y_temp * y_temp);

		// K2s
		kvx2 = -(x_temp) / pow(r, 3);
		kx2 = vx_temp;
		kvy2 = -(y_temp) / pow(r, 3);
		ky2 = vy_temp;

		// auxilliary
		vx_temp = vx[i] + 0.5*h*kvx2;
		x_temp = x[i] + 0.5*kx2*h;
		vy_temp = vy[i] + 0.5*h*kvy2;
		y_temp = y[i] + 0.5*ky2*h;
		r = sqrt(x_temp*x_temp + y_temp * y_temp);

		// K3s
		kvx3 = -(x_temp) / pow(r, 3);
		kx3 = vx_temp;
		kvy3 = -(y_temp) / pow(r, 3);
		ky3 = vy_temp;

		// auxilliary
		vx_temp = vx[i] + h * kvx3;
		x_temp = x[i] + kx3 * h;
		vy_temp = vy[i] + h * kvy3;
		y_temp = y[i] + ky3 * h;
		r = sqrt(x_temp*x_temp + y_temp * y_temp);

		// K4s
		kvx4 = -(x_temp) / pow(r, 3);
		kx4 = vx_temp;
		kvy4 = -(y_temp) / pow(r, 3);
		ky4 = vy_temp;


		vx[i + 1] = vx[i] + (h / 6)*(kvx1 + 2 * kvx2 + 2 * kvx3 + kvx4);
		x[i + 1] = x[i] + (h / 6)*(kx1 + 2 * kx2 + 2 * kx3 + kx4);
		vy[i + 1] = vy[i] + (h / 6)*(kvy1 + 2 * kvy2 + 2 * kvy3 + kvy4);
		y[i + 1] = y[i] + (h / 6)*(ky1 + 2 * ky2 + 2 * ky3 + ky4);

		r = sqrt(x[i + 1] * x[i + 1] + y[i + 1] * y[i + 1]);
		Ek[i + 1] = 0.5 * (vx[i+1] * vx[i+1] + vy[i+1] * vy[i+1]);
		Ep[i + 1] = 1 / (r*r);
		E[i + 1] = Ek[i + 1] + Ep[i + 1];
		t[i + 1] = i * h;
	}

	file << "x,y,vx,vy,Ep,Ek,E\n";
	for (int i = 0; i<n; i++)
	{
		file << x[i] << ',' << y[i] << ',' << vx[i] << ',' << vy[i] << ',' << Ep[i] << ',' << Ek[i] << ',' << E[i] << ',' << t[i] << '\n';
	}
	file.close();
}
void Zadanie2()
{
	std::ofstream file1, file2, file3;
	file1.open("./Q_01.csv", std::ios::out);
	file2.open("./Q_1.csv", std::ios::out);
	file3.open("./Q_10.csv", std::ios::out);

	const int n = 20000;
	double Q = 0.1;

	for (int j = 1; j < 4; j++)
	{
		double q[n]; q[0] = 0.0;
		double p[n]; p[0] = 1.0;
		double z[n]; z[0] = 0;
		double h = 0.001;

		double kq1, kq2, kq3, kq4;
		double kp1, kp2, kp3, kp4;
		double kz1, kz2, kz3, kz4;

		for (int i = 0; i < n - 1; i++)
		{
			kq1 = h * p[i];
			kp1 = h * (-q[i] - z[i] * p[i]);
			kz1 = h * ((p[i] * p[i] - 1) / Q);

			kq2 = h * p[i] + 0.5 * h * kq1;
			kp2 = h * (-q[i] - z[i] * p[i]) + 0.5 * h * kp1;
			kz2 = h * ((p[i] * p[i] - 1) / Q) + 0.5 * h * kz1;

			kq3 = h * p[i] + 0.5 * h * kq2;
			kp3 = h * (-q[i] - z[i] * p[i]) + 0.5 * h * kp2;
			kz3 = h * ((p[i] * p[i] - 1) / Q) + 0.5 * h * kz2;

			kq4 = h * p[i] + h * kq2;
			kp4 = h * (-q[i] - z[i] * p[i]) + h * kp2;
			kz4 = h * ((p[i] * p[i] - 1) / Q) + h * kz2;

			q[i + 1] = q[i] + (1.0 / 6.0) * (kq1 + 2 * kq2 + 2 * kq3 + kq4);
			p[i + 1] = p[i] + (1.0 / 6.0) * (kp1 + 2 * kp2 + 2 * kp3 + kp4);
			z[i + 1] = z[i] + (1.0 / 6.0) * (kz1 + 2 * kz2 + 2 * kz3 + kz4);
		}
		//std::cout << "---------------- Q = " << Q << " --------------------" << std::endl;
		//std::cout << "q, p, z" << std::endl;
		
		for (int k = 0; k < n; k++)
		{
			if(Q == 0.1) file1 << q[k] << ',' << p[k] << ',' << z[k] << std::endl;
			if(Q == 1) file2 << q[k] << ',' << p[k] << ',' << z[k] << std::endl;
			if (Q == 10) file3 << q[k] << ',' << p[k] << ',' << z[k] << std::endl;

		}
		Q *= 10;
	}
	file1.close();
	file2.close();
	file3.close();
}

int main()
{
	Zadanie1();
	//Zadanie2();

	system("pause");
	return 0;
}
