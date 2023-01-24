/**
 * Copyright (c) 2015 K.Musayeva <khmusayeva@gmail.com>
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <ctype.h>


/**
 * Handles errors.
 */
void error_message(int type) {
  switch(type){
      case 1:
	printf("Usage: abc \t[-f input file]\n\t\t[-c clustering_coefficient (a positive real value)]\n\t\t[-t tolerance (a positive real value)]\n\t\t[-r repetitions (a positive integer value)]\n\t\t[-n number of networks to be generated (a positive integer value)]\n\t\t[-h number of hubs (a positive integer value not bigger than or equal to the number of genes)]\n");
        break;
      case 2:
	printf("Invalid value for tolerance.\n");
        break;
      case 3:
	printf("Invalid value for repetitions.\n");
        break;
      case 4:
	printf("Invalid number of networks to be generated.\n");
        break;
      case 5:
	printf("Invalid value for the number of hubs.\n");
        break;
      case 6:
	printf("Invalid value for the clustering coefficient.\n");
        break;
      case 7:
	printf("File not found.\n");
        break;
      default:
	abort();
	break;
      }
 }




int main(int argc, char* argv[]) {
 if(argc<6) {
	error_message(1);
	return(1);
	}

 int option;
 char *file, *cclust_coef, *ctol, *cinner_iter, *couter_iter, *cnumber_hubs;

 while ((option = getopt (argc, argv, "f:c:t:r:n:h:")) != -1) {
    switch (option){
      case 'f':
        file = optarg;
        break;
      case 'c':
        cclust_coef = optarg;
        break;
      case 't':
        ctol = optarg;
        break;
      case 'r':
        couter_iter = optarg;
        break;
      case 'n':
        cinner_iter = optarg;
        break;
      case 'h':
        cnumber_hubs = optarg;
        break;
      default:
	error_message(0);
        exit(EXIT_FAILURE);
      }
  }

 double tolerance=atof(ctol);
 int outer_iteration=atoi(couter_iter);
 int inner_iteration=atoi(cinner_iter);
 int number_hubs=atoi(cnumber_hubs);
 double clust_coef=atof(cclust_coef);

 if(tolerance==0) {error_message(2);error_message(1);return(1);}	
 if(number_hubs==0) {error_message(5);error_message(1);return(1);}	
 if(outer_iteration==0) {error_message(3);error_message(1);return(1);}	
 if(inner_iteration==0) {error_message(4);error_message(1);return(1);}	
 if(clust_coef==0) {error_message(6);error_message(1);return(1);}	

srand(getpid());

abc(file, clust_size, clust_coeffs, tolerance, number_hubs, outer_iteration, inner_iteration);

/*****************************************
for the debugging purposes of abc_R.c
***********

double data_array[30]={296.000000,590.200000,240.100000,0.000000,164.900000,267.400000,12.500000,219.400000,44.600000,240.100000,181.600000,93.000000,5.500000,156.800000,1.800000,29.400000,47.500000,219.400000,284.900000,15.400000,149.600000,27.300000,219.400000,184.100000,306.300000,15.400000,33.500000,300.300000,37.400000,611.300000};
int number_genes=15;
int number_times=2;
double clust_coeffs[]={1.5, 2.0, 3.0};
int clust_size=3; 
double tolerance=3000;
int number_hubs=3;
int number_outer_iter=2;
int number_inner_iter=5000;
int number_accepted=0;
int is_probs=0;
double dist_array[5000];
double hub_probs[15];
double neighbour_probs[225];

abc(data_array, &number_genes, &number_times, &clust_size, clust_coeffs, &tolerance, &number_hubs, &number_outer_iter, &number_inner_iter, &number_accepted, dist_array, hub_probs, neighbour_probs, &is_probs);
**********************************************/

}






