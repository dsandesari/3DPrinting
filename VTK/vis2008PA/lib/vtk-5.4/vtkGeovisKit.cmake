# Directory containing class headers.
SET(VTK_GEOVIS_HEADER_DIR "${VTK_INSTALL_PREFIX}/include/vtk-5.4")

# Classes in vtkGeovis.
SET(VTK_GEOVIS_CLASSES
  "vtkCompassRepresentation"
  "vtkCompassWidget"
  "vtkGeoAdaptiveArcs"
  "vtkGeoAlignedImageRepresentation"
  "vtkGeoAlignedImageSource"
  "vtkGeoArcs"
  "vtkGeoAssignCoordinates"
  "vtkGeoCamera"
  "vtkGeoEdgeStrategy"
  "vtkGeoFileImageSource"
  "vtkGeoFileTerrainSource"
  "vtkGeoGlobeSource"
  "vtkGeoGraphRepresentation"
  "vtkGeoGraphRepresentation2D"
  "vtkGeoGraticule"
  "vtkGeoImageNode"
  "vtkGeoInteractorStyle"
  "vtkGeoLineRepresentation"
  "vtkGeoMath"
  "vtkGeoProjectionSource"
  "vtkGeoProjection"
  "vtkGeoRandomGraphSource"
  "vtkGeoSampleArcs"
  "vtkGeoSource"
  "vtkGeoTreeNode"
  "vtkGeoTerrain"
  "vtkGeoTerrain2D"
  "vtkGeoTerrainNode"
  "vtkGeoTransform"
  "vtkGeoView"
  "vtkGeoView2D"
  "vtkGlobeSource")

# Abstract classes in vtkGeovis.
SET(VTK_GEOVIS_CLASSES_ABSTRACT
  "vtkGeoSource")

# Wrap-exclude classes in vtkGeovis.
SET(VTK_GEOVIS_CLASSES_WRAP_EXCLUDE)

# Set convenient variables to test each class.
FOREACH(class ${VTK_GEOVIS_CLASSES})
  SET(VTK_CLASS_EXISTS_${class} 1)
ENDFOREACH(class)
FOREACH(class ${VTK_GEOVIS_CLASSES_ABSTRACT})
  SET(VTK_CLASS_ABSTRACT_${class} 1)
ENDFOREACH(class)
FOREACH(class ${VTK_GEOVIS_CLASSES_WRAP_EXCLUDE})
  SET(VTK_CLASS_WRAP_EXCLUDE_${class} 1)
ENDFOREACH(class)
