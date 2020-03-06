#pragma once
#include <vector>
#include <glm/glm.hpp>
using std::vector;
class BSpline
{
public:
	vector<glm::vec2> ctrlPoints;
	vector<glm::vec2> resultPoints;
	vector<int> colorMap;
	BSpline() {
		colorMap.resize(256);
	}
	void addOriginPoints(glm::vec2 point)
	{
		ctrlPoints.emplace_back(point);
	}

	void clear() {
		ctrlPoints.clear();
		resultPoints.clear();
	}
	void update() {
		computeBSplineCurveArray3(colorMap, ctrlPoints);
	}
	float F(float x) {
		float y = x * x * x - x;
		return y;
	}

	void setPandU(vector<float>& p, vector<float>& u, vector<glm::vec2>& pt)
	{
		if (p.size() == 0 || u.size() == 0 || pt.size() == 0) {
			return;
		}
		int ptCount = pt.size();
		float* d = new float[ptCount];
		float* w = new float[ptCount];
		for (int i = 0; i < ptCount; i++)
		{
			d[i] = 0.0f;
			w[i] = 0.0f;
		}
		for (int i = 1; i < ptCount - 1; i++)
			d[i] = 2 * (pt[i + 1].x - pt[i - 1].x);
		for (int i = 0; i < ptCount - 1; i++)
			u[i] = (pt[i + 1].x - pt[i].x);
		for (int i = 1; i < ptCount - 1; i++)
			w[i] = 6.0f * ((pt[i + 1].y - pt[i].y) / u[i] - (pt[i].y - pt[i - 1].y) / u[i - 1]);
		for (int i = 1; i < ptCount - 2; i++)
		{
			w[i + 1] = w[i + 1] - w[i] * u[i] / d[i];
			d[i + 1] = d[i + 1] - u[i] * u[i] / d[i];
		}
		p[0] = 0.0f;
		for (int i = ptCount - 2; i > 0; i--)
			p[i] = (w[i] - u[i] * p[i + 1]) / d[i];
		p[ptCount - 1] = 0.0f;
		delete[] d;
		delete[] w;
	}

	int getCurvePoint(int i, int v, vector<glm::vec2>& pt, vector<float>& u, vector<float>& p)
	{
		float t = 0.0f;
		float m = (float)v;
		int getcurvepoint;
		t = (float)((m - pt[i].x) / u[i]);
		getcurvepoint = (int)(t * (pt[i + 1].y) + (1 - t) * (pt[i].y) + u[i] * u[i] * (F(t) * p[i + 1] + F(1 - t) * p[i]) / 6.0 + 0.5);
		return getcurvepoint;
	}


	int computeBSplineCurveArray3(vector<int>& colors, vector<glm::vec2>& pt)
	{
		int i;
		int ptCount = pt.size();
		int colorsCount = colors.size();
		int minX = colors.size();
		int maxX = -1;
		vector<float> p(ptCount, 0.0f);
		vector<float> u(ptCount, 0.0f);
		setPandU(p, u, pt);
		int xPos, yPos;
		for (i = 0; i < ptCount - 1; i++)
		{
			for (xPos = (int)(pt[i].x); xPos < pt[i + 1].x; xPos++)
			{
				yPos = getCurvePoint(i, xPos, pt, u, p);
				if (xPos < minX)
					minX = xPos;
				if (xPos > maxX)
					maxX = xPos;
				if (yPos > colorsCount)
					yPos = colorsCount - 1;
				if (yPos < 0)
					yPos = 0;
				colors[xPos] = yPos;

				if (colors[xPos] > colorsCount - 1) {
					colors[xPos] = colorsCount - 1;
				}
				if (colors[xPos] < 0) {
					colors[xPos] = 0;
				}
			}
		}
		if (minX > colorsCount - 1) {
			minX = colorsCount - 1;
		}
		for (i = 0; i < minX; i++) {
			colors[i] = colors[minX];
			if (colors[i] > colorsCount - 1) {
				colors[i] = colorsCount - 1;
			}
			if (colors[i] < 0) {
				colors[i] = 0;
			}
		}
		for (i = colorsCount - 1; i > maxX; i--)
		{
			if (ptCount < 1)
				break;
			colors[i] = (int)pt[ptCount - 1].y;
			if (colors[i] > colorsCount - 1)
			{
				colors[i] = colorsCount - 1;
			}
			if (colors[i] < 0)
			{
				colors[i] = 0;
			}
		}

		return 1;
	}
};