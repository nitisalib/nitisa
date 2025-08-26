R"===(
struct BLOCK_DATA
{
	vec4 Rect; // Block rectangle
	vec4 Border; // Block border widths
	vec4 Radius; // Block corner radiuses

	float InnerScale[4]; // Precalculated value. You can find how to calculate in in renderer implementation source code
	float InnerRadius[4]; // Precalculated value. You can find how to calculate in in renderer implementation source code
	vec2 CornerCenter[4]; // Corner center. Edge point of corner. Precalculated value. You can find how to calculate in in renderer implementation source code
	vec2 OuterRCenter[4]; // Circle center to check if poin is outside outer radius. Precalculated value. You can find how to calculate in in renderer implementation source code
	bvec4 HasInner; // Whether inner corner is round or sharp. Precalculated value. You can find how to calculate in in renderer implementation source code
};

uniform BLOCK_DATA app_Blocks[2];
uniform vec4 app_BlockColors[6];

const int plLeft = 0;
const int plTop = 1;
const int plRight = 2;
const int plBottom = 3;
const int plInside = 4;
const int plOutside = 5;

const float Tolerance = 0.001;

int BlockPointLocation(const vec2 p, const int index)
{
	if (p.x < app_Blocks[index].Rect[0] || p.x >= app_Blocks[index].Rect[2] || p.y < app_Blocks[index].Rect[1] || p.y >= app_Blocks[index].Rect[3]) // Check if point is outside block rectangle at all
		return plOutside;
	//	Left-top corner
	if (p.x < app_Blocks[index].CornerCenter[0].x && p.y < app_Blocks[index].CornerCenter[0].y) // Check point is inside left-top corner area
	{
		if (app_Blocks[index].Radius[0] > Tolerance) // Check the corner is round one
		{
			if (p.x < app_Blocks[index].OuterRCenter[0].x && p.y < app_Blocks[index].OuterRCenter[0].y) // Check point is outside outer radius
			{
				float dx = app_Blocks[index].OuterRCenter[0].x - p.x, dy = app_Blocks[index].OuterRCenter[0].y - p.y, d = sqrt(dx * dx + dy * dy); // Distance from point to circle center
				if (d > app_Blocks[index].Radius[0]) // Check if point is outside of round corner
					return plOutside;
			}
			if (app_Blocks[index].HasInner[0]) // There is inside round corner. Check if point is inside the block
			{
				float dx = app_Blocks[index].OuterRCenter[0].x - p.x, dy = (app_Blocks[index].OuterRCenter[0].y - p.y) / app_Blocks[index].InnerScale[0], d = sqrt(dx * dx + dy * dy);
				if (d < app_Blocks[index].InnerRadius[0])
					return plInside;
			}
		}
		if (app_Blocks[index].Border[0] > Tolerance)
		{
			if (app_Blocks[index].Border[1] > Tolerance)
			{
				if (p.y - app_Blocks[index].Rect[1] > (p.x - app_Blocks[index].Rect[0]) * app_Blocks[index].Border[1] / app_Blocks[index].Border[0])
					return plLeft;
				return plTop;
			}
			return plLeft;
		}
		return plTop;
	}
	// Right-top corner
	if (p.x >= app_Blocks[index].CornerCenter[1].x && p.y < app_Blocks[index].CornerCenter[1].y)
	{
		if (app_Blocks[index].Radius[1] > Tolerance)
		{
			if (p.x >= app_Blocks[index].OuterRCenter[1].x && p.y < app_Blocks[index].OuterRCenter[1].y)
			{
				float dx = p.x - app_Blocks[index].OuterRCenter[1].x, dy = app_Blocks[index].OuterRCenter[1].y - p.y, d = sqrt(dx * dx + dy * dy); // Distance from point to circle center
				if (d > app_Blocks[index].Radius[1]) // Check if point is outside of round corner
					return plOutside;
			}
			if (app_Blocks[index].HasInner[1]) // There is inside rounded corner. Check if point is inside block
			{
				float dx = p.x - app_Blocks[index].OuterRCenter[1].x, dy = (app_Blocks[index].OuterRCenter[1].y - p.y) / app_Blocks[index].InnerScale[1], d = sqrt(dx * dx + dy * dy);
				if (d < app_Blocks[index].InnerRadius[1])
					return plInside;
			}
		}
		if (app_Blocks[index].Border[2] > Tolerance)
		{
			if (app_Blocks[index].Border[1] > Tolerance)
			{
				if (p.y - app_Blocks[index].Rect[1] > (app_Blocks[index].Rect[2] - p.x) * app_Blocks[index].Border[1] / app_Blocks[index].Border[2])
					return plRight;
				return plTop;
			}
			return plRight;
		}
		return plTop;
	}
	// Right-bottom corner
	if (p.x >= app_Blocks[index].CornerCenter[2].x && p.y >= app_Blocks[index].CornerCenter[2].y)
	{
		if (app_Blocks[index].Radius[2] > Tolerance)
		{
			if (p.x >= app_Blocks[index].OuterRCenter[2].x && p.y >= app_Blocks[index].OuterRCenter[2].y)
			{
				float dx = p.x - app_Blocks[index].OuterRCenter[2].x, dy = p.y - app_Blocks[index].OuterRCenter[2].y, d = sqrt(dx * dx + dy * dy); // Distance from point to circle center
				if (d > app_Blocks[index].Radius[2]) // Check if point is outside of round corner
					return plOutside;
			}
			if (app_Blocks[index].HasInner[2]) // There is inside rounded corner. Check if point is inside block
			{
				float dx = p.x - app_Blocks[index].OuterRCenter[2].x, dy = (app_Blocks[index].OuterRCenter[2].y - p.y) / app_Blocks[index].InnerScale[2], d = sqrt(dx * dx + dy * dy);
				if (d < app_Blocks[index].InnerRadius[2])
					return plInside;
			}
		}
		if (app_Blocks[index].Border[2] > Tolerance)
		{
			if (app_Blocks[index].Border[3] > Tolerance)
			{
				float k = app_Blocks[index].Border[3] / app_Blocks[index].Border[2], b = app_Blocks[index].Rect[3] - app_Blocks[index].Border[3] - k * (app_Blocks[index].Rect[2] - app_Blocks[index].Border[2]);
				if (p.y > k * p.x + b)
					return plBottom;
				return plRight;
			}
			return plRight;
		}
		return plBottom;
	}
	// Left-bottom corner
	if (p.x < app_Blocks[index].CornerCenter[3].x && p.y >= app_Blocks[index].CornerCenter[3].y)
	{
		if (app_Blocks[index].Radius[3] > Tolerance)
		{
			if (p.x < app_Blocks[index].OuterRCenter[3].x && p.y >= app_Blocks[index].OuterRCenter[3].y)
			{
				float dx = app_Blocks[index].OuterRCenter[3].x - p.x, dy = p.y - app_Blocks[index].OuterRCenter[3].y, d = sqrt(dx * dx + dy * dy); // Distance from point to circle center
				if (d > app_Blocks[index].Radius[3]) // Check if point is outside of round corner
					return plOutside;
			}
			if (app_Blocks[index].HasInner[3]) // There is inside rounded corner. Check if point is inside block
			{
				float dx = app_Blocks[index].OuterRCenter[3].x - p.x, dy = (app_Blocks[index].OuterRCenter[3].y - p.y) / app_Blocks[index].InnerScale[3], d = sqrt(dx * dx + dy * dy);
				if (d < app_Blocks[index].InnerRadius[3])
					return plInside;
			}
		}
		if (app_Blocks[index].Border[0] > Tolerance)
		{
			if (app_Blocks[index].Border[3] > Tolerance)
			{
				if (app_Blocks[index].Rect[3] - p.y > (p.x - app_Blocks[index].Rect[0]) * app_Blocks[index].Border[3] / app_Blocks[index].Border[0])
					return plLeft;
				return plBottom;
			}
			return plLeft;
		}
		return plBottom;
	}
	// Left border
	if (p.x < app_Blocks[index].Rect[0] + app_Blocks[index].Border[0])
		return plLeft;
	// Top border
	if (p.y < app_Blocks[index].Rect[1] + app_Blocks[index].Border[1])
		return plTop;
	// Right border
	if (p.x >= app_Blocks[index].Rect[2] - app_Blocks[index].Border[2])
		return plRight;
	// Bottom border
	if (p.y >= app_Blocks[index].Rect[3] - app_Blocks[index].Border[3])
		return plBottom;
	// Inside
	return plInside;
}

vec4 BlockPointColor(const vec2 p, const int index)
{
	return app_BlockColors[BlockPointLocation(p, index)];
}
)==="