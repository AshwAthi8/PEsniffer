# PE file Structure
Every operating system has respective file structures which are built and developed as per the requirement. Ever since the beginning of Microsoft Windows, there have been many updates for the file structure evolving from DOS, NE, LX to the current  PE structure. We will be dealing here with PE structure.

PE stands for **Portable Executable**.  This is the standard file structure used in windows operating systems. This structure is adopted for DLLs(32bit and 64bit), windows executables, .NET executables and few more. 

### The Basic Structure

Every PE has a DOS header, then comes the PE headers followed by the section table. Then section headers for each section. These sections include .text , .bss, .rdata., .data,  .rsc,.idata, .edata .debug, and .pdata. It's not necessary that all these sections have to be present. 

![Structure 1](https://github.com/AshwAthi8/PEsniffer/blob/master/PE_File_Structure/images/pe1.png)

This DOS headers is to make sure a backward compatibility to MS-DOS. If the program runs on MS-DOS then it will run and print that this is not for MS-DOS mode program and exit without any errors. Its 64 BYTES long


![Structure 2] (https://github.com/AshwAthi8/PEsniffer/blob/master/PE_File_Structure/images/pe2.png)

DOS header is a predefined structure of windows with the following members:


[!DOS header members](link)
