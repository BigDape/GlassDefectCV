/***********************************************************
 * File generated by the HALCON-Compiler hcomp version 22.05
 * Usage: Interface to C++
 *
 * Software by: MVTec Software GmbH, www.mvtec.com
 ***********************************************************/


#ifndef HCPP_HSTEREOMODEL
#define HCPP_HSTEREOMODEL

namespace HalconCpp
{

// Represents an instance of a stereo model.
class LIntExport HStereoModel : public HHandle
{

public:

  // Create an uninitialized instance
  HStereoModel():HHandle() {}

  // Copy constructor
  HStereoModel(const HStereoModel& source) : HHandle(source) {}

  // Copy constructor
  HStereoModel(const HHandle& handle);

  // Create HStereoModel from handle, taking ownership
  explicit HStereoModel(Hlong handle);

  bool operator==(const HHandle& obj) const
  {
    return HHandleBase::operator==(obj);
  }

  bool operator!=(const HHandle& obj) const
  {
    return HHandleBase::operator!=(obj);
  }

protected:

  // Verify matching semantic type ('stereo_model')!
  virtual void AssertType(Hphandle handle) const;

public:



/*****************************************************************************
 * Operator-based class constructors
 *****************************************************************************/

  // create_stereo_model: Create a HALCON stereo model.
  explicit HStereoModel(const HCameraSetupModel& CameraSetupModelID, const HString& Method, const HTuple& GenParamName, const HTuple& GenParamValue);

  // create_stereo_model: Create a HALCON stereo model.
  explicit HStereoModel(const HCameraSetupModel& CameraSetupModelID, const HString& Method, const HString& GenParamName, const HTuple& GenParamValue);

  // create_stereo_model: Create a HALCON stereo model.
  explicit HStereoModel(const HCameraSetupModel& CameraSetupModelID, const char* Method, const char* GenParamName, const HTuple& GenParamValue);

#ifdef _WIN32
  // create_stereo_model: Create a HALCON stereo model.
  explicit HStereoModel(const HCameraSetupModel& CameraSetupModelID, const wchar_t* Method, const wchar_t* GenParamName, const HTuple& GenParamValue);
#endif




  /***************************************************************************
   * Operators                                                               *
   ***************************************************************************/

  // Free the memory of a stereo model.
  void ClearStereoModel() const;

  // Reconstruct 3D points from calibrated multi-view stereo images.
  void ReconstructPointsStereo(const HTuple& Row, const HTuple& Column, const HTuple& CovIP, Hlong CameraIdx, Hlong PointIdx, HTuple* X, HTuple* Y, HTuple* Z, HTuple* CovWP, HTuple* PointIdxOut) const;

  // Reconstruct 3D points from calibrated multi-view stereo images.
  void ReconstructPointsStereo(double Row, double Column, const HTuple& CovIP, Hlong CameraIdx, Hlong PointIdx, double* X, double* Y, double* Z, double* CovWP, Hlong* PointIdxOut) const;

  // Reconstruct surface from calibrated multi-view stereo images.
  HObjectModel3D ReconstructSurfaceStereo(const HImage& Images) const;

  // Get intermediate iconic results of a stereo reconstruction.
  HObject GetStereoModelObject(const HTuple& PairIndex, const HString& ObjectName) const;

  // Get intermediate iconic results of a stereo reconstruction.
  HObject GetStereoModelObject(Hlong PairIndex, const HString& ObjectName) const;

  // Get intermediate iconic results of a stereo reconstruction.
  HObject GetStereoModelObject(Hlong PairIndex, const char* ObjectName) const;

#ifdef _WIN32
  // Get intermediate iconic results of a stereo reconstruction.
  HObject GetStereoModelObject(Hlong PairIndex, const wchar_t* ObjectName) const;
#endif

  // Return the list of image pairs set in a stereo model.
  HTuple GetStereoModelImagePairs(HTuple* To) const;

  // Specify image pairs to be used for surface stereo reconstruction.
  void SetStereoModelImagePairs(const HTuple& From, const HTuple& To) const;

  // Get stereo model parameters.
  HTuple GetStereoModelParam(const HTuple& GenParamName) const;

  // Get stereo model parameters.
  HTuple GetStereoModelParam(const HString& GenParamName) const;

  // Get stereo model parameters.
  HTuple GetStereoModelParam(const char* GenParamName) const;

#ifdef _WIN32
  // Get stereo model parameters.
  HTuple GetStereoModelParam(const wchar_t* GenParamName) const;
#endif

  // Set stereo model parameters.
  void SetStereoModelParam(const HTuple& GenParamName, const HTuple& GenParamValue) const;

  // Set stereo model parameters.
  void SetStereoModelParam(const HString& GenParamName, const HTuple& GenParamValue) const;

  // Set stereo model parameters.
  void SetStereoModelParam(const char* GenParamName, const HTuple& GenParamValue) const;

#ifdef _WIN32
  // Set stereo model parameters.
  void SetStereoModelParam(const wchar_t* GenParamName, const HTuple& GenParamValue) const;
#endif

  // Create a HALCON stereo model.
  void CreateStereoModel(const HCameraSetupModel& CameraSetupModelID, const HString& Method, const HTuple& GenParamName, const HTuple& GenParamValue);

  // Create a HALCON stereo model.
  void CreateStereoModel(const HCameraSetupModel& CameraSetupModelID, const HString& Method, const HString& GenParamName, const HTuple& GenParamValue);

  // Create a HALCON stereo model.
  void CreateStereoModel(const HCameraSetupModel& CameraSetupModelID, const char* Method, const char* GenParamName, const HTuple& GenParamValue);

#ifdef _WIN32
  // Create a HALCON stereo model.
  void CreateStereoModel(const HCameraSetupModel& CameraSetupModelID, const wchar_t* Method, const wchar_t* GenParamName, const HTuple& GenParamValue);
#endif

  // Get intermediate 3D object model of a stereo reconstruction
  HObjectModel3D GetStereoModelObjectModel3d(const HTuple& GenParamName) const;

  // Get intermediate 3D object model of a stereo reconstruction
  HObjectModel3D GetStereoModelObjectModel3d(const HString& GenParamName) const;

  // Get intermediate 3D object model of a stereo reconstruction
  HObjectModel3D GetStereoModelObjectModel3d(const char* GenParamName) const;

#ifdef _WIN32
  // Get intermediate 3D object model of a stereo reconstruction
  HObjectModel3D GetStereoModelObjectModel3d(const wchar_t* GenParamName) const;
#endif

};

// forward declarations and types for internal array implementation

template<class T> class HSmartPtr;
template<class T> class HHandleBaseArrayRef;

typedef HHandleBaseArrayRef<HStereoModel> HStereoModelArrayRef;
typedef HSmartPtr< HStereoModelArrayRef > HStereoModelArrayPtr;


// Represents multiple tool instances
class LIntExport HStereoModelArray : public HHandleBaseArray
{

public:

  // Create empty array
  HStereoModelArray();

  // Create array from native array of tool instances
  HStereoModelArray(const HStereoModel* classes, Hlong length);

  // Copy constructor
  HStereoModelArray(const HStereoModelArray &tool_array);

  // Destructor
  virtual ~HStereoModelArray();

  // Assignment operator
  HStereoModelArray &operator=(const HStereoModelArray &tool_array);

  // Clears array and all tool instances
  virtual void Clear();

  // Get array of native tool instances
  const HStereoModel* Tools() const;

  // Get number of tools
  virtual Hlong Length() const;

  // Create tool array from tuple of handles
  virtual void SetFromTuple(const HTuple& handles);

  // Get tuple of handles for tool array
  virtual HTuple ConvertToTuple() const;

protected:

// Smart pointer to internal data container
   HStereoModelArrayPtr *mArrayPtr;
};

}

#endif
