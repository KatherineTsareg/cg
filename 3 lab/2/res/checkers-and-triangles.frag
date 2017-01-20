const float M_PI = 3.14159265359;

// Check if the point p is on the left side of the line p0p1
bool PointIsOnTheLeft(vec2 p0, vec2 p1, vec2 p)
{
    vec2 p0p1 = p1 - p0;
    // find the orthogonal vector to p0p1
    vec2 n = vec2(-p0p1.y, p0p1.x);
    // Find the dot product between n and (p - p0)
    return dot(p - p0, n) > 0.0;
}

bool PointIsInsideTriangle(vec2 p0, vec2 p1, vec2 p2, vec2 p)
{
    return PointIsOnTheLeft(p0, p1, p) &&
           PointIsOnTheLeft(p1, p2, p) &&
           PointIsOnTheLeft(p2, p0, p);
}

vec2[6] InitializeComponentsOfStar(vec2 pos, float radius, float additionalAngle)
{
	float step = (M_PI * 2.f) / 5.f;
	float angle = M_PI / 2.f + additionalAngle;
	float littleRadius = radius * cos(2.f * M_PI / 5.f) / cos(M_PI / 5.f);
	vec2 center = vec2(pos.x, pos.y - radius);
	vec2 vertexes[6] = vec2[6](
							  vec2(cos(angle + step * 0.f) * radius + center.x, sin(angle + step * 0.f) * radius + center.y),
							  vec2(cos(angle + step) * radius + center.x, sin(angle + step) * radius + center.y),
							  vec2(cos(angle + step * 2.f) * radius + center.x, sin(angle + step * 2.f) * radius + center.y),
							  vec2(cos(angle + step * 3.f) * radius + center.x, sin(angle + step * 3.f) * radius + center.y),
							  vec2(cos(angle + step * 4.f) * radius + center.x, sin(angle + step * 4.f) * radius + center.y),
							  vec2(cos(angle + M_PI) * littleRadius + center.x, sin(angle + M_PI) * littleRadius + center.y));
	return vertexes;
}

bool PointIsInsideStar(vec2 p, vec2 pos, float radius, float additionalAngle)
{
	vec2 vertexesOfStar[6] = InitializeComponentsOfStar(pos, radius, additionalAngle);
	
	return PointIsInsideTriangle(vertexesOfStar[2], vertexesOfStar[5], vertexesOfStar[0], p) || 
		   PointIsInsideTriangle(vertexesOfStar[5], vertexesOfStar[4], vertexesOfStar[1], p) || 
		   PointIsInsideTriangle(vertexesOfStar[5], vertexesOfStar[3], vertexesOfStar[0], p);
}

void main()
{
    vec2 p = gl_TexCoord[0].xy;
	float mainStarSize = 1.3;
	float additionalStarsSize = 0.4;
	
    if (PointIsInsideStar(p, vec2(2.3, 7.0), mainStarSize, 0.f))
    {
        gl_FragColor = vec4(1.f, 0.9, 0.0, 1.0);
    }
	else if (PointIsInsideStar(p, vec2(4.3, 7.5), additionalStarsSize, M_PI / 4.f) ||
			 PointIsInsideStar(p, vec2(5.f, 6.5), additionalStarsSize, M_PI / 8.f) ||
			 PointIsInsideStar(p, vec2(5.f, 5.4), additionalStarsSize, 0.f) ||
			 PointIsInsideStar(p, vec2(4.3, 4.5), additionalStarsSize, -M_PI / 8.f))
    {
        gl_FragColor = vec4(1.f, 0.9, 0.0, 1.0);
    }
    else
    {
		gl_FragColor = vec4(1.f, 0.f, 0.f, 1.f);
    }
}
