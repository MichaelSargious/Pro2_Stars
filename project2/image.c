#include <stdlib.h>
#include <string.h>

#include "image.h"

void image_init(struct image* img, int w, int h)
{
	//abort(); // TODO implement
	img->w = w;
	img->h = h;
	img->data = (int*) calloc ((w*h),sizeof(int)) ;
}

void image_destroy(struct image* img) {
	//abort(); // TODO implement

	free (img->data) ;
}

void image_draw_pixel(struct image* img, int color, int x, int y)
{
	//abort(); // TODO implement
	int loc = (img->w)*y  + x ;
   if (x >= 0 && x < img->w && y >= 0 && y < img->h) {
    img->data[loc]=color ;
   }
}

/* Helper function for image_draw_line */
void swap(int* a, int* b)
{
	int tmp = *a; 
	*a = *b;
	*b = tmp;
}

/**
 * Draw a line using Bresenham's algorithm.
 * @see http://en.wikipedia.org/wiki/Bresenham's_line_algorithm
 */
void image_draw_line(struct image* img, int color, int x0, int y0, int x1, int y1)
{

	int dx    = x1 > x0 ? x1 - x0 : x0 - x1;
	int dy    = y1 > y0 ? y1 - y0 : y0 - y1;
	int sx    = x1 > x0 ? 1 : -1;
	int sy    = y1 > y0 ? 1 : -1;
	int not_steep = dy > dx;

	if (not_steep) {
		swap(&x0, &y0);
		swap(&dx, &dy);
		swap(&sx, &sy);
	}

	int e = 2 * dy - dx;
	for (int i = 0; i < dx; i++) {
		if (not_steep)
			image_draw_pixel(img, color, y0, x0);
		else
			image_draw_pixel(img, color, x0, y0);

		if (e >= 0) {
			int d  = 1 + e / (2 * dx);
			y0    += sy < 0 ? -d : d;
			e     -= d * 2 * dx;
		}

		x0 += sx;
		e += 2 * dy;
	}
}

void image_write_to_file(struct image* img, FILE* f)
{
	//abort(); // TODO implement
	fprintf(f,"P3\n");
	fprintf(f,"%i %i\n",img->w ,img->h);
	int y = 255 ;
	fprintf(f, "%i \n", y );
	int i = 0;
	for (int j=0 ; j<img->h ; j++){
	for (int x=0 ; x<img->w ; x++){
		int color = img->data[i];
		int r_color = ((color >> 16) & 0xff);
		int g_color = ((color >> 8) & 0xff);
		int b_color = (color & 0xff);
		fprintf (f,"%i %i %i ", r_color , g_color , b_color);
		i++;
 	}
	fprintf(f,"\n");
	}
}
