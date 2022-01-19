#pragma once

#include "Vector.h"

float getZ0();

Vector3 getProjectedPoint(Vector3* vec);
Vector3 translateOrigin(Vector3* vec);
Vector3 applyPerspective(Vector3* vec);