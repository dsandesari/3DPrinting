/*=========================================================================

  Program:      3460:658 Visualization (Vtk Assignment 3)
  Instructor:   Dr. Yingcai Xiao 
  Module:       Main.cxx
  Author:	    Deekshith Sandesari
  Student Id:   2951829
  Email:        ds168@zips.uakron.xxedu
  
=========================================================================*/

//Step 1. Modeling.

//Used the Shepard’s method (with alpha index = 2) to interpolate the scattered data 
//from file name:scaled_scattered_data.txt into a uniform grid 
//and then output it into a text file :newFile.vtk// . 
//Allow the user to specify the dimensions of the grid at the start of your program. 

//Step 2. Rendering.

// Read the above grid data from newFile.vtk.Created and displayed isosurfaces using a contour filter.  
//Allowed the user to use the “i” key to increase the contour value and the “d” key to decrease the contour value.  
//In a separate viewport, display the operation instructions.



// First include the required header files for the VTK classes we are using.

#include "vtkTextActor.h"
#include "vtkTextProperty.h"
#include "vtkPolyDataMapper.h"
#include "vtkContourFilter.h"
#include "vtkActor.h"
#include "vtkCamera.h"
#include "vtkFloatArray.h"
#include "vtkMath.h"
#include "vtkPoints.h"
#include "vtkPolyDataMapper.h"
#include "vtkProperty.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkRenderer.h"
#include "vtkStructuredGrid.h"
#include "vtkInteractorStyleTrackballCamera.h"
#include "vtkStructuredPointsReader.h"
#include <string>
#include <sstream>
#include <Math.h>
#include "vtkOutlineFilter.h"
#include <vtkObjectFactory.h>

double countour_value=0.01;//global countour value


//*Key Press Interactor*//
class KeyPressInteractorStyle : public vtkInteractorStyleTrackballCamera
{
  public:
    static KeyPressInteractorStyle* New();
    vtkTypeMacro(KeyPressInteractorStyle, vtkInteractorStyleTrackballCamera);
 
	virtual void OnKeyPress()     
    {
      // Get the keypress
      vtkRenderWindowInteractor *rwi = this->Interactor;
      std::string key = rwi->GetKeySym();
      if(key == "d") {//decreases the contour value
		countour_value = countour_value - 0.01;
	    this->ContourFilter->SetValue(0, countour_value);
		
        } 
 
      if(key == "i") {	//increases the contour value
		countour_value = countour_value + 0.01;
		this->ContourFilter->SetValue(0, countour_value);
        }
	    cout<< "countour_value: " << countour_value<<endl;
		//renders the window when key is pressed
        rwi->GetRenderWindow()->Render();
 
      // Forward events
      vtkInteractorStyleTrackballCamera::OnKeyPress();
	  
    }

	KeyPressInteractorStyle():ContourFilter(NULL) {}
	vtkContourFilter* ContourFilter;
 
};
vtkStandardNewMacro(KeyPressInteractorStyle);


 
//*Implementation of shepeard Method*//
  double Shepeard_method(double dx, double dy, double dz, double x_arr[], double y_arr[], double z_arr[], double v_arr[])
  {

	   double numerator = 0,denominator = 0;
	     double  dist=0;

	  for (int l=0; l<=137;l++) 

	  {
		 
		  dist= pow( (dx - x_arr[l]),2) + pow( (dy - y_arr[l]),2) + pow((dz - v_arr[l]),2);
		  numerator += v_arr[l]/dist;
		  denominator += 1/dist;

	  }
	
	  return numerator/denominator;

  }

int main()
{

	//**Reading the data from file**//


	std::string line;
  ifstream myfile ("scaled_scattered_data.txt");//input file
   double x_arr[138],y_arr[138],z_arr[138],v_arr[138];
   int i=0;
  
  if (myfile.is_open())
  {

    while (getline (myfile,line))
    {
    double x = 0,y = 0,z = 0,v = 0;
    std::stringstream linestream; 
    linestream << line;
    linestream >> x >> y >> z>> v;
	x_arr[i] = x;
	y_arr[i] = y;
	z_arr[i] = z;
	v_arr[i] = v;
	i++;
	}
   }
  else{
   cout<<"Unable to open the file"<<endl;
  }
    myfile.close();
 
	
	double dims[3]={50,50,50}, di = 0, dj = 0, dk = 0;
	cout<<"Enter the dimensions \n"; 
		cout<<"Enter Dimension X: ";
		cin>>dims[0];
		cout<<"Enter Dimension Y: ";
		cin>>dims[1];
		cout<<"Enter Dimension Z: ";
		cin>>dims[2];
 
  di = 1/dims[0];
  dj = 1/dims[1];
  dk = 1/dims[2];
  //**Performing interpolation using shepeard Method**//
  double dx = 0, dy = 0, dz = 0, f_value = 0;
  int point_data = dims[0] * dims[1] * dims[2];
  double* interpolated_values = new double[point_data]();
  int count=0;
 for (int i = 0; i < dims[0];i++)
  {
	  for (int j = 0; j < dims[1];j++)
		{
			for (int k = 0; k < dims[2];k++)
			 {
				 dx = i * di;
				 dy = j * dj;
				 dz = k * dk;
				 interpolated_values[count++] = Shepeard_method(dx, dy, dz, x_arr, y_arr, z_arr, v_arr);
				 
			 }	  
		}	  
  }

 //Copying the interpolated values to strutured file.

  ofstream newFile;
  newFile.open("newFile.vtk");
  newFile << "# vtk DataFile Version 3.0" << endl;
  newFile << "vtk output" << endl;
  newFile << "ASCII" << endl;
  newFile << "DATASET STRUCTURED_POINTS" << endl;
  newFile << "DIMENSIONS " << dims[0] << " " << dims[1]<< " " <<dims[2] <<endl;
  newFile << "SPACING " << di<<" "<< dj << " "<< dk<< endl;
  newFile << "ORIGIN 0 0 0" << endl;
  newFile << "POINT_DATA " << count <<endl;
  newFile << "SCALARS scalars float" << endl;
  newFile << "LOOKUP_TABLE default" << endl;
 
  for (int val =0;val < count; val++)  {
   newFile<< interpolated_values[val]<< endl;
  }

  newFile.close();

  //Rendering//

  //*Reading the contents from structured file and displaying he contours**//


   	vtkStructuredPointsReader *inFile = vtkStructuredPointsReader::New();
	 inFile->SetFileName("newFile.vtk");
	 vtkContourFilter *c= vtkContourFilter::New();
	 c->SetInputConnection(inFile->GetOutputPort());
	 c->SetValue(0,countour_value);
		
		vtkPolyDataMapper *m= vtkPolyDataMapper::New();
		m->SetInputConnection(c->GetOutputPort());
		vtkActor *myact=vtkActor::New();
		myact->SetMapper(m);
		myact->GetProperty()->SetDiffuseColor(1, .8, .9);
		myact->GetProperty()->SetSpecular(.8);
		myact->GetProperty()->SetSpecularPower(200);

  
	//vtk outline to view the outline of the dataset.	
    vtkOutlineFilter *outlineData = vtkOutlineFilter::New();
    outlineData->SetInputConnection(inFile->GetOutputPort());

	vtkPolyDataMapper *mapOutline = vtkPolyDataMapper::New();
    mapOutline->SetInputConnection(outlineData->GetOutputPort());

	vtkActor *outline = vtkActor::New();
    outline->SetMapper(mapOutline);
    outline->GetProperty()->SetColor(0.5,0.8,1);

	  
	// Create the usual rendering stuff
	vtkRenderer *renderer = vtkRenderer::New();
	//Instructions to display on the screen.
	vtkTextActor *t_header=vtkTextActor::New();
		t_header->SetInput ( "\t \t SCATTERED DATA VISUALIZATION \n \n  1. Press ""i"" on keyboard to increase the counter value \n  2. Press ""d"" on keyboard to decrease the counter value "); 
		t_header->SetDisplayPosition(100,400);
		t_header->GetTextProperty()->SetColor(0,0,1);
		
	vtkRenderer *instruction_ren= vtkRenderer::New();
	 instruction_ren->SetBackground( 1, 1, 1 );
	 instruction_ren->SetViewport(0.0,0.8,1.0,1.0);
	 instruction_ren->AddActor(t_header);

    vtkCamera *aCamera = vtkCamera::New();
	aCamera->SetViewUp (1, 0, 0);
	aCamera->SetPosition (0.5, 4, 3);
	renderer->ResetCamera ();
	renderer->AddActor(myact);
	renderer->AddActor(outline);
	renderer->SetBackground(1,1,1);
	renderer->SetViewport(0.0,0.0,1.00,0.8);
	renderer->SetActiveCamera(aCamera);

	vtkRenderWindow *renWin = vtkRenderWindow::New();
	 renWin->AddRenderer(renderer);
	 renWin->AddRenderer(instruction_ren);
	
	// Key press interactor which sets the counter value each time we call it. 
	
	KeyPressInteractorStyle *interactorstyle = KeyPressInteractorStyle::New();
    interactorstyle->ContourFilter = c;//Sets the updated countour value.
	interactorstyle->SetCurrentRenderer(renderer);

	vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
    iren->SetRenderWindow(renWin);
    iren->SetInteractorStyle(interactorstyle);
	renWin->SetSize(500,500);
	renWin->Render();
	iren->Start();
	
	
     // All instances in VTK are deleted by using the Delete() method.
	

     renWin->Delete();
	 renderer->Delete();
	 myact->Delete();
	 mapOutline->Delete();
	 m->Delete();
	 c->Delete();
	 outline->Delete();
	 iren->Delete();
	 interactorstyle->Delete();
	 aCamera->Delete();


      return 0;
}