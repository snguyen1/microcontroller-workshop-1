
HRI Researchers - Introduction to Microcontrollers and Environmental Sensing Workshop
================================
##### (scroll down to see instructions)
----
This repository contains the teaching material and other info associated with the "HRI Researchers - Introduction to Microcontrollers and Environmental Sensing Workshop" to be held on November 7, 2018 in HRI 127 at Texas A&M University - Corpus Christi.

#### If you will be participating in the November 7 workshop, you should prepare your laptop with the software that is needed before the event (instructions below). We will be using the “Arduino IDE” (IDE=integrated development environment), or for short, just “Arduino software”, which is freely available for Windows or Mac OS X (and Linux, too!).

Instructors/Contributors
-----------

- Michael van den Eijnden [[Github](https://github.com/mickel1138)]
- Michael S. Williamson [[Github](https://github.com/fightingtexasaggie)]
- Mark Besonen [[Github](https://github.com/verbage)]
- Mikell Smith
- Joe Holland [[Github](https://github.com/joevholland)]
- Son Nguyen [[Github](https://github.com/snguyen1)]

---

# Table of Contents

<!-- TOC -->
- [1.   Preparation before the Workshop](#preparation-before-the-workshop)
    - [1.1  Tutorial Download](#tutorial-download)
    - [1.2  Installation of Microcontroller Software and Drivers](#installation-of-microcontroller-software-and-drivers)
        - [a.   Mac OS](#for-mac-os)
        - [b.   Windows](#for-windows)

<!-- /TOC -->

# Preparation before the Workshop
If you are a workshop participant, please download the lesson material and follow the instructions to download and configure the Arduino software before heading to the workshop.
## Tutorial Download
---------------------

If you are not familiar with git, you can download the repository as a .zip file by clicking the green “Download” button in the upper right at the top of this page (https://github.com/snguyen1/microcontroller-workshop-1). 
![](images/github-download.png)

## Installation of Microcontroller Software and Drivers

### For Mac OS
Step 1— Download and install the Arduino software
- Visit https://www.arduino.cc/en/Main/Software and download the MacOS X version of the Arduino software installer.
- Install the software per the instructions at https://www.arduino.cc/en/Guide/MacOSX. Skip the last section of the installation instructions, i.e. the “Proceed with board specific instructions” portion.

Step 2— Open the Arduino Software
- Start up the Arduino software. The icon should be in your Applications folder; the Arduino icon looks like a white “Figure-8” on a blue-green background.

Step 3— Configure the Arduino Software
 
#### (Same for both windows and mac)

- Add the necessary libraries (libraries are like “drivers”) to let the Arduino software know how to communicate with the ESP32 microcontroller and components we will be using.
- To add support for the ESP32 microcontroller, click on Arduino -> Preferences (Mac) or File -> Preferences (Windows).
![](images/arduino-fig2.png)

- Paste “https://dl.espressif.com/dl/package_esp32_index.json” (without the quotes) into the blank space next to “Additional Boards Manager URLs:" then lick “OK” to return to the main Arduino software window.
![](images/arduino-fig3.png)

- Click on Tools -> Board: “Arduino/Genuine Uno” -> Boards Manager…. 
![](images/arduino-fig4.png)

- Type “esp32” (without the quotes) into the filter at the top of the Boards Manager dialog, and you should see an “esp32 by Espressif Systems” option appear.  Click on its “Install” button, and let the process run to completion.  Altogether it has to download about 150MB of additional data at this point so it will take several minutes. Click the "Close" button once the install is completed.
![](images/arduino-fig5.png)

- To add support for the various components we will be using, click on Tools -> Manage Libraries…
![](images/arduino-fig6.png)
- Type “adafruit” (without the quotes) into the filter at the top of the Library Manager dialog, and you should see many Adafruit options appear.
- Find and install the “Adafruit BME280 Library by Adafruit”, “Adafruit SSD1306 by Adafruit”, and “Adafruit Unified Sensor by Adafruit” libraries (similar to how you installed ESP32 microcontroller support in the previous step).
- Update the filter text to “rtclib”, and find and install the “RTClib by Adafruit” library.
- Click the “Close” button to return to the main Arduino software window.

### For Windows
Step 1— Download and install the Arduino software
- Visit https://www.arduino.cc/en/Main/Software and download the Windows version of the Arduino software installer depending on your system (Windows 7, 8 10, etc.).  Be sure to select the "Installer" version, not the "Zip" or "App" versions.
- Install the software per the instructions at https://www.arduino.cc/en/Guide/Window. Skip the last section of the installation instructions, i.e. the “Proceed with board specific instructions” portion.

Step 2— Open the Arduino software
- Start up the Arduino software. The installer should have left an Arduino icon on your desktop.
- After launching the software for the first time, you may see a Windows Security Alert dialog warning that “Windows Firewall has blocked some features of this program”.  If so, click the “Allow access” button for this alert so that the Arduino software can download additional components it needs for the workshop.

Step 3— Configure the Arduino software (see Step 3 for Mac OS or click [here](#same-for-both-windows-and-mac))

## If you run into problems…

If you run into problems, please visit either Mickel van den Eijnden or Michael Williamson in HRI 310, or Mark Besonen in HRI 215B, for a hand. Otherwise, congratulations, your computer is now ready for the microcontroller workshop!
