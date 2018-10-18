# Releases:
# v1.1:
+ Moved dump folder to ux0:PSM/TitleID/RW/Temp instead of ux0:PSM/TitleID/RW/Documents/Application (This acturally improves compadibility for some reason)  
+ Improved memory usage in the dumper itself, - improved directory walking and copy method can now handle larger files.  
+ Both these changes fixes an issue with dumping Large PSM games (eg: Cytus Lambda) fixes Issue #1  
Download: https://bitbucket.org/SilicaAndPina/fuckpsse/downloads/FuckPSSEv1.1.suprx  
# v1.0
Inital Release.  
Download: https://bitbucket.org/SilicaAndPina/fuckpsse/downloads/FuckPSSE.suprx  
  
# FuckPSSE  

To install:  
    This plugin installs under \*ALL  
    (\*ALL is the only way to attach to the runtime)
    
when you run a PSM game, the screen will go RED.. While the screen is RED. the game files are being dumped  
  
There is no progess indicaton (doing pretty much anything requires aditional DLL's that the game might not have)  
  
however. once it is done, the screen will go GREEN at this point you can close out of the game.  
and look in the ux0:/PSM/<TITLEID>/Temp folder and there will be a complete (Now decrypted) mirror of the Application/ folder.  
  
Games decrypted can be run on PC using the PSM Simulator found in the PSM SDK, simply drag n drop app.exe onto psm.exe and play!
  
What this will enable:  
1) PSM Game/Application Modding  
2) Inspecting PSM Game/Application files  
3) Running retail PSM Games/Applications in the PSM Simulator  
4) Reverse Engineering of PSM Games/Applications  
5) Probably more things too  
6) Run Retail PSM Games in the PSM Developer App (LOL)  
  
What this will NOT enable  
1) Vita Game Emulation (no. j-just stop the simulator isnt even emulating anything)  
2) Running PSM games you dont have a license for (dumper requires you to *RUN* the game in the first place!)  
3) PSM Dev or PSM Unity applications.  
  
Credits:  
Main Developer: SilicaAndPina  
PSM_Handle Help: [DOTS_TB](https://twitter.com/dots_tb)  
Biggest Tester: [@FUCK_S3CURITY](https://twitter.com/FUCK_S3CURITY)  