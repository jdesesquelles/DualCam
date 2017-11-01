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

#include "objectextractor.h"


ObjectExtractor::ObjectExtractor(int track_number)
{
    if (track_number == 1)
    {
        m_trackColor = red;
    }
    else if (track_number == 2)
    {
        m_trackColor = blue;
    }
}

void ObjectExtractor::extractObjectFromFrame(const cv::Mat & frame){
    // detect green objects
    cv::Mat temp;
    cvtColor(frame, temp, COLOR_BGR2HSV);

    //        construct a mask for the color "green", then perform
    //        a series of dilations and erosions to remove any small
    //        blobs left in the mask
    inRange(temp, lowerGreen, upperGreen, temp);
    erode(temp,temp,Mat(),Point(-1,-1),2);
    dilate(temp,temp,Mat(),Point(-1,-1),2);
    cv::Mat temp_copy = temp.clone();
    findContours(temp_copy, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

    // only proceed if at least one contour was found
    if (contours.size() > 0)
    {
        // largest_contour_index = maxContour(contours);
        largest_area = 0;
        for( int i = 0; i< int(contours.size()); i++ ) // iterate through each contour.
        {
            double a=contourArea( contours[i],false);  //  Find the area of contour
            if(a>largest_area){
                largest_area=a;
                largest_contour_index=i;  //Store the index of largest contour
            }
        }

        // Point2f centroid = get_contour_centroid(vector<Point> contours[largest_contour_index])
        // Get the moments
        moment = moments( contours[largest_contour_index], false );
        //  Get the mass centers:
        center = Point2f( moment.m10/moment.m00 , moment.m01/moment.m00 );
        //  Get the enclosing circle:
        minEnclosingCircle(Mat(contours[largest_contour_index]),centroid, radius);

        // only proceed if the radius meets a minimum size
        // int track_thickness;
        if (radius > 10)
        {
            // draw the circle and centroid on the frame,
            // then update the list of tracked points
            circle(frame, centroid, radius, Scalar(0, 255, 255), 2);
            circle(frame, center, 5, Scalar(0, 0, 255), -1);
            m_points.push_back(center);
            //track_thickness = radius * radius / 400;
        }

        if (m_points.size() > 1)
        {
            for (int i = 1; i < int(m_points.size()); i++)
            {
                line(frame, m_points[i-1], m_points[i], m_trackColor, 4);
            }
        }
    }

}

