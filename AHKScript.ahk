#NoEnv  ; Recommended for performance and compatibility with future AutoHotkey releases.
; #Warn  ; Enable warnings to assist with detecting common errors.
SendMode Input  ; Recommended for new scripts due to its superior speed and reliability.
SetWorkingDir %A_ScriptDir%  ; Ensures a consistent starting directory.

^+j::
SoundSet, +5
return

^+k::
SoundSet, -5
return

^+h::
Send {Media_Next}
return

^+g::
Send {Media_Prev}
return

^+f::
Send {Media_Play_Pause}
return

^+1::
run, firefox.exe
return

^+2::
run, C:\Users\Jake Harrison\AppData\Roaming\Microsoft\Windows\Start Menu\Programs\Discord Inc\Discord.lnk
return

^+3::
run, C:\Users\Jake Harrison\AppData\Roaming\Microsoft\Windows\Start Menu\Programs\Steam\Steam.lnk
return