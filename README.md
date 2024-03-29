# WSJTXHelper
WSJXTHelper : Help WSJTX Calling CQ for long distances and high power.

I wrote this program to solve two problems i had using WSJTX in trying to get a QSO with Alaska :

1) When I Call CQ, if the "EnableTX" button is still checked within the 2 seconds of the end of the frame, 
   users that reply to me changes my configuration so that WSJTX will reply to them instead of continuing 
   my call to Alaska at next transmission period. 
   That was anoying... 
   Sorry for them, but I'm calling Alaska and I don't want to reply to them at this time.

2) I'm using a Diamond CP-6S antenna, witch is supposed to be powered with only 40W in digital modes (FT8, FT4, MSK144, ...)
   But I need more pover to be heard in Alaska. At least 80W...
   So, during my calls, I want to set power to 80W, and to prevent antenna damage, 
   i want to transmit only one 15s frame by minute instead of two. 

To do this, i was constantly disabling transmission two seconds before the end of the frame, 
waiting 45 seconds, before Enabling TX again for 13 seconds. This was very anoying...

So, I wrote this WSJTXHelper program to do this automatically.

How to use WSJTXHelper :

Start WSJTX and WSJTXHelper program.

In WSJTX :
  Check or uncheck the "even/1st" check box so that your CQ will be done during even/1st period if you beam to East or South,
  or Uncheck it if you beam to West or North.

  Prepare your CQ message: 
    CQ AK F4LAA JN38

In WSJTXHelper (having WSJTX visible on your screen) :

  1) Check the "even/1st" check box in the same way you check/uncheck the identical checkbox in WSJTX.

  2) Click the "Calibrate" button to teach WSJTXHelper where the "EnableTX" button is in WSJTX.
     Right click on "EnableTX" in WSJTX window (this will not start transmission) .
     You have 5 seconds to do so.
     If you don't do it in time, you will get a KO message saying that calibration fail.

  3) When calibration is done, WSJTXHelper memorize the "Enable TX" button position, 
     and the "Start" button becomes enabled.

  4) Check the "Only 1 CQ / mn" checkbox if you want to transmit only 1 frame by minutes (instead of 2).

  5) Click the "Start" button.
     WSJTXHelper will synchronize itself on the current time.
     At time 0s and 30s (if even/1st is checked), or at time 15s and 45s (if even/1st is unchecked)
     il will automatically click the "EnableTX" button in WSJTX (this starts the transmission)
     then, 3 seconds later, it will click it again, disabling next transmission (but current transmission continues to run), 
     and preventing responders to change your current calling configuration in WSJTX.
     if you have "Only 1 CQ / mn" checked, it will not click "EnableTX" at time 30s and 45s, 
     so you will send only one frame by minute instead of two.

As WSJTXHelper relies on mouse move/click events, WSJTX should always be visible for this process to work.

This project was compiled using VisualStudio 2015, 
and the source code is in C++ language (to be able to easily access "win32" and "user" Windows DLLs).
The executable WSJTXHelper.exe is located in the "Debug" directory.

V1.1 2024/01/28 :
  Added the "Prevent Auto Reply" checkbox. When it is checked, the program act as in V1.0 
  and uncheck the "Enable TX" in WSJTX 3s after checking it.
  But if you unchecked it, it will leaves the "Enable TX" button checked so that replies to your call will be normally managed by WSJTX.

  Save window position, checkboxes state, and calibration in Windows registries.

  The version V1.1 was compiled using VisualStudio 2015 - Update3, 
  and the executable WSJTXHelper.exe is now located in the "x64/Debug" directory.


