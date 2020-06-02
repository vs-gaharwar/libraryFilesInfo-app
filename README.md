# libraryFilesInfo-app
Target architecture information of all library files' in a folder  

                                                 -------INTRODUCTION----------
Different computing devices use different CPU architectures, which in turn support different instruction sets. 
Application Binary Interface (ABI) is different for each combination of CPU and instruction set.
This program determines the total number of libraries present in a folder and its subfolders and architecture of each library.
Libraries can be of the following architecture type:
	armeabi: compiled code for all ARM based processors only
	armeabi-v7a: compiled code for all ARMv7 and above based processors only
	arm64-v8a: compiled code for all ARMv8 arm64 and above based processors only 
	x86: compiled code for x86 processors only
	x86_64: compiled code for x86_64 processors only 
	mips: compiled code for MIPS processors only.

                                 ------BRIEF EXPLANATION ABOUT THE SOURCE CODE/ALGORITHM------

1. Check for given path 
	a. if it's a directory, recursively check files inside it reading directory file info using dirent.h
	b. if it's an elf file (library file), check for machine architecture reading elf file info using elf.h
2. Used dirent.h for reading directory files: 
	https://code.woboq.org/userspace/glibc/dirent/dirent.h.html
3. Used elf.h (ELF: Executable and Linkable Format) for reading library files: 
	https://code.woboq.org/userspace/glibc/elf/elf.h.html
	
#TESTING ENVIRONMENT: Linux OS - Kernel-5.4.0-26-generic

                                               -------COMPILATION STEPS-------
1. g++ fileCh.cpp										//compile 
2. ./a.out											//run binary
3. Input::	Insert path: <insert path here> 
4. Ouutput:: Total number of library files in a folder & their target architecture 
