#version 330 core
in vec2 position;

uniform vec3 cameraPos;
uniform vec3 cameraTargetPos;
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 objectColor;
uniform vec3 bgColor;
uniform vec3 cameraUp;
uniform float fov;
uniform vec2 resolution;
uniform float intensity;

out vec4 fragColor;

#define M_PI 3.1415926538

// Функция SDF для текущего объекта (может быть заменена динамически)
float sdf(vec3 p);

// Вычисление нормали к поверхности на основе SDF
vec3 calculateNormal(vec3 p) {
    float epsilon = 0.0015;
    return normalize(vec3(
        sdf(p + vec3(epsilon, 0.0, 0.0)) - sdf(p - vec3(epsilon, 0.0, 0.0)),
        sdf(p + vec3(0.0, epsilon, 0.0)) - sdf(p - vec3(0.0, epsilon, 0.0)),
        sdf(p + vec3(0.0, 0.0, epsilon)) - sdf(p - vec3(0.0, 0.0, epsilon))
    ));
}

vec3 getRayDirection() {
  float aR = resolution.x / resolution.y;
  float fovScale = tan(fov * 0.5 * M_PI / 180.0);
  vec2 screen = vec2(
    position.x * aR * fovScale,
    position.y * fovScale
  );

  vec3 forward = normalize(cameraTargetPos-cameraPos);
  vec3 right = normalize(cross(forward, cameraUp));
  vec3 up = normalize(cross(right, forward));
  return normalize(vec3(forward + screen.x * right + screen.y * up));
}

// Реализация затенения по модели Фонга
vec3 phongShading(vec3 point, vec3 normal, vec3 viewDir) {
    vec3 lightDir = normalize(point - lightPos);

    // Диффузное освещение
    float diff = max(dot(normal, lightDir), 0.0);

    // Зеркальное освещение
    vec3 reflectDir = 2 * dot(normal, lightDir) * normal - lightDir;
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0); // 32 - коэффициент блеска

    // Итоговый цвет
    vec3 ambient = 0.1 * lightColor * intensity;  // Фоновое освещение
    vec3 diffuse = diff * objectColor * 0.7;
    vec3 specular = spec * 0.2 * vec3(1.0, 1.0, 1.0);

    vec3 result = (ambient + diffuse + specular) * intensity;
    result.x = min(result.x, 1.0);
    result.y = min(result.y, 1.0);
    result.z = min(result.z, 1.0);
    return result;
}

void main() {
    // fragColor = vec4(1.0, 0.0, 0.0, 1.0);
    // Вычисляем луч
    vec3 rayDir = getRayDirection();
    vec3 rayOrigin = cameraPos;

    float k = length(cameraPos) / 4.0;
    // Raymarching
    float t = 0.0; // расстояние вдоль луча
    int maxSteps = 1000 + int(k) * 50;
    float minDist = max(0.0001, 0.001 * k);
    float maxDist = 10.0 * k;

    for (int i = 0; i < maxSteps; ++i) {
        vec3 point = rayOrigin + t * rayDir;
        float dist = sdf(point); // вызов функции SDF

        if (dist < minDist) {
            vec3 normal = calculateNormal(point);
            vec3 viewDir = normalize(cameraPos - point);
            fragColor = vec4(phongShading(point, normal, viewDir), 1.0);
            return;
        }

        t += dist;
        if (t > maxDist) break;
    }

    // Фон (если пересечение не найдено)
    fragColor = vec4(bgColor, 1.0);
}

