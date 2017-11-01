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

#ifndef CAPTURE_H
#define CAPTURE_H

#include "objectextractor.h"
#include "QObject"
#include "QBasicTimer"
#include <QTimer>

class Capture: public QObject
{
    Q_OBJECT
public:
    explicit Capture(QObject *parent = 0);
    ~Capture(void);
public slots:
    void start();
    void startRecording();
    void stopRecording();
    void toggleDisplayRightHand();
    void toggleDisplayLeftHand();
    void toggleDisplayRightTrack();
    void toggleDisplayLeftTrack();
    void toggleDisplayGrid();

private:
    double m_alpha = 0.5;
    QBasicTimer m_timer;
    bool isCam1Active = false;
    bool isCam2Active = false;
    ObjectExtractor m_track1 = ObjectExtractor(1);
    ObjectExtractor m_track2  = ObjectExtractor(2);
    bool display_right_hand = true;
    bool display_left_hand = true;
    bool display_right_track = true;
    bool display_left_track = true;
    bool display_grid = false;
    bool isRecording = false;
    void timerEvent(QTimerEvent * ev);
    string m_video_window_name = "DualCam";

    VideoWriter m_video_writer;
    string m_file_base_name = "DualCam-recording-";
    string m_file_path = "~/Documents/";
    string m_file_full_name;

    int m_ex = 0;
    double m_fps = 0;
    Size m_size;

    VideoCapture m_videoCapture = VideoCapture(0);
    VideoCapture m_videoCapture2 = VideoCapture(2);
    string time_stamp();
    bool toggleValue(bool value);
};

#endif // CAPTURE_H
