#ifndef FRAME_CPP_INTERFACE__FrameStream_HH
#define FRAME_CPP_INTERFACE__FrameStream_HH
 
#include "framecpp/FrameCPP.hh"
 
#include "framecpp/Version8/FrameStream.hh"
 
#if defined(__cplusplus)
#if !defined(SWIG)
namespace FrameCPP
{
  /**
   * \brief 
   */
  typedef Version::IFrameStream IFrameStream;
  typedef Common::OFrameStream OFrameStream;
}
#endif /* !defined(SWIG) */
#endif /* defined(__cplusplus) */
 
#endif /* FRAME_CPP_INTERFACE__FrameStream_HH */
