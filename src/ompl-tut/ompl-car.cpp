#include <ompl/control/SpaceInformation.h>
#include <ompl/base/spaces/SE2StateSpace.h>
#include <ompl/control/ODESolver.h>
#include <ompl/control/spaces/RealVectorControlSpace.h>
#include <ompl/control/SimpleSetup.h>
#include <ompl/config.h>
#include <ompl/control/planners/kpiece/KPIECE1.h>
#include <ompl/control/planners/rrt/RRT.h>
#include <ompl/control/planners/est/EST.h>
#include <ompl/control/planners/syclop/SyclopRRT.h>
#include <ompl/control/planners/syclop/SyclopEST.h>
#include <ompl/control/planners/pdst/PDST.h>
#include <ompl/control/planners/syclop/GridDecomposition.h>

#include <iostream>
#include <fstream>
#include <valarray>
#include <limits>

namespace ob = ompl::base;
namespace oc = ompl::control;

// Definition of the ODE for the kinematic car.
// This method is analogous to the above KinematicCarModel::ode function.
void KinematicCarODE (const oc::ODESolver::StateType& q, const oc::Control* control, oc::ODESolver::StateType& qdot)
{
    const double *u = control->as<oc::RealVectorControlSpace::ControlType>()->values;
    const double theta = q[2];
    double carLength = 0.0002;

    // Zero out qdot
    qdot.resize (q.size (), 0);

    qdot[0] = u[0] * cos(theta);
    qdot[1] = u[0] * sin(theta);
    qdot[2] = u[0] * tan(u[1]) / carLength;
}

// This is a callback method invoked after numerical integration.
void KinematicCarPostIntegration (const ob::State* /*state*/, const oc::Control* /*control*/, const double /*duration*/, ob::State *result)
{
    // Normalize orientation between 0 and 2*pi
    ob::SO2StateSpace SO2;
    SO2.enforceBounds(result->as<ob::SE2StateSpace::StateType>()->as<ob::SO2StateSpace::StateType>(1));
}

bool isStateValid(const oc::SpaceInformation *si, const ob::State *state)
{
    //    ob::ScopedState<ob::SE2StateSpace>
    const auto *se2state = state->as<ob::SE2StateSpace::StateType>();

    const auto *pos = se2state->as<ob::RealVectorStateSpace::StateType>(0);

    const auto *rot = se2state->as<ob::SO2StateSpace::StateType>(1);

    // return a value that is always true but uses the two variables we define,
    // so we avoid compiler warnings
    return si->satisfiesBounds(state) && (const void*)rot != (const void*)pos;
}

class DemoControlSpace : public oc::RealVectorControlSpace
{
public:

    DemoControlSpace(const ob::StateSpacePtr &stateSpace) : oc::RealVectorControlSpace(stateSpace, 2)
        {
        }
};

void planWithSimpleSetup()
{
    auto space(std::make_shared<ob::SE2StateSpace>());

    ob::RealVectorBounds bounds(2);
    bounds.setLow(-1);
    bounds.setHigh(1);

    space->setBounds(bounds);

    // create a control space
    auto cspace(std::make_shared<DemoControlSpace>(space));

    // set the bounds for the control space
    ob::RealVectorBounds cbounds(2);
    cbounds.setLow(-0.3);
    cbounds.setHigh(0.3);

    cspace->setBounds(cbounds);

    // define a simple setup class
    oc::SimpleSetup ss(cspace);

    // set state validity checking for this space
    oc::SpaceInformation *si = ss.getSpaceInformation().get();
    ss.setStateValidityChecker(
        [si](const ob::State *state) { return isStateValid(si, state); });

    // Use the ODESolver to propagate the system.  Call KinematicCarPostIntegration
    // when integration has finished to normalize the orientation values.
    auto odeSolver(std::make_shared<oc::ODEBasicSolver<>>(ss.getSpaceInformation(), &KinematicCarODE));
    ss.setStatePropagator(oc::ODESolver::getStatePropagator(odeSolver, &KinematicCarPostIntegration));

    ob::ScopedState<ob::SE2StateSpace> start(space);
    start->setX(-0.5);
    start->setY(0.0);
    start->setYaw(0.0);

    ob::ScopedState<ob::SE2StateSpace> goal(space);
    goal->setX(0.0);
    goal->setY(0.5);
    goal->setYaw(0.0);

    ss.setStartAndGoalStates(start, goal, 0.01);

    ss.setup();

    ob::PlannerStatus solved = ss.solve(10.0);

    if (solved)
    {
        std::cout << "Found solution:" << std::endl;        
        //ss.getSolutionPath().asGeometric().printAsMatrix(std::cout);

        std::ofstream path_stream;
        path_stream.open("./path.txt");
        ss.getSolutionPath().asGeometric().printAsMatrix(path_stream);        
    }
    else
        std::cout << "No solution found" << std::endl;
}

// a decomposition is only needed for SyclopRRT and SyclopEST
class MyDecomposition : public oc::GridDecomposition
{
public:
    MyDecomposition(const int length, const ob::RealVectorBounds& bounds)
        : GridDecomposition(length, 2, bounds)
        {
        }
    void project(const ob::State* s, std::vector<double>& coord) const override
        {
            coord.resize(2);
            coord[0] = s->as<ob::SE2StateSpace::StateType>()->getX();
            coord[1] = s->as<ob::SE2StateSpace::StateType>()->getY();
        }
   
    void sampleFullState(const ob::StateSamplerPtr& sampler, const std::vector<double>& coord, ob::State* s) const override
        {
            sampler->sampleUniform(s);
            s->as<ob::SE2StateSpace::StateType>()->setXY(coord[0], coord[1]);
        }
};

void plan()
{
    auto space(std::make_shared<ob::SE2StateSpace>());

    ob::RealVectorBounds bounds(2);
    bounds.setLow(-1);
    bounds.setHigh(1);

    space->setBounds(bounds);

    // create a control space
    auto cspace(std::make_shared<DemoControlSpace>(space));

    // set the bounds for the control space
    ob::RealVectorBounds cbounds(2);
    cbounds.setLow(-0.3);
    cbounds.setHigh(0.3);

    cspace->setBounds(cbounds);

    // construct an instance of space information from this state space
    auto si(std::make_shared<oc::SpaceInformation>(space, cspace));

    // set state validity checking for this space
    si->setStateValidityChecker(
        [&si](const ob::State *state) { return isStateValid(si.get(), state); });
   
    // Use the ODESolver to propagate the system.  Call KinematicCarPostIntegration
    // when integration has finished to normalize the orientation values.
    auto odeSolver(std::make_shared<oc::ODEBasicSolver<>>(si, &KinematicCarODE));
    si->setStatePropagator(oc::ODESolver::getStatePropagator(odeSolver, &KinematicCarPostIntegration));
    
    ob::ScopedState<ob::SE2StateSpace> start(space);
    start->setX(-0.5);
    start->setY(0.0);
    start->setYaw(0.0);
    
    ob::ScopedState<ob::SE2StateSpace> goal(space);
    goal->setX(0.0);
    goal->setY(0.5);
    goal->setYaw(0.0);

    // create a problem instance
    auto pdef(std::make_shared<ob::ProblemDefinition>(si));
    
    pdef->setStartAndGoalStates(start, goal, 0.01);

    // create a planner for the defined space
    //auto planner(std::make_shared<oc::RRT>(si));
    //auto planner(std::make_shared<oc::EST>(si));
    auto planner(std::make_shared<oc::KPIECE1>(si));
    //auto decomp(std::make_shared<MyDecomposition>(32, bounds));
    //auto planner(std::make_shared<oc::SyclopEST>(si, decomp));
    //auto planner(std::make_shared<oc::SyclopRRT>(si, decomp));

    planner->setProblemDefinition(pdef);

    planner->setup();

    si->printSettings(std::cout);

    pdef->print(std::cout);

    ob::PlannerStatus solved = planner->ob::Planner::solve(10.0);
    
    if (solved) {
        std::cout << "Found solution:" << std::endl;

        std::ofstream path_stream;
        path_stream.open("./path.txt");

        ob::PathPtr path = pdef->getSolutionPath();
        path->as<ompl::geometric::PathGeometric>()->printAsMatrix(path_stream);
        //pdef->getSolutionPath.asGeometric.printAsMatrix(path_stream);        
    } else {
        std::cout << "No solution found" << std::endl;
    }
}


int main(int /*argc*/, char ** /*argv*/)
{
    std::cout << "OMPL version: " << OMPL_VERSION << std::endl;

    //planWithSimpleSetup();
    plan();

    return 0;
}
