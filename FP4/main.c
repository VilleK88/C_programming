#include <stdio.h>

#define SLIP_END 0xC0
#define SLIP_ESC 0xDB
#define SLIP_ESC_END 0xDC
#define SLIP_ESC_ESC 0xDD

void (*callback_func)(const unsigned char*, int);
void register_slip_frame_callback(void (*callback)(const unsigned char*, int));
void process_slip_data(int (*reader)(void));

int main() {
    return 0;
}

void register_slip_frame_callback(void (*callback)(const unsigned char*, int)) {
    callback_func = callback;
}

void process_slip_data(int (*reader)(void)) {
    unsigned char buffer[40];
    int len = 0;
    int c;

    while ((c = reader()) != EOF) {
        if (c == SLIP_END) {
            if (len > 0) {
                callback_func(buffer, len);
                len = 0;
            }
        }
        else if (c == SLIP_ESC) {
            int next = reader();
            if (next == SLIP_ESC_END)
                buffer[len++] = SLIP_END;
            else if (next == SLIP_ESC_ESC)
                buffer[len++] = SLIP_ESC;
        }
        else {
            buffer[len++] = c;
        }
    }
}