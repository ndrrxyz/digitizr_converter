
#include <iostream>
#include <windows.h>
#include <string>
#include <shlobj.h>
//#include <sstream>


std::string getDigitizrFile(){
	char filename_ply[MAX_PATH];

	OPENFILENAME ofn;
	ZeroMemory(&filename_ply, sizeof(filename_ply));
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;  // If you have a window to center over, put its HANDLE here
	ofn.lpstrFilter = "Polygon File Format\0*.ply\0Any File\0*.*\0";
	ofn.lpstrFile = filename_ply;
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrTitle = "Digitizr Converter - Select a File.";
	ofn.Flags = OFN_DONTADDTORECENT | OFN_FILEMUSTEXIST;

	
	
	
	if (GetOpenFileNameA(&ofn))
	{
		std::cout << "You choose the file \"" << filename_ply << "\"\n";
	}
	else
	{
		switch (CommDlgExtendedError())
		{
		case CDERR_DIALOGFAILURE:	std::cout << "CDERR_DIALOGFAILURE\n";   break;
		case CDERR_FINDRESFAILURE:	std::cout << "CDERR_FINDRESFAILURE\n";  break;
		case CDERR_INITIALIZATION:	std::cout << "CDERR_INITIALIZATION\n";  break;
		case CDERR_LOADRESFAILURE:	std::cout << "CDERR_LOADRESFAILURE\n";  break;
		case CDERR_LOADSTRFAILURE:	std::cout << "CDERR_LOADSTRFAILURE\n";  break;
		case CDERR_LOCKRESFAILURE:	std::cout << "CDERR_LOCKRESFAILURE\n";  break;
		case CDERR_MEMALLOCFAILURE: std::cout << "CDERR_MEMALLOCFAILURE\n"; break;
		case CDERR_MEMLOCKFAILURE:	std::cout << "CDERR_MEMLOCKFAILURE\n";  break;
		case CDERR_NOHINSTANCE:		std::cout << "CDERR_NOHINSTANCE\n";     break;
		case CDERR_NOHOOK:			std::cout << "CDERR_NOHOOK\n";          break;
		case CDERR_NOTEMPLATE:		std::cout << "CDERR_NOTEMPLATE\n";      break;
		case CDERR_STRUCTSIZE:		std::cout << "CDERR_STRUCTSIZE\n";      break;
		case FNERR_BUFFERTOOSMALL:	std::cout << "FNERR_BUFFERTOOSMALL\n";  break;
		case FNERR_INVALIDFILENAME: std::cout << "FNERR_INVALIDFILENAME\n"; break;
		case FNERR_SUBCLASSFAILURE: std::cout << "FNERR_SUBCLASSFAILURE\n"; break;
		default: std::cout << "You cancelled.\n";
		}
	}


	return filename_ply;
}

static int CALLBACK BrowseCallbackProc(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData)
{

	if (uMsg == BFFM_INITIALIZED)
	{
		std::string tmp = (const char *)lpData;
		std::cout << "fileending: " << tmp << std::endl;
		SendMessage(hwnd, BFFM_SETSELECTION, TRUE, lpData);
	}

	return 0;
}

std::string getSaveDirectory(std::string saved_path){
	std::string ret;

	TCHAR path[MAX_PATH];

	const char * path_param = saved_path.c_str();

	BROWSEINFO bi = { 0 };
	bi.lpszTitle = ("Browse for folder...");
	bi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE;
	bi.lpfn = BrowseCallbackProc;
	bi.lParam = (LPARAM)path_param;

	LPITEMIDLIST pidl = SHBrowseForFolder(&bi);

	if (pidl != 0)
	{
		//get the name of the folder and put it in path
		SHGetPathFromIDList(pidl, path);

		//free memory used
		IMalloc * imalloc = 0;
		if (SUCCEEDED(SHGetMalloc(&imalloc)))
		{
			imalloc->Free(pidl);
			imalloc->Release();
		}

		return path;
	}


	return ret;
}

int* getOutput(int arr[]){
	int outputs[7];




	return outputs;
}