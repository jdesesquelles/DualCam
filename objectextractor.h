/* Copyright (C) 2017  jérémie Desesquelles
*                     jdesesquelles@gmail.com
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*      http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

#ifndef OBJECTEXTRACTOR_H
#define OBJECTEXTRACTOR_H
#include "opencv2/opencv.hpp"
using namespace cv;
using namespace std;

class ObjectExtractor
{
public:
    cv::Mat m_object;
    cv::Mat m_track;
    vector<Point2f> m_points;
    Scalar m_trackColor;
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
    int largest_area=0;
    int largest_contour_index=0;
    Moments moment;
    Point2f centroid;
    Point2f center;
    float radius;
    float aspectRatio;
    Scalar lowerGreen = Scalar(29, 86, 6);
    Scalar upperGreen = Scalar(64, 255, 255);
    Scalar red = Scalar(255, 0, 0);
    Scalar blue = Scalar(0, 0, 255);

    ObjectExtractor(int track_number);

    void extractObjectFromFrame(const cv::Mat & frame);
};


#endif // OBJECTEXTRACTOR_H

