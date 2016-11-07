/// ---------------------------------------------------------------------------
/// @section LICENSE
///  
/// Copyright (c) 2016 Georgia Tech Research Institute (GTRI) 
///               All Rights Reserved
///  
/// The above copyright notice and this permission notice shall be included in 
/// all copies or substantial portions of the Software.
///  
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
/// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
/// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
/// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
/// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
/// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER 
/// DEALINGS IN THE SOFTWARE.
/// ---------------------------------------------------------------------------
/// @file filename.ext
/// @author Kevin DeMarco <kevin.demarco@gtri.gatech.edu> 
/// @author Eric Squires <eric.squires@gtri.gatech.edu>
/// @version 1.0
/// ---------------------------------------------------------------------------
/// @brief A brief description.
/// 
/// @section DESCRIPTION
/// A long description.
/// ---------------------------------------------------------------------------
#include <iostream>
#include <FGFDMExec.h>
#include <models/FGAircraft.h>
#include <input_output/FGPropertyManager.h>
#include <initialization/FGInitialCondition.h>
#include <string>
#include <sstream>

using std::cout;
using std::endl;

int main(int argc, char *argv[])
{
    if (argc < 2) {
        cout << "usage: " << argv[0] << " script.xml" << endl;
        return -1;
    }

    int num_ents = 1;

    double t0 = 0;
    double tend = 100;
    double dt = 0.00833333;

    std::vector<JSBSim::FGFDMExec*> ents;

    for (int i = 0; i < num_ents; i++) {
        JSBSim::FGFDMExec *exec = new JSBSim::FGFDMExec();;
        exec->SetRootDir("./");
        exec->SetAircraftPath("aircraft");
        exec->SetEnginePath("engine");
        exec->SetSystemsPath("systems");

        exec->LoadScript(argv[1]);

        //exec->LoadModel(argv[1]);
        //
        //std::stringstream ss;
        //ss << i;
        //std::string out_str = "out-" + ss.str() + ".csv";
        //exec->SetOutputFileName(0,out_str);

        //JSBSim::FGInitialCondition *ic=exec->GetIC();
        //if ( ! ic->Load( argv[2] )) {
        //     cerr << "Initialization unsuccessful" << endl;
        //     return false;
        //}
        //ic->SetUBodyFpsIC(i*2);

        //JSBSim::FGPropertyManager* mgr = exec->GetPropertyManager();
        //JSBSim::FGPropertyNode *node = mgr->GetNode("fcs/throttle-cmd-norm");
        //node->setDoubleValue(1000);

        //node = mgr->GetNode("fcs/elevator-cmd-norm");
        //node->setDoubleValue(0);

        exec->RunIC();
        exec->Setdt(dt);

        ents.push_back(exec);
    }

    for (double t = t0; t < tend; t += dt) {
        for (std::vector<JSBSim::FGFDMExec*>::iterator it = ents.begin();
             it != ents.end(); it++) {

            JSBSim::FGPropertyManager* mgr = (*it)->GetPropertyManager();
            JSBSim::FGPropertyNode *node = mgr->GetNode("fcs/throttle-cmd-norm");
            node->setDoubleValue(0.75);

            //node = mgr->GetNode("fcs/pitch-trim-cmd-norm");
            //node->setDoubleValue(0);


            //// Roll
            //node = mgr->GetNode("attitude/phi-deg");
            //double phi = node->getDoubleValue();
            //
            //// Pitch
            //node = mgr->GetNode("attitude/theta-deg");
            //double theta = node->getDoubleValue();
            //
            //// Heading (yaw)
            //node = mgr->GetNode("attitude/psi-deg");
            //double psi = node->getDoubleValue();
            //
            //// Level flight
            //node = mgr->GetNode("fcs/pitch-trim-cmd-norm");
            //double pitch_cmd = 0;
            //pitch_cmd = (0-theta)* 0.001;
            //node->setDoubleValue(pitch_cmd);

            (*it)->Run();
        }
    }

    // Cleanup
    for (std::vector<JSBSim::FGFDMExec*>::iterator it = ents.begin();
         it != ents.end(); it++) {
        delete *it;
    }

    return 0;
}


// int main(int argc, char *argv[])
// {
//      if (argc < 2) {
//           cout << "Missing script file" << endl;
//           return -1;
//      }
//
//      //JSBSim::FGPropertyManager *mgr1 = new JSBSim::FGPropertyManager;
//      //JSBSim::FGPropertyManager *mgr2 = new JSBSim::FGPropertyManager;
//      //unsigned int *fdmctr1 = new unsigned int;
//      //unsigned int *fdmctr2 = new unsigned int;
//      //*fdmctr1 = 0;
//      //*fdmctr2 = 0;
//      //
//      //JSBSim::FGFDMExec *FDMExec1 = new JSBSim::FGFDMExec(mgr1,fdmctr1);
//      //JSBSim::FGFDMExec *FDMExec2 = new JSBSim::FGFDMExec(mgr2,fdmctr2);
//
//      JSBSim::FGFDMExec FDMExec1;
//      JSBSim::FGFDMExec FDMExec2;
//
//      FDMExec1.LoadScript(argv[1]);
//      FDMExec2.LoadScript(argv[1]);
//
//      //cout << "========================================" << endl;
//      //std::vector<std::string> fdms = FDMExec1->EnumerateFDMs();
//      //for (std::vector<std::string>::iterator it = fdms.begin(); it != fdms.end(); it++) {
//      //     cout << *it << endl;
//      //}
//      //cout << "========================================" << endl;
//      //return 0;
//
//      //cout << "Output File 1: " << FDMExec1->GetOutputFileName(0) << endl;
//      FDMExec2.SetOutputFileName(0,"BallOut2.csv");
//
//      FDMExec1.RunIC();
//      FDMExec2.RunIC();
//
//      //JSBSim::FGAircraft *aircraft = FDMExec.GetAircraft();
//      //JSBSim::FGPropagate *prop1 = FDMExec1->GetPropagate();
//      //JSBSim::FGPropagate *prop2 = FDMExec2->GetPropagate();
//
//      while (FDMExec1.Run()) {
//           if (!FDMExec2.Run()) break;
//           //while (true) {
//           //if (!FDMExec1->Run()) break;
//           //while (FDMExec.Run()) {
//           //JSBSim::FGPropagate::VehicleState vec = prop->GetVState();
//           //double altitude1 = prop1->GetAltitudeASL();
//           //double altitude2 = prop2->GetAltitudeASL();
//           //cout << "Altitude: " << altitude2 << endl;
//      }
//
//
//
//      //delete FDMExec1;
//      //delete FDMExec2;
//      //delete fdmctr1; // Gets deleted in FGFMDExec's destructor
//      //delete mgr1;    // Gets deleted in FGFMDExec's destructor
//
//
//      return 0;
// }
