#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "star.h"

int star_read_from_file(struct star* s, FILE* f)
{
	//abort(); // TODO implement
	double z ;
	int har ;
	if ((fscanf(f,"%lf %lf %lf %i %lf %i", &(s->x) ,&(s->y),&z , &(s->draper) , &(s->magnitude) , &har )) == 6 ) {
		return 1;
	}
	else
		return 0;
}

void star_coord_to_pixel(struct star const* s, struct image* const img, int* x, int* y)
{
    //abort(); // TODO implement
	*x = (int) (((1 + s->x)*(img->w - 1))/2);
	*y = (int) (((1 - s->y)*(img->h - 1))/2);
}

void star_plot(struct star const* s, struct image* img)
{
	//abort(); // TODO implement
        int a ;
        int b ;
		star_coord_to_pixel(s, img, &a, &b) ;
	    int color = 0x00ffffff ;
	    image_draw_pixel( img, color, a , b) ;
	}


void draw_constellation_from_file(FILE* f, struct image* img, struct star const* stars, int num_stars){

	//abort(); // TODO implement
    int d_1 = 0 , d_2 = 0 ;
    int x_0 = 0 , y_0 = 0 ;
    int x_1 = 0 , y_1 = 0 ;
    int start_treffer_1 = -1 ;
    int start_treffer_2 = -1 ;
    if ((fscanf(f ,"%i,%i", &d_1 , &d_2 )) == 2){
    	for(int i = 0 ; i < num_stars ; i++){
    		if (stars[i].draper == d_1 ){
    			start_treffer_1 = i ;
    			star_coord_to_pixel(&stars[i], img , &x_0 , &y_0 ) ;
    		}
    	}
    	for(int q = 0 ; q < num_stars ; q++){
    		if (stars[q].draper == d_2 ){
    		    			start_treffer_2 = q ;
    		    			star_coord_to_pixel(&stars[q],img, &x_1 , &y_1 ) ;
    		}
    	}
    	int yellow = 0x00ffff00 ;
    	if (start_treffer_1 >= 0 && start_treffer_2 >= 0) {
    		if (start_treffer_1 < start_treffer_2 ) {
    			image_draw_line(img , yellow , x_0 , y_0 , x_1 , y_1 );
    		}else {
    			image_draw_line(img , yellow , x_1 , y_1 , x_0 , y_0 );
    		}
    	}
    }
}


