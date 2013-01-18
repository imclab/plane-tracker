#ifndef MESSAGES_H
#define MESSAGES_H
#include <cvblob.h>
#include <cv.h>

using namespace cv;
using namespace cvb;

namespace Messages{

  class DisableMessage;
  class EnableMessage;

  class AmplificationMessage{
    public:
      AmplificationMessage(int amplification): amplification(amplification){}
      int amplification;
  };

  class ImageMessage{
    public:
      String name;
      IplImage* image;
      ImageMessage(IplImage* image): name("unnamed"), image(image){}
      ImageMessage(String name, IplImage* image): name(name), image(image){}
  };

  class BlobPositionMessage{
    public:
      BlobPositionMessage(double x, double y): x(x), y(y) {}
      double x,y;
  };

  /**
   * This class represents the result of a successful CV plane detection
   * planeBlob: The CvBlob that the plane has been identified as
   * image: The image that captured by the camera
   */
  class PlaneVisionMessage {
    public:
      CvBlob planeBlob;
      IplImage* result;
      vector<ImageMessage> extras;
      vector<int> getDisplacement();
      bool hasPlane;
      bool userHasConfirmed;
      PlaneVisionMessage(CvBlob planeBlob, IplImage* result, vector<ImageMessage> extras):
        planeBlob(planeBlob),
        result(result),
        extras(extras),
        hasPlane(true),
        userHasConfirmed(false){}
      PlaneVisionMessage(CvBlob planeBlob, IplImage* result,
                         vector<ImageMessage> extras, bool userHasConfirmed):
        planeBlob(planeBlob),
        result(result),
        extras(extras),
        hasPlane(true),
        userHasConfirmed(userHasConfirmed){}
      PlaneVisionMessage(): 
        planeBlob(CvBlob()),
        result(0),
        extras(vector<ImageMessage>()),
        hasPlane(false),
        userHasConfirmed(false){}
      PlaneVisionMessage(IplImage* image, vector<ImageMessage> extras): 
        planeBlob(CvBlob()),
        result(image),
        extras(extras),
        hasPlane(false),
        userHasConfirmed(false){}
  };

  class GPSDataMessage{
    public:
      double lat, lon, alt;
      bool hasData;
      GPSDataMessage(double lat, double lon, double alt): lat(lat),lon(lon),alt(alt),hasData(true){}
      GPSDataMessage(): lat(0),lon(0),alt(0),hasData(false){}
  };


  class PositionMessage{
    public:
      double pan, tilt;
      bool positionLost;
      PositionMessage(double pan, double tilt): pan(pan), tilt(tilt), positionLost(false){}
      PositionMessage(): pan(0), tilt(0), positionLost(true){}
      virtual vector<char> toBytes() const = 0;
  };

  class RelativePositionMessage: public PositionMessage{
    public:
      RelativePositionMessage(double pan, double tilt): PositionMessage(pan,tilt){}
      RelativePositionMessage(): PositionMessage(){}
      vector<char> toBytes() const;
  };

  class AbsolutePositionMessage: public PositionMessage{
    public:
      AbsolutePositionMessage(double pan, double tilt): PositionMessage(pan,tilt){}
      AbsolutePositionMessage(): PositionMessage(){}
      vector<char> toBytes() const;
  };

  class UseRSSIMessage: public PositionMessage{
    public:
      vector<char> toBytes() const;
  };
}

#endif
