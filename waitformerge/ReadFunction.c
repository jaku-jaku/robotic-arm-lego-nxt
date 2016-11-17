

bool readPoints(Point [] p, int index, int & count) {
	float nextRead = 0;
	float currX, currY, currZ;

	ReadFloat(hFileHandle, nIOResult, nextRead);
	currX = nextRead;

	ReadFloat(hFileHandle, nIOResult, nextRead);
	currY = nextRead;

	ReadFloat(hFileHandle, nIOResult, nextRead);
	currZ = nextRead;

	if (currX < xMIN || currX > xMAX || currY < yMIN || currY > yMAX
			|| currZ < zMIN || currZ > zMAX) {

		return false;
	}

	else  {
		p[i].x = currX; p[i].y = currY; p[i].z = currZ;
		return true;
	}

}

const int MAX = 30;

Point filePoints[MAX];

task main() {

	typedef struct {
		float x;
		float y;
		float z;
	} Point;

	TFileHandle   hFileHandle;              // will keep track of our file
  TFileIOResult nIOResult;                // will store our IO results
  string        sFileName = "test.txt";   // the name of our file
  int           nFileSize;                //will store our file size

 	OpenRead(hFileHandle, nIOResult, nFileSize, sFileName);

 	Point filePoints[MAX];

 	// make read points functtion first ....

 	readPoints(filePoints, i, cnt);

 	Close(hFileHandle, nIOResult);



}
