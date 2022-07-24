#ifndef LMP_POINTERS_H
#define LMP_POINTERS_H

#include "lmptype.h"   // IWYU pragma: export
#include <mpi.h>       // IWYU pragma: export
#include <cstddef>     // IWYU pragme: export
#include <cstdio>      // IWYU pragma: export
#include "lammps.h"    // IWYU pragma: export

namespace LAMMPS_NS {

// universal defines inside namespace

#define FLERR __FILE__,__LINE__

#define MIN(A,B) ((A) < (B) ? (A) : (B))
#define MAX(A,B) ((A) > (B) ? (A) : (B))

// enum used for KOKKOS host/device flags

enum ExecutionSpace{Host,Device};

// global forward declarations

template <class T> class MyPoolChunk;
template <class T> class MyPage;

class Pointers {
 public:
  Pointers(LAMMPS *ptr) :
    lmp(ptr),
    memory(ptr->memory),
    error(ptr->error),
    universe(ptr->universe),
    input(ptr->input),
    atom(ptr->atom),
    update(ptr->update),
    neighbor(ptr->neighbor),
    comm(ptr->comm),
    domain(ptr->domain),
    force(ptr->force),
    modify(ptr->modify),
    group(ptr->group),
    output(ptr->output),
    timer(ptr->timer),
    world(ptr->world),
    infile(ptr->infile),
    screen(ptr->screen),
    logfile(ptr->logfile),
    atomKK(ptr->atomKK),
    memoryKK(ptr->memoryKK),
    python(ptr->python) {}
  virtual ~Pointers() {}

 protected:
  LAMMPS *lmp;
  Memory *&memory;
  Error *&error;
  Universe *&universe;
  Input *&input;

  Atom *&atom;
  Update *&update;
  Neighbor *&neighbor;
  Comm *&comm;
  Domain *&domain;
  Force *&force;
  Modify *&modify;
  Group *&group;
  Output *&output;
  Timer *&timer;

  MPI_Comm &world;
  FILE *&infile;
  FILE *&screen;
  FILE *&logfile;

  class AtomKokkos *&atomKK;
  class MemoryKokkos *&memoryKK;
  class Python *&python;
};

}

#endif
