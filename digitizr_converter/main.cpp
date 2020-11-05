#include <assimp\Importer.hpp>
#include <assimp\Exporter.hpp>
#include <assimp\postprocess.h>
#include <iostream>
#include <windows.h>
#include "file_handler.h"

int main(){	

	std::string ending; //Contains the file-format ending
	int output = 0; //Output-Mode (0-9)

	std::string fileformat_output[10] = {".dae", ".x", ".stp",".obj",".stl",".stl",".ply",".ply",".3ds", ".json"};

	std::string filename = getDigitizrFile();

	Assimp::Importer Importer;
	const aiScene* aiscene = Importer.ReadFile(filename.c_str(), aiProcess_JoinIdenticalVertices |
		aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_SortByPType | aiProcess_Triangulate);

	std::string str = Importer.GetErrorString();

	if (!aiscene) {
		printf("Error parsing '%s': '%s'\n", filename.c_str(), Importer.GetErrorString());
		return false;
	}

	std::cout << "Select your output format: ";
	std::cin >> output;

	ending = fileformat_output[output];

	Assimp::Exporter exporter;
	const aiExportFormatDesc* format = exporter.GetExportFormatDescription(output); //.obj
	
	std::string path = getSaveDirectory(ending);

	std::cout << "Choosen output-path: " << path << std::endl;

	std::string output_name;

	std::cout << "output file name [without fileformat ending!]: ";
	std::cin >> output_name;

	path = path + "\\" + output_name + ending;
	std::cout << "Output-Filelocation: " << path << std::endl;
	aiReturn ret = exporter.Export(aiscene, format->id, path, 0);
	std::cout << exporter.GetErrorString() << std::endl;

	system("pause");
	return EXIT_SUCCESS;
}