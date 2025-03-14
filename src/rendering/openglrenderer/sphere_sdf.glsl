uniform float radius;

float sdf(vec3 p) {
    return length(p) - radius;
}

