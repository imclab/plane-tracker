#ifndef VISION_H
#define VISION_H 

#include <vector>
#include <cv.h>
#include <cvblob.h>

#include "src/util/Messages.h"

using namespace std;
using namespace cvb;
using namespace Messages;

class Vision {
  public:
    Vision(bool intermediateSteps): intermediateSteps(intermediateSteps) {}
    /**
     * This function attempts to find the plane from the image, and uses CV along with some
     * heurestics to determine the plane's location.
     */
    PlaneVisionMessage findPlane(IplImage* image, vector<PlaneVisionMessage> previousPlanes);
  private:
    bool intermediateSteps;
    class BlobScore {
      public: 
        float ratioScore; 		// The score given based on the blobs width/height ratio
        float positionScore; 	// Score based on current position vs expected position
        float sizeScore; 		// Plane size vs Expected size
        float gpsScore; 		// Visual plane position vs GPS plane position
        float computeScore();	// Computes a weighted some of the scores to
                                // determine a confidence level for this blob
    };

    /**
     * Returns all of the blobs that are returned from a CV analysis of 
     * the image, taking only the sky color into account. Later filtering will 
     * be performed on this data to reduce the number of blobs found
     */
    CvBlobs findCandidates(IplImage *image, vector<ImageMessage> &extras);

    /**
     * Converts the image into a binary image that is suitable for blob detection, using 
     * a given conversion method. This does most of the CV work.
     */
    IplImage* fullColorToBW (IplImage* image, vector<ImageMessage> &extras);


    /**
     * This determines the displacement between the centroids of the blobs. This is used for 
     * velocity calculation
     */
    vector<double> getDisplacement(CvBlob* currentBlob, CvBlob* lastBlob);

    IplImage* canny(IplImage* grayImage, vector<ImageMessage> &extras);
};
#endif