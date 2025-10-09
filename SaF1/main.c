#include <stdio.h>
#include <math.h>

struct point { double x; double y; };

double distance(struct point a, struct point b);

int main() {
    struct point point_a = { 0, 4 };
    struct point point_b = { 3, 0 };
    printf("%.3f", distance(point_a, point_b));
    return 0;
}

double distance(struct point a, struct point b) {
    return sqrt((b.y - a.y) * (b.y - a.y) + (b.x - a.x) * (b.x - a.x));
}