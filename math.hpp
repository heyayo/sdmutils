namespace sdm
{
	constexpr float EPSILON = 0.00001f;

	constexpr double root(double num)
	{
		constexpr double error = 1 * 10e-5;
		double s = num;
	
		while (s - num / s > error)
		{
			s = (s + num / s) / 2;
		}
		return s;
	}
	constexpr bool fEqual(float a, float b)
	{ return a - b <= EPSILON && b - a <= EPSILON; }
}
