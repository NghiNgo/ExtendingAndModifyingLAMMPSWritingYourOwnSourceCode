#include "lammps.h"
#include <mpi.h>
#include "input.h"

#if defined(LAMMPS_TRAP_FPE) && defined(_GNU_SOURCE)
#include <fenv.h>
#endif

#ifdef FFT_FFTW3
#include <fftw3.h>
#endif

#if defined(LAMMPS_EXCEPTIONS)
#include "exceptions.h"
#endif

using namespace LAMMPS_NS;

/* ----------------------------------------------------------------------
   main program to drive LAMMPS
------------------------------------------------------------------------- */

int main(int argc, char **argv)
{
  MPI_Init(&argc,&argv);

// enable trapping selected floating point exceptions.
// this uses GNU extensions and is only tested on Linux
// therefore we make it depend on -D_GNU_SOURCE, too.

#if defined(LAMMPS_TRAP_FPE) && defined(_GNU_SOURCE)
  fesetenv(FE_NOMASK_ENV);
  fedisableexcept(FE_ALL_EXCEPT);
  feenableexcept(FE_DIVBYZERO);
  feenableexcept(FE_INVALID);
  feenableexcept(FE_OVERFLOW);
#endif

#ifdef LAMMPS_EXCEPTIONS
  try {
    LAMMPS *lammps = new LAMMPS(argc,argv,MPI_COMM_WORLD);
    lammps->input->file();
    delete lammps;
  } catch(LAMMPSAbortException & ae) {
    MPI_Abort(ae.universe, 1);
  } catch(LAMMPSException & e) {
    MPI_Finalize();
    exit(1);
  }
#else
  LAMMPS *lammps = new LAMMPS(argc,argv,MPI_COMM_WORLD);
  lammps->input->file();
  delete lammps;
#endif
  MPI_Barrier(MPI_COMM_WORLD);
  MPI_Finalize();

#ifdef FFT_FFTW3
  // tell fftw3 to delete its global memory pool
  // and thus avoid bogus valgrind memory leak reports
#ifdef FFT_SINGLE
  fftwf_cleanup();
#else
  fftw_cleanup();
#endif
#endif
}
