#include <zmk/hid.h>
#include <zmk/input.h>
#include <zmk/layers.h>
#include <zephyr/kernel.h>

#define MOUSE_LAYER 3        // 自動でオンにしたいレイヤー番号
#define TIMEOUT_MS 800       // マウス操作が止まってからオフにするまでの時間

static int64_t last_mouse_time = 0;
static bool mouse_layer_active = false;

int input_processor_mouse_movement(struct zmk_hid_mouse_movement *movement) {
    int64_t now = k_uptime_get();

    // マウスが動いたら記録
    if (movement->x != 0 || movement->y != 0) {
        last_mouse_time = now;

        // レイヤーがまだオンでなければオンにする
        if (!mouse_layer_active) {
            zmk_layer_activate(MOUSE_LAYER);
            mouse_layer_active = true;
        }
    }

    return 0;
}

int input_processor_mouse_scroll(struct zmk_hid_mouse_scroll *scroll) {
    int64_t now = k_uptime_get();

    // スクロールがあれば記録
    if (scroll->y != 0 || scroll->x != 0) {
        last_mouse_time = now;

        if (!mouse_layer_active) {
            zmk_layer_activate(MOUSE_LAYER);
            mouse_layer_active = true;
        }
    }

    return 0;
}

// 定期チェックしてレイヤーをオフにする
int input_processor_tick(uint32_t dt) {
    int64_t now = k_uptime_get();

    if (mouse_layer_active && (now - last_mouse_time) > TIMEOUT_MS) {
        zmk_layer_deactivate(MOUSE_LAYER);
        mouse_layer_active = false;
    }

    return 0;
}
