#include "ortools/linear_solver/linear_solver.h"

namespace operations_research{
void optimizer(std::vector<long long> current_inventory, std::vector<double> buying_price, std::vector<double> selling_price, std::vector<double> holding_cost, std::vector<double> forecast, long double capital) {
  // Create the mip solver with the SCIP backend.
  std::unique_ptr<MPSolver> solver(MPSolver::CreateSolver("SCIP"));
  if (!solver) {
    LOG(WARNING) << "SCIP solver unavailable.";
    return;
  }
  long long n = current_inventory.size();
  const double infinity = solver->infinity();
  // x[j] is an array of non-negative, integer variables.
  std::vector<const MPVariable*> x(2*n);
  for (long long int j = 0; j < n; ++j) {
    x[j] = solver->MakeIntVar(0.0, infinity, "");
    x[n+j] = solver->MakeIntVar(-infinity, infinity, "");

  }
  //LOG(INFO) << "Number of variables = " << solver->NumVariables();

  // Create the constraints.
  for (long long int i = 0; i <n; ++i) {
    long double lower_bound_1,lower_bound_2;
    lower_bound_1 = holding_cost[i]*(current_inventory[i] - forecast[i]);
    lower_bound_2 = -selling_price[i]*(current_inventory[i] - forecast[i]);
    MPConstraint* constraint_1 = solver->MakeRowConstraint(lower_bound_1, infinity, "");
    MPConstraint* constraint_2 = solver->MakeRowConstraint(lower_bound_2, infinity, "");
    constraint_1->SetCoefficient(x[i],-holding_cost[i] );
    constraint_1->SetCoefficient(x[n+i],1 );
    constraint_2->SetCoefficient(x[i],selling_price[i] );
    constraint_2->SetCoefficient(x[n+i],1 );
  }

  MPConstraint* constraint = solver->MakeRowConstraint(0,capital,"");
  for (long long int i =0; i<n; ++i){
    constraint->SetCoefficient(x[i],buying_price[i]);
  }
  //LOG(INFO) << "Number of constraints = " << solver->NumConstraints();

  // Create the objective function.
  MPObjective* const objective = solver->MutableObjective();
  for (long long int j = 0; j < n; ++j) {
    objective->SetCoefficient(x[j], -buying_price[j]);
    objective->SetCoefficient(x[n+j], -1);
  }
  objective->SetMaximization();

  const MPSolver::ResultStatus result_status = solver->Solve();

  // Check that the problem has an optimal solution.
  if (result_status != MPSolver::OPTIMAL) {
    LOG(FATAL) << "The problem does not have an optimal solution.";
  }
  //LOG(INFO) << "Solution:";
  //LOG(INFO) << "Optimal objective value = " << objective->Value();
  for (int j = 0; j < n; ++j) {
    LOG(INFO) << "x[" << j << "] = " << x[j]->solution_value();
  }

 return;

}
}

int main(int argc, char** argv) {
  std::vector<long long> current_inventory;
  std::vector<double> buying_price,selling_price,holding_cost,forecast;
  long double capital = 10000;
  current_inventory  = {10,20,30};
  buying_price = {120,130,140};
  selling_price = {140,150,160};
  holding_cost = {5,5,5};
  forecast = {40,40,40};

  operations_research::optimizer(current_inventory, buying_price,selling_price,holding_cost,forecast,capital);
  return EXIT_SUCCESS;
}