#include <all_shop_states.hpp>

ShopState& RestockingSuggestion::getInstance() {
  static RestockingSuggestion singleton;
  return singleton;
}

void RestockingSuggestion::enter(Shop* shop) {}
void RestockingSuggestion::exit(Shop* shop) {}

void RestockingSuggestion::eventCalled(Event event, Shop* shop) {
  switch (event)
  {
  case ShopState::Event::kExitCalled:
    shop->setState(AdminOptionSelection::getInstance());
    break;
  
  default:
    break;
  }
}

RestockingSuggestion::RestockingSuggestion() {}

void RestockingSuggestion::MipVarArray(std::vector<long long> current_inventory, std::vector<long double> buying_price, std::vector<long double> selling_price, std::vector<long double> holding_cost, std::vector<long long> forecast, long double capital) {
  // Create the mip solver with the SCIP backend.
  std::unique_ptr<MPSolver> solver(MPSolver::CreateSolver("SCIP"));
  if (!solver) {
    LOG(WARNING) << "SCIP solver unavailable.";
    return;
  }
  std::vector<double> solution;
  long long n = current_inventory.size();
  const double infinity = solver->infinity();
  // x[j] is an array of non-negative, integer variables.
  std::vector<const MPVariable*> x(2*n);
  for (int j = 0; j < n; ++j) {
    x[j] = solver->MakeIntVar(0.0, infinity, "");
    x[n+j] = solver->MakeIntVar(-infinity, infinity, "");

  }
  //LOG(INFO) << "Number of variables = " << solver->NumVariables();

  // Create the constraints.
  for (int i = 0; i <n; ++i) {
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
  for (int i =0; i<n; ++i){
    constraint->SetCoefficient(x[i],buying_price[i]);
  }
  //LOG(INFO) << "Number of constraints = " << solver->NumConstraints();

  // Create the objective function.
  MPObjective* const objective = solver->MutableObjective();
  for (int j = 0; j < n; ++j) {
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

  for (int j = 0; j <n; ++j) {
    solution.push_back(x[j]->solution_value());
  }
  return(solution);

}