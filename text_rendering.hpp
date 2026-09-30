
#include "text.hpp"

void draw_char_at(char c, int x_at, int y_at, Frame* f){
    // we first want to retrieve where we are at frame, then we want to write into its data by using bitmask
    // bitmask need to be parsed, how to do this... what is get bitmap output... it is char* but what is that is it like a ptr onto array inside... 
    const unsigned char* bm = get_bitmap(c);
    if (!bm) return;
    
    for (int y = y_at; (y < y_at + 8); ++y) {
        for (int x = x_at; (x < x_at + 8); ++x) {
            bool is_white = (bm[y - y_at] >> (7 - (x - x_at))) & 1;
            if (!is_white) {continue;}
            f->pixels[y * f->width + x] = FRAGMENT_WHITE;
        }
    }
}

void draw_string_at(std::string s, int x, int y, Frame* f){
    for (int index = 0 ; (index < s.length()); ++index)
    {
        draw_char_at(s[index], (x + (index * 8)), y, f);
    }
}
