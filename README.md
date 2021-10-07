# Biometric Registration System Project

## Table of Contents
- [Introduction](#introduction)
- [Brief](#brief)
- [Method of Operation](#method-of-operation)
  * [Logging the Register Data on the Connected PC](#logging-the-register-data-on-the-connected-pc)
  * [Registering a Fingerprint](#registering-a-fingerprint)
  * [Setting up a Class](#setting-up-a-class)
  * [Registering Attendance](#registering-attendance)
- [Circuitry](#circuitry)
  * [Button Board](#button-board)
  * [Full Schematic](#full-schematic)
- [Case](#case)
- [Demonstration](#demonstration)
- [Further Work](#further-work)

## Introduction

I have just finished my first year of studying electronic engineering at university. I completed this project over the summer to learn how to do object oriented programming with an Arduino.


## Brief

This project is designed to record the attendance of students in lectures. The lecturer can set the day and module number for the lecture, before setting how long the register should remain open for. To register their attendance, students just need to scan their fingerprint as they enter the lecture theatre.

## Method of Operation

<p align="center">
 <img src="./Images/Registration Menu.gif" width="350" />
</p>


### Logging the Register Data on the Connected PC

- Install PuTTY on the PC

- Select the "Serial" connection type and enter the COM Port that the Arduino is connected to

<p align="center">
  <img src="./Images/PuTTY Session Settings 1.PNG" alt="PuTTY Session Settings 1" />
</p>


- Set it to log "All session output" and name the file 

<p align="center">
  <img src="./Images/PuTTY Session Settings 2.PNG" alt="PuTTY Session Settings 2" />
</p>


- Press the "Open" button when the Arduino is connected


### Registering a Fingerprint

- Select "Register Finger" 
- Type your student ID number 
- Scan your finger 

### Setting up a Class 

- Select "Set Up Class" 
- Scroll through and select the day of the week 
- Type the module number of the lecture 
- Select the time that the registration will remain open for 
- A lecturer must then scan their finger to open the register 

### Registering Attendance 

- Scan your finger and your attendance will be recorded

- The register will automatically close after the set time 


## Circuitry

### Button Board

This board allows the 3 navigation buttons to be read by 1 Analog input on the Arduino 

| <img src="./Images/Button PCB Schematic.PNG" alt="Button PCB Schematic" /> | <img src="./Images/Button PCB.PNG" alt="Button PCB" /> |
| ------------------------------------------------------------ | ------------------------------------------------------ |




### Full Schematic

<img src="./Images/Biometric Registration System Full Schematic FROM PDF.png" alt="Biometric Registration System Full Schematic" />

## Case

The .stl and .f3d files for this case are included in the repository. 

| <img src="./Images/Biometric Registration System Case 2.png" alt="Biometric Registration System Case" /> | <img src="./Images/Biometric Registration System Case 3.png" alt="Biometric Registration System Case" /> |
| ------------------------------------------------------------ | ------------------------------------------------------------ |

<img src="./Images/Biometric Registration System Case Layout.png" alt="Biometric Registration System Case Layout" />

| <img src="./Images/Case Front.jpg" alt="Case Front" /> | <img src="./Images/Case Internals.jpg" alt="Case Internals" /> |
| ------------------------------------------------------ | ------------------------------------------------------------ |

## Demonstration

[<img src="./Images/Demo Video Screenshot.PNG" alt="Demo Video" />](https://www.youtube.com/watch?v=rIEnxN8tB8w&t "Demo Video")

## Further Work

In the future I plan to add the following features;

- RFID card scanning
- Class pre-sets for the A, B, C & D buttons
- A serial interpreter program to log the serial data on the connected PC
- An online database to store the register files
- User names linked to the ID numbers
