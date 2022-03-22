#include "Light.h"
#include <Gizmos.h>
void Light::draw()
{
	aie::Gizmos::addSphere(direction, 0.1f, 8, 16, glm::vec4(colour,1));
}
