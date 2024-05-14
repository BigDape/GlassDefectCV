/***********************************************************
 * File generated by the HALCON-Compiler hcomp version 22.05
 * Usage: Interface to C++
 *
 * Software by: MVTec Software GmbH, www.mvtec.com
 ***********************************************************/


#ifndef HCPP_HDEFORMABLEMODEL
#define HCPP_HDEFORMABLEMODEL

namespace HalconCpp
{

// Represents an instance of a deformable model for matching.
class LIntExport HDeformableModel : public HHandle
{

public:

  // Create an uninitialized instance
  HDeformableModel():HHandle() {}

  // Copy constructor
  HDeformableModel(const HDeformableModel& source) : HHandle(source) {}

  // Copy constructor
  HDeformableModel(const HHandle& handle);

  // Create HDeformableModel from handle, taking ownership
  explicit HDeformableModel(Hlong handle);

  bool operator==(const HHandle& obj) const
  {
    return HHandleBase::operator==(obj);
  }

  bool operator!=(const HHandle& obj) const
  {
    return HHandleBase::operator!=(obj);
  }

protected:

  // Verify matching semantic type ('deformable_model')!
  virtual void AssertType(Hphandle handle) const;

public:

  // Deep copy of all data represented by this object instance
  HDeformableModel Clone() const;



/*****************************************************************************
 * Operator-based class constructors
 *****************************************************************************/

  // read_deformable_model: Read a deformable model from a file.
  explicit HDeformableModel(const HString& FileName);

  // read_deformable_model: Read a deformable model from a file.
  explicit HDeformableModel(const char* FileName);

#ifdef _WIN32
  // read_deformable_model: Read a deformable model from a file.
  explicit HDeformableModel(const wchar_t* FileName);
#endif

  // create_planar_calib_deformable_model_xld: Prepare a deformable model for planar calibrated matching from XLD contours.
  explicit HDeformableModel(const HXLDCont& Contours, const HCamPar& CamParam, const HPose& ReferencePose, const HTuple& NumLevels, const HTuple& AngleStart, const HTuple& AngleExtent, const HTuple& AngleStep, double ScaleRMin, const HTuple& ScaleRMax, const HTuple& ScaleRStep, double ScaleCMin, const HTuple& ScaleCMax, const HTuple& ScaleCStep, const HTuple& Optimization, const HString& Metric, Hlong MinContrast, const HTuple& GenParamName, const HTuple& GenParamValue);

  // create_planar_calib_deformable_model_xld: Prepare a deformable model for planar calibrated matching from XLD contours.
  explicit HDeformableModel(const HXLDCont& Contours, const HCamPar& CamParam, const HPose& ReferencePose, Hlong NumLevels, const HTuple& AngleStart, const HTuple& AngleExtent, double AngleStep, double ScaleRMin, const HTuple& ScaleRMax, double ScaleRStep, double ScaleCMin, const HTuple& ScaleCMax, double ScaleCStep, const HString& Optimization, const HString& Metric, Hlong MinContrast, const HTuple& GenParamName, const HTuple& GenParamValue);

  // create_planar_calib_deformable_model_xld: Prepare a deformable model for planar calibrated matching from XLD contours.
  explicit HDeformableModel(const HXLDCont& Contours, const HCamPar& CamParam, const HPose& ReferencePose, Hlong NumLevels, const HTuple& AngleStart, const HTuple& AngleExtent, double AngleStep, double ScaleRMin, const HTuple& ScaleRMax, double ScaleRStep, double ScaleCMin, const HTuple& ScaleCMax, double ScaleCStep, const char* Optimization, const char* Metric, Hlong MinContrast, const HTuple& GenParamName, const HTuple& GenParamValue);

#ifdef _WIN32
  // create_planar_calib_deformable_model_xld: Prepare a deformable model for planar calibrated matching from XLD contours.
  explicit HDeformableModel(const HXLDCont& Contours, const HCamPar& CamParam, const HPose& ReferencePose, Hlong NumLevels, const HTuple& AngleStart, const HTuple& AngleExtent, double AngleStep, double ScaleRMin, const HTuple& ScaleRMax, double ScaleRStep, double ScaleCMin, const HTuple& ScaleCMax, double ScaleCStep, const wchar_t* Optimization, const wchar_t* Metric, Hlong MinContrast, const HTuple& GenParamName, const HTuple& GenParamValue);
#endif

  // create_planar_uncalib_deformable_model_xld: Prepare a deformable model for planar uncalibrated matching from XLD contours.
  explicit HDeformableModel(const HXLDCont& Contours, const HTuple& NumLevels, const HTuple& AngleStart, const HTuple& AngleExtent, const HTuple& AngleStep, double ScaleRMin, const HTuple& ScaleRMax, const HTuple& ScaleRStep, double ScaleCMin, const HTuple& ScaleCMax, const HTuple& ScaleCStep, const HTuple& Optimization, const HString& Metric, Hlong MinContrast, const HTuple& GenParamName, const HTuple& GenParamValue);

  // create_planar_uncalib_deformable_model_xld: Prepare a deformable model for planar uncalibrated matching from XLD contours.
  explicit HDeformableModel(const HXLDCont& Contours, Hlong NumLevels, const HTuple& AngleStart, const HTuple& AngleExtent, double AngleStep, double ScaleRMin, const HTuple& ScaleRMax, double ScaleRStep, double ScaleCMin, const HTuple& ScaleCMax, double ScaleCStep, const HString& Optimization, const HString& Metric, Hlong MinContrast, const HTuple& GenParamName, const HTuple& GenParamValue);

  // create_planar_uncalib_deformable_model_xld: Prepare a deformable model for planar uncalibrated matching from XLD contours.
  explicit HDeformableModel(const HXLDCont& Contours, Hlong NumLevels, const HTuple& AngleStart, const HTuple& AngleExtent, double AngleStep, double ScaleRMin, const HTuple& ScaleRMax, double ScaleRStep, double ScaleCMin, const HTuple& ScaleCMax, double ScaleCStep, const char* Optimization, const char* Metric, Hlong MinContrast, const HTuple& GenParamName, const HTuple& GenParamValue);

#ifdef _WIN32
  // create_planar_uncalib_deformable_model_xld: Prepare a deformable model for planar uncalibrated matching from XLD contours.
  explicit HDeformableModel(const HXLDCont& Contours, Hlong NumLevels, const HTuple& AngleStart, const HTuple& AngleExtent, double AngleStep, double ScaleRMin, const HTuple& ScaleRMax, double ScaleRStep, double ScaleCMin, const HTuple& ScaleCMax, double ScaleCStep, const wchar_t* Optimization, const wchar_t* Metric, Hlong MinContrast, const HTuple& GenParamName, const HTuple& GenParamValue);
#endif

  // create_planar_calib_deformable_model: Create a deformable model for calibrated perspective matching.
  explicit HDeformableModel(const HImage& Template, const HCamPar& CamParam, const HPose& ReferencePose, const HTuple& NumLevels, const HTuple& AngleStart, const HTuple& AngleExtent, const HTuple& AngleStep, double ScaleRMin, const HTuple& ScaleRMax, const HTuple& ScaleRStep, double ScaleCMin, const HTuple& ScaleCMax, const HTuple& ScaleCStep, const HTuple& Optimization, const HString& Metric, const HTuple& Contrast, const HTuple& MinContrast, const HTuple& GenParamName, const HTuple& GenParamValue);

  // create_planar_calib_deformable_model: Create a deformable model for calibrated perspective matching.
  explicit HDeformableModel(const HImage& Template, const HCamPar& CamParam, const HPose& ReferencePose, Hlong NumLevels, const HTuple& AngleStart, const HTuple& AngleExtent, double AngleStep, double ScaleRMin, const HTuple& ScaleRMax, double ScaleRStep, double ScaleCMin, const HTuple& ScaleCMax, double ScaleCStep, const HString& Optimization, const HString& Metric, const HTuple& Contrast, Hlong MinContrast, const HTuple& GenParamName, const HTuple& GenParamValue);

  // create_planar_calib_deformable_model: Create a deformable model for calibrated perspective matching.
  explicit HDeformableModel(const HImage& Template, const HCamPar& CamParam, const HPose& ReferencePose, Hlong NumLevels, const HTuple& AngleStart, const HTuple& AngleExtent, double AngleStep, double ScaleRMin, const HTuple& ScaleRMax, double ScaleRStep, double ScaleCMin, const HTuple& ScaleCMax, double ScaleCStep, const char* Optimization, const char* Metric, const HTuple& Contrast, Hlong MinContrast, const HTuple& GenParamName, const HTuple& GenParamValue);

#ifdef _WIN32
  // create_planar_calib_deformable_model: Create a deformable model for calibrated perspective matching.
  explicit HDeformableModel(const HImage& Template, const HCamPar& CamParam, const HPose& ReferencePose, Hlong NumLevels, const HTuple& AngleStart, const HTuple& AngleExtent, double AngleStep, double ScaleRMin, const HTuple& ScaleRMax, double ScaleRStep, double ScaleCMin, const HTuple& ScaleCMax, double ScaleCStep, const wchar_t* Optimization, const wchar_t* Metric, const HTuple& Contrast, Hlong MinContrast, const HTuple& GenParamName, const HTuple& GenParamValue);
#endif

  // create_planar_uncalib_deformable_model: Creates a deformable model for uncalibrated, perspective matching.
  explicit HDeformableModel(const HImage& Template, const HTuple& NumLevels, const HTuple& AngleStart, const HTuple& AngleExtent, const HTuple& AngleStep, double ScaleRMin, const HTuple& ScaleRMax, const HTuple& ScaleRStep, double ScaleCMin, const HTuple& ScaleCMax, const HTuple& ScaleCStep, const HTuple& Optimization, const HString& Metric, const HTuple& Contrast, const HTuple& MinContrast, const HTuple& GenParamName, const HTuple& GenParamValue);

  // create_planar_uncalib_deformable_model: Creates a deformable model for uncalibrated, perspective matching.
  explicit HDeformableModel(const HImage& Template, Hlong NumLevels, const HTuple& AngleStart, const HTuple& AngleExtent, double AngleStep, double ScaleRMin, const HTuple& ScaleRMax, double ScaleRStep, double ScaleCMin, const HTuple& ScaleCMax, double ScaleCStep, const HString& Optimization, const HString& Metric, const HTuple& Contrast, Hlong MinContrast, const HTuple& GenParamName, const HTuple& GenParamValue);

  // create_planar_uncalib_deformable_model: Creates a deformable model for uncalibrated, perspective matching.
  explicit HDeformableModel(const HImage& Template, Hlong NumLevels, const HTuple& AngleStart, const HTuple& AngleExtent, double AngleStep, double ScaleRMin, const HTuple& ScaleRMax, double ScaleRStep, double ScaleCMin, const HTuple& ScaleCMax, double ScaleCStep, const char* Optimization, const char* Metric, const HTuple& Contrast, Hlong MinContrast, const HTuple& GenParamName, const HTuple& GenParamValue);

#ifdef _WIN32
  // create_planar_uncalib_deformable_model: Creates a deformable model for uncalibrated, perspective matching.
  explicit HDeformableModel(const HImage& Template, Hlong NumLevels, const HTuple& AngleStart, const HTuple& AngleExtent, double AngleStep, double ScaleRMin, const HTuple& ScaleRMax, double ScaleRStep, double ScaleCMin, const HTuple& ScaleCMax, double ScaleCStep, const wchar_t* Optimization, const wchar_t* Metric, const HTuple& Contrast, Hlong MinContrast, const HTuple& GenParamName, const HTuple& GenParamValue);
#endif




  /***************************************************************************
   * Operators                                                               *
   ***************************************************************************/

  // Return the origin (reference point) of a deformable model.
  void GetDeformableModelOrigin(double* Row, double* Column) const;

  // Set the origin (reference point) of a deformable model.
  void SetDeformableModelOrigin(double Row, double Column) const;

  // Set selected parameters of the deformable model.
  void SetDeformableModelParam(const HTuple& GenParamName, const HTuple& GenParamValue) const;

  // Return the parameters of a deformable model.
  HTuple GetDeformableModelParams(const HTuple& GenParamName) const;

  // Return the parameters of a deformable model.
  HTuple GetDeformableModelParams(const HString& GenParamName) const;

  // Return the parameters of a deformable model.
  HTuple GetDeformableModelParams(const char* GenParamName) const;

#ifdef _WIN32
  // Return the parameters of a deformable model.
  HTuple GetDeformableModelParams(const wchar_t* GenParamName) const;
#endif

  // Return the contour representation of a deformable model.
  HXLDCont GetDeformableModelContours(Hlong Level) const;

  // Deserialize a deformable model.
  void DeserializeDeformableModel(const HSerializedItem& SerializedItemHandle);

  // Serialize a deformable model.
  HSerializedItem SerializeDeformableModel() const;

  // Read a deformable model from a file.
  void ReadDeformableModel(const HString& FileName);

  // Read a deformable model from a file.
  void ReadDeformableModel(const char* FileName);

#ifdef _WIN32
  // Read a deformable model from a file.
  void ReadDeformableModel(const wchar_t* FileName);
#endif

  // Write a deformable model to a file.
  void WriteDeformableModel(const HString& FileName) const;

  // Write a deformable model to a file.
  void WriteDeformableModel(const char* FileName) const;

#ifdef _WIN32
  // Write a deformable model to a file.
  void WriteDeformableModel(const wchar_t* FileName) const;
#endif

  // Free the memory of a deformable model.
  static void ClearDeformableModel(const HDeformableModelArray& ModelID);

  // Free the memory of a deformable model.
  void ClearDeformableModel() const;

  // Find the best matches of a local deformable model in an image.
  HImage FindLocalDeformableModel(const HImage& Image, HImage* VectorField, HXLDCont* DeformedContours, double AngleStart, double AngleExtent, double ScaleRMin, double ScaleRMax, double ScaleCMin, double ScaleCMax, double MinScore, Hlong NumMatches, double MaxOverlap, Hlong NumLevels, double Greediness, const HTuple& ResultType, const HTuple& GenParamName, const HTuple& GenParamValue, HTuple* Score, HTuple* Row, HTuple* Column) const;

  // Find the best matches of a calibrated deformable model in an image and return their 3D pose.
  HPoseArray FindPlanarCalibDeformableModel(const HImage& Image, double AngleStart, double AngleExtent, double ScaleRMin, double ScaleRMax, double ScaleCMin, double ScaleCMax, double MinScore, Hlong NumMatches, double MaxOverlap, const HTuple& NumLevels, double Greediness, const HTuple& GenParamName, const HTuple& GenParamValue, HTuple* CovPose, HTuple* Score) const;

  // Find the best matches of a calibrated deformable model in an image and return their 3D pose.
  HPose FindPlanarCalibDeformableModel(const HImage& Image, double AngleStart, double AngleExtent, double ScaleRMin, double ScaleRMax, double ScaleCMin, double ScaleCMax, double MinScore, Hlong NumMatches, double MaxOverlap, Hlong NumLevels, double Greediness, const HTuple& GenParamName, const HTuple& GenParamValue, HTuple* CovPose, HTuple* Score) const;

  // Find the best matches of a planar projective invariant deformable model in an image.
  HHomMat2DArray FindPlanarUncalibDeformableModel(const HImage& Image, double AngleStart, double AngleExtent, double ScaleRMin, double ScaleRMax, double ScaleCMin, double ScaleCMax, double MinScore, Hlong NumMatches, double MaxOverlap, const HTuple& NumLevels, double Greediness, const HTuple& GenParamName, const HTuple& GenParamValue, HTuple* Score) const;

  // Find the best matches of a planar projective invariant deformable model in an image.
  HHomMat2D FindPlanarUncalibDeformableModel(const HImage& Image, double AngleStart, double AngleExtent, double ScaleRMin, double ScaleRMax, double ScaleCMin, double ScaleCMax, double MinScore, Hlong NumMatches, double MaxOverlap, Hlong NumLevels, double Greediness, const HTuple& GenParamName, const HTuple& GenParamValue, HTuple* Score) const;

  // Set the metric of a local deformable model that was created from XLD contours.
  void SetLocalDeformableModelMetric(const HImage& Image, const HImage& VectorField, const HString& Metric) const;

  // Set the metric of a local deformable model that was created from XLD contours.
  void SetLocalDeformableModelMetric(const HImage& Image, const HImage& VectorField, const char* Metric) const;

#ifdef _WIN32
  // Set the metric of a local deformable model that was created from XLD contours.
  void SetLocalDeformableModelMetric(const HImage& Image, const HImage& VectorField, const wchar_t* Metric) const;
#endif

  // Set the metric of a planar calibrated deformable model that was created from XLD contours.
  void SetPlanarCalibDeformableModelMetric(const HImage& Image, const HPose& Pose, const HString& Metric) const;

  // Set the metric of a planar calibrated deformable model that was created from XLD contours.
  void SetPlanarCalibDeformableModelMetric(const HImage& Image, const HPose& Pose, const char* Metric) const;

#ifdef _WIN32
  // Set the metric of a planar calibrated deformable model that was created from XLD contours.
  void SetPlanarCalibDeformableModelMetric(const HImage& Image, const HPose& Pose, const wchar_t* Metric) const;
#endif

  // Set the metric of a planar uncalibrated deformable model that was created from XLD contours.
  void SetPlanarUncalibDeformableModelMetric(const HImage& Image, const HHomMat2D& HomMat2D, const HString& Metric) const;

  // Set the metric of a planar uncalibrated deformable model that was created from XLD contours.
  void SetPlanarUncalibDeformableModelMetric(const HImage& Image, const HHomMat2D& HomMat2D, const char* Metric) const;

#ifdef _WIN32
  // Set the metric of a planar uncalibrated deformable model that was created from XLD contours.
  void SetPlanarUncalibDeformableModelMetric(const HImage& Image, const HHomMat2D& HomMat2D, const wchar_t* Metric) const;
#endif

  // Prepare a deformable model for local deformable matching from XLD contours.
  void CreateLocalDeformableModelXld(const HXLDCont& Contours, const HTuple& NumLevels, const HTuple& AngleStart, const HTuple& AngleExtent, const HTuple& AngleStep, double ScaleRMin, const HTuple& ScaleRMax, const HTuple& ScaleRStep, double ScaleCMin, const HTuple& ScaleCMax, const HTuple& ScaleCStep, const HTuple& Optimization, const HString& Metric, Hlong MinContrast, const HTuple& GenParamName, const HTuple& GenParamValue);

  // Prepare a deformable model for local deformable matching from XLD contours.
  void CreateLocalDeformableModelXld(const HXLDCont& Contours, Hlong NumLevels, const HTuple& AngleStart, const HTuple& AngleExtent, double AngleStep, double ScaleRMin, const HTuple& ScaleRMax, double ScaleRStep, double ScaleCMin, const HTuple& ScaleCMax, double ScaleCStep, const HString& Optimization, const HString& Metric, Hlong MinContrast, const HTuple& GenParamName, const HTuple& GenParamValue);

  // Prepare a deformable model for local deformable matching from XLD contours.
  void CreateLocalDeformableModelXld(const HXLDCont& Contours, Hlong NumLevels, const HTuple& AngleStart, const HTuple& AngleExtent, double AngleStep, double ScaleRMin, const HTuple& ScaleRMax, double ScaleRStep, double ScaleCMin, const HTuple& ScaleCMax, double ScaleCStep, const char* Optimization, const char* Metric, Hlong MinContrast, const HTuple& GenParamName, const HTuple& GenParamValue);

#ifdef _WIN32
  // Prepare a deformable model for local deformable matching from XLD contours.
  void CreateLocalDeformableModelXld(const HXLDCont& Contours, Hlong NumLevels, const HTuple& AngleStart, const HTuple& AngleExtent, double AngleStep, double ScaleRMin, const HTuple& ScaleRMax, double ScaleRStep, double ScaleCMin, const HTuple& ScaleCMax, double ScaleCStep, const wchar_t* Optimization, const wchar_t* Metric, Hlong MinContrast, const HTuple& GenParamName, const HTuple& GenParamValue);
#endif

  // Prepare a deformable model for planar calibrated matching from XLD contours.
  void CreatePlanarCalibDeformableModelXld(const HXLDCont& Contours, const HCamPar& CamParam, const HPose& ReferencePose, const HTuple& NumLevels, const HTuple& AngleStart, const HTuple& AngleExtent, const HTuple& AngleStep, double ScaleRMin, const HTuple& ScaleRMax, const HTuple& ScaleRStep, double ScaleCMin, const HTuple& ScaleCMax, const HTuple& ScaleCStep, const HTuple& Optimization, const HString& Metric, Hlong MinContrast, const HTuple& GenParamName, const HTuple& GenParamValue);

  // Prepare a deformable model for planar calibrated matching from XLD contours.
  void CreatePlanarCalibDeformableModelXld(const HXLDCont& Contours, const HCamPar& CamParam, const HPose& ReferencePose, Hlong NumLevels, const HTuple& AngleStart, const HTuple& AngleExtent, double AngleStep, double ScaleRMin, const HTuple& ScaleRMax, double ScaleRStep, double ScaleCMin, const HTuple& ScaleCMax, double ScaleCStep, const HString& Optimization, const HString& Metric, Hlong MinContrast, const HTuple& GenParamName, const HTuple& GenParamValue);

  // Prepare a deformable model for planar calibrated matching from XLD contours.
  void CreatePlanarCalibDeformableModelXld(const HXLDCont& Contours, const HCamPar& CamParam, const HPose& ReferencePose, Hlong NumLevels, const HTuple& AngleStart, const HTuple& AngleExtent, double AngleStep, double ScaleRMin, const HTuple& ScaleRMax, double ScaleRStep, double ScaleCMin, const HTuple& ScaleCMax, double ScaleCStep, const char* Optimization, const char* Metric, Hlong MinContrast, const HTuple& GenParamName, const HTuple& GenParamValue);

#ifdef _WIN32
  // Prepare a deformable model for planar calibrated matching from XLD contours.
  void CreatePlanarCalibDeformableModelXld(const HXLDCont& Contours, const HCamPar& CamParam, const HPose& ReferencePose, Hlong NumLevels, const HTuple& AngleStart, const HTuple& AngleExtent, double AngleStep, double ScaleRMin, const HTuple& ScaleRMax, double ScaleRStep, double ScaleCMin, const HTuple& ScaleCMax, double ScaleCStep, const wchar_t* Optimization, const wchar_t* Metric, Hlong MinContrast, const HTuple& GenParamName, const HTuple& GenParamValue);
#endif

  // Prepare a deformable model for planar uncalibrated matching from XLD contours.
  void CreatePlanarUncalibDeformableModelXld(const HXLDCont& Contours, const HTuple& NumLevels, const HTuple& AngleStart, const HTuple& AngleExtent, const HTuple& AngleStep, double ScaleRMin, const HTuple& ScaleRMax, const HTuple& ScaleRStep, double ScaleCMin, const HTuple& ScaleCMax, const HTuple& ScaleCStep, const HTuple& Optimization, const HString& Metric, Hlong MinContrast, const HTuple& GenParamName, const HTuple& GenParamValue);

  // Prepare a deformable model for planar uncalibrated matching from XLD contours.
  void CreatePlanarUncalibDeformableModelXld(const HXLDCont& Contours, Hlong NumLevels, const HTuple& AngleStart, const HTuple& AngleExtent, double AngleStep, double ScaleRMin, const HTuple& ScaleRMax, double ScaleRStep, double ScaleCMin, const HTuple& ScaleCMax, double ScaleCStep, const HString& Optimization, const HString& Metric, Hlong MinContrast, const HTuple& GenParamName, const HTuple& GenParamValue);

  // Prepare a deformable model for planar uncalibrated matching from XLD contours.
  void CreatePlanarUncalibDeformableModelXld(const HXLDCont& Contours, Hlong NumLevels, const HTuple& AngleStart, const HTuple& AngleExtent, double AngleStep, double ScaleRMin, const HTuple& ScaleRMax, double ScaleRStep, double ScaleCMin, const HTuple& ScaleCMax, double ScaleCStep, const char* Optimization, const char* Metric, Hlong MinContrast, const HTuple& GenParamName, const HTuple& GenParamValue);

#ifdef _WIN32
  // Prepare a deformable model for planar uncalibrated matching from XLD contours.
  void CreatePlanarUncalibDeformableModelXld(const HXLDCont& Contours, Hlong NumLevels, const HTuple& AngleStart, const HTuple& AngleExtent, double AngleStep, double ScaleRMin, const HTuple& ScaleRMax, double ScaleRStep, double ScaleCMin, const HTuple& ScaleCMax, double ScaleCStep, const wchar_t* Optimization, const wchar_t* Metric, Hlong MinContrast, const HTuple& GenParamName, const HTuple& GenParamValue);
#endif

  // Creates a deformable model for local, deformable matching.
  void CreateLocalDeformableModel(const HImage& Template, const HTuple& NumLevels, const HTuple& AngleStart, const HTuple& AngleExtent, const HTuple& AngleStep, double ScaleRMin, const HTuple& ScaleRMax, const HTuple& ScaleRStep, double ScaleCMin, const HTuple& ScaleCMax, const HTuple& ScaleCStep, const HTuple& Optimization, const HString& Metric, const HTuple& Contrast, const HTuple& MinContrast, const HTuple& GenParamName, const HTuple& GenParamValue);

  // Creates a deformable model for local, deformable matching.
  void CreateLocalDeformableModel(const HImage& Template, Hlong NumLevels, const HTuple& AngleStart, const HTuple& AngleExtent, double AngleStep, double ScaleRMin, const HTuple& ScaleRMax, double ScaleRStep, double ScaleCMin, const HTuple& ScaleCMax, double ScaleCStep, const HString& Optimization, const HString& Metric, const HTuple& Contrast, Hlong MinContrast, const HTuple& GenParamName, const HTuple& GenParamValue);

  // Creates a deformable model for local, deformable matching.
  void CreateLocalDeformableModel(const HImage& Template, Hlong NumLevels, const HTuple& AngleStart, const HTuple& AngleExtent, double AngleStep, double ScaleRMin, const HTuple& ScaleRMax, double ScaleRStep, double ScaleCMin, const HTuple& ScaleCMax, double ScaleCStep, const char* Optimization, const char* Metric, const HTuple& Contrast, Hlong MinContrast, const HTuple& GenParamName, const HTuple& GenParamValue);

#ifdef _WIN32
  // Creates a deformable model for local, deformable matching.
  void CreateLocalDeformableModel(const HImage& Template, Hlong NumLevels, const HTuple& AngleStart, const HTuple& AngleExtent, double AngleStep, double ScaleRMin, const HTuple& ScaleRMax, double ScaleRStep, double ScaleCMin, const HTuple& ScaleCMax, double ScaleCStep, const wchar_t* Optimization, const wchar_t* Metric, const HTuple& Contrast, Hlong MinContrast, const HTuple& GenParamName, const HTuple& GenParamValue);
#endif

  // Create a deformable model for calibrated perspective matching.
  void CreatePlanarCalibDeformableModel(const HImage& Template, const HCamPar& CamParam, const HPose& ReferencePose, const HTuple& NumLevels, const HTuple& AngleStart, const HTuple& AngleExtent, const HTuple& AngleStep, double ScaleRMin, const HTuple& ScaleRMax, const HTuple& ScaleRStep, double ScaleCMin, const HTuple& ScaleCMax, const HTuple& ScaleCStep, const HTuple& Optimization, const HString& Metric, const HTuple& Contrast, const HTuple& MinContrast, const HTuple& GenParamName, const HTuple& GenParamValue);

  // Create a deformable model for calibrated perspective matching.
  void CreatePlanarCalibDeformableModel(const HImage& Template, const HCamPar& CamParam, const HPose& ReferencePose, Hlong NumLevels, const HTuple& AngleStart, const HTuple& AngleExtent, double AngleStep, double ScaleRMin, const HTuple& ScaleRMax, double ScaleRStep, double ScaleCMin, const HTuple& ScaleCMax, double ScaleCStep, const HString& Optimization, const HString& Metric, const HTuple& Contrast, Hlong MinContrast, const HTuple& GenParamName, const HTuple& GenParamValue);

  // Create a deformable model for calibrated perspective matching.
  void CreatePlanarCalibDeformableModel(const HImage& Template, const HCamPar& CamParam, const HPose& ReferencePose, Hlong NumLevels, const HTuple& AngleStart, const HTuple& AngleExtent, double AngleStep, double ScaleRMin, const HTuple& ScaleRMax, double ScaleRStep, double ScaleCMin, const HTuple& ScaleCMax, double ScaleCStep, const char* Optimization, const char* Metric, const HTuple& Contrast, Hlong MinContrast, const HTuple& GenParamName, const HTuple& GenParamValue);

#ifdef _WIN32
  // Create a deformable model for calibrated perspective matching.
  void CreatePlanarCalibDeformableModel(const HImage& Template, const HCamPar& CamParam, const HPose& ReferencePose, Hlong NumLevels, const HTuple& AngleStart, const HTuple& AngleExtent, double AngleStep, double ScaleRMin, const HTuple& ScaleRMax, double ScaleRStep, double ScaleCMin, const HTuple& ScaleCMax, double ScaleCStep, const wchar_t* Optimization, const wchar_t* Metric, const HTuple& Contrast, Hlong MinContrast, const HTuple& GenParamName, const HTuple& GenParamValue);
#endif

  // Creates a deformable model for uncalibrated, perspective matching.
  void CreatePlanarUncalibDeformableModel(const HImage& Template, const HTuple& NumLevels, const HTuple& AngleStart, const HTuple& AngleExtent, const HTuple& AngleStep, double ScaleRMin, const HTuple& ScaleRMax, const HTuple& ScaleRStep, double ScaleCMin, const HTuple& ScaleCMax, const HTuple& ScaleCStep, const HTuple& Optimization, const HString& Metric, const HTuple& Contrast, const HTuple& MinContrast, const HTuple& GenParamName, const HTuple& GenParamValue);

  // Creates a deformable model for uncalibrated, perspective matching.
  void CreatePlanarUncalibDeformableModel(const HImage& Template, Hlong NumLevels, const HTuple& AngleStart, const HTuple& AngleExtent, double AngleStep, double ScaleRMin, const HTuple& ScaleRMax, double ScaleRStep, double ScaleCMin, const HTuple& ScaleCMax, double ScaleCStep, const HString& Optimization, const HString& Metric, const HTuple& Contrast, Hlong MinContrast, const HTuple& GenParamName, const HTuple& GenParamValue);

  // Creates a deformable model for uncalibrated, perspective matching.
  void CreatePlanarUncalibDeformableModel(const HImage& Template, Hlong NumLevels, const HTuple& AngleStart, const HTuple& AngleExtent, double AngleStep, double ScaleRMin, const HTuple& ScaleRMax, double ScaleRStep, double ScaleCMin, const HTuple& ScaleCMax, double ScaleCStep, const char* Optimization, const char* Metric, const HTuple& Contrast, Hlong MinContrast, const HTuple& GenParamName, const HTuple& GenParamValue);

#ifdef _WIN32
  // Creates a deformable model for uncalibrated, perspective matching.
  void CreatePlanarUncalibDeformableModel(const HImage& Template, Hlong NumLevels, const HTuple& AngleStart, const HTuple& AngleExtent, double AngleStep, double ScaleRMin, const HTuple& ScaleRMax, double ScaleRStep, double ScaleCMin, const HTuple& ScaleCMax, double ScaleCStep, const wchar_t* Optimization, const wchar_t* Metric, const HTuple& Contrast, Hlong MinContrast, const HTuple& GenParamName, const HTuple& GenParamValue);
#endif

};

// forward declarations and types for internal array implementation

template<class T> class HSmartPtr;
template<class T> class HHandleBaseArrayRef;

typedef HHandleBaseArrayRef<HDeformableModel> HDeformableModelArrayRef;
typedef HSmartPtr< HDeformableModelArrayRef > HDeformableModelArrayPtr;


// Represents multiple tool instances
class LIntExport HDeformableModelArray : public HHandleBaseArray
{

public:

  // Create empty array
  HDeformableModelArray();

  // Create array from native array of tool instances
  HDeformableModelArray(const HDeformableModel* classes, Hlong length);

  // Copy constructor
  HDeformableModelArray(const HDeformableModelArray &tool_array);

  // Destructor
  virtual ~HDeformableModelArray();

  // Assignment operator
  HDeformableModelArray &operator=(const HDeformableModelArray &tool_array);

  // Clears array and all tool instances
  virtual void Clear();

  // Get array of native tool instances
  const HDeformableModel* Tools() const;

  // Get number of tools
  virtual Hlong Length() const;

  // Create tool array from tuple of handles
  virtual void SetFromTuple(const HTuple& handles);

  // Get tuple of handles for tool array
  virtual HTuple ConvertToTuple() const;

protected:

// Smart pointer to internal data container
   HDeformableModelArrayPtr *mArrayPtr;
};

}

#endif
