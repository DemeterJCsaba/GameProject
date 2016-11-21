#include "Maths.h"

vec3 norm(vec3 a, vec3 b, vec3 c) {
	vec3 A = vec3(b.z - a.z,b.y - a.y,b.x - a.x);
	vec3 B = vec3(c.z - a.z,c.y - a.y, c.x - a.x);

	return vec3(A.y*B.x - A.x*B.y , - A.z*B.x + A.x*B.z,A.z*B.y - A.y*B.z);
}