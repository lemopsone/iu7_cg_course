uniform float side;

float sdf(vec3 p) {
    vec3 b = vec3(side / 2, side / 2, side / 2);
    vec3 d = abs(p) - b;
    return min(max(d.x,max(d.y,d.z)),0.0) +
             length(max(d,vec3(0.0, 0.0, 0.0)));
}
