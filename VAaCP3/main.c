#include <stdio.h>
#include <stdbool.h>

typedef struct {
    const char *text;
    int position;
} text_reader_ctx;

void text_reader_init(text_reader_ctx *ctx, const char *str);
int text_reader_read(text_reader_ctx *ctx, char *buffer, int size);

int main() {
    const char *text = "This is first row\nThis is second row\nThis is third row\n";
    text_reader_ctx ctx;
    text_reader_init(&ctx, text);

    char buffer[64];
    while (true) {
        const int n = text_reader_read(&ctx, buffer, sizeof buffer);
        if (n == 0)
            break;
        printf("Luettiin: %s", buffer);
    }

    return 0;
}

void text_reader_init(text_reader_ctx *ctx, const char *str) {
    ctx->text = str;
    ctx->position = 0;
}

int text_reader_read(text_reader_ctx *ctx, char *buffer, int size) {
    int count = 0;
    bool continue_loop = true;

    do {
        char c = ctx->text[ctx->position];
        if (c != '\0' && count < size - 1) {
            if (c != '\n') {
                buffer[count++] = c;
                ctx->position++;
            }
            else {
                buffer[count++] = c;
                ctx->position++;
                continue_loop = false;
            }
        }
        else
            continue_loop = false;

    } while (continue_loop);

    buffer[count] = '\0';
    return count;
}