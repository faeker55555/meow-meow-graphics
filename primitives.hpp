struct vec3 {
    float x, y, z;
    
    vec3() : x(0.0f), y(0.0f), z(0.0f) {}
    vec3(float x, float y, float z):
    x(x), y(y), z(z) {}

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
    vec4() : x(0.0f), y(0.0f), z(0.0f), w(1.0f) {}
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

#define FRAGMENT_WHITE Fragment{ vec4(255.0f, 255.0f, 255.0f, 255.0f), (float)(0.0f) }
#define FRAGMENT_BLACK Fragment{ vec4(0.0f, 0.0f, 0.0f, 1.0f), (float)(0.0f) }

struct Frame {
    int height = 16;
    int width = 9;
    std::vector<Fragment> pixels;
    Frame(int h,int w):
        height(h),
        width(w),
        pixels(w*h) {}
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

void from_frame(Frame i, std::vector<uint32_t>* buffer) {
    // here we create elements in buffer if they don't exist (resize does this) and then get acces to data + write in for loop
    size_t total_pixels = static_cast<size_t>(i.height * i.width);

    buffer->resize(total_pixels);

    uint32_t* raw_buffer = buffer->data();
    for (size_t index = 0; (index < total_pixels); ++index){
        const Fragment frag = i.pixels[index];

        raw_buffer[index] = 
            (convert_to_byte(frag.color.w) << 24) |
            (convert_to_byte(frag.color.x) << 16) |
            (convert_to_byte(frag.color.y) << 8)  |
            (convert_to_byte(frag.color.z));
    }
}

