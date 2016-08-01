#include "../MaxRectsBinPack.h"
#include "../ShelfBinPack.h"
#include "../SkylineBinPack.h"
#include "../Rect.h"
#include <cstdio>
#include <iostream>
#include <vector>


int main(int argc, char **argv)
{
	if (argc < 5 || argc % 2 != 1)
	{
		printf("Usage: MaxRectsBinPackTest binWidth binHeight w_0 h_0 w_1 h_1 w_2 h_2 ... w_n h_n\n");
		printf("       where binWidth and binHeight define the size of the bin.\n");
		printf("       w_i is the width of the i'th rectangle to pack, and h_i the height.\n");
		printf("Example: MaxRectsBinPackTest 256 256 30 20 50 20 10 80 90 20\n");
		return 0;
	}

	using namespace rbp;
	using namespace std;

	int minH = 999999999;

	// Create a bin to pack to, use the bin size from command line.
	int binWidth = atoi(argv[1])-3;
	int binHeight = atoi(argv[2])-3;

	std::vector<RectSize> originales;
	for(int i = 3; i < argc; i += 2){
		// Read next rectangle to pack.
		int rectWidth = atoi(argv[i])+3;
		int rectHeight = atoi(argv[i+1])+3;

		RectSize r = {rectWidth, rectHeight};
		originales.push_back(r);
  }

{
  // ------------ MAX RECTS BINPACK ---------------
  int maxH = 0;
	bool failed = false;

	std::vector<RectSize> mR = originales;
	std::vector<Rect> dest;

	MaxRectsBinPack bin;
	bin.Init(binWidth, binHeight);
	bin.Insert(mR, dest, MaxRectsBinPack::RectBottomLeftRule);

  std::cout << " ------------- MAXRECTSBINPACK" << std::endl;
  for(std::vector<Rect>::iterator it=dest.begin(); it!=dest.end(); it++){
		Rect packedRect = *it;
		if (packedRect.height > 0) {
			printf("Packed to (x,y)=(%d,%d), (w,h)=(%d,%d)\n", packedRect.x, packedRect.y, packedRect.width, packedRect.height);
			if(packedRect.y+packedRect.height > maxH){
				maxH = packedRect.y + packedRect.height;
			}
	  } else {
			printf("*** No pude colocar (%d,%d)", packedRect.width, packedRect.height);
			failed = true;
			break;
		}
	}
	if(mR.size() != 0) failed = true;

  if(!failed){
		std::cout << "///// MAXRECTSBINPACK " << maxH << std::endl;

		if(minH > maxH){
			minH = maxH;
		}
	} else {
		std::cout << "///// MAXRECTSBINPACK NO PUDO COLOCAR //////" << std::endl;
	}
}

{
	std::cout << " ------------- SHELF BIN PACK" << std::endl;
	int maxH = 0;
	bool failed = false;

	ShelfBinPack bin;
	bin.Init(binWidth, binHeight, true);

	for(std::vector<RectSize>::iterator it=originales.begin(); it!=originales.end(); it++){
		// Perform the packing.
		ShelfBinPack::ShelfChoiceHeuristic heuristic = ShelfBinPack::ShelfBestHeightFit;
		Rect packedRect = bin.Insert((*it).width, (*it).height, heuristic);

		// Test success or failure.
		if (packedRect.height > 0) {
			printf("Packed to (x,y)=(%d,%d), (w,h)=(%d,%d).\n", packedRect.x, packedRect.y, packedRect.width, packedRect.height);
			if(packedRect.y+packedRect.height > maxH){
				maxH = packedRect.y + packedRect.height;
			}
		} else {
			failed = true;
			break;
			//printf("Failed! Could not find a proper position to pack this rectangle into. Skipping this one.\n");
		}
  }

	if(!failed){
		std::cout << "///// SHELF BIN PACK " << maxH << std::endl;
		if(maxH < minH){
			minH = maxH;
		}
	} else {
		std::cout << "///// SHELF BIN PACK NO PUDO COLOCAR /////" << std::endl;
	}
}

{
  int maxH = 0;
	bool failed = false;

	std::vector<RectSize> mR = originales;
	std::vector<Rect> dest;

  std::cout << " ------------- SKYLINE PACK" << std::endl;

	SkylineBinPack bin;
	bin.Init(binWidth, binHeight, true);


	SkylineBinPack::LevelChoiceHeuristic heuristic = SkylineBinPack::LevelBottomLeft;
	bin.Insert(mR, dest, heuristic);

	for(std::vector<Rect>::iterator it=dest.begin(); it!=dest.end(); it++){
		Rect packedRect = *it;
		if (packedRect.height > 0) {
			printf("Packed to (x,y)=(%d,%d), (w,h)=(%d,%d)\n", packedRect.x, packedRect.y, packedRect.width, packedRect.height);
			if(packedRect.y+packedRect.height > maxH){
				maxH = packedRect.y + packedRect.height;
			}
	  } else {
			printf("*** No pude colocar (%d,%d)", packedRect.width, packedRect.height);
			failed = true;
			break;
		}
	}
  if(mR.size() != 0) failed = true;

	if(!failed){
		std::cout << "///// SKYLINE BIN PACK " << maxH << std::endl;
		if(maxH < minH){
			minH = maxH;
		}
	} else {
		std::cout << "///// SKYLINE BIN PACK NO PUDO COLOCAR /////" << std::endl;
	}
}

	printf("**** El mejor fue ALTO %d\n", minH);
}
