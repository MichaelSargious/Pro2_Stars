#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "star.h"
#include "image.h"

int main(int argc, char *argv[])
{
	if (argc < 3) {
		fprintf(stderr, "syntax: %s size starlist [lines...]\n", argv[0]);
		return EXIT_FAILURE;
	}

	int size = atoi(argv[1]);
	if (size <= 0) {
		fprintf(stderr, "size of image cannot be <= 0\n");
		return EXIT_FAILURE;
	}

	struct image img;
	image_init(&img, size, size);

	FILE* fp = fopen(argv[2], "r");
	if (fp == NULL) {
				fprintf(stderr, "cannot open stars file \"%s\"\n", argv[2]);
	}
	 int star_counter = 0;
	    double  x = 0.0 , y = 0.0 , z = 0.0 , mag = 0.0 ;
	    int har = 0 , draper = 0 ;
	    while(!feof(fp)) {
	        if ((fscanf(fp ,"%lf %lf %lf %i %lf %i", &x ,&y, &z , &draper , &mag , &har )) == 6){
	        	star_counter++ ;
	        }
	    }

	   star_counter++;
	    rewind(fp);

	    struct star* stars = malloc (star_counter*sizeof(*stars));

	 for (int q = 0; q < star_counter ; q++) {
		 if(star_read_from_file( &stars[q] , fp) == 1) {
			 star_plot( &stars[q] , &img) ;
		 }
		 }
    rewind (fp) ;
	// TODO: Read in the stars from the file with name argv[2] 
	// save them in an array in the order they are read in and draw them to the image.
	//abort();

	// open every constellation file
	for (int i = 3; i < argc; i++) {
		FILE* f = fopen(argv[i], "r");
		// if the file could not be opened, skip to the next one.
		if (f == NULL) {
			fprintf(stderr, "cannot open line file \"%s\"\n", argv[i]);
			continue;
		}
		int line_counter ;
		int d1 = 0 , d2 = 0 ;
		while(!feof(f)) {
			        if ((fscanf(f ,"%i,%i", &d1 , &d2 )) == 2){
			        	line_counter++ ;
			        }
		}
		line_counter++;
		rewind(f) ;
		for (int e = 0 ; e < line_counter ; e++){
			draw_constellation_from_file(f, &img, stars , star_counter);
		}
        //abort(); // TODO draw the constellation to the image
		fclose(f);
	}

	// write the painted image to the output file.
	FILE* image_file = fopen("stars.pbm", "w");
	if (image_file == NULL) {
		fprintf(stderr, "cannot open output file.\n");
		return EXIT_FAILURE;
	}

	image_write_to_file(&img, image_file);

	fclose(image_file);
	image_destroy(&img);
	free (stars) ;

}
