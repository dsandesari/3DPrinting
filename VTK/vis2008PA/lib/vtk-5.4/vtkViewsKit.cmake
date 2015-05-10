# Directory containing class headers.
SET(VTK_VIEWS_HEADER_DIR "${VTK_INSTALL_PREFIX}/include/vtk-5.4")

# Classes in vtkViews.
SET(VTK_VIEWS_CLASSES
  "vtkConvertSelectionDomain"
  "vtkDataRepresentation"
  "vtkGraphLayoutView"
  "vtkHierarchicalGraphView"
  "vtkRenderView"
  "vtkSurfaceRepresentation"
  "vtkTreeAreaView"
  "vtkTreeLayoutView"
  "vtkTreeMapView"
  "vtkTreeRingView"
  "vtkIcicleView"
  "vtkView")

# Abstract classes in vtkViews.
SET(VTK_VIEWS_CLASSES_ABSTRACT)

# Wrap-exclude classes in vtkViews.
SET(VTK_VIEWS_CLASSES_WRAP_EXCLUDE)

# Set convenient variables to test each class.
FOREACH(class ${VTK_VIEWS_CLASSES})
  SET(VTK_CLASS_EXISTS_${class} 1)
ENDFOREACH(class)
FOREACH(class ${VTK_VIEWS_CLASSES_ABSTRACT})
  SET(VTK_CLASS_ABSTRACT_${class} 1)
ENDFOREACH(class)
FOREACH(class ${VTK_VIEWS_CLASSES_WRAP_EXCLUDE})
  SET(VTK_CLASS_WRAP_EXCLUDE_${class} 1)
ENDFOREACH(class)
