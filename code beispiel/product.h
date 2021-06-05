//
// Created by me on 05.05.19.
//

#ifndef CINTRO_PRODUCT_H
#define CINTRO_PRODUCT_H

struct product {
    int id;
    int year;
    int month;
    int day;
    float grade;
};

void product_init(struct product* kid, int id, int year, int month, int day, float grade);

float avg_grade(struct product* products, int product_count);

void print_products(struct product* products, int product_count);

#endif //CINTRO_PRODUCT_H
