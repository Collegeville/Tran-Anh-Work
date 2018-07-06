
//@HEADER
// ***************************************************
//
// HPCG: High Performance Conjugate Gradient Benchmark
//
// Contact:
// Michael A. Heroux ( maherou@sandia.gov)
// Jack Dongarra     (dongarra@eecs.utk.edu)
// Piotr Luszczek    (luszczek@eecs.utk.edu)
//
// ***************************************************
//@HEADER

/*!
 @file ReportResults.cpp

 HPCG routine
 */

//#ifndef HPCG_NO_MPI
//#include <mpi.h>
//#endif

#include <vector>
#include "ReportResults.hpp"
#include "OutputFile.hpp"
#include "OptimizeProblem.hpp"

#ifdef HPCG_DEBUG
#include <fstream>
using std::endl;

#include "hpcg.hpp"
#endif

/*!
 Creates a YAML file and writes the information about the HPCG run, its results, and validity.

  @param[in] geom The description of the problem's geometry.
  @param[in] A    The known system matrix
  @param[in] numberOfMgLevels Number of levels in multigrid V cycle
  @param[in] numberOfCgSets Number of CG runs performed
  @param[in] niters Number of preconditioned CG iterations performed to lower the residual below a threshold
  @param[in] times  Vector of cumulative timings for each of the phases of a preconditioned CG iteration
  @param[in] testcg_data    the data structure with the results of the CG-correctness test including pass/fail information
  @param[in] testsymmetry_data the data structure with the results of the CG symmetry test including pass/fail information

*/
double ReportGFlops(const SparseMatrix & A, int numberOfMgLevels, int numberOfCgSets, int refMaxIters,int optMaxIters, double times[],
    const TestCGData & testcg_data, const TestSymmetryData & testsymmetry_data, const TestNormsData & testnorms_data) {
    double result;
  //double minOfficialTime = 1800; // Any official benchmark result must run at least this many seconds
//#ifndef HPCG_NO_MPI
  //double t4 = times[4];
  //double t4min = 0.0;
  //double t4max = 0.0;
  //double t4avg = 0.0;
  //MPI_Allreduce(&t4, &t4min, 1, MPI_DOUBLE, MPI_MIN, MPI_COMM_WORLD);
  //MPI_Allreduce(&t4, &t4max, 1, MPI_DOUBLE, MPI_MAX, MPI_COMM_WORLD);
  //MPI_Allreduce(&t4, &t4avg, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);
  //t4avg = t4avg/((double) A.geom->size);
//#endif

  if (A.geom->rank==0) { // Only PE 0 needs to compute and report timing results

    // TODO: Put the FLOP count, Memory BW and Memory Usage models into separate functions

    // ======================== FLOP count model =======================================

    double fNumberOfCgSets = numberOfCgSets;
    double fniters = fNumberOfCgSets * (double) optMaxIters;
    double fnrow = A.totalNumberOfRows;
    double fnnz = A.totalNumberOfNonzeros;

    // Op counts come from implementation of CG in CG.cpp (include 1 extra for the CG preamble ops)
    double fnops_ddot = (3.0*fniters+fNumberOfCgSets)*2.0*fnrow; // 3 ddots with nrow adds and nrow mults
    double fnops_waxpby = (3.0*fniters+fNumberOfCgSets)*2.0*fnrow; // 3 WAXPBYs with nrow adds and nrow mults
    double fnops_sparsemv = (fniters+fNumberOfCgSets)*2.0*fnnz; // 1 SpMV with nnz adds and nnz mults
    // Op counts from the multigrid preconditioners
    double fnops_precond = 0.0;
    const SparseMatrix * Af = &A;
    for (int i=1; i<numberOfMgLevels; ++i) {
      double fnnz_Af = Af->totalNumberOfNonzeros;
      double fnumberOfPresmootherSteps = Af->mgData->numberOfPresmootherSteps;
      double fnumberOfPostsmootherSteps = Af->mgData->numberOfPostsmootherSteps;
      fnops_precond += fnumberOfPresmootherSteps*fniters*4.0*fnnz_Af; // number of presmoother flops
      fnops_precond += fniters*2.0*fnnz_Af; // cost of fine grid residual calculation
      fnops_precond += fnumberOfPostsmootherSteps*fniters*4.0*fnnz_Af;  // number of postsmoother flops
      Af = Af->Ac; // Go to next coarse level
    }

    fnops_precond += fniters*4.0*((double) Af->totalNumberOfNonzeros); // One symmetric GS sweep at the coarsest level
    double fnops = fnops_ddot+fnops_waxpby+fnops_sparsemv+fnops_precond;
    double frefnops = fnops * ((double) refMaxIters)/((double) optMaxIters);

    // This final GFLOP/s rating includes the overhead of problem setup and optimizing the data structures vs ten sets of 50 iterations of CG
    double totalGflops = frefnops/(times[0]+fNumberOfCgSets*(times[7]/10.0+times[9]/10.0))/1.0E9;
      result= totalGflops;
    //double totalGflops24 = frefnops/(times[0]+fNumberOfCgSets*times[7]/10.0)/1.0E9;
  }
  return result;
}

double ReportBandwidth(const SparseMatrix & A, int numberOfMgLevels, int numberOfCgSets,int optMaxIters, double times[],
                   const TestCGData & testcg_data, const TestSymmetryData & testsymmetry_data, const TestNormsData & testnorms_data) {
    double result;
    if (A.geom->rank==0) { // Only PE 0 needs to compute and report timing results

        // TODO: Put the FLOP count, Memory BW and Memory Usage models into separate functions

        // ======================== FLOP count model =======================================

        double fNumberOfCgSets = numberOfCgSets;
        double fniters = fNumberOfCgSets * (double) optMaxIters;
        double fnrow = A.totalNumberOfRows;
        double fnnz = A.totalNumberOfNonzeros;

        // Op counts come from implementation of CG in CG.cpp (include 1 extra for the CG preamble ops)
        double fnops_ddot = (3.0*fniters+fNumberOfCgSets)*2.0*fnrow; // 3 ddots with nrow adds and nrow mults
        double fnops_waxpby = (3.0*fniters+fNumberOfCgSets)*2.0*fnrow; // 3 WAXPBYs with nrow adds and nrow mults
        double fnops_sparsemv = (fniters+fNumberOfCgSets)*2.0*fnnz; // 1 SpMV with nnz adds and nnz mults
        // Op counts from the multigrid preconditioners
        double fnops_precond = 0.0;
        const SparseMatrix * Af = &A;
        for (int i=1; i<numberOfMgLevels; ++i) {
            double fnnz_Af = Af->totalNumberOfNonzeros;
            double fnumberOfPresmootherSteps = Af->mgData->numberOfPresmootherSteps;
            double fnumberOfPostsmootherSteps = Af->mgData->numberOfPostsmootherSteps;
            fnops_precond += fnumberOfPresmootherSteps*fniters*4.0*fnnz_Af; // number of presmoother flops
            fnops_precond += fniters*2.0*fnnz_Af; // cost of fine grid residual calculation
            fnops_precond += fnumberOfPostsmootherSteps*fniters*4.0*fnnz_Af;  // number of postsmoother flops
            Af = Af->Ac; // Go to next coarse level
        }


        // ======================== Memory bandwidth model =======================================

        // Read/Write counts come from implementation of CG in CG.cpp (include 1 extra for the CG preamble ops)
        double fnreads_ddot = (3.0*fniters+fNumberOfCgSets)*2.0*fnrow*sizeof(double); // 3 ddots with 2 nrow reads
        double fnwrites_ddot = (3.0*fniters+fNumberOfCgSets)*sizeof(double); // 3 ddots with 1 write
        double fnreads_waxpby = (3.0*fniters+fNumberOfCgSets)*2.0*fnrow*sizeof(double); // 3 WAXPBYs with nrow adds and nrow mults
        double fnwrites_waxpby = (3.0*fniters+fNumberOfCgSets)*fnrow*sizeof(double); // 3 WAXPBYs with nrow adds and nrow mults
        double fnreads_sparsemv = (fniters+fNumberOfCgSets)*(fnnz*(sizeof(double)+sizeof(local_int_t)) + fnrow*sizeof(double));// 1 SpMV with nnz reads of values, nnz reads indices,
        // plus nrow reads of x
        double fnwrites_sparsemv = (fniters+fNumberOfCgSets)*fnrow*sizeof(double); // 1 SpMV nrow writes
        // Op counts from the multigrid preconditioners
        double fnreads_precond = 0.0;
        double fnwrites_precond = 0.0;
        Af = &A;
        for (int i=1; i<numberOfMgLevels; ++i) {
            double fnnz_Af = Af->totalNumberOfNonzeros;
            double fnrow_Af = Af->totalNumberOfRows;
            double fnumberOfPresmootherSteps = Af->mgData->numberOfPresmootherSteps;
            double fnumberOfPostsmootherSteps = Af->mgData->numberOfPostsmootherSteps;
            fnreads_precond += fnumberOfPresmootherSteps*fniters*(2.0*fnnz_Af*(sizeof(double)+sizeof(local_int_t)) + fnrow_Af*sizeof(double)); // number of presmoother reads
            fnwrites_precond += fnumberOfPresmootherSteps*fniters*fnrow_Af*sizeof(double); // number of presmoother writes
            fnreads_precond += fniters*(fnnz_Af*(sizeof(double)+sizeof(local_int_t)) + fnrow_Af*sizeof(double)); // Number of reads for fine grid residual calculation
            fnwrites_precond += fniters*fnnz_Af*sizeof(double); // Number of writes for fine grid residual calculation
            fnreads_precond += fnumberOfPostsmootherSteps*fniters*(2.0*fnnz_Af*(sizeof(double)+sizeof(local_int_t)) + fnrow_Af*sizeof(double));  // number of postsmoother reads
            fnwrites_precond += fnumberOfPostsmootherSteps*fniters*fnnz_Af*sizeof(double);  // number of postsmoother writes
            Af = Af->Ac; // Go to next coarse level
        }

        double fnnz_Af = Af->totalNumberOfNonzeros;
        double fnrow_Af = Af->totalNumberOfRows;
        fnreads_precond += fniters*(2.0*fnnz_Af*(sizeof(double)+sizeof(local_int_t)) + fnrow_Af*sizeof(double));; // One symmetric GS sweep at the coarsest level
        fnwrites_precond += fniters*fnrow_Af*sizeof(double); // One symmetric GS sweep at the coarsest level
        double fnreads = fnreads_ddot+fnreads_waxpby+fnreads_sparsemv+fnreads_precond;
        double fnwrites = fnwrites_ddot+fnwrites_waxpby+fnwrites_sparsemv+fnwrites_precond;
        //double frefnreads = fnreads * ((double) refMaxIters)/((double) optMaxIters);
        //double frefnwrites = fnwrites * ((double) refMaxIters)/((double) optMaxIters);

        result =(fnreads+fnwrites)/(times[0])/1.0E9;
    }
    return result;
}
