const int test = 0;

struct vec3 {
    float x, y, z;
    
    //vec3(float x, float y, float z) : { x(x) y(y) z(z) }

    // vector ops
    vec3 operator+(const vec3& other) {
        return {x + other.x, y + other.y, z + other.z};
    }
    vec3 operator-(const vec3& other){
        return {x - other.x, y - other.y, z - other.z};
    }
    vec3 operator*(const vec3& other){
        return {x * other.x, y * other.y, z * other.z};
    }
    vec3 operator/(const vec3& other){
        return {x / other.x, y / other.y, z / other.z};
    }

    // scalar ops
    vec3 operator+(const float other) {
        return {x + other, y + other, z + other};
    }
    vec3 operator-(const float other){
        return {x - other, y - other, z - other};
    }
    vec3 operator*(const float other){
        return {x * other, y * other, z * other};
    }
    vec3 operator/(const float other){
        return {x / other, y / other, z / other};
    }

};
struct vec4 {
    float x, y, z, w;
    
    vec4(float x, float y, float z, float w):
        x(x), y(y), z(z), w(w) {}

    // vector ops
    vec4 operator+(const vec4& other) {
        return {x + other.x, y + other.y, z + other.z, w + other.w};
    }
    vec4 operator-(const vec4& other){
        return {x - other.x, y - other.y, z - other.z, w - other.w};
    }
    vec4 operator*(const vec4& other){
        return {x * other.x, y * other.y, z * other.z, w * other.w};
    }
    vec4 operator/(const vec4& other){
        return {x / other.x, y / other.y, z / other.z, w / other.w};
    }

    // scalar ops
    vec4 operator+(const float other) {
        return {x + other, y + other, z + other, w + other};
    }
    vec4 operator-(const float other){
        return {x - other, y - other, z - other, w - other};
    }
    vec4 operator*(const float other){
        return {x * other, y * other, z * other, w * other};
    }
    vec4 operator/(const float other){
        return {x / other, y / other, z / other, w / other};
    }

};

struct Fragment {
    vec4 color;
    float depth;
};

uint8_t convert_to_byte(float color)
{
    uint8_t output;
    output = (uint8_t)(color);
    return output;
}

void from_fragment(Fragment i, uint32_t* buffer) {
    *buffer = (convert_to_byte(i.color.w) << 24) | (convert_to_byte(i.color.x) << 16) | (convert_to_byte(i.color.y) << 8) | (convert_to_byte(i.color.z));
}
