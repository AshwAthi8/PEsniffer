# PE file Structure
Every operating system has respective file structures which are built and developed as per the requirement. Ever since the beginning of Microsoft Windows, there have been many updates for the file structure evolving from DOS, NE, LX to the current  PE structure. We will be dealing here with PE structure.
PE stands for **Portable Executable**.  This is the standard file structure used in windows operating systems. This structure is adopted for DLLs(32bit and 64bit), windows executables, .NET executables and few more. 
### The Basic Structure
Every PE has a DOS header, then comes the PE headers followed by the section table. Then section headers for each section. These sections include .text , .bss, .rdata., .data,  .rsc,.idata, .edata .debug, and .pdata. It's not necessary that all these sections have to be present. 
![Structure 1](https://github.com/AshwAthi8/Sniffer/blob/master/PESniffer/images/pe1.png)
This DOS headers is to make sure a backward compatibility to MS-DOS. If the program runs on MS-DOS then it will run and print that this is not for MS-DOS mode program and exit without any errors. Its 64 BYTES long
<div align="center">
<img src="https://github.com/AshwAthi8/Sniffer/blob/master/PESniffer/images/pe2.png" width="450" height="700">
</div>

[comment]: <> [title](./images/pe2.png)


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

Out of these, the important ones are 
- e_magic - the letters MZ (Mark Zbikowsky) which is the MS-DOS header

- e_lfanew - contains the offset to PE header with respect to the file.


### PE headers
It is again a structure defined as below:

```
 IMAGE_NT_HEADERS STRUCT {
	Signature
	FileHeader
	OptionalHeader
}
```

- Signature contains 4 bytes  PE followed by two terminating zeros.
```
50 45 00 00
```

- File header is again a structure: 

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

These all are mainly the physical layout of file, filling `120 bytes` of the PE file.

- `Machine` basically tells the targetted machine for that executable.
- `NumberofSections` this is an important parameter. Incase if any section is added/deleted then Corresponding changes must be made here too.
- `Characteristics` - This contains few important details, such as flags to know whether the file is a DLL or an exe.


#### OptionalHeader 
It is the next `224 bytes`. 

It has lot of details...

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

- `Magic` Identifies whether its is:
  - PE32 - 0x10b
  - ROM image - 0x107
  - PE32+ (64 bit)  - 0X20B

- `major and minor linker version`, as the name suggests can be used to itentify the linker version. [such as visual studio version]

- `SizeOfCode` is basically ther size of the entire Code/Text section. 

- `SizeOfInitializedData` size of the whole initialised data - entire data section.
- `SizeOfUninitializedData(BSS)` size of the whole uninitialised data - entire .bss section.

- `AddressOfEntryPoint` is with respect to the image base when its loaded in the memory. Its basically the RVA of the first instruction to be executed. 
  - If the flow of the Instruction has to be altered from the start then this shall be changes. 
  - Incase in packers this will be pointing to the decompression stub then later on jump instruction to the original entry point.

- `BaseOfCode` is the offset to the starting of the code/text section from the imagebase.

- `BaseOfData` is the offset to the starting of the data section from the imagebase. [absent in PE 32+]

- `ImageBase` is the preferred address of the image’s starting byte when loaded in the memory.(Mostly 0x400000)

- `Alignment`
  - There are two alignments taking place which are `Section` and `file` alignment. 
  - `Section alignment` is for the executable present in the memory and  `file alignment` is for the file present on the disk. 

#### DataDirectory

The Next Important is the last member of the optional headers, that is DataDirectory. Its the last 128 bytes of the optional headers, having 16 structures, 8 bytes each.

```
IMAGE_DATA_DIRECTORY_STRUCT {
  DWORD VirtualAddress
  DWORD Size
}
```

The various directories with these two values includ Export directories, Import directories, Resource directories, debug directories, TLS and more. 
