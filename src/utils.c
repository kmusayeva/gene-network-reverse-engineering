/**
 * Some utility functions
 * Copyright (c) 2015 K.Musayeva <khmusayeva@gmail.com>
 * */
#include <stdlib.h>
#include <stdio.h>
#include <math.h>



int sign(double x) {
    return (x > 0) - (x < 0);
	}


int sample_int(int min, int max) {
	return(min + rand()/(RAND_MAX/(max - min + 1)+1));
	}


double sample_double(int min, int max) {
	return(min+rand()/(RAND_MAX/(max-min)));
	}


void shuffle(int *array, size_t n) {
	if (n > 1) {
		size_t i;
		for (i = 0; i < n - 1; i++) {
		          size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
        		  int t = array[j];
		          array[j] = array[i];
		          array[i] = t;
        		}
    		}	
	}



void swap(int *array, int a, int b) {
	int tmp=array[b];
	array[b]=array[a];
	array[a]=tmp;
	}



int sample(int size, double *probs) {
        int i;
        double sum=0.0;

        double *cumul_probs=calloc((size+1), sizeof(double));

        for(i=0; i<size; ++i) {
                sum+=probs[i];
                }
	
	if(sum<0.0000001) {
		return(sample_int(0, size-1));
		}


        for(i=0; i<size; ++i) {
                probs[i]/=sum;
                //printf("%lf ", probs[i]);
                }
        //printf("\n");


        for(i=1; i<=size; ++i) {
                cumul_probs[i]=cumul_probs[i-1]+probs[i-1];
                //printf("%lf ", cumul_probs[i]);
                }
        //printf("\n");

        double random_number=((double)rand()/RAND_MAX);
        //printf("random number=%lf \n", random_number);

        int elm;

        for(i=1; i<=size; i++) {
              if(random_number<=cumul_probs[i] && random_number>cumul_probs[i-1]) {
                                elm=i-1;
                                break;
                                }
                        }

        free(cumul_probs);

        return elm;
        }



void sample_multiple(int size, double *probs, int *elms, int *track_elms) {
        double random_number, max;
        int i, j, t, k, elm, z=0;

	double *cumul_probs=(double*)malloc(size*sizeof(double));

	for(i=0; i<size; i++) {
                elms[i]=i;
                track_elms[i]=-1;
                }

        for(i=1; i<=size; ++i) {
                cumul_probs[i]=cumul_probs[i-1]+probs[i-1];
                }

        max=cumul_probs[size];

	for(i=1; i<=size; ++i){
                
		if(max<0.00000001) {
                        break;
                        }
                
		random_number=((double)rand()/RAND_MAX) * max;
                
		for(j=1; j<=size; j++){
                        if(random_number<=cumul_probs[j] && random_number>cumul_probs[j-1]) {
                                        elm=j-1;
                                        max=cumul_probs[size]-probs[elm];
                                        cumul_probs[j]=cumul_probs[j-1];
                                        for(k=j+1; k<=size; k++){
                                                cumul_probs[k]-=probs[elm];
                                                }
                                        elms[z++]=elm;
                                        track_elms[elm]=1;
                                        break;

                                }
                         }
                 }


	for(i=0; i<size; i++) {
               	if(track_elms[i]==-1) {
                        elms[z]=i;            
                        z=z+1;
                      }

                }

        }



void sampleFromGaussian(double mu, double sigma, double *Z) {
	static double U, V;
	static int phase = 0;

	if(phase == 0) {
		U = (rand() + 1.0) / (RAND_MAX + 2.0);
		V = rand() / (RAND_MAX + 1.0);
		*Z = sqrt(-2 * log(U)) * sin(2 * M_PI * V);
		}
	else {
		*Z = sqrt(-2 * log(U)) * cos(2 * M_PI * V);
		}

	phase=1-phase;
	*Z=mu+sigma*(*Z);

	}



void getPowerLawDegreeDistribution(double *array, int number, double gamma) {
	int i;
	for(i=0; i<number; ++i) {
		array[i]=pow(i+1, -1*gamma);		
		}

	}



int max(int x, int y) {
    if(x > y) {return x;}
    else {return y;}
	}



void sort_helper(int *input, int *nodes, int left, int right, int *scratch, int *nodes_helper) {
    if(right == left + 1) {
        return;
    }

    else {
        int i = 0;
        int length = right - left;
        int midpoint_distance = length/2;
        int l = left, r = left + midpoint_distance;

	sort_helper(input, nodes, left, left + midpoint_distance, scratch, nodes_helper);
        sort_helper(input, nodes, left + midpoint_distance, right, scratch, nodes_helper);

        for(i = 0; i < length; i++) {

            if(l < left + midpoint_distance && (r == right || max(input[l], input[r]) == input[l])) {
                scratch[i] = input[l];
                nodes_helper[i]=nodes[l];
                l++;
            }

            else {
                scratch[i] = input[r];
                nodes_helper[i]=nodes[r];
                r++;
            }

        }

        for(i = left; i < right; i++) {
            input[i] = scratch[i - left];
            nodes[i] = nodes_helper[i - left];
        }

    }

}


int sort(int *input, int *nodes, int size) {
    int *scratch = (int *)malloc(size * sizeof(int));
    int *nodes_helper = (int *)malloc(size * sizeof(int));

    if(scratch != NULL) {
        sort_helper(input, nodes, 0, size, scratch, nodes_helper);
        free(scratch);
        free(nodes_helper);
        return 1;
    }

    else {
        return 0;
    }

}



double generateRandomNumber(int min, int max) {
        double range = (max - min);
        double div = RAND_MAX / range;
        return(min+(rand()/div));
        }


//computes the factorial
int factorial(int n) {
	int i, result=1;

	for (i=1; i<=n; i++){
		result*=i;
		}

	return(result);

	}


//used for permutations
void rotate_left(int *v, int start, int n){
  int tmp = v[start], i;
  for (i = start; i < n-1; i++) {
    v[i] = v[i+1];
  }
  v[n-1] = tmp;
}


//Computes all permutations and stores in the array, in this case perm_array
//The algorithm is taken from the "Practical Algorithms in C++"
void permute(int *v, int start, int n, int **perm_array, int number_perm){
  int i, j, p;
  static int m=0;
  for(p=0; p<n; ++p) {
        perm_array[m%number_perm][p]=v[p];
        }
  ++m;
  if (start < n) {
    for (i = n-2; i >= start; i--) {
      for (j = i + 1; j < n; j++) {
        swap(v, i, j);
        permute(v, i+1, n, perm_array, number_perm);
           }
      rotate_left(v, i, n);
    	}
    }

}



