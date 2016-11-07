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
#include <vtkImageData.h>
#include <vtkJPEGReader.h>
#include <vtkTextureMapToPlane.h>
#include <vtkTexture.h>
#include <vtkCylinderSource.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkAxesActor.h>
#include <vtkTransform.h>
#include <vtkPlaneSource.h>
#include <vtkCommand.h>
#include <vtkCamera.h>
#include <list>

class vtkTimerCallback2 : public vtkCommand
{
public:
    static vtkTimerCallback2 *New()
        {
            vtkTimerCallback2 *cb = new vtkTimerCallback2;
            cb->TimerCount = 0;
            return cb;
        }

    virtual void Execute(vtkObject *caller, unsigned long eventId,
                         void * vtkNotUsed(callData))
        {
            if (vtkCommand::TimerEvent == eventId)
            {
                ++this->TimerCount;
            }

            double data[3];
            int count = 0;
            for (std::list<vtkSmartPointer<vtkActor> >::iterator it = actors.begin(); it != actors.end(); it++) {
                (*it)->GetPosition(data);
                data[0] += 0.1;
                (*it)->SetPosition(data);

                // Follow the first item
                if (count == 0) {
                    double camera_pos[3];
                    camera_pos[0] = data[0] + 50;
                    camera_pos[1] = data[1] + 50;
                    camera_pos[2] = data[2] + 50;

                    camera->SetPosition(camera_pos);
                    camera->SetFocalPoint(data);
                }
                count++;
            }
            vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::SafeDownCast(caller);
            iren->GetRenderWindow()->Render();
        }

private:
    int TimerCount;
public:
    std::list<vtkSmartPointer<vtkActor> > actors;
    vtkSmartPointer<vtkCamera> camera;
};

int main(int, char *argv[])
{
    //Create a renderer, render window, and interactor
    vtkSmartPointer<vtkRenderer> renderer =
        vtkSmartPointer<vtkRenderer>::New();
    vtkSmartPointer<vtkRenderWindow> renderWindow =
        vtkSmartPointer<vtkRenderWindow>::New();
    renderWindow->AddRenderer(renderer);
    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
        vtkSmartPointer<vtkRenderWindowInteractor>::New();
    renderWindowInteractor->SetRenderWindow(renderWindow);

    int x_max = 10;
    int y_max = 10;
    int z_pos = 2;
    //int z_max = 10;

    std::list< vtkSmartPointer<vtkActor> > actors;
    for (int x = 0; x < x_max; x++) {
        for (int y = 0; y < y_max; y++) {
            //for (int z = 0; z < z_max; z++) {
            /////////////
            // Create a sphere
            vtkSmartPointer<vtkCylinderSource> cylinderSource =
                vtkSmartPointer<vtkCylinderSource>::New();
            cylinderSource->SetCenter(x*2,y*2,z_pos);
            cylinderSource->SetRadius(1);
            cylinderSource->SetHeight(1);
            cylinderSource->SetResolution(10);

            // Create a mapper and actor
            vtkSmartPointer<vtkPolyDataMapper> mapper =
                vtkSmartPointer<vtkPolyDataMapper>::New();
            mapper->SetInputConnection(cylinderSource->GetOutputPort());
            vtkSmartPointer<vtkActor> actor =
                vtkSmartPointer<vtkActor>::New();
            actor->SetMapper(mapper);

            // Add the actor to the scene
            renderer->AddActor(actor);
            actors.push_back(actor);
            //}
        }
    }

    vtkSmartPointer<vtkCamera> camera =
        vtkSmartPointer<vtkCamera>::New();
    camera->SetViewUp(0,0,1);
    camera->SetPosition(0, 0, 20);
    camera->SetFocalPoint(0, 0, 0);

    renderer->SetActiveCamera(camera);

    std::string inputFilename = "/home/syllogismrxs/Downloads/do.jpg";

    // Read the image which will be the texture
    vtkSmartPointer<vtkJPEGReader> jPEGReader =
        vtkSmartPointer<vtkJPEGReader>::New();
    jPEGReader->SetFileName ( inputFilename.c_str() );

    // Create a plane
    double plane_size = 100;
    vtkSmartPointer<vtkPlaneSource> plane =
        vtkSmartPointer<vtkPlaneSource>::New();
    plane->SetCenter(0.0, 0.0, 0.0);
    plane->SetNormal(0.0, 0.0, 1.0);
    plane->SetPoint1(plane_size,0,0);
    plane->SetPoint2(0,plane_size,0);

    // Apply the texture
    vtkSmartPointer<vtkTexture> texture =
        vtkSmartPointer<vtkTexture>::New();
    texture->SetInputConnection(jPEGReader->GetOutputPort());
    //texture->RepeatOn();
    //texture->SetRepeat(100);

    vtkSmartPointer<vtkTextureMapToPlane> texturePlane =
        vtkSmartPointer<vtkTextureMapToPlane>::New();
    texturePlane->SetInputConnection(plane->GetOutputPort());

    vtkSmartPointer<vtkPolyDataMapper> planeMapper =
        vtkSmartPointer<vtkPolyDataMapper>::New();
    planeMapper->SetInputConnection(texturePlane->GetOutputPort());

    vtkSmartPointer<vtkActor> texturedPlane =
        vtkSmartPointer<vtkActor>::New();
    texturedPlane->SetMapper(planeMapper);
    texturedPlane->SetTexture(texture);

    renderer->AddActor(texturedPlane);

    //renderer->SetBackground(.1, .3,.2); // Background color dark green
    renderer->SetBackground(.1, .2, .3); // Background color dark blue

    vtkSmartPointer<vtkAxesActor> axes =
        vtkSmartPointer<vtkAxesActor>::New();

    // The axes are positioned with a user transform
    vtkSmartPointer<vtkTransform> transform =
        vtkSmartPointer<vtkTransform>::New();
    transform->Translate(0, 0.0, 0.0);

    axes->SetUserTransform(transform);

    // properties of the axes labels can be set as follows
    // this sets the x axis label to red
    // axes->GetXAxisCaptionActor2D()->GetCaptionTextProperty()->SetColor(1,0,0);

    // the actual text of the axis label can be changed:
    // axes->SetXAxisLabelText("test");

    renderer->AddActor(axes);

    // Render and interact
    renderWindow->SetWindowName(argv[0]);
    renderWindow->Render();

    // Initialize must be called prior to creating timer events.
    renderWindowInteractor->Initialize();

    // Sign up to receive TimerEvent
    vtkSmartPointer<vtkTimerCallback2> cb =
        vtkSmartPointer<vtkTimerCallback2>::New();

    cb->actors = actors;
    cb->camera = camera;

    renderWindowInteractor->AddObserver(vtkCommand::TimerEvent, cb);

    renderWindowInteractor->CreateRepeatingTimer(10);
    renderWindowInteractor->Start();

    return EXIT_SUCCESS;
}
