#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>

#include "data.h"

double growth_factor = 1.5;

// parameters for end time, cut off, cell size, grid size and number of particles
double t_end = 0.5;
double r_cut_off = 2.5;
double cell_size = 2.5;
int x = 500;
int y = 500;
int num_particles;

// number of iterations, timestep duration and half-timestep duration
int niters = 1000;
double dt;
double dth;

// square of the cut off (to prevent need for some sqrts later)
double r_cut_off_2;

// constants required to calculate the potential energy
double r_cut_off_2_inv; 
double r_cut_off_6_inv;	
double Uc;
double Duc;


// constants required to calculate the potential energy
double r2cutinv;
double r6cutinv;
double Uc;
double Duc;

// random seed (to allow reproducibility)
long seed;

// initial temperature and the number of particles per cell per dimension
double init_temp = 1.0;
int num_part_per_dim = 2;

// the cell list
struct cell_list ** cells;

struct particle_t particles;

/**
 * @brief Add a particle to a particular cell list
 * 
 * @param list The cell list to add the particle to
 * @param particle The particle
 */
void add_particle(struct cell_list * cell, int part_id) {
	if (cell->count == cell->size) {
		cell->size *= growth_factor;
		int * tmp = realloc(cell->part_ids, sizeof(int) * cell->size);
		if (!tmp) {
			fprintf(stderr, "realloc failed\n");
			exit(2);
		} else {
			cell->part_ids = tmp;
		}
	}
	cell->part_ids[cell->count] = part_id;
	cell->count++; 
}

/**
 * @brief Remove a particle from a particular cell list
 * 
 * @param list The cell list to remove the particle from
 * @param particle The particle
 */
void remove_particle(struct cell_list * cell, int part_id) {
	cell->count--;
}

/**
 * @brief Allocate a 2D array of cell list structures
 * 
 * @param m Dimension in X direction
 * @param n Dimension in Y direction
 * @return struct cell_list** An allocated 2D cell list structure
 */
struct cell_list ** alloc_2d_cell_list_array(int m, int n) {
  	struct cell_list ** x;

  	x = (struct cell_list **) malloc(m * sizeof(struct cell_list));
  	x[0] = (struct cell_list *) calloc(m * n, sizeof(struct cell_list));
  	for (int i = 1; i < m; i++)
    	x[i] = &x[0][i*n];
	return x;
}

/**
 * @brief Free a 2D array
 * 
 * @param array The 2D array to free
 */
void free_2d_array(void ** array) {
	free(array[0]);
	free(array);
}