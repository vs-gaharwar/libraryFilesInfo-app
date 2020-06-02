# include <iostream>
# include <string>
# include <unordered_map> 
# include <dirent.h>
# include <elf.h>

using namespace std;

unordered_map<string, string> libDB;

string elf_check_file(Elf32_Ehdr* hdr) {
	string archType;
	if (!hdr) return archType;
	if (hdr->e_ident[EI_MAG0] != ELFMAG0 || hdr->e_ident[EI_MAG1] != ELFMAG1 || hdr->e_ident[EI_MAG2] != ELFMAG2 || hdr->e_ident[EI_MAG3] != ELFMAG3)
		return archType;
	
	if(hdr->e_ident[EI_CLASS]==ELFCLASSNONE || hdr->e_ident[EI_DATA]==ELFDATANONE)	return archType;
	
	if(hdr->e_ident[EI_DATA]==ELFDATA2MSB)
	{	
		hdr->e_type=((hdr->e_type)>>8)|((hdr->e_type)<<8);
		hdr->e_machine=((hdr->e_machine)>>8)|((hdr->e_machine)<<8);
	}
	
	if(hdr->e_type!=ET_DYN)	return archType;	
	
	if(hdr->e_machine==EM_386)	archType="x86";
	else if(hdr->e_machine==EM_X86_64)	archType="x86_64";
	else if(hdr->e_machine==EM_QDSP6)	archType="armeabi";
	else if(hdr->e_machine==EM_ARM)	archType="armeabi-v7a";
	else if(hdr->e_machine==EM_AARCH64)	archType="armeabi-v8a";
	else if(hdr->e_machine==EM_MIPS || hdr->e_machine==EM_MIPS_RS3_LE)	archType="mips";
	
	return archType;
}

void find_directory_files(string dirPath)
{
	DIR *dir;
	if(!(dir=opendir(dirPath.c_str())))	return;
	
	struct dirent *dirRead;
	FILE *fp;
	Elf32_Ehdr header;
	while((dirRead=readdir(dir)))
	{
		string filePath = dirPath+"/"+dirRead->d_name;
		if(dirRead->d_type==DT_REG)
		{	
			if((fp=fopen(filePath.c_str(), "r")))
			{
				fread(&header, 1, sizeof(header), fp);
				string archType = elf_check_file(&header);
				if(!archType.empty())	libDB[filePath]=archType;
				fclose(fp);
			}
		}
		else if(dirRead->d_type==DT_DIR)
		{	
			
			if(!(!(string(dirRead->d_name)).compare(".") || !(string(dirRead->d_name)).compare("..")))
				find_directory_files(filePath);
		}
	}
	closedir(dir);
}

int main()
{
	string dirPath;
	cout << "Insert path: ";
	cin >> dirPath;
	
	libDB.clear();
	
	find_directory_files(dirPath);
	
	cout<<"Total number of libraries:  "<<libDB.size()<<endl; 
	unordered_map<string, string>::iterator it=libDB.begin();
	if(libDB.size()>0)
	{
		cout<<"File ArchType"<<endl;
		cout<<"==== ==========="<<endl;
	}		
	while(it!=libDB.end())
	{
		cout<<it->first<<"  "<<it->second<<endl;
		it++;
	}
	
	return 0;
}
