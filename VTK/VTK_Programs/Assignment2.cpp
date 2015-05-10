/*=========================================================================

  Program:      3460:658 Visualization (Vtk Assignment 1)
  Instructor:   Dr. Yingcai Xiao 
  Module:       Main.cxx
  Author:	    Deekshith Sandesari
  Student Id:   2951829
  Email:        ds168@zips.uakron.edu
  
=========================================================================*/
//
//	Implementing a VTK program to display UA as 3D shapes and make them "walking".
//	The window is also interactive. The animation of the walk is at the start of the program.
//	My program has at least two different instances of the following: 
//	VTKRender
//	VTKLight
//	VTKCamera
//	VTKActor
//	VTKProperty
//	VTKMapper
//

// First include the required header files for the VTK classes we are using.
#include "vtkSphereSource.h"
#include "vtkPolyDataMapper.h"
#include "vtkRenderWindow.h"
#include "vtkCamera.h"
#include "vtkActor.h"
#include "vtkRenderer.h"
#include "vtkProperty.h"
#include "vtkCubeSource.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkInteractorStyleTrackballCamera.h"
#include "vtklight.h"
#include "vtkTransform.h"


#include "vtkActorCollection.h"

int main()
{
 
 // We create an instance of vtkSphereSource and set its properties
  vtkSphereSource *sphere = vtkSphereSource::New();
  sphere->SetRadius(1);
  sphere->SetThetaResolution(100);

// We create an instance of vtkCubeSource and set its properties
  vtkCubeSource *cube =vtkCubeSource::New();
  cube->SetXLength(1);
  cube->SetYLength(1);
  cube->SetZLength(1);

  // We create an instance of vtkPolyDataMapper to map the polygonal data into graphics primitives.
  // We connect the output of the  source to the input of this mapper.

   vtkPolyDataMapper *sphereMapper = vtkPolyDataMapper::New();
   sphereMapper->SetInputConnection( sphere->GetOutputPort() );

   vtkPolyDataMapper *cubeMapper = vtkPolyDataMapper::New();
   cubeMapper->SetInputConnection( cube->GetOutputPort() );
 

  // Create a property and directly manipulate it. 

  vtkProperty *property = vtkProperty::New();
  property->SetColor(0.2, 0.52, 0.8784); //Blue Color
  property->SetDiffuse(0.7);
  property->SetSpecular(0.4);
  property->SetSpecularPower(20);

  // Create the Renderers and set the background colors.
 
    vtkRenderer *ren1= vtkRenderer::New();//Renderer One
    ren1->SetBackground( 1, 0, 0 );//Red Background
    ren1->SetViewport(0.0, 0.5, 0.5, 1.0);

    vtkRenderer *ren2= vtkRenderer::New();//Renderer Two
    ren2->SetBackground( 0, 1, 0 );//Green Background
    ren2->SetViewport(0.5, 0.5, 1.0, 1.0);

	vtkRenderer *ren3= vtkRenderer::New();//Renderer Three
    ren3->SetBackground( 0.2, 0.3, 0.5);//Blue Background
    ren3->SetViewport(0.0, 0.0, 0.5, 0.5);

    vtkRenderer *ren4= vtkRenderer::New();//Renderer Four
    ren4->SetBackground( 1, 1, 0 );//Yellow Background
    ren4->SetViewport(0.5, 0.0, 1.0, 0.5);

	//Create Actors and assign actors to the renderers.
	//To modify the properties we just modify the existing property.  

	vtkActorCollection *coll=vtkActorCollection::New();//vtkActor Collection to access actors outside.
  // Actors for letter U
    for(int j=0;j<8;j=j+2){

	  vtkActor *sphereActor= vtkActor::New();
      sphereActor->SetMapper(sphereMapper);
      sphereActor->GetProperty()->SetColor(1, 1, 0);
      sphereActor->SetPosition(0, j, 0);
	  ren1->AddActor( sphereActor );
	  ren2->AddActor( sphereActor );
	  ren3->AddActor( sphereActor );
	  ren4->AddActor( sphereActor );
	  coll->AddItem(sphereActor);
	  coll->InitTraversal();
	  sphereActor->Delete();
	  
}
	for(int j=0;j<8;j=j+2){
	
	  vtkActor *sphereActor= vtkActor::New();
      sphereActor->SetMapper(sphereMapper);
	  sphereActor->GetProperty()->SetColor(0.2, 0.52, 0.8784);
      sphereActor->SetPosition(4, j, 0);
	  ren1->AddActor( sphereActor );
	  ren2->AddActor( sphereActor );
	  ren3->AddActor( sphereActor );
	  ren4->AddActor( sphereActor );
	  coll->AddItem(sphereActor);
	  coll->InitTraversal();
	  sphereActor->Delete();
}

	
	for(int i=1.75;i<=3.75;i=i+2){
		

	  vtkActor *sphereActor= vtkActor::New();
      sphereActor->SetMapper(sphereMapper);
	  sphereActor->GetProperty()->SetColor(1, 1, 0);
      sphereActor->SetPosition(i, -1.5, 0);
	  ren1->AddActor( sphereActor );
	  ren2->AddActor( sphereActor );
	  ren3->AddActor( sphereActor );
	  ren4->AddActor( sphereActor );
	  coll->AddItem(sphereActor);
	  coll->InitTraversal();
      sphereActor->Delete();
}
	
	
	// Actors for letter A

	for(float i=6,j=-1.5;j<=8;i=i+1.5,j=j+2){

      vtkActor *sphereActor= vtkActor::New();
      sphereActor->SetMapper(sphereMapper);
	  sphereActor->GetProperty()->SetColor(1, 1, 0);
      sphereActor->SetPosition(i, j, 0);
	  ren1->AddActor( sphereActor );
	  ren2->AddActor( sphereActor );
	  ren3->AddActor( sphereActor );
	  ren4->AddActor( sphereActor );
	  coll->AddItem(sphereActor);
	  coll->InitTraversal();
	  sphereActor->Delete();
}
	for(float i=12,j=6.5;i<=18;i=i+1.5,j=j-2){

	  vtkActor *sphereActor= vtkActor::New();
      sphereActor->SetMapper(sphereMapper);
	  sphereActor->GetProperty()->SetColor(0.2, 0.52, 0.8784);
      sphereActor->SetPosition(i, j, 0);
	  ren1->AddActor( sphereActor );
	  ren2->AddActor( sphereActor );
	  ren3->AddActor( sphereActor );
	  ren4->AddActor( sphereActor );
	  coll->AddItem(sphereActor);
	  coll->InitTraversal();
	  sphereActor->Delete();
	}
	for(float i=9;i<=15;i=i+2){
	  
	  vtkActor *sphereActor= vtkActor::New();
      sphereActor->SetMapper(sphereMapper);
	  sphereActor->GetProperty()->SetColor(1, 1, 0);
      sphereActor->SetPosition(i, 2.5, 0);
	  ren1->AddActor( sphereActor );
	  ren2->AddActor( sphereActor );
	  ren3->AddActor( sphereActor );
	  ren4->AddActor( sphereActor );
	  coll->AddItem(sphereActor);
	  coll->InitTraversal();
	  sphereActor->Delete();
	}
	
 
  //Actors for Cubes
   
   for(int i=-2;i<20;i=i++){
    for(int k=-25;k<5;k++){
	  vtkActor *cubeActorG= vtkActor::New();
      cubeActorG->SetMapper(cubeMapper);
      if((i+k)%2==0){//Condition for alternate Black and white cubes
       cubeActorG->GetProperty()->SetColor(1, 1, 1);
      }  
      else{
	    cubeActorG->GetProperty()->SetColor(0, 0, 0);
	  }
      cubeActorG->SetPosition(i, -3, k);
	  ren1->AddActor( cubeActorG );
	  ren2->AddActor( cubeActorG );
	  ren3->AddActor( cubeActorG );
	  ren4->AddActor( cubeActorG );
	  cubeActorG->Delete();

	}
  }



  // Finally we create the render window which will show up on the screen. 
  vtkRenderWindow *renWin = vtkRenderWindow::New();
  // We put our renderer into the render window using AddRenderer
  renWin->AddRenderer( ren1 );
  renWin->AddRenderer( ren2 );
  renWin->AddRenderer( ren3 );
  renWin->AddRenderer( ren4 );
  // set the size to be 800 pixels by 800.
  renWin->SetSize( 800, 800 );
  ren1->GetActiveCamera()->SetPosition(15,15,-15);
  ren2->GetActiveCamera()->SetPosition(15,15,15);
  ren4->GetActiveCamera()->SetPosition(-15,-5,15);


  //Use of vtk Light to change the color of the actors using light
  vtkLight *vl=vtkLight::New();
  vl->SetLightTypeToCameraLight();
  vl->SetColor(1,1,0);//sheds yellow light on renderer four
  ren4->AddLight(vl);

  vtkLight *vl1=vtkLight::New();
  vl1->SetLightTypeToCameraLight();
  vl1->SetColor(0,1,0);//sheds green light on renderer two
  ren2->AddLight(vl1);
   renWin->Render();

 
  vtkTransform *walk=vtkTransform::New();
	
    //Transform all actors for letters U and A.      
    for(vtkIdType i = 0; i < coll->GetNumberOfItems(); i++)//tranverse for each actor
    {
       vtkActor* act = coll->GetNextActor(); //get each actor
	   walk->Translate(0,0,-1); 
       act->SetUserTransform(walk);  //translates each actor
	   ren1->AddActor(act);
	   ren2->AddActor(act);
	   ren3->AddActor(act);
	   ren4->AddActor(act);
	   ren1->ResetCamera();
	   ren2->ResetCamera();
       ren3->ResetCamera();
	   ren4->ResetCamera();
	   renWin->Render();
     }


   // The vtkRenderWindowInteractor class watches for events.
  vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
  iren->SetRenderWindow(renWin);


  // vtkInteractorStyle translates a set of events operates camera on actors in trackball style.
 
  vtkInteractorStyleTrackballCamera *style = 
  vtkInteractorStyleTrackballCamera::New();
  iren->SetInteractorStyle(style);

  //We intialise vtkRenderWindowInteractor and trigger it by the Start() method 
  iren->Initialize();
  iren->Start();

  // All instances in VTK are deleted by using the Delete() method.

  sphere->Delete();
  sphereMapper->Delete();
  property->Delete();
  ren1->Delete();
  renWin->Delete();
  coll->Delete();

  return 0;
}