
#include "makexml.h"

string str;

void makexml(string folder, string filename, string imgtype, string name, int width, int height, int xmin, int xmax, int ymin, int ymax) {
	string type = ".xml";
	ofstream outfile(folder + filename + type);
	str = "<annotation verified = \"yes\">\n\t<folder>"
		+ folder + "</folder>\n\t<filename>"
		+ filename + "</filename>\n\t<path>"
		+ folder + filename + imgtype + "</path>\n\t<source>\n\t\t<database>Unknown</database>\n\t</source>\n\t<size>\n\t\t<width>"
		+ to_string(width) + "</width>\n\t\t<height>"
		+ to_string(height) + "</height>\n\t\t<depth>3</depth>\n\t</size>\n\t<segmented>0</segmented>\n\t<object>\n\t\t<name>"
		+ name + "</name>\n\t\t<pose>Unspecified</pose>\n\t\t<truncated>0</truncated>\n\t\t<difficult>0</difficult>\n\t\t<bndbox>\n\t\t\t<xmin>"
		+ to_string(xmin) + "</xmin>\n\t\t\t<ymin>"
		+ to_string(ymin) + "</ymin>\n\t\t\t<xmax>"
		+ to_string(xmax) + "</xmax>\n\t\t\t<ymax>"
		+ to_string(ymax) + "</ymax>\n\t\t</bndbox>\n\t</object>\n</annotation>\0\0";

	const char* buffer = str.c_str();
	outfile.write(buffer, str.size());
	char line[700]; // 한 줄씩 읽어서 임시로 저장할 공간
	if (outfile.is_open())
	{
	}
	outfile.close();

	return;
}