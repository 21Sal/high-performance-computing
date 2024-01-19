#include <stdio.h>

#include "boundary.h"
#include "data.h"

/**
 * @brief Apply the boundary conditions. This effectively points the ghost cell areas
 *        to the same cell list as the opposite edge (i.e. wraps the domain).
 *        This has to be done after every cell list update, just to ensure that a destructive
 *        operations hasn't broken things.
 * 
 */
void apply_boundary() {
	MPI_Status status;
	// Apply boundary conditions
	// exchange column 1 with right-most ghost column
	MPI_Sendrecv(&(cells[0][1]).part_ids, 1, mpi_part_ids_column, west_rank, 0, &(cells[0][sizej+1]).part_ids, 1, mpi_part_ids_column, east_rank, 0, cart_comm, &status);
	// MPI_Sendrecv(&(cells[0][1]).count, 1, mpi_count_column, west_rank, 0, &(cells[0][sizej+1]).count, 1, mpi_count_column, east_rank, 0, cart_comm, &status);
	// MPI_Sendrecv(&(cells[0][1]).size, 1, MPI_INT, west_rank, 0, &(cells[0][sizej+1]).size, 1, MPI_INT, east_rank, 0, cart_comm, &status);

	// exchange right-most regular column with left-most ghost column 
	MPI_Sendrecv(&(cells[0][sizej]).part_ids, 1, mpi_part_ids_column, west_rank, 0, &(cells[0][0]).part_ids, 1, mpi_part_ids_column, east_rank, 0, cart_comm, MPI_STATUS_IGNORE);
	// MPI_Sendrecv(&(cells[0][sizej]).count, 1, MPI_INT, west_rank, 0, &(cells[0][0]).count, 1, MPI_INT, east_rank, 0, cart_comm, MPI_STATUS_IGNORE);
	// MPI_Sendrecv(&(cells[0][sizej]).size, 1, MPI_INT, west_rank, 0, &(cells[0][0]).size, 1, MPI_INT, east_rank, 0, cart_comm, MPI_STATUS_IGNORE);

	MPI_Sendrecv(&(cells[1][0]).part_ids, sizei * 2 * num_part_per_dim * num_part_per_dim, MPI_INT, north_rank, 1, &(cells[sizej+1][0]).part_ids, sizei, MPI_INT, south_rank, 1, cart_comm, MPI_STATUS_IGNORE);
	// MPI_Sendrecv(&(cells[1][0]).count, sizei, MPI_INT, north_rank, 1, &(cells[sizej+1][0]).count, sizei, MPI_INT, south_rank, 1, cart_comm, MPI_STATUS_IGNORE);
	// MPI_Sendrecv(&(cells[1][0]).size, sizei, MPI_INT, north_rank, 1, &(cells[sizej+1][0]).size, sizei, MPI_INT, south_rank, 1, cart_comm, MPI_STATUS_IGNORE);

	MPI_Sendrecv(&(cells[sizei][1]).part_ids, sizei * 2 * num_part_per_dim * num_part_per_dim, MPI_INT, north_rank, 1, &(cells[1][0]).part_ids, sizei, MPI_INT, south_rank, 1, cart_comm, MPI_STATUS_IGNORE);
	// MPI_Sendrecv(&(cells[sizei][1]).count, sizei, MPI_INT, north_rank, 1, &(cells[1][0]).count, sizei, MPI_INT, south_rank, 1, cart_comm, MPI_STATUS_IGNORE);
	// MPI_Sendrecv(&(cells[sizei][1]).size, sizei, MPI_INT, north_rank, 1, &(cells[1][0]).size, sizei, MPI_INT, south_rank, 1, cart_comm, MPI_STATUS_IGNORE);

	// for (int j = 1; j < y+1; j++) {
	// 	cells[0][j].part_ids = cells[x][j].part_ids;
	// 	cells[0][j].count = cells[x][j].count;
	// 	cells[0][j].size = cells[x][j].size;

	// 	cells[x+1][j].part_ids = cells[1][j].part_ids;
	// 	cells[x+1][j].count = cells[1][j].count;
	// 	cells[x+1][j].size = cells[1][j].size;
	// }

	// for (int i = 0; i < x+2; i++) {
	// 	cells[i][0].part_ids = cells[i][y].part_ids;
	// 	cells[i][0].count = cells[i][y].count;
	// 	cells[i][0].size = cells[i][y].size;

	// 	cells[i][y+1].part_ids = cells[i][1].part_ids;
	// 	cells[i][y+1].count = cells[i][1].count;
	// 	cells[i][y+1].size = cells[i][1].size;
	// }
}