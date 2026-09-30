#include "MiniFB.h"
#include <vector>
#include <iostream>
#include "primitives.hpp"

int WIDTH = 800;
int HEIGHT = 600;

void on_resize(struct mfb_window *window, int width, int height){
    WIDTH = width;
    HEIGHT = height;
}

int main() {
    struct mfb_window *window = mfb_open_ex("GRAPHICS", WIDTH, HEIGHT, MFB_WF_RESIZABLE);
    if (!window) {
        std::cerr << "Failed to open window!" << std::endl;
        return -1;
    }

    std::vector<uint32_t> draw_buffer(WIDTH * HEIGHT);
    uint8_t frame_counter = 0;

    while (true) {
        frame_counter++;
        Frame current_frame(HEIGHT,WIDTH);

        // test loop setting frame to UV + B as time
        for (int y = 0; y < HEIGHT; ++y) {
            for (int x = 0; x < WIDTH; ++x) {
                uint8_t r = (x * 255) / WIDTH;
                uint8_t g = (y * 255) / HEIGHT;
                uint8_t b = frame_counter;
                uint8_t a = 255;
                Fragment out = {vec4((float)(r),(float)(g),(float)(b),(float)(a)), 1};

                current_frame.pixels[y * WIDTH + x] = out;
            }
        }
        from_frame(current_frame, &draw_buffer);

        int state = mfb_update_ex(window, draw_buffer.data(), WIDTH, HEIGHT);

        if (state < 0) {
            break;
        }
    }

    mfb_close(window);
    return 0;
}

