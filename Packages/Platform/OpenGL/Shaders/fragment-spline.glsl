R"===(
struct SPLINE
{
	float A[4];
	float B[4];
	float AConsts[4];
	float BConsts[4];
};

uniform SPLINE app_Spline;

const float TOLERANCE = 0.000001;

int SolveEquation1n(const float a, out float x1)
{
	x1 = -a;
	return 1;
}

int SolveEquation1n(const float a, const float b, out float x1, const float tolerance)
{
	if (abs(a) >= tolerance)
		return SolveEquation1n(b / a, x1);
	return 0;
}

int SolveEquation2n(const float a, const float b, out float x1, out float x2)
{
	float d = a * a - 4.0f * b;
	if (d > 0.0f)
	{
		float ds = sqrt(d);
		x1 = (-a + ds) / 2.0f;
		x2 = (-a - ds) / 2.0f;
		return 2;
	}
	if (d == 0.0f)
	{
		x1 = -a / 2.0f;
		return 1;
	}
	return 0;
}

int SolveEquation2n(const float a, const float b, const float c, out float x1, out float x2, const float tolerance)
{
	if (abs(a) >= tolerance)
		return SolveEquation2n(b / a, c / a, x1, x2);
	return SolveEquation1n(b, c, x1, tolerance);
}

int SolveEquation3n(const float a, const float b, const float c, out float x1, out float x2, out float x3)
{
	float q = (a * a - 3.0f * b) / 9.0f, r = (2.0f * a * a * a - 9.0f * a * b + 27.0f * c) / 54.0f;
	float q3 = q * q * q, r2 = r * r;
	if (r2 < q3)
	{
		float t = acos(r / sqrt(q3));
		q = -2.0f * sqrt(q);
		x1 = q * cos(t / 3.0f) - a / 3.0f;
		x2 = q * cos((t + 2.0f * 3.1415926535897932384626f) / 3.0f) - a / 3.0f;
		x3 = q * cos((t - 2.0f * 3.1415926535897932384626f) / 3.0f) - a / 3.0f;
		return 3;
	}
	float A = -sign(r) * pow(abs(r) + sqrt(r2 - q3), 1.0f / 3.0f);
	float B = (A == 0.0f) ? 0.0f : (q / A);
	x1 = A + B - a / 3.0f;
	if (A == B)
	{
		x2 = -A - a / 3.0f;
		return 2;
	}
	return 1;
}

int SolveEquation3n(const float a, const float b, const float c, const float d, out float x1, out float x2, out float x3, const float tolerance)
{
	if (abs(a) >= tolerance)
		return SolveEquation3n(b / a, c / a, d / a, x1, x2, x3);
	return SolveEquation2n(b, c, d, x1, x2, tolerance);
}

float CheckPointBetweenSplines(const vec2 point)
{
	float temp_roots1[3];
	int temp_root_count1 = SolveEquation3n(app_Spline.AConsts[0], app_Spline.AConsts[1], app_Spline.AConsts[2], app_Spline.AConsts[3] - point.x, temp_roots1[0], temp_roots1[1], temp_roots1[2], TOLERANCE);
	if (temp_root_count1 > 0)
	{
		float roots1[3];
		int root_count1 = 0;
		for (int i = 0; i < temp_root_count1; i++)
			if (temp_roots1[i] >= 0.0f && temp_roots1[i] <= 1.0f)
				roots1[root_count1++] = temp_roots1[i];
		if (root_count1 > 0)
		{
			float temp_roots2[3];
			int temp_root_count2 = SolveEquation3n(app_Spline.BConsts[0], app_Spline.BConsts[1], app_Spline.BConsts[2], app_Spline.BConsts[3] - point.x, temp_roots2[0], temp_roots2[1], temp_roots2[2], TOLERANCE);
			if (temp_root_count2 > 0)
			{
				float roots2[3];
				int root_count2 = 0;
				for (int i = 0; i < temp_root_count2; i++)
					if (temp_roots2[i] >= 0.0f && temp_roots2[i] <= 1.0f)
						roots2[root_count2++] = temp_roots2[i];
				if (root_count2 > 0)
				{
					float y_min, y_max;
					for (int i = 0; i < root_count1; i++)
					{
						float t = roots1[i], t1 = 1.0f - t;
						float y = t1 * t1 * t1 * app_Spline.A[0] + 3.0f * t * t1 * t1 * app_Spline.A[1] + 3.0f * t * t * t1 * app_Spline.A[2] + t * t * t * app_Spline.A[3];
						if (i == 0)
						{
							y_min = y;
							y_max = y;
						}
						else
						{
							y_min = min(y_min, y);
							y_max = max(y_max, y);
						}
					}
					for (int i = 0; i < root_count2; i++)
					{
						float t = roots2[i], t1 = 1.0f - t;
						float y = t1 * t1 * t1 * app_Spline.B[0] + 3.0f * t * t1 * t1 * app_Spline.B[1] + 3.0f * t * t * t1 * app_Spline.B[2] + t * t * t * app_Spline.B[3];
						y_min = min(y_min, y);
						y_max = max(y_max, y);
					}
					if (point.y >= y_min && point.y <= y_max)
						return 1.0f;
				}
			}
		}
	}
	return 0.0f;
}
)==="