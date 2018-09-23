#include "pch.h"
#include "rayt.h"

float hit_sphere(const vec3& center, float radius, const rayt::Ray& r) {
	vec3 oc = r.origin() - center;
	float a = dot(r.direction(), r.direction());
	float b = 2.0f * dot(r.direction(), oc);
	float c = dot(oc, oc) - pow2(radius);
	float D = b * b - 4 * a*c;
	if (D < 0) {
		return -1.0f;
	}
	else {
		return (-b - sqrtf(D)) / (2.0f*a);
	}
}

vec3 color(const rayt::Ray& r) {
	vec3 c(0, 0, -1);
	float t = hit_sphere(c, 0.5f, r);
	if (t > 0.0f) {
		vec3 N = normalize(r.at(t) - c);
		return 0.5f*(N + vec3(1.0f));
	}
	vec3 d = normalize(r.direction());
	t = 0.5f*(r.direction().getY() + 1.0f);
	return lerp(t, vec3(1), vec3(0.5f, 0.7f, 1.0f));
}



int main()
{
	int nx = 800;
	int ny = 400;
	int ns = 50;
	std::unique_ptr<rayt::Scene> scene(std::make_unique<rayt::Scene>(nx, ny, ns));
	scene->render();

	system("PAUSE");
	return 0;
}