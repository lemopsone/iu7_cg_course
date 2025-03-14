void ballFold(inout vec3 z, inout float dz) {
    float z_sq = dot(z, z);
    float z_sqrt = sqrt(z_sq);

    if (z_sqrt < 0.5) {
        float temp = 2.0;
        z *= temp;
        dz *= temp;
    } else if (z_sqrt < 1.0) {
        float temp = 1.0 / z_sq;
        z *= temp;
        dz *= temp;
    }
}

void boxFold(inout vec3 z) {
    z = clamp(z, -1.0, 1.0) * 2.0 - z;
}

float sdf(vec3 z) {
    float scale = 2.0;
    vec3 offset = z * 1.6;
    float dr = 1.0;

    int iter = 15;
    for (int n = 0; n < iter; ++n) {
        boxFold(z);
        ballFold(z, dr);
        z = scale * z + offset;
        dr = dr * abs(scale) + 1.0;
    }

    float r = length(z);
    return r / abs(dr);
}
