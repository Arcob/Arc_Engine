/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.8
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */


using System;
using System.Runtime.InteropServices;

public class aiLight : IDisposable {
  private HandleRef swigCPtr;
  protected bool swigCMemOwn;

  internal aiLight(IntPtr cPtr, bool cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(aiLight obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~aiLight() {
    Dispose();
  }

  public virtual void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          AssimpPINVOKE.delete_aiLight(swigCPtr);
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
    }
  }

  public aiString mName {
    set {
      AssimpPINVOKE.aiLight_mName_set(swigCPtr, aiString.getCPtr(value));
    } 
    get {
      IntPtr cPtr = AssimpPINVOKE.aiLight_mName_get(swigCPtr);
      aiString ret = (cPtr == IntPtr.Zero) ? null : new aiString(cPtr, false);
      return ret;
    } 
  }

  public aiLightSourceType mType {
    set {
      AssimpPINVOKE.aiLight_mType_set(swigCPtr, (int)value);
    } 
    get {
      aiLightSourceType ret = (aiLightSourceType)AssimpPINVOKE.aiLight_mType_get(swigCPtr);
      return ret;
    } 
  }

  public aiVector3D mPosition {
    set {
      AssimpPINVOKE.aiLight_mPosition_set(swigCPtr, aiVector3D.getCPtr(value));
    } 
    get {
      IntPtr cPtr = AssimpPINVOKE.aiLight_mPosition_get(swigCPtr);
      aiVector3D ret = (cPtr == IntPtr.Zero) ? null : new aiVector3D(cPtr, false);
      return ret;
    } 
  }

  public aiVector3D mDirection {
    set {
      AssimpPINVOKE.aiLight_mDirection_set(swigCPtr, aiVector3D.getCPtr(value));
    } 
    get {
      IntPtr cPtr = AssimpPINVOKE.aiLight_mDirection_get(swigCPtr);
      aiVector3D ret = (cPtr == IntPtr.Zero) ? null : new aiVector3D(cPtr, false);
      return ret;
    } 
  }

  public float mAttenuationConstant {
    set {
      AssimpPINVOKE.aiLight_mAttenuationConstant_set(swigCPtr, value);
    } 
    get {
      float ret = AssimpPINVOKE.aiLight_mAttenuationConstant_get(swigCPtr);
      return ret;
    } 
  }

  public float mAttenuationLinear {
    set {
      AssimpPINVOKE.aiLight_mAttenuationLinear_set(swigCPtr, value);
    } 
    get {
      float ret = AssimpPINVOKE.aiLight_mAttenuationLinear_get(swigCPtr);
      return ret;
    } 
  }

  public float mAttenuationQuadratic {
    set {
      AssimpPINVOKE.aiLight_mAttenuationQuadratic_set(swigCPtr, value);
    } 
    get {
      float ret = AssimpPINVOKE.aiLight_mAttenuationQuadratic_get(swigCPtr);
      return ret;
    } 
  }

  public aiColor3D mColorDiffuse {
    set {
      AssimpPINVOKE.aiLight_mColorDiffuse_set(swigCPtr, aiColor3D.getCPtr(value));
    } 
    get {
      IntPtr cPtr = AssimpPINVOKE.aiLight_mColorDiffuse_get(swigCPtr);
      aiColor3D ret = (cPtr == IntPtr.Zero) ? null : new aiColor3D(cPtr, false);
      return ret;
    } 
  }

  public aiColor3D mColorSpecular {
    set {
      AssimpPINVOKE.aiLight_mColorSpecular_set(swigCPtr, aiColor3D.getCPtr(value));
    } 
    get {
      IntPtr cPtr = AssimpPINVOKE.aiLight_mColorSpecular_get(swigCPtr);
      aiColor3D ret = (cPtr == IntPtr.Zero) ? null : new aiColor3D(cPtr, false);
      return ret;
    } 
  }

  public aiColor3D mColorAmbient {
    set {
      AssimpPINVOKE.aiLight_mColorAmbient_set(swigCPtr, aiColor3D.getCPtr(value));
    } 
    get {
      IntPtr cPtr = AssimpPINVOKE.aiLight_mColorAmbient_get(swigCPtr);
      aiColor3D ret = (cPtr == IntPtr.Zero) ? null : new aiColor3D(cPtr, false);
      return ret;
    } 
  }

  public float mAngleInnerCone {
    set {
      AssimpPINVOKE.aiLight_mAngleInnerCone_set(swigCPtr, value);
    } 
    get {
      float ret = AssimpPINVOKE.aiLight_mAngleInnerCone_get(swigCPtr);
      return ret;
    } 
  }

  public float mAngleOuterCone {
    set {
      AssimpPINVOKE.aiLight_mAngleOuterCone_set(swigCPtr, value);
    } 
    get {
      float ret = AssimpPINVOKE.aiLight_mAngleOuterCone_get(swigCPtr);
      return ret;
    } 
  }

  public aiLight() : this(AssimpPINVOKE.new_aiLight(), true) {
  }

}
