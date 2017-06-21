#ifndef MATCHER
#define MATCHER

#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/nonfree/features2d.hpp>
#include <opencv2/legacy/legacy.hpp>
#include "algcommon.h"

class Matcher
{
private:

    cv::Ptr<cv::FeatureDetector> detector;
    cv::Ptr<cv::DescriptorExtractor> extractor;
    float ratio;
    bool refineF;
    double distance;
    double confidence;

public:

    Matcher() : ratio(0.65f), refineF(true), confidence(0.99), distance(3.0)
    {
        detector = new cv::SurfFeatureDetector();
        extractor = new cv::SurfFeatureDetector();
    }

    void setFeatureDetector(cv::Ptr<cv::FeatureDetector>& detect)
    {
        detector= detect;
    }
    void setDescriptorExtractor(cv::Ptr<cv::DescriptorExtractor>& desc)
    {
        extractor= desc;
    }
    void setMinDistanceToEpipolar(double d)
    {
        distance= d;
    }
    void setConfidenceLevel(double c)
    {
        confidence= c;
    }
    void setRatio(float r)
    {
        ratio= r;
    }
    void refineFundamental(bool flag)
    {

        refineF= flag;
    }
    int ratioTest(std::vector<std::vector<cv::DMatch> >& matches)
    {
        int removed=0;
        for (std::vector<std::vector<cv::DMatch> >::iterator matchIterator= matches.begin();
             matchIterator!= matches.end(); ++matchIterator) {

            if (matchIterator->size() > 1)
            {
                if ((*matchIterator)[0].distance/(*matchIterator)[1].distance > ratio)
                {

                    matchIterator->clear();
                    removed++;
                }
            } else
            {
                matchIterator->clear();
                removed++;
            }
        }
        return removed;
    }

    void symmetryTest(const std::vector<std::vector<cv::DMatch> >& matches1,
                      const std::vector<std::vector<cv::DMatch> >& matches2,
                      std::vector<cv::DMatch>& symMatches)
    {

        for (std::vector<std::vector<cv::DMatch> >::const_iterator matchIterator1= matches1.begin();
             matchIterator1!= matches1.end(); ++matchIterator1)
        {
            if (matchIterator1->size() < 2)
                continue;
            for (std::vector<std::vector<cv::DMatch> >::const_iterator matchIterator2= matches2.begin();
                 matchIterator2!= matches2.end(); ++matchIterator2)
            {

                if (matchIterator2->size() < 2)
                    continue;

                if ((*matchIterator1)[0].queryIdx == (*matchIterator2)[0].trainIdx  &&
                        (*matchIterator2)[0].queryIdx == (*matchIterator1)[0].trainIdx)
                {
                    symMatches.push_back(cv::DMatch((*matchIterator1)[0].queryIdx,
                                         (*matchIterator1)[0].trainIdx,
                            (*matchIterator1)[0].distance));
                    break;
                }
            }
        }
    }

    cv::Mat ransacTest(const std::vector<cv::DMatch>& matches,
                       const std::vector<cv::KeyPoint>& keypoints1,
                       const std::vector<cv::KeyPoint>& keypoints2,
                       std::vector<cv::DMatch>& outMatches)
    {
        std::vector<cv::Point2f> points1, points2;
        for (std::vector<cv::DMatch>::const_iterator it= matches.begin();
             it!= matches.end(); ++it)
        {
            float x= keypoints1[it->queryIdx].pt.x;
            float y= keypoints1[it->queryIdx].pt.y;
            points1.push_back(cv::Point2f(x,y));
            x= keypoints2[it->trainIdx].pt.x;
            y= keypoints2[it->trainIdx].pt.y;
            points2.push_back(cv::Point2f(x,y));
        }

        std::vector<uchar> inliers(points1.size(),0);
        cv::Mat fundemental= cv::findFundamentalMat(
                    cv::Mat(points1),cv::Mat(points2), // matching points
                    inliers,      // match status (inlier ou outlier)
                    CV_FM_RANSAC, // RANSAC method
                    distance,     // distance to epipolar line
                    confidence);  // confidence probability

        std::vector<uchar>::const_iterator itIn= inliers.begin();
        std::vector<cv::DMatch>::const_iterator itM= matches.begin();
        for ( ;itIn!= inliers.end(); ++itIn, ++itM)
        {

            if (*itIn)
            {

                outMatches.push_back(*itM);
            }
        }
        DEBUG_STATE_OUT << " Number of matched points (after cleaning): "  << outMatches.size() << std::endl;

        if (refineF)
        {
            points1.clear();
            points2.clear();
            for (std::vector<cv::DMatch>::const_iterator it= outMatches.begin();
                 it!= outMatches.end(); ++it) {
                float x= keypoints1[it->queryIdx].pt.x;
                float y= keypoints1[it->queryIdx].pt.y;
                points1.push_back(cv::Point2f(x,y));
                x= keypoints2[it->trainIdx].pt.x;
                y= keypoints2[it->trainIdx].pt.y;
                points2.push_back(cv::Point2f(x,y));
            }
            fundemental= cv::findFundamentalMat(
                        cv::Mat(points1),cv::Mat(points2),
                        CV_FM_8POINT);
        }

        return fundemental;
    }

    cv::Mat match(cv::Mat& image1, cv::Mat& image2, // input images
                  std::vector<cv::DMatch>& matches, // output matches and keypoints
                  std::vector<cv::KeyPoint>& keypoints1, std::vector<cv::KeyPoint>& keypoints2,bool &checkres)
    {

        detector->detect(image1,keypoints1);
        detector->detect(image2,keypoints2);

        DEBUG_STATE_OUT << " Number of SURF points (1): "  << keypoints1.size() << std::endl;
        DEBUG_STATE_OUT << " Number of SURF points (2): "  << keypoints2.size() << std::endl;

        if(keypoints1.size()<100||keypoints2.size()<100)
        {
            checkres=false;
            return cv::Mat();
        }

        cv::Mat descriptors1, descriptors2;
        extractor->compute(image1,keypoints1,descriptors1);
        extractor->compute(image2,keypoints2,descriptors2);

        DEBUG_STATE_OUT << " descriptor matrix size: "  << descriptors1.rows << "  by "  << descriptors1.cols << std::endl;

        cv::BruteForceMatcher<cv::L2<float> > matcher;

        std::vector<std::vector<cv::DMatch> > matches1;
        matcher.knnMatch(descriptors1,descriptors2,
                         matches1,
                         2);
        std::vector<std::vector<cv::DMatch> > matches2;
        matcher.knnMatch(descriptors2,descriptors1,
                         matches2,
                         2);
        DEBUG_STATE_OUT << " Number of matched points 1->2: "  << matches1.size() << std::endl;
        DEBUG_STATE_OUT << " Number of matched points 2->1: "  << matches2.size() << std::endl;

        if(matches1.size()<60||matches2.size()<60)
        {
            checkres=false;
            return cv::Mat();
        }

        int removed= ratioTest(matches1);
        DEBUG_STATE_OUT << " Number of matched points 1->2 (ratio test) : "  << matches1.size()-removed << std::endl;


        removed= ratioTest(matches2);
        DEBUG_STATE_OUT << " Number of matched points 1->2 (ratio test) : "  << matches2.size()-removed << std::endl;
        if(matches1.size()<30||matches2.size()<30)
        {
            checkres=false;
            return cv::Mat();
        }

        std::vector<cv::DMatch> symMatches;
        symmetryTest(matches1,matches2,symMatches);
        if(matches1.size()<20||matches2.size()<20)
        {
            checkres=false;
            return cv::Mat();
        }

        DEBUG_STATE_OUT << " Number of matched points (symmetry test): "  << symMatches.size() << std::endl;
        cv::Mat fundemental= ransacTest(symMatches, keypoints1, keypoints2, matches);
        checkres=true;

        return fundemental;
    }
};

#endif
