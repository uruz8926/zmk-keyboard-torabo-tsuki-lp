#include <zmk/hid.h>
#include <zmk/input.h>

int input_processor_mouse_scroll(struct zmk_hid_mouse_scroll *scroll) {
    // とりあえずスクロール量を2倍にする例
    if (scroll->y > 0) {
        scroll->y = 2;
    } else if (scroll->y < 0) {
        scroll->y = -2;
    }
    return 0;
}
