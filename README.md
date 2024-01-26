# WSJTXHelper
WSJXTHelper : Help WSJTX Calling CQ for long distances and high power.

I wrote this program to solve two problems i had using WSJTX in trying to get a QSO with Alaska :

1) When I Call CQ, if the "EnableTX" button is still checked within the 2 seconds of the end of the trame, 
   users that reply to me changes my configuration so that WSJTX will reply to them instead of continuing 
   my call to Alaska at next transmission period. 
   Than was anoying... 
   Sorry for them, but I'm calling Alaska and I don't want to reply to them.

2) I'm using a Diamond CP-6S antenna, witch is suppose to be powered with only 40W in digital modes (FT8, FT4, MSK144, ...)
   And I need more pover to be heard in Alaska. At least 80W...
   So, during my calls, I want to set Power to 80W, and to prevent antenna damage, 
   i want to transmit only one frame by minutes instead of two. 

To do this, i was constantly disabling transmission two seconds before the end of trame, 
wait 45 seconds, before Enabling TX again for 13 seconds. This was very anoying....

So, I wrote this program to do this automatically.

How to use WSJTXHelper :

Start WSJTX and this program.

In WSJTX :
  Check or uncheck the "even/1st" check box so that your CQ will be done during even/1st period if you beam to East or South,
  or Uncheck it if you beam to West or North.

  Prepare your CQ message: 
    CQ AK F4LAA JN38

In WSJTXHelper (having WSJTX visible on your screen) :

  1) Check the "even/1st" check box in the same way you check/uncheck the same checkbox in WSJTX.

  2) Click the "Calibrate" button to teach WSJTXHelper where the "EnableTX" button is in WSJTX.
     Right click on "EnableTX" in WSJTX window (this will not start transmission) .
     You have 5 seconds to do so.
     If you don't do it in time, you will get a KO message saying that calibration fail.

  3) When calibration is done, WSJTXHelper memorize the "Enable TX" button position, 
     and the "Start" button becomes enabled.

  4) Check the "Only 1 CQ / mn" checkbox if you want to transmit only 1 trame by minutes (instead of 2).

  5) Click the "Start" button.
     WSJTXHelper will synchronize itself on the current time.
     At time 0s and 30s (if even/1st is checked), or at time 15s and 45s (if even/1st is unchecked)
     il will automatically click the "EnableTX" button in WSJTX (this start transmission)
     then, 3 seconds later, it will click it again, disabling next transmission (but current transmission continue), 
     and preventing responders to change your current calling configuration.
     if you have "Only 1 CQ / mn" checked, it will not click "EnableTX" at time 30s and 45s, 
     so you will send only one trame by minute instead of two.

This project was compiled using VisualStudio 2015, 
and the source code is in C++ language (to be able to easily access "win32" and "user" Windows DLLs).


