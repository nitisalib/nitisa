R"===(
vec4 HSVToRGB(const vec4 hsva)
{
	float C = hsva.b * hsva.g, X = C * (1.0f - abs(mod(hsva.r * 6.0f, 2.0f) - 1.0f)), m = hsva.b - C;
	if (hsva.r <= 1.0f / 6.0f)
		return vec4(C + m, X + m, m, hsva.a);
	if (hsva.r <= 2.0f / 6.0f)
		return vec4(X + m, C + m, m, hsva.a);
	if (hsva.r <= 3.0f / 6.0f)
		return vec4(m, C + m, X + m, hsva.a);
	if (hsva.r <= 4.0f / 6.0f)
		return vec4(m, X + m, C + m, hsva.a);
	if (hsva.r <= 5.0f / 6.0f)
		return vec4(X + m, m, C + m, hsva.a);
	return vec4(C + m, m, X + m, hsva.a);
}
)==="