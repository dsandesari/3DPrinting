# Directory containing class headers.
SET(VTK_INFOVIS_HEADER_DIR "${VTK_INSTALL_PREFIX}/include/vtk-5.4")

# Classes in vtkInfovis.
SET(VTK_INFOVIS_CLASSES
  "vtkArcParallelEdgeStrategy"
  "vtkAreaLayout"
  "vtkAreaLayoutStrategy"
  "vtkArrayMap"
  "vtkAssignCoordinates"
  "vtkBivariateStatisticsAlgorithm"
  "vtkBoxLayoutStrategy"
  "vtkChacoGraphReader"
  "vtkCircularLayoutStrategy"
  "vtkClustering2DLayoutStrategy"
  "vtkCollapseGraph"
  "vtkCommunity2DLayoutStrategy"
  "vtkConstrained2DLayoutStrategy"
  "vtkContingencyStatistics"
  "vtkCorrelativeStatistics"
  "vtkCosmicTreeLayoutStrategy"
  "vtkDataObjectToTable"
  "vtkDelimitedTextReader"
  "vtkDescriptiveStatistics"
  "vtkEdgeCenters"
  "vtkEdgeLayout"
  "vtkEdgeLayoutStrategy"
  "vtkExtractSelectedGraph"
  "vtkFast2DLayoutStrategy"
  "vtkFixedWidthTextReader"
  "vtkForceDirectedLayoutStrategy"
  "vtkGenerateIndexArray"
  "vtkGraphHierarchicalBundle"
  "vtkGraphLayout"
  "vtkGraphLayoutStrategy"
  "vtkGraphMapper"
  "vtkGraphToPolyData"
  "vtkGroupLeafVertices"
  "vtkISIReader"
  "vtkInteractorStyleAreaSelectHover"
  "vtkInteractorStyleTreeMapHover"
  "vtkLabeledTreeMapDataMapper"
  "vtkMergeColumns"
  "vtkMergeTables"
  "vtkMultiCorrelativeStatistics"
  "vtkMutableGraphHelper"
  "vtkNetworkHierarchy"
  "vtkOrderStatistics"
  "vtkPassThrough"
  "vtkPassThroughEdgeStrategy"
  "vtkPassThroughLayoutStrategy"
  "vtkPerturbCoincidentVertices"
  "vtkPCAStatistics"
  "vtkPruneTreeFilter"
  "vtkRISReader"
  "vtkRandomGraphSource"
  "vtkRandomLayoutStrategy"
  "vtkRemoveIsolatedVertices"
  "vtkSimple2DLayoutStrategy"
  "vtkSliceAndDiceLayoutStrategy"
  "vtkSquarifyLayoutStrategy"
  "vtkStackedTreeLayoutStrategy"
  "vtkStatisticsAlgorithm"
  "vtkStringToCategory"
  "vtkStringToNumeric"
  "vtkTableToGraph"
  "vtkTableToTreeFilter"
  "vtkThresholdTable"
  "vtkTransferAttributes"
  "vtkTreeFieldAggregator"
  "vtkTreeLayoutStrategy"
  "vtkTreeOrbitLayoutStrategy"
  "vtkTreeLevelsFilter"
  "vtkTreeMapLayout"
  "vtkTreeMapLayoutStrategy"
  "vtkTreeMapToPolyData"
  "vtkTreeMapViewer"
  "vtkTreeRingToPolyData"
  "vtkTulipReader"
  "vtkUnivariateStatisticsAlgorithm"
  "vtkVertexDegree"
  "vtkViewTheme"
  "vtkViewUpdater"
  "vtkXMLTreeReader"
  "vtkSQLDatabaseGraphSource"
  "vtkSQLDatabaseTableSource"
  "vtkSQLGraphReader"
  "vtkStringToTimePoint"
  "vtkTimePointToString")

# Abstract classes in vtkInfovis.
SET(VTK_INFOVIS_CLASSES_ABSTRACT
  "vtkAreaLayoutStrategy"
  "vtkBivariateStatisticsAlgorithm"
  "vtkEdgeLayoutStrategy"
  "vtkGraphLayoutStrategy"
  "vtkStatisticsAlgorithm"
  "vtkTreeMapLayoutStrategy"
  "vtkUnivariateStatisticsAlgorithm")

# Wrap-exclude classes in vtkInfovis.
SET(VTK_INFOVIS_CLASSES_WRAP_EXCLUDE)

# Set convenient variables to test each class.
FOREACH(class ${VTK_INFOVIS_CLASSES})
  SET(VTK_CLASS_EXISTS_${class} 1)
ENDFOREACH(class)
FOREACH(class ${VTK_INFOVIS_CLASSES_ABSTRACT})
  SET(VTK_CLASS_ABSTRACT_${class} 1)
ENDFOREACH(class)
FOREACH(class ${VTK_INFOVIS_CLASSES_WRAP_EXCLUDE})
  SET(VTK_CLASS_WRAP_EXCLUDE_${class} 1)
ENDFOREACH(class)
