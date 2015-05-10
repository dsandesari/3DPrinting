/*=========================================================================

  Program:      3460:658 Visualization (Term Project - 3D Printing of Medical Images )
  Instructor:   Dr. Yingcai Xiao 
  Module:       Main.cxx
  Author:	    Deekshith Sandesari
  Student Id:   2951829
  Email:        ds168@zips.uakron.xxedu
  
=========================================================================*/

// This program reads a volume dataset (vtk structured format,Minc image format)
// extracts isosurfaces that represent the skin or bone, 
// and then displays them on vtk render window.
// It also generates the ouput in STL format avilable to 3D printing.

#include <windows.h>
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkPolyDataMapper.h"
#include "vtkActor.h"
#include "vtkProperty.h"
#include "vtkCamera.h"
#include "vtkPolyDataMapper.h"
#include "vtkStripper.h"
#include "vtkPolyDataNormals.h"
#include "vtkContourFilter.h"
#include "vtkStructuredPointsReader.h"
#include "vtkInteractorStyleTrackballCamera.h"
#include "vtkTransform.h"
#include <vtkConeSource.h>
#include <vtkSTLWriter.h>
#include <vtkTransformFilter.h>
#include <string.h>
#include <iostream>
#include <vtkMINCImageReader.h>
#include "vtkInteractorStyleTrackballCamera.h"
#include <vtkObjectFactory.h>
int countour_value=1150;//global countour value


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
      if(key == "d") {//decreases the contour value when "d" is pressed
		countour_value = countour_value - 100;
	    this->ContourFilter->SetValue(0, countour_value);
		
        } 
 
      if(key == "i") {	//increases the contour value when "i" is pressed
		countour_value = countour_value + 100;
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


int main()
{


  double bOpacity=3.0;
  std::string str;

  std::string outputSTLFile = "C:\\Users\\ds168.CS\\Desktop\\brainOut.stl";
  
  cout<<"Enter the type of file (vtk /mnc) you want to analyse to 3D Print :  "<<endl;
  cout<<"Enter vtk if you want to input VTK file"<< endl;
  cout<<"Enter mnc if you want to input MINC file"<<endl;
  abc:
  cin>>str;
  vtkContourFilter *boneExtractor = vtkContourFilter::New();
  vtkActor *skin = vtkActor::New();
  cout<<"Processing.."<<endl;
  if(str=="vtk"){
    // Read the input from vtk file extract he bone and skin contours.

	vtkStructuredPointsReader *vminc = vtkStructuredPointsReader::New();
	vminc->SetFileName("head.vtk");
	boneExtractor->SetInputConnection(vminc->GetOutputPort());
	// Generate contours 
	vtkContourFilter *skinExtractor = vtkContourFilter::New();
    skinExtractor->SetInputConnection(vminc->GetOutputPort());
    skinExtractor->SetValue(0, 500);
     // Mapping contours to an actor
	vtkPolyDataMapper *skinMapper = vtkPolyDataMapper::New();
    skinMapper->SetInputConnection(skinExtractor->GetOutputPort());
	skinMapper->ScalarVisibilityOff();


	
    skin->SetMapper(skinMapper);
    skin->GetProperty()->SetDiffuseColor(1, .49, .25);
    skin->GetProperty()->SetSpecular(.3);
    skin->GetProperty()->SetSpecularPower(20);
	skin->GetProperty()->SetOpacity(0.5);

  
  }
  else if(str=="mnc"){
	 // Read the input from vtk file extract the bone and skin contours.
	 // vtkMINCImageReader reads Minc format files, which are medical images.
	vtkMINCImageReader *vminc=vtkMINCImageReader::New();
	vminc->SetFileName("icbm.mnc");
	// Data Source:the McConnell Brain Imaging Centre (BIC) of the Montreal Neurological Institute
	// McGill University  http://www.bic.mni.mcgill.ca/ServicesAtlases/ICBM152Lin
	boneExtractor->SetInputConnection(vminc->GetOutputPort());
	countour_value=1700;
	// Generate contours 
	vtkContourFilter *skinExtractor = vtkContourFilter::New();
    skinExtractor->SetInputConnection(vminc->GetOutputPort());
    skinExtractor->SetValue(0, 400);
	// Mapping contours to an actor
	vtkPolyDataMapper *skinMapper = vtkPolyDataMapper::New();
    skinMapper->SetInputConnection(skinExtractor->GetOutputPort());
	skinMapper->ScalarVisibilityOff();


	
    skin->SetMapper(skinMapper);
    skin->GetProperty()->SetDiffuseColor(1, .49, .25);
    skin->GetProperty()->SetSpecular(.3);
    skin->GetProperty()->SetSpecularPower(20);
	skin->GetProperty()->SetOpacity(0.5);
	
  }
  else{
	cout<<"Invalid input : Enter mnc / vtk "<<endl;
	
	goto abc;
	return 0 ;
  }
   //setting the default contour value
    boneExtractor->SetValue(0, countour_value);
   
    
    // Mapping contours to an actor 
	vtkPolyDataMapper *boneMapper = vtkPolyDataMapper::New();
	boneMapper->SetInputConnection(boneExtractor->GetOutputPort());
    boneMapper->ScalarVisibilityOff();
	vtkActor *bone = vtkActor::New();
    bone->SetMapper(boneMapper);
    bone->GetProperty()->SetDiffuseColor(1, .45, .25);
	bone->GetProperty()->SetOpacity(bOpacity);


	vtkCamera *aCamera = vtkCamera::New();
    aCamera->SetViewUp (0, -1, 0);
    aCamera->SetPosition (0, 1, 1);
    aCamera->SetFocalPoint (0, 0, 0);
    aCamera->ComputeViewPlaneNormal();

	vtkRenderer *aRenderer = vtkRenderer::New();
	// We create the render window which will show up on the screen. 
    vtkRenderWindow *renWin = vtkRenderWindow::New();
	 // We put our renderer into the render window using AddRenderer
    renWin->AddRenderer(aRenderer);
    renWin->SetSize(940, 480);
    aRenderer->SetBackground(0,0,0);

    KeyPressInteractorStyle *interactorstyle = KeyPressInteractorStyle::New();
	//passes the updated countour value from the key press interactor
    interactorstyle->ContourFilter = boneExtractor;
	interactorstyle->SetCurrentRenderer(aRenderer);

	// The vtkRenderWindowInteractor class watches for the key press event.
    vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
    iren->SetRenderWindow(renWin);
    iren->SetInteractorStyle(interactorstyle);
 
    aRenderer->AddActor(bone);
	aRenderer->AddActor(skin);
    aRenderer->SetActiveCamera(aCamera);
    aRenderer->ResetCamera ();

    // Writing Bone information to STL File: brainout.stl

	vtkSTLWriter *stlWriter = vtkSTLWriter::New();
    // Set bone output filename
	stlWriter->SetFileName(outputSTLFile.c_str());
	stlWriter->SetInputConnection(boneExtractor->GetOutputPort());
	// Writing onto the file
	stlWriter->Write();
	cout<<"STL file written to brainout.STL at location: "<<endl;
	cout<<outputSTLFile<<endl;
	cout<<"Press i to increase contour and d to decrease the contour"<<endl;
	renWin->Render();
	// We intialise vtkRenderWindowInteractor and trigger it by the Start() method 
	iren->Initialize();
    iren->Start(); 
    // All instances in VTK are deleted by using the Delete() method.
    boneExtractor->Delete();
	boneMapper->Delete();
    bone->Delete();
	aRenderer->Delete();
	renWin->Delete();
	interactorstyle->Delete();
    iren->Delete();

    return 0;
}
