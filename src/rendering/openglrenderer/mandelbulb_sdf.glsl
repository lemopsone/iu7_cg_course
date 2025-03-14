uniform float power;
uniform int iters;
uniform float rad;

float sdf(vec3 p) {
    // float power = 9.0; // Степень фрактала
    vec3 z = p;
    float dr = 1.0;
    float r = length(z);

    for (int i = 0; i < iters; i++) {
        if (r > rad) break;
        float theta = acos(z.z / r);
        float phi = atan(z.y, z.x);
        dr = pow(r, power - 1.0) * power * dr + 1.0;
        float zr = pow(r, power);
        z = zr * vec3(sin(theta * power) * cos(phi * power),
                      sin(theta * power) * sin(phi * power),
                      cos(theta * power)) + p;
        r = length(z);
    }
    return 0.5 * log(r) * r / dr;
}

