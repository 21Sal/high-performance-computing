#ifndef DATA_H
#define DATA_H

// particle data type (with pointers to next and previous for linked list)
struct particle_t {
	double * x, * y; // position within cell
	double * ax, * ay; // acceleration
	double * vx, * vy; // velocity
	int * part_id;
};

// list for a cell, with a head
struct cell_list {
	int count;
	int size;
	int * part_ids;
};

// parameters for end time, cut off, cell size, grid size and number of particles
extern double t_end;
extern double r_cut_off;
extern double cell_size;
extern int x;
extern int y;
extern int num_particles;

// number of iterations, timestep duration and half-timestep duration
extern int niters;
extern double dt;
extern double dth;

// square of the cut off (to prevent need for some sqrts later)
extern double r_cut_off_2;

// constants required to calculate the potential energy
extern double r_cut_off_2_inv; 
extern double r_cut_off_6_inv;	
extern double Uc;
extern double Duc;

// random seed (to allow reproducibility)
extern long seed;

// initial temperature and the number of particles per cell per dimension
extern double init_temp;
extern int num_part_per_dim;

// the cell list
extern struct cell_list ** cells;
extern struct particle_t particles;


void add_particle(struct cell_list * list, int part_id);
void remove_particle(struct cell_list * list, int part_id);
struct cell_list ** alloc_2d_cell_list_array(int m, int n);
void free_2d_array(void ** array);

#endif