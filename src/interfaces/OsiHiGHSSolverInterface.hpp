/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                       */
/*    This file is part of the HiGHS linear optimization suite           */
/*                                                                       */
/*    Written and engineered 2008-2019 at the University of Edinburgh    */
/*                                                                       */
/*    Available as open-source under the MIT License                     */
/*                                                                       */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/**@file interfaces/OsiHiGHSInterface.hpp
 * @brief Osi/HiGHS interface header
 * @author Julian Hall, Ivet Galabova, Qi Huangfu and Michael Feldmeier
 */
#ifndef OsiHiGHSSolverInterface_H
#define OsiHiGHSSolverInterface_H

#include "OsiSolverInterface.hpp"
#include "HighsStatus.h"

// forward declarations
class Highs;
class HighsLp;

/** HiGHS Solver Interface
 *
 *  Instantiation of OsiSolverInterface for HiGHS
 */
class OsiHiGHSSolverInterface : virtual public OsiSolverInterface {

public:
   //---------------------------------------------------------------------------
   /**@name Solve methods */
   //@{
   /// Solve initial LP relaxation
   /// @todo implement
   virtual void initialSolve();

   /// Resolve an LP relaxation after problem modification
   /// @todo implement
   virtual void resolve() { };

   /// Invoke solver's built-in enumeration algorithm
   /// @todo implement
   virtual void branchAndBound() { }
   //@}

   //---------------------------------------------------------------------------
   ///@name Parameter set/get methods
   ///@todo use OsiSolverInterface default implementation or override?
   ///@{
   // Set an integer parameter
   // bool setIntParam(OsiIntParam key, int value);
   // Set an double parameter
   // bool setDblParam(OsiDblParam key, double value);
   // Set a string parameter
   // bool setStrParam(OsiStrParam key, const std::string &value);
   // Get an integer parameter
   // bool getIntParam(OsiIntParam key, int &value) const;
   // Get an double parameter
   // bool getDblParam(OsiDblParam key, double &value) const;
   // Get a string parameter
   // bool getStrParam(OsiStrParam key, std::string &value) const;
   //@}

   //---------------------------------------------------------------------------
   ///@name Methods returning info on how the solution process terminated
   ///@{
   ///@todo implement
   /// Are there a numerical difficulties?
   virtual bool isAbandoned() const ;
   /// Is optimality proven?
   virtual bool isProvenOptimal() const;
   /// Is primal infeasiblity proven?
   virtual bool isProvenPrimalInfeasible() const;
   /// Is dual infeasiblity proven?
   virtual bool isProvenDualInfeasible() const;
   /// Is the given primal objective limit reached?
   virtual bool isPrimalObjectiveLimitReached() const;
   /// Is the given dual objective limit reached?
   virtual bool isDualObjectiveLimitReached() const;
   /// Iteration limit reached?
   virtual bool isIterationLimitReached() const;
   //@}

   //---------------------------------------------------------------------------
   ///@name Warm start methods
   ///@{
   ///@todo implement

   /// Get an empty warm start object
   CoinWarmStart *getEmptyWarmStart() const { return NULL; }

   /// Get warmstarting information
   virtual CoinWarmStart* getWarmStart() const { return NULL; }

   /** Set warmstarting information. Return true/false depending on whether
    *  the warmstart information was accepted or not.
    */
   virtual bool setWarmStart(const CoinWarmStart *warmstart) { return false; }
   ///@}

   //---------------------------------------------------------------------------
   ///@name Problem query methods
   ///@{
   ///@todo implement

   /// Get number of columns
   virtual int getNumCols() const;

   /// Get number of rows
   virtual int getNumRows() const;

   /// Get number of nonzero elements
   virtual int getNumElements() const;

   /// Get pointer to array[getNumCols()] of column lower bounds
   virtual const double* getColLower() const;

   /// Get pointer to array[getNumCols()] of column upper bounds
   virtual const double* getColUpper() const;

   /// Get pointer to array[getNumRows()] of row constraint senses.
   virtual const char* getRowSense() const;

   /// Get pointer to array[getNumRows()] of rows right-hand sides
   virtual const double* getRightHandSide() const;

   /// Get pointer to array[getNumRows()] of row ranges.
   virtual const double* getRowRange() const;

   /// Get pointer to array[getNumRows()] of row lower bounds
   virtual const double* getRowLower() const;

   /// Get pointer to array[getNumRows()] of row upper bounds
   virtual const double* getRowUpper() const;

   /// Get pointer to array[getNumCols()] of objective function coefficients
   virtual const double* getObjCoefficients() const;

   /// Get objective function sense (1 for min (default), -1 for max)
   double getObjSense() const;

   /// Return true if column is continuous
   virtual bool isContinuous(int colNumber) const  { return true; }

   /// Get pointer to row-wise copy of matrix
   virtual const CoinPackedMatrix* getMatrixByRow() const { return NULL; }

   /// Get pointer to column-wise copy of matrix
   virtual const CoinPackedMatrix *getMatrixByCol() const { return NULL; }

   /// Get solver's value for infinity
   virtual double getInfinity() const;
   //@}

   ///@name Solution query methods
   ///@{
   ///@todo implement

   /// Get pointer to array[getNumCols()] of primal solution vector
   virtual const double* getColSolution() const { return NULL; }

   /// Get pointer to array[getNumRows()] of dual prices
   virtual const double* getRowPrice() const { return NULL; }

   /// Get a pointer to array[getNumCols()] of reduced costs
   virtual const double* getReducedCost() const { return NULL; }

   /// Get pointer to array[getNumRows()] of row activity levels (constraint matrix times the solution vector)
   virtual const double *getRowActivity() const { return NULL; }

   /// Get objective function value
   virtual double getObjValue() const { return 0.0; }

   /// Get how many iterations it took to solve the problem (whatever "iteration" mean to the solver)
   virtual int getIterationCount() const { return 42; }

   /// Get as many dual rays as the solver can provide.
   virtual std::vector< double*> getDualRays(int maxNumRays, bool fullRay = false) const { return std::vector<double*>(0); }

   /// Get as many primal rays as the solver can provide.
   virtual std::vector<double*> getPrimalRays(int maxNumRays) const { return std::vector<double*>(0); }

   ///@}

   //---------------------------------------------------------------------------

   ///@name Methods to modify the objective, bounds, and solution
   ///@{
   ///@todo implement

   /// Set an objective function coefficient
   virtual void setObjCoeff(int elementIndex, double elementValue) { };

   /// Set a set of objective function coefficients
   virtual void setObjCoeffSet(const int *indexFirst,
     const int *indexLast,
     const double *coeffList) { };

   /// Set objective function sense (1 for min (default), -1 for max)
   virtual void setObjSense(double s) { }

   using OsiSolverInterface::setColLower;
   /// Set a single column lower bound
   virtual void setColLower(int elementIndex, double elementValue) { };

   using OsiSolverInterface::setColUpper;
   /// Set a single column upper bound
   virtual void setColUpper(int elementIndex, double elementValue) { };

   /// Set a single column lower and upper bound
   //virtual void setColBounds(int elementIndex,
   //  double lower, double upper)

   /// Set the bounds on a number of columns simultaneously
   //virtual void setColSetBounds(const int *indexFirst,
   //  const int *indexLast,
   //  const double *boundList);

   /// Set a single row lower bound
   virtual void setRowLower(int elementIndex, double elementValue) { }

   /// Set a single row upper bound
   virtual void setRowUpper(int elementIndex, double elementValue) { }

   /// Set a single row lower and upper bound
   //virtual void setRowBounds(int elementIndex,
   //  double lower, double upper);

   /// Set the bounds on a number of rows simultaneously
   // virtual void setRowSetBounds(const int *indexFirst,
   //   const int *indexLast,
   //  const double *boundList);

   /// Set the type of a single row
   virtual void setRowType(int index, char sense, double rightHandSide,
     double range) { };

   /// Set the type of a number of rows simultaneously
   // virtual void setRowSetTypes(const int *indexFirst,
   //  const int *indexLast,
   //  const char *senseList,
   //  const double *rhsList,
   //  const double *rangeList);
   //@}

   /// Set the primal solution column values
   virtual void setColSolution(const double *colsol) { }

   /// Set dual solution vector
   virtual void setRowPrice(const double *rowprice) { };

   /// Set the index-th variable to be a continuous variable
   virtual void setContinuous(int index) { }

   /// Set the index-th variable to be an integer variable
   virtual void setInteger(int index) { };

   /// Set the variables listed in indices (which is of length len) to be continuous variables
   // virtual void setContinuous(const int *indices, int len);

   /// Set the variables listed in indices (which is of length len) to be integer variables
   // virtual void setInteger(const int *indices, int len);

   //-------------------------------------------------------------------------
   ///@name Methods to modify the constraint system.
   ///@{
   ///@todo implement

   using OsiSolverInterface::addCol;
   // Add a column (primal variable) to the problem.
   virtual void addCol(const CoinPackedVectorBase &vec,
     const double collb, const double colub,
     const double obj) { }

   /// Remove a set of columns (primal variables) from the problem.
   virtual void deleteCols(const int num, const int *colIndices) { };

   using OsiSolverInterface::addRow;
   /// Add a row (constraint) to the problem.
   void addRow(const CoinPackedVectorBase &vec,
     const double rowlb, const double rowub);

   /// Add a row (constraint) to the problem. */
   virtual void addRow(const CoinPackedVectorBase &vec,
     const char rowsen, const double rowrhs,
     const double rowrng) { };

   /// Delete a set of rows (constraints) from the problem.
   virtual void deleteRows(const int num, const int *rowIndices) { };

   ///@}

   //---------------------------------------------------------------------------
   ///@name Methods for problem input and output
   ///@{
   ///@todo implement

   /// Load in an problem by copying the arguments
   virtual void loadProblem(const CoinPackedMatrix& matrix,
     const double* collb, const double* colub,
     const double* obj,
     const double* rowlb, const double* rowub);

   /// Load in an problem by assuming ownership of the arguments.
   virtual void assignProblem(CoinPackedMatrix*& matrix,
     double*& collb, double*& colub, double*& obj,
     double*& rowlb, double*& rowub) { };

   /// Load in an problem by copying the arguments.
   virtual void loadProblem(const CoinPackedMatrix &matrix,
     const double* collb, const double* colub,
     const double* obj,
     const char* rowsen, const double* rowrhs,
     const double* rowrng) { };

   /// Load in an problem by assuming ownership of the arguments
   virtual void assignProblem(CoinPackedMatrix*& matrix,
     double*& collb, double*& colub, double*& obj,
     char*& rowsen, double*& rowrhs,
     double*& rowrng) { };

   /// Load in a problem by copying the arguments.
   virtual void loadProblem(const int numcols, const int numrows,
     const CoinBigIndex* start, const int* index,
     const double* value,
     const double* collb, const double* colub,
     const double* obj,
     const double* rowlb, const double* rowub) { }

   /// Load in a problem by copying the arguments.
   virtual void loadProblem(const int numcols, const int numrows,
     const CoinBigIndex *start, const int *index,
     const double *value,
     const double *collb, const double *colub,
     const double *obj,
     const char *rowsen, const double *rowrhs,
     const double *rowrng) { }

   /// Write the problem into an mps file of the given filename.
   virtual void writeMps(const char* filename,
     const char* extension = "mps",
     double objSense = 0.0) const { };

   ///@}

   ///@name Constructors and destructor
   ///@{

   /// Default Constructor
   OsiHiGHSSolverInterface();

   /// Clone
   /// @todo implement
   virtual OsiSolverInterface* clone(bool copyData = true) const { return new OsiHiGHSSolverInterface(); }

   /// Copy constructor
   // OsiHiGHSSolverInterface(const OsiHiGHSSolverInterface &);

   /// Assignment operator
   // OsiHiGHSSolverInterface &operator=(const OsiHiGHSSolverInterface& rhs);

  /// Destructor
  virtual ~OsiHiGHSSolverInterface();

   /// Resets as if default constructor
   // virtual void reset();
   ///@}
   /***************************************************************************/

 protected:
   /// Apply a row cut.
   virtual void applyRowCut(const OsiRowCut& rc) { }

   /// Apply a column cut (bound adjustment).
   virtual void applyColCut(const OsiColCut& cc) { }


private:

  Highs* highs;
  HighsLp* lp = NULL;
  HighsStatus status = HighsStatus::Init;
  mutable double* rowRange = NULL;
  mutable double* rhs = NULL;
  mutable char* rowSense = NULL;

};

#endif
