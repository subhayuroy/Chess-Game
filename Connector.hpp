#ifndef CONNECTOR_H
#define CONNECTOR_H

#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <string>

STARTUPINFO sti = {0};
SECURITY_ATTRIBUTES sats ={0};
PROCESS_INFORMATION pi ={0};
HANDLE pipin_w, pipin_r, pipout_w, pipout_r;
BYTE buffer[2048];
DWORD writ, excode, read, available;

void ConnectorToEngine(char* path)
{
    pipin_w = pipin_r = pipout_w = pipout_r = NULL;
    sats.nLength = sizeof(sats);
    sats.bInheritHandle = TRUE;
    sats.lpsecurityDescriptor = NULL;

    CreatePipe(&pipout_r, &pipout_w, &sats,0);
    CreatePipe(&pipin_r, &pipin_w, &sats,0);

    sti.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTHANDLES;
    sti.wShowWindow = SW_HIDE;
    sti.hStdInput = pipin_r;
    sti.hStdOutput = pipout_w;
    sti.hStdError = pipout_w;

    CreateProcess(NULL, path, NULL, NULL, TRUE, 0, NULL, NULL, &sti, &pi);
}


#endif CONNECTOR_H