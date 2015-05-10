/*=========================================================================

  Program:      3460:658 Visualization (Vtk Assignment 2)
  Instructor:   Dr. Yingcai Xiao 
  Module:       Main.cxx
  Author:	    Deekshith Sandesari
  Student Id:   2951829
  Email:        ds168@zips.uakron.edu
  
=========================================================================*/
//
//	 Implementing a program to visualize a uniform grid. 
//   Window has four views displaying the following:
//	 Isosurfaces 
//   Cutting planes
//   Contour lines 
//   Brief documentation explaining techniques used to create the visualization.
//



// First include the required header files for the VTK classes we are using.


#include "vtkRenderWindow.h"
#include "vtkStructuredPointsSource.h"
#include "vtkRenderer.h"
#include "vtkSphereSource.h"
#include "vtkProperty.h"
#include "vtkCamera.h"
#include "vtkTextActor.h"
#include "vtkPolyDataMapper.h"
#include "vtkQuadric.h"
#include "vtkSampleFunction.h"
#include "vtkContourFilter.h"
#include "vtkLookupTable.h"
#include "vtkActor.h"
#include "vtkPlane.h"
#include "vtkCutter.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkInteractorStyleTrackballCamera.h"
#include "vtkTextActor.h"
#include "vtkTextProperty.h"
int main()
{

	//**ISO SURFACES**//

	//// Use an implicit funtion to generate the data source
	//// Generate contours from the datasource
	//// Display by mapping to an actor with colors using Lookuptable
 
		// Create an implicit function (continuous)
		vtkQuadric *q = vtkQuadric::New();
		q->SetCoefficients(1,1,1,0,0,0,-.8,-.8,-.8,-0.05);

		//Create a sample filter (discrete)
		vtkSampleFunction *s = vtkSampleFunction::New();
		s->SetImplicitFunction(q);
		s->SetSampleDimensions(50,50,50); // uniform grid

		//Create a contour filter object using sample function
		vtkContourFilter *c= vtkContourFilter::New();
		c->SetInputConnection(s->GetOutputPort());
		c->GenerateValues(5,-0.2,1);

		vtkPolyDataMapper *m= vtkPolyDataMapper::New();
		m->SetInputConnection(c->GetOutputPort());
		m->SetScalarRange(0,1);
		//Mapping contours to an actor
		vtkActor *myact=vtkActor::New();
		myact->SetMapper(m);
	
		//Set attributes for color using lookuptable to get dicrete color values.
		vtkLookupTable *lut = vtkLookupTable::New();
		lut->SetHueRange(0.667, 0); //value range [0, 2* П]
		lut->SetSaturationRange(1,1); 
		lut->SetValueRange(1,1); 
		lut->SetAlphaRange(1,1);
		lut->SetNumberOfColors(250);
		lut->Build();
		m->SetLookupTable(lut);
	
	
	//**CUTTING PLANES**//

	
	//// The cutter uses an implicit function to perform the cutting.
	//// Here we define a plane, specifying its center and normal.
	//// Then we assign the plane to the cutter.
	
 
		// Define a plane
		vtkPlane *plane = vtkPlane::New();
		// Set Normal and Origin
		plane->SetOrigin(0,0,0);
		plane->SetNormal(5,4,5);
 
		// Use cutter to interpolate source data onto the plane 
		vtkCutter *planeCut =vtkCutter::New();
		// Use of implicit function to perform the cutting.
		planeCut->SetCutFunction(plane);
		planeCut->SetInputConnection(s->GetOutputPort());
		// Generate multiple planes
		planeCut->GenerateValues(10, 0, 9);
		planeCut->Update();
 

		// Assigning same color values to the mapper using the same lookuptable
	    vtkPolyDataMapper *cutMapper = vtkPolyDataMapper::New();
        cutMapper->SetInputConnection(planeCut->GetOutputPort());
		cutMapper->SetLookupTable(lut);
		// Mapping cutters to an actor
	    vtkActor *cutActor = vtkActor::New();
        cutActor->SetMapper(cutMapper);
	



	//**CONTOUR LINES**//

	//// The cutter uses an implicit function to perform the cutting.
	//// Here we define a plane, specifying its center and normal.
	//// Then we assign the plane to the cutter.

		// Define a plane
		vtkPlane *lplane = vtkPlane::New();
		// Set Normal and Origin
	    lplane->SetOrigin(0,0,0);
	    lplane->SetNormal(-2,-5,10);
		// Use cutter to interpolate source data onto the plane 
		vtkCutter *singleplane =vtkCutter::New();
		// Use of implicit function to perform the cutting.
		singleplane->SetCutFunction(lplane);
		singleplane->SetInputConnection(s->GetOutputPort());
		// Generate single plane
		singleplane->GenerateValues(1, -0.5, -0.5);
		// Generate contours from the single plane
		vtkContourFilter *cf= vtkContourFilter::New();
		cf->SetInputConnection(singleplane->GetOutputPort());
		cf->GenerateValues(10,0,4);
		// Mapping contours to an actor
		vtkPolyDataMapper *mk= vtkPolyDataMapper::New();
		mk->SetInputConnection(cf->GetOutputPort());
		mk->SetScalarRange(0,5);
		vtkActor *myactr=vtkActor::New();
		myactr->SetMapper(mk);
	
		// Setup the text and add it to the window
		vtkTextProperty *vp = vtkTextProperty::New();
		vp->BoldOn();
		vp->SetFontFamilyToArial();
		vtkTextActor *textActor1 = vtkTextActor::New();
		textActor1->SetInput ( "1. ISO SURFACES" );
		textActor1->SetTextProperty(vp);
		vtkTextActor *textActor2 = vtkTextActor::New();
		textActor2->SetInput ( "2. CUTTING PLANES" );
		textActor2->SetTextProperty(vp);
		vtkTextActor *textActor3 = vtkTextActor::New();
		textActor3->SetInput ( "3. CONTOUR LINES" );
		textActor3->SetTextProperty(vp);
	



 
	// Finally we create the render window which will show up on the screen. 

		vtkRenderer *ren1= vtkRenderer::New();
	    ren1->SetBackground( 1, 0.2, 0.2 );
	    ren1->SetViewport(0.0,0.5,0.33,1.0);
	    ren1->AddActor(myact);
		ren1->AddActor2D ( textActor1 );

		vtkRenderer *ren2= vtkRenderer::New();
		ren2->AddActor(cutActor);
		ren2->SetBackground(0.2,0.8,0.2);
		ren2->SetViewport(0.33,0.5,0.66,1.0);
		ren2->AddActor2D ( textActor2 );
	
	    vtkRenderer *ren3= vtkRenderer::New();
	    ren3->SetBackground(0.2,0.2,0.8);
		ren3->SetViewport(0.66,0.5,1.0,1.0);
	  	ren3->AddActor(myactr);
		ren3->AddActor2D ( textActor3 );
		

		vtkTextActor *t_header=vtkTextActor::New();
		t_header->SetInput ( "VISUALIZATION ASSIGNMENT # 2 " );
		t_header->SetDisplayPosition(600,230);
		t_header->GetTextProperty()->SetColor(1,0,1);
		vtkTextActor *t_text1=vtkTextActor::New();
		t_text1->SetInput ( "1. ISO SURFACES \n \n \t Used an implicit function to generate the data source.Created a contour filter object using sample function. \n  \t Displayed Iso surfaces by mapping contours to an actor with colours using Look up table. \n \n 2. CUTTING PLANES \n \n \t  Defined a plane, specifying its center and normal.Used cutter to interpolate source data onto the plane .\n \t Used implicit function to perform the cutting.Generated multiple planes. Mapped contours to an actor. \n \n 3.CONTOUR LINES \n \n \t  Defined a plane, specifying its center and normal.Used cutter to interpolate source data onto the plane .\n \t Used implicit function to perform the cutting.Generated single plane. Mapped contours to an actor." );
		t_text1->SetDisplayPosition(300,20);
		t_text1->GetTextProperty()->SetColor(1,0,0);
	
	    vtkRenderer *ren4= vtkRenderer::New();
		ren4->SetBackground(1,1,1);
	    ren4->SetViewport(0.0,0.0,1.0,0.5);
	  	ren4->AddActor(t_header);
		ren4->AddActor(t_text1);
	
	
 

	// Finally we create the render window which will show up on the screen. 
	 vtkRenderWindow *renWin = vtkRenderWindow::New();
	 // We put our renderer into the render window using AddRenderer
	 renWin->AddRenderer(ren1);
	 renWin->AddRenderer(ren2);
	 renWin->AddRenderer(ren3);
	 renWin->AddRenderer(ren4);
	 renWin->SetSize( 1500, 500 );
    

    // The vtkRenderWindowInteractor class watches for events.
	 vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
     iren->SetRenderWindow(renWin);
     renWin->Render();


     // vtkInteractorStyle translates a set of events operates camera on actors in trackball style.
 
	 vtkInteractorStyleTrackballCamera *style = 
	 vtkInteractorStyleTrackballCamera::New();
	 iren->SetInteractorStyle(style);

     // We intialise vtkRenderWindowInteractor and trigger it by the Start() method 
	 iren->Initialize();
	 iren->Start();

     // All instances in VTK are deleted by using the Delete() method.
	 planeCut->Delete();
	 lplane->Delete();
	 cutActor->Delete();
	 myactr->Delete();
	 myact->Delete();
	 textActor1->Delete();
	 textActor2->Delete();
	 textActor3->Delete();
	 t_text1->Delete();
	 t_header->Delete();

     renWin->Delete();



      return 0;
}