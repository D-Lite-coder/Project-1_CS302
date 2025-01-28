//Student Names: David Carpenter and Michael Batchelor
//David NetID:
//David StudentID:
//Michael NetID: mbatche1
//Michael StudentID: 000663958

#include <iostream>
#include <map>
#include <sstream>
#include <fstream>

using namespace std;

string replaceUnderscores(string str) {

  for (size_t i = 0; i < str.length(); ++i) {
	          if (str[i] == '_') str[i] = ' ';
	
  }
      return str;
}

int timeToSec(string timestr) {

	int min, sec;

	char colon;//ignored, used to simplify the stringstream

	istringstream ss(timestr);

	ss >> min >> colon >> sec;

	return min * 60 + sec;
}

string secToTime(int time)
{
	int min, sec;
	
	min = time / 60;
	sec = time % 60;

	return to_string(min) + ":" + (sec < 10 ? "0" : "") + to_string(sec);
}


int main(int argc, char *argv[]) {

	if(argc != 2) {

		cerr << "Usage: " << argv[0] << " <filename>" << endl;
		return 0;

	}

	int timeInSec, track;

	string line;

	string title, time, artist, album, genre;
	
    map<string, int> songs; //Song title + Duration in sec
	map<string, map<int, string>> albums; //Album title + (Track number + Song title)
	map<string, map<string, int>> artists; //Artist name + (Album + Total time)

	//storing the data into maps enables the use of iterators 
	map<int, string>::iterator songIt;
	map<string, int>::iterator albumIt;
	map<string, map<string, int>>::iterator artistIt;

	ifstream file(argv[1]);

	if (!file) {

		cerr << "Error opening file: " << argv[1] << endl;
		return 0;
	}

	
		while (file >> title >> time >> artist >> album >> genre >> track) {//stores all of the formatted data into their relevant maps
	
		title = replaceUnderscores(title);
		artist = replaceUnderscores(artist);
		album = replaceUnderscores(album);
		genre = replaceUnderscores(genre);

		timeInSec = timeToSec(time);

		songs[title] = timeInSec;
		artists[artist][album] += timeInSec;
		albums[album][track] = title;


	}

	for(artistIt = artists.begin(); artistIt != artists.end(); artistIt++)//iterates through each artist
	{
		int artistTime = 0;
		int songCount = 0;


		for(albumIt = artistIt->second.begin(); albumIt != artistIt->second.end(); albumIt++)//iterate through each album for a given artist
		{
			artistTime += albumIt->second;//determines total length of all songs in all albums and the number of songs
			songCount += albums[albumIt->first].size();// ^^
		}

		cout << artistIt->first << ": " << songCount << ", " << secToTime(artistTime) << endl;//artist's song count and total album duration


		for(albumIt = artistIt->second.begin(); albumIt != artistIt->second.end(); albumIt++)//iterate through each album for a given artist
		{

			cout << "        " << albumIt->first << ": " << secToTime(albumIt->second) << endl;//album's song count and total duration

			for(songIt = albums[albumIt->first].begin(); songIt != albums[albumIt->first].end(); songIt++)//iterate through each song in a given album
			{
				
				cout << "                " << songIt->first << ". " << songIt->second << ": " << secToTime(songs[songIt->second]) << endl;//duration of the song
			}
		}
	}

return 0;

}
