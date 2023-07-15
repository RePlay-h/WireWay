# __WireWay__
![Static Badge](https://img.shields.io/badge/C%2B%2B-v20-red?labelColor=gray&color=orange) ![Static Badge](https://img.shields.io/badge/Qt-v6.5.2-blue?color=green)

__WireWay__  - this application is part of the WireWay software system, allowing the user to connect to and interact with currently active contacts.

<br/>
<br/>

## __Build__
---
__Before building, make sure you have the right version of the language and Qt__ 

```cmd
mkdir build 
cd build
cmake ..
cmake --build .
```

<br/>
<br/>

## __Specification__
---

This application allows the user to view current contacts and connect to them. That is, the user can safely control the computer of the selected contact.

___P.s. The contact knows that his screen is being watched and can stop broadcasting at any time.___

<br/>

The program converts keystrokes on the keyboard, mouse clicks and mouse movements into various COMMAND packets and sends them. The program also processes incoming SCREEN packets, which store a JPEG image of the contact screen

## __Extra__
---
Description of package functions can be found [___here___](https://github.com/RePlay-h/WireWay-packets)
