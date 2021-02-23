/*
 * uv4l-time-overlay.cpp
 * g++ -Ofast -std=c++11 uv4l-time-overlay.cpp -o uv4l-time-overlay
 * Original Program: Text Scrolling Demo; Author Luca Risolia
 *
 * This program will update the json file associated with uv4l_raspicam.
 * Text overlay must be enabled and the json text file must be identified
 * in /etc/uv4l/uv4l-raspicam.conf. This program is a stripped down/modified
 * version of uv4l-overlay.cpp that was downloaded from http://www.linux-projects.org.
 * This version assumes a 640 x 480 resolution and puts the current date at
 * bottom left with the current time at bottom right. It updates time and date
 * once per second. I am running this at 2 frames per second.
*/

#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <linux/videodev2.h>
#include <string>
#include <iostream>
#include <cstdlib>
#include <fstream>


int main(int argc, char **argv) {
  if (argc != 3) {
    std::cerr << "Usage: uv4l-overlay <video_device> <filename>\n";
    return EXIT_FAILURE;
  }
  std::cout << "Press Ctrl-C to terminate\n";
//simplex, plain, duplex, complex, triplex, complex_small, script_simplex, script_complex, italic

  char myAscTime[10];
  char myAscDate[10];
  time_t rawTime;
  std::ofstream jsonFile;

  for (;; sleep(5)) {
    auto fd = open(argv[1], O_RDWR | O_NONBLOCK);
    if (fd == -1) {
      std::cerr << "Failed to open " << argv[1] << '\n';
      continue;
    }
    struct v4l2_queryctrl queryctrl{};
    struct v4l2_control ctrl{0, 1};
    for (queryctrl.id = V4L2_CID_PRIVATE_BASE;; ++queryctrl.id) {
      if (!ioctl(fd, VIDIOC_QUERYCTRL, &queryctrl)) {
        const std::string name{std::begin(queryctrl.name), std::end(queryctrl.name)};
        if (name.find("overlay") != std::string::npos) {
          ctrl.id = queryctrl.id;
          break;
        }
      } else {
        break;
      }
    }
    if (!ctrl.id) {
      std::cerr << "Text overlay not supported\n";
      return EXIT_FAILURE;
    }
    struct v4l2_format fmt{};
    do {
      time(&rawTime);
      strftime(myAscTime, 9, "%T", localtime(&rawTime));
      strftime(myAscDate, 9, "%D", localtime(&rawTime));
      jsonFile.open("/usr/share/uv4l/raspicam/textnew.json");
      jsonFile << "[\n  {\n";
      jsonFile << "    \"font\": \"courier_new\",\n";
      jsonFile << "    \"scale\": 0.8,\n";
      jsonFile << "    \"thickness\": 2,\n";
      jsonFile << "    \"red\": 200,\n";
      jsonFile << "    \"green\": 200,\n";
      jsonFile << "    \"blue\": 200,\n";
      jsonFile << "    \"line_type\": 8,\n";
      jsonFile << "    \"text_line\": \"" << myAscDate << "\",\n";
      jsonFile << "    \"x\": 600,\n";
      jsonFile << "    \"y\": 25\n";
      jsonFile << "  },\n  {\n";
      jsonFile << "    \"text_line\": \"" << myAscTime << "\",\n";
      jsonFile << "    \"x\": 1100,\n";
      jsonFile << "    \"y\": 25\n";
      jsonFile << "  }\n]\n";
      jsonFile.close();
      if (ioctl(fd, VIDIOC_S_CTRL, &ctrl) == -1) {
        std::cerr << "Failed to notify the driver\n";
        break;
      }
      usleep(1000000);
    } while(true);
    close(fd);
    std::cout << "Retrying to open in 5 seconds...\n";
  }
}