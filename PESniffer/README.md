# PE file Structure
Every operating system has respective file structures which are built and developed as per the requirement. Ever since the beginning of Microsoft Windows, there have been many updates for the file structure evolving from DOS, NE, LX to the current  PE structure. We will be dealing here with PE structure.
PE stands for **Portable Executable**.  This is the standard file structure used in windows operating systems. This structure is adopted for DLLs(32bit and 64bit), windows executables, .NET executables and few more. 
### The Basic Structure
Every PE has a DOS header, then comes the PE headers followed by the section table. Then section headers for each section. These sections include .text , .bss, .rdata., .data,  .rsc,.idata, .edata .debug, and .pdata. It's not necessary that all these sections have to be present. 
![Structure 1](https://github.com/AshwAthi8/PEsniffer/blob/master/PE_File_Structure/images/pe1.png)
This DOS headers is to make sure a backward compatibility to MS-DOS. If the program runs on MS-DOS then it will run and print that this is not for MS-DOS mode program and exit without any errors. Its 64 BYTES long
<div align="center">
<img src="https://github.com/AshwAthi8/PEsniffer/blob/master/PE_File_Structure/images/pe2.png" width="450" height="700">
</div>

DOS header is a predefined structure of windows with 19 members. 
### DOS header members:

```
e_magic
e_cblp
e_cp
e_crlc
e_cparhdr
e_minalloc
e_maxalloc
e_ss
e_sp
e_csum
e_ip
e_ip
e_ifarlc
e_ovna
e_res
e_oemid
e_oeminfo
e_res2
e_lfanew
```

Out of these, the important ones are e_magic and e_lfanew. 
Magic part has the letters MZ (Mark Zbikowsky) which is the MS-DOS header and ifanew contains the offset to PE header with respect to the file.

PE header
It is again a structure defined as below:

```
 IMAGE_NT_HEADERS STRUCT {
	Signature
	FileHeader
	OptionalHeader
}
```

Signature contains 4 bytes  PE followed by two terminating zeros.
File header is again a structure

```
IMAGE_FILE_HEADER_STRUCT{
Machine
NumberOfSections
TimeDateStamp
PointerToSymbolTable
NumberOfSymbols
SizeOfOptionalHeader
Characteristics
}
```
These all are mainly the physical layout of file, filling 20 bytes of the PE file.
OptionalHeader is the next 224 bytes

```
IMAGE_OPTIONAL_HEADER_STRUCT {
  Magic
  MajorLinkerVersion
  MinorLinkerVersion
  SizeOfCode
  SizeOfInitializedData
  SizeOfUninitializedData
  AddressOfEntryPoint
  BaseOfCode
  BaseOfData
  ImageBase
  SectionAlignment
  FileAlignment
  MajorOperatingSystemVersion
  MinorOperatingSystemVersion
  MajorImageVersion
  MinorImageVersion
  MajorSubsystemVersion
  MinorSubsystemVersion
  Win32VersionValue
  SizeOfImage
  SizeOfHeaders
  CheckSum
  Subsystem
  DllCharacteristics
  SizeOfStackReserve
  SizeOfStackCommit
  SizeOfHeapReserve
  SizeOfHeapCommit
  LoaderFlags
  NumberOfRvaAndSizes
  DataDirectory
}
```

Identifies the state of the image file, whether its is:
- normal executable - 0x10b
- ROM image 0x107
- PE32+  0X20B
The functionality of Most the members can be interpreted from their names itself such as major and minor linker version. ```SizeOfCode``` is basically ther size of the Code section, similarly there is ```SizeOfInitializedData``` and ```SizeOfUninitializedData(BSS)```. ```AddressOfEntryPoint``` is with respect to the image base when its loaded in the memory. 
```BaseOfCode``` and ```BaseOfData``` are the addresses relative to the image base of the beginning-of-code section and beginning-of-data section When loaded in memory. 
```ImageBase``` is the preferred address of the image’s starting byte when loaded in the memory.(Mostly 0x400000)
There are two alignments taking place which are Section and file alignment. One alignment is for the executable present in the memory and other one is for the file present on the disk. 

The Next Important is the Last member of the struct, that is DataDirectory. 
```
IMAGE_DATA_DIRECTORY_STRUCT {
  DWORD VirtualAddress
  DWORD Size
}
```

There are various directories with these two values including the ones for Export, Import, Resource, debug, TLS and more. 
