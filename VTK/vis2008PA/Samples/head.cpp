/*=========================================================================

  Program:   Visualization Toolkit
  Module:    Medical
  Author:    Kalyan Thokala


=========================================================================*/
//
// This example reads a volume dataset, extracts two isosurfaces that
// represent the skin and bone, and then displays them.
//

#include <windows.h>
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkVolume16Reader.h"
#include "vtkPolyDataMapper.h"
#include "vtkActor.h"
#include "vtkProperty.h"
#include "vtkOutlineFilter.h"
#include "vtkCamera.h"
#include "vtkPolyDataMapper.h"
#include "vtkStripper.h"
#include "vtkPolyDataNormals.h"
#include "vtkContourFilter.h"
#include "vtkStructuredPointsReader.h"
#include "vtkInteractorStyleTrackballCamera.h"
#include "vtkCommand.h"
#include "vtkBoxWidget.h"
#include "vtkTransform.h"
#include <vtkContourWidget.h>
#include <vtkOrientedGlyphContourRepresentation.h>
#include <vtkWidgetEvent.h>
#include <vtkWidgetEventTranslator.h>
#include <vtkConeSource.h>

//
// Similar to Cone2.cxx, we define a callback for interaction.
// 
class vtkMyCallback : public vtkCommand
{
public:
  static vtkMyCallback *New() 
    { return new vtkMyCallback; }
  virtual void Execute(vtkObject *caller, unsigned long, void*)
    {
      vtkTransform *t = vtkTransform::New();
      vtkBoxWidget *widget = reinterpret_cast<vtkBoxWidget*>(caller);
      widget->GetTransform(t);
      widget->GetProp3D()->SetUserTransform(t);
      t->Delete();
    }
};



int main()
{

  int choice=0;
  int skinscalarvis=0;

  double sOpacity=0.0;
  double bOpacity=1.0;
  bool Error=true;
  
  choice = 1;
  
  sOpacity = 1.0;
  bOpacity = 0.8;

  vtkRenderer *aRenderer = vtkRenderer::New();
  vtkRenderer *aRenderer2 = vtkRenderer::New();
  vtkRenderer *aRenderer3 = vtkRenderer::New();

  vtkRenderWindow *renWin = vtkRenderWindow::New();
  renWin->AddRenderer(aRenderer);
  renWin->AddRenderer(aRenderer2);
  renWin->AddRenderer(aRenderer3);
  renWin->SetSize(940, 480);


  aRenderer->SetBackground(1,1,1);
  aRenderer->ResetCameraClippingRange ();
  aRenderer->SetViewport(0.0,0.0,0.33,1.0);

  aRenderer2->SetBackground(0,0,0);
  aRenderer2->SetViewport(0.33,0.0,0.66,1.0);

  aRenderer3->SetBackground(0.3,0.3,0.3);
  aRenderer3->SetViewport(0.66,0.0,1.0,1.0);


  vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
  iren->SetRenderWindow(renWin);




	vtkStructuredPointsReader *v16 = vtkStructuredPointsReader::New();

	if(choice==2)
	{
		v16->SetFileName("C:\\Users\\kalyan\\Desktop\\headVisio\\1.vtk");


	}
	else//if(choice==2)
	{
		v16->SetFileName("head.vtk");
	}

	vtkContourFilter *skinExtractor = vtkContourFilter::New();
    skinExtractor->SetInputConnection(v16->GetOutputPort());
    skinExtractor->SetValue(0, 500);
  
	vtkPolyDataNormals *skinNormals = vtkPolyDataNormals::New();
    skinNormals->SetInputConnection(skinExtractor->GetOutputPort());
    skinNormals->SetFeatureAngle(60.0);
	


	vtkStripper *skinStripper = vtkStripper::New();
    skinStripper->SetInputConnection(skinNormals->GetOutputPort());
	


	vtkPolyDataMapper *skinMapper = vtkPolyDataMapper::New();
    skinMapper->SetInputConnection(skinStripper->GetOutputPort());
  


	if(skinscalarvis==0)
	{
	skinMapper->ScalarVisibilityOff();
	}
	else
	{
	skinMapper->ScalarVisibilityOn();
	}


	vtkActor *skin = vtkActor::New();
    skin->SetMapper(skinMapper);
    skin->GetProperty()->SetDiffuseColor(1, .49, .25);
    skin->GetProperty()->SetSpecular(.3);
    skin->GetProperty()->SetSpecularPower(20);
	skin->GetProperty()->SetOpacity(sOpacity);
	

	
	
	vtkContourFilter *boneExtractor = vtkContourFilter::New();
    boneExtractor->SetInputConnection(v16->GetOutputPort());
    boneExtractor->SetValue(0, 1150);

	vtkPolyDataNormals *boneNormals = vtkPolyDataNormals::New();
    boneNormals->SetInputConnection(boneExtractor->GetOutputPort());
    boneNormals->SetFeatureAngle(60.0);

	vtkStripper *boneStripper = vtkStripper::New();
    boneStripper->SetInputConnection(boneNormals->GetOutputPort());
    
	vtkPolyDataMapper *boneMapper = vtkPolyDataMapper::New();
    boneMapper->SetInputConnection(boneStripper->GetOutputPort());
    boneMapper->ScalarVisibilityOff();

	vtkActor *bone = vtkActor::New();
    bone->SetMapper(boneMapper);
    bone->GetProperty()->SetDiffuseColor(1, 1, .9412);
	bone->GetProperty()->SetOpacity(bOpacity);

    vtkOutlineFilter *outlineData = vtkOutlineFilter::New();
    outlineData->SetInputConnection(v16->GetOutputPort());

	vtkPolyDataMapper *mapOutline = vtkPolyDataMapper::New();
    mapOutline->SetInputConnection(outlineData->GetOutputPort());

	vtkActor *outline = vtkActor::New();
    outline->SetMapper(mapOutline);
    outline->GetProperty()->SetColor(0,0,0);




	vtkCamera *aCamera = vtkCamera::New();
    aCamera->SetViewUp (0, 0, -1);
    aCamera->SetPosition (0, 1, 0);
    aCamera->SetFocalPoint (0, 0, 0);
    aCamera->ComputeViewPlaneNormal();

	vtkCamera *aCamera2 = vtkCamera::New();
    aCamera2->SetViewUp (0, -1, 0);
    aCamera2->SetPosition (0, 1, 1);
    aCamera2->SetFocalPoint (0, 0, 0);
    aCamera2->ComputeViewPlaneNormal();

    vtkCamera *aCamera3 = vtkCamera::New();
    aCamera3->SetViewUp (-1, 0, 0);
    aCamera3->SetPosition (0, 1, 1);
    aCamera3->SetFocalPoint (0, 0, 0);
    aCamera3->ComputeViewPlaneNormal();



    vtkConeSource *coneSource = vtkConeSource::New();
	coneSource->SetHeight(30);
	coneSource->SetRadius(10);
	

    vtkPolyDataMapper *map = vtkPolyDataMapper::New();
    map->SetInput(coneSource->GetOutput()); 

    vtkActor *actorCone = vtkActor::New();
    actorCone->SetMapper(map);



	

    //aRenderer->AddActor(outline);
    aRenderer->AddActor(skin);

	aRenderer->AddActor(actorCone);

    aRenderer->SetActiveCamera(aCamera);
    aRenderer->ResetCamera ();
    aCamera->Dolly(1.5);


    aRenderer2->AddActor(bone);
    aRenderer2->SetActiveCamera(aCamera2);
    aRenderer2->ResetCamera ();

	aRenderer3->AddActor(skin);
    aRenderer3->AddActor(bone);
    aRenderer3->SetActiveCamera(aCamera3);
    aRenderer3->ResetCamera ();




    


  vtkInteractorStyleTrackballCamera *style = 
  vtkInteractorStyleTrackballCamera::New();
  iren->SetInteractorStyle(style);


  //vtkPointWidget *pointWidget = vtkPointWidget::New();


  vtkBoxWidget *boxWidget = vtkBoxWidget::New();
  boxWidget->SetInteractor(iren);
  boxWidget->SetPlaceFactor(1.25);
  boxWidget->SetProp3D(actorCone);
  boxWidget->PlaceWidget();

  vtkMyCallback *callback = vtkMyCallback::New();
  boxWidget->AddObserver(vtkCommand::InteractionEvent, callback);
  boxWidget->On();


  ////vtkOrientedGlyphContourRepresentation contourRep = vtkOrientedGlyphContourRepresentation::New();
  //vtkContourWidget contourWidget = vtkContourWidget::New();
  //contourWidget->SetInteractor(iren);
  ////contourWidget->SetRepresentation(contourRep);
  //contourWidget->On();
  //contourWidget->Initialize(skinStripper->GetOutputPort());
  //contourWidget->Render();

    
	
	iren->Initialize();
    iren->Start(); 

  for(int i=0;i<100;i++)
  {
	  skin->RotateY(1);
	  
	  aRenderer3->Render();
  }










	v16->Delete();
    skinExtractor->Delete();
    skinNormals->Delete();
    skinStripper->Delete();
    skinMapper->Delete();
    skin->Delete();
    boneExtractor->Delete();
    boneNormals->Delete();
    boneStripper->Delete();
    boneMapper->Delete();
    bone->Delete();
    outlineData->Delete();
    mapOutline->Delete();
    outline->Delete();
    aCamera->Delete();

    aRenderer->Delete();
	aRenderer2->Delete();

    renWin->Delete();
    iren->Delete();

    return 0;
}
