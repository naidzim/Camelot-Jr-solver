<!--
*** Thanks for checking out this README Template. If you have a suggestion that would
*** make this better, please fork the repo and create a pull request or simply open
*** an issue with the tag "enhancement".
*** Thanks again! Now go create something AMAZING! :D
-->





<!-- PROJECT SHIELDS -->
<!--
*** I'm using markdown "reference style" links for readability.
*** Reference links are enclosed in brackets [ ] instead of parentheses ( ).
*** See the bottom of this document for the declaration of the reference variables
*** for contributors-url, forks-url, etc. This is an optional, concise syntax you may use.
*** https://www.markdownguide.org/basic-syntax/#reference-style-links
-->

<!--
[![Contributors][contributors-shield]][contributors-url]
[![Forks][forks-shield]][forks-url]
[![Stargazers][stars-shield]][stars-url]
[![Issues][issues-shield]][issues-url]
[![MIT License][license-shield]][license-url]
[![LinkedIn][linkedin-shield]][linkedin-url]

-->

<!-- PROJECT LOGO -->
<br />
<p align="center">
  <a href="https://github.com/othneildrew/Best-README-Template">
    <img src="images/logo.png" alt="Logo" width="80" height="80">
  </a>

  <h3 align="center">Camelot-Jr Solver</h3>

</p>



<!-- TABLE OF CONTENTS -->
## Table of Contents

* [About the Project](#about-the-project)
  * [Built With](#built-with)
* [Getting Started](#getting-started)
  * [Prerequisites](#prerequisites)
  * [Installation](#installation)
* [Usage](#usage)
* [Roadmap](#roadmap)
* [Contributing](#contributing)
* [License](#license)
* [Contact](#contact)
* [Acknowledgements](#acknowledgements)



<!-- ABOUT THE PROJECT -->
## About The Project

[![Product Name Screen Shot][product-screenshot]]

Camelot-Jr automatic solver for robotic purposes.  and provides the solution of the 48 game puzzles and others if any.

### Built With

* [ROS](https://www.ros.org/)
* [Aruco](https://www.uco.es/investiga/grupos/ava/node/26)




<!-- GETTING STARTED -->
## Getting Started
The programm runs on ROS environement and Uses Aruco augmented reality libraries for object detection (you may need a webcamera).

### Prerequisites

This project use ROS melodic distribution. Before you start you need to install it and create a catkin workspace.
Please refer to ros tutorials to install and create the workspace : (http://wiki.ros.org/ROS/Tutorials)

* Aruco

Clone the Aruco git repository in your catkin workspace
```sh
$ cd catkin_ws/src/
$ git clone https://github.com/pal-robotics/aruco_ros.git
$ cd ../ && catkin_make
```
* Usb_cam 
```sh
sudo apt install ros-melodic-usb-cam
```
### Installation

1. Clone the repository in your catkin workspace
```sh
$ cd catkin_ws/src/
$ git clone https://github.com/naidzim/Camelot-Jr-solver.git
```
2. Go back to the Catkin_ws and run 
```sh
$ cd ../ 
$ catkin_make
```
3. Source your environements 
```sh
$ source /opt/ros/melodic/setup.bash
$ source catkin_ws/devel/setup.bash
```
4. Make sure your webcam is connected to the computer
<!-- USAGE EXAMPLES -->
## Usage
### Terminal 1
Open a new terminal in which we are going to launch the ROS core and the Aruco/Camera nodes

Run:

```sh
$ roslaunch camelot_jr ArucoWebCam.launch
```

A new windows will open showing the sight of your camera using Aruco. Make sure that it detects and localize the "Ar markers" on Camelot-jr pieces. 

### Terminal 2

On this terminal we are going to run the Camelot-Jr programm

Run :

```sh
$ rosrun camelot_jr game_resolving_node 
```
And follow the instructions on the screen 


<!-- ROADMAP -->
## Roadmap

See the [open issues](https://github.com/naidzim/Camelot-Jr-solver/issues) for a list of proposed features (and known issues).



<!-- CONTRIBUTING -->
## Contributing

Contributions are what make the open source community such an amazing place to be learn, inspire, and create. Any contributions you make are **greatly appreciated**.

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the Branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request



<!-- LICENSE -->
## License

Distributed under the MIT License.


<!-- CONTACT -->
## Contact

Najib IDZIM - najib.idzim@etu.uca.fr

Project Link: [https://github.com/naidzim/Camelot-Jr-solver](https://github.com/naidzim/Camelot-Jr-solver)



<!-- ACKNOWLEDGEMENTS -->
## Acknowledgements





<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[contributors-shield]: https://img.shields.io/github/contributors/othneildrew/Best-README-Template.svg?style=flat-square
[contributors-url]: https://github.com/othneildrew/Best-README-Template/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/othneildrew/Best-README-Template.svg?style=flat-square
[forks-url]: https://github.com/othneildrew/Best-README-Template/network/members
[stars-shield]: https://img.shields.io/github/stars/othneildrew/Best-README-Template.svg?style=flat-square
[stars-url]: https://github.com/othneildrew/Best-README-Template/stargazers
[issues-shield]: https://img.shields.io/github/issues/othneildrew/Best-README-Template.svg?style=flat-square
[issues-url]: https://github.com/othneildrew/Best-README-Template/issues
[license-shield]: https://img.shields.io/github/license/othneildrew/Best-README-Template.svg?style=flat-square
[license-url]: https://github.com/othneildrew/Best-README-Template/blob/master/LICENSE.txt
[linkedin-shield]: https://img.shields.io/badge/-LinkedIn-black.svg?style=flat-square&logo=linkedin&colorB=555
[linkedin-url]: https://linkedin.com/in/othneildrew
[product-screenshot]: images/screenshot.png
