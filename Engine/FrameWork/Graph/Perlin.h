#ifndef NOISE_H
#define NOISE_H
#include <cmath>
#include <iostream>
class Perlin {
public:
	static float persistence;
	static int Number_Of_Octaves;
	
	Perlin() {
	}

	static double Noise(int x, int y)    // ����(x,y)��ȡһ����������ֵ
	{
		int n = x + y * 57;
		n = (n << 13) ^ n;
		return (1.0 - ((n * (n * n * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0);
	}

	static double SmoothedNoise(int x, int y)   //�⻬����
	{
		double corners = (Noise(x - 1, y - 1) + Noise(x + 1, y - 1) + Noise(x - 1, y + 1) + Noise(x + 1, y + 1)) / 16;
		double sides = (Noise(x - 1, y) + Noise(x + 1, y) + Noise(x, y - 1) + Noise(x, y + 1)) / 8;
		double center = Noise(x, y) / 4;
		return corners + sides + center;
	}
	static double Cosine_Interpolate(double a, double b, double x)  // ���Ҳ�ֵ
	{
		double ft = x * 3.1415927;
		double f = (1 - cos(ft)) * 0.5;
		return a * (1 - f) + b * f;
	}
	static double Linear_Interpolate(double a, double b, double x) //���Բ�ֵ
	{
		return a * (1 - x) + b * x;
	}

	static double InterpolatedNoise(float x, float y)   // ��ȡ��ֵ����
	{
		int integer_X = int(x);
		float  fractional_X = x - integer_X;
		int integer_Y = int(y);
		float fractional_Y = y - integer_Y;
		double v1 = SmoothedNoise(integer_X, integer_Y);
		double v2 = SmoothedNoise(integer_X + 1, integer_Y);
		double v3 = SmoothedNoise(integer_X, integer_Y + 1);
		double v4 = SmoothedNoise(integer_X + 1, integer_Y + 1);
		double i1 = Cosine_Interpolate(v1, v2, fractional_X);
		double i2 = Cosine_Interpolate(v3, v4, fractional_X);
		return Cosine_Interpolate(i1, i2, fractional_Y);
	}

	static double PerlinNoise(float x, float y)    // ���յ��ã�����(x,y)������Ӧ��PerlinNoiseֵ
	{
		double noise = 0;
		double p = persistence;
		int n = Number_Of_Octaves;
		for (int i = 0; i < n; i++)
		{
			double frequency = pow(2, i);
			double amplitude = pow(p, i);
			noise = noise + InterpolatedNoise(x * frequency, y * frequency) * amplitude;
		}
		std::cout << "Perlin:(" << x << ", " << noise << ", " << y << std::endl;
		return noise;
	}


};
#endif // NOISE_H
