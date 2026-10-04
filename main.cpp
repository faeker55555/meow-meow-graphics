#include "MiniFB.h"
#include <vector>
#include <iostream>
#include <chrono>
#include "primitives.hpp"
#include "text_rendering.hpp"

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
    uint64_t frame_counter = 0;
    Frame current_frame(HEIGHT,WIDTH);

    while (true) {
        auto start = std::chrono::steady_clock::now();
        frame_counter++;

        // test loop setting frame to UV + Blue as time
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

        draw_string_at("FAEK OS, VERSION 0.1 FRAME: " + std::to_string(static_cast<int>(frame_counter)), 100, 108, &current_frame);

        auto end = std::chrono::steady_clock::now();

        draw_string_at("MS: " + std::to_string(static_cast<int>(std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count())), 100, 116, &current_frame);


        from_frame(current_frame, &draw_buffer);


        int state = mfb_update_ex(window, draw_buffer.data(), WIDTH, HEIGHT);

        if (state < 0) {
            break;
        }
    }

    mfb_close(window);
    return 0;
}

