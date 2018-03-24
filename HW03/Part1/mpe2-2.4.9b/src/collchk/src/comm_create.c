/*
   (C) 2004 by Argonne National Laboratory.
       See COPYRIGHT in top-level directory.
*/
#include "collchk.h" 

int MPI_Comm_create(MPI_Comm comm, MPI_Group group, MPI_Comm *newcomm)
{
    int g2g = 1;
    char call[COLLCHK_SM_STRLEN];

    sprintf(call, "COMM_CREATE");

    /* Check if init has been called */
    g2g = CollChk_is_init();

    if(g2g) {
        /* check for call consistancy */
        CollChk_same_call(comm, call);

        /* make the call */
        return PMPI_Comm_create(comm, group, newcomm); 
    }
    else {
        /* init not called */
        return CollChk_err_han("MPI_Init() has not been called!",
                               COLLCHK_ERR_NOT_INIT, call, comm);
    }
}
