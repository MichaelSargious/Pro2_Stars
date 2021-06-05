#include <stdio.h>
#include "product.h"

void product_init(struct product* kid, int id, int year, int month, int day, float grade) {
    kid->id = id;
    kid->year = year;
    kid->month = month;
    kid->day = day;
    kid->grade = grade;
}

float avg_grade(struct product* products, int product_count) {
    float acc = 0;

    for (int i = 0; i < product_count; i++) {
        acc += products[i].grade;
    }

    return acc / (float) product_count;
}

void print_products(struct product* products, int product_count) {
    for (int i = 0; i < product_count; i++) {
        struct product current = products[i];
        printf("Day-Month-Year: %d %d.%d.%d\nGrade: %.2f\n", current.id, current.day, current.month, current.year, current.grade);
    }
}
