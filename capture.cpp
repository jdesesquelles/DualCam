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

#include "Capture.h"
#include <QTimerEvent>

Capture::Capture(QObject *parent): QObject(parent){}

Capture::~Capture(void){m_timer.stop();}

string Capture::time_stamp()
{
    time_t temps;
    struct tm datetime;
    char  format[32];
    time(&temps);
    datetime = *localtime(&temps);
    strftime(format, 32, "%Y-%m-%d %H-%M", &datetime);
    string time_stamp(format);
    return time_stamp;

}

void Capture::timerEvent(QTimerEvent * ev) {
    if (ev->timerId() != m_timer.timerId()) return;
    cv::Mat frame;
    cv::Mat frame2;
    cv::Mat temp;
    cv::Mat resizedFrame;

    if(!isCam1Active && !isCam2Active)
        return;

    if (isCam1Active)
    {
        m_videoCapture >> frame;
        if (display_right_track)
            m_track1.extractObjectFromFrame(frame);
        if(!isCam2Active) {frame2 = frame;}

    }
    if (isCam2Active)
    {
        m_videoCapture2 >> frame2;
        if (display_left_track)
            m_track2.extractObjectFromFrame(frame2);
        if(!isCam1Active) {frame = frame2;}
    }

    if(isCam1Active && isCam2Active)
    {
        cv::flip(frame2, temp,1);
        cv::addWeighted(temp, m_alpha, frame, m_alpha, 0.0, frame);
    }
    if(isRecording) {m_video_writer << frame;}
    // Resizing the frame beofre display
    cv::resize(frame, resizedFrame, cv::Size(800, 600));
    imshow(m_video_window_name, resizedFrame);
}

void Capture::start() {
    if(m_videoCapture.isOpened())
        isCam1Active = true;
    if(m_videoCapture2.isOpened())
        isCam2Active = true;

    // If no camera has been detected return
    if(!isCam1Active && !isCam2Active)
        return;

    if(isCam1Active)
    {
        m_ex = static_cast<int>(m_videoCapture.get(CV_CAP_PROP_FOURCC));
        m_size = Size((int) m_videoCapture.get(CV_CAP_PROP_FRAME_WIDTH),    //Acquire input size
                      (int) m_videoCapture.get(CV_CAP_PROP_FRAME_HEIGHT));
        m_fps = m_videoCapture.get(CV_CAP_PROP_FPS);
    }
    else if(isCam2Active)
    {
        m_ex = static_cast<int>(m_videoCapture2.get(CV_CAP_PROP_FOURCC));
        m_size = Size((int) m_videoCapture2.get(CV_CAP_PROP_FRAME_WIDTH),    //Acquire input size
                      (int) m_videoCapture2.get(CV_CAP_PROP_FRAME_HEIGHT));
        m_fps = m_videoCapture2.get(CV_CAP_PROP_FPS);
    }

    cv::namedWindow(m_video_window_name,cv::WINDOW_OPENGL);
    moveWindow(m_video_window_name, 20,20);


    if (isCam1Active || isCam2Active){
        int timer_period_msec = int(1000/(m_fps));
        m_timer.start(timer_period_msec, this);
    }
}

void Capture::startRecording()
{
    m_file_full_name = m_file_path + m_file_base_name + time_stamp() + ".mp4";
    m_video_writer.fourcc('M', 'P', '4', '2');
    m_video_writer.open(m_file_full_name , m_ex, m_fps, m_size, true);
    if (!m_video_writer.isOpened())
    {
        std::cout << m_file_full_name + " (output video file) could not be opened" << std::endl;
        return;
    }
    isRecording = true;
}

void Capture::stopRecording()
{
    isRecording = false;
    m_video_writer.release();
}

void Capture::toggleDisplayRightHand()
{
    display_right_hand = toggleValue(display_right_hand);

}

void Capture::toggleDisplayLeftHand()
{
    display_left_hand = toggleValue(display_left_hand);

}

void Capture::toggleDisplayRightTrack()
{
    display_right_track = toggleValue(display_right_track);

}

void Capture::toggleDisplayLeftTrack()
{
    display_left_track = toggleValue(display_left_track);

}

void Capture::toggleDisplayGrid()
{
    display_grid = toggleValue(display_grid);

}

bool Capture::toggleValue(bool value)
{
    if (value)
        return false;
    else
        return true;
}

