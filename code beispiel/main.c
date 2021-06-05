#include <stdio.h>
#include <stdlib.h>
#include "product.h"

int main(int argc, char *argv[]) {

    if (argc < 2) {
        fprintf(stderr, "Usage: %s products.txt\n", argv[0]);
        return 1;
    }

    FILE* fp = fopen(argv[1], "r");

    if (!fp) {
        fprintf(stderr, "Could not open %s\n", argv[1]);
        return 1;
    }

    int product_count = 0;
    int c = 0;
    while(!feof(fp)) {
        c = fgetc(fp);
        if (c == ',') {
            product_count++;
        }
    }

    product_count++;
    rewind(fp);

    struct product* products = calloc(product_count, sizeof(*products));

    for (int i = 0; i < product_count; i++) {
        int year, month, day, id;
        float grade = 0.0;
        year = 0;
        month = 0;
        day = 0;
        id = 0;

        fscanf(fp, "%d %d %d %d %f, ", &id, &day, &month, &year, &grade);

        product_init(&products[i], id, year, month, day, grade);
    }
    print_products(products, product_count);
    printf("Average: %.2f\n", avg_grade(products, product_count));
    free(products);
}