#include <iostream>
#include <map>
#include <sstream>

using namespace std;

string replaceUnderscores(string str) {

  for (size_t i = 0; i < str.length(); ++i) {
	          if (str[i] == '_') str[i] = ' ';
	
  }
      return str;
}

int timeToSec(string timestr) {

	int min, sec;

	char colon;

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


int main() {

	int timeInSec;

	string line;

	string title, time, artist, album, genre, track;
	
    map<string, map<string, int>> songs; //Song title + (Genre + Duration in sec)
	map<string, map<int, string>> albums; //Album title + (Track number + Song title)
	map<string, map<string, int>> artists; //Artist name + (Album + Total time)

	map<int, map<string, int>>::const_iterator songIt;
	map<string, map<int, string>>::const_iterator albumIt;
	map<string, map<string, int>>::const_iterator artistIt;

	while (getline(cin, line))	{

		stringstream musicLine(line);
		musicLine >> title >> time >> artist >> album >> genre >> track;
	
		title = replaceUnderscores(title);
		artist = replaceUnderscores(artist);
		album = replaceUnderscores(album);
		genre = replaceUnderscores(genre);
		track = stoi(track);

		timeInSec = timeToSec(time);

		//songs[title][genre] = timeInSec;
		//artists[artist][album] += timeInSec;
		//albums[album][track] = title;

		cout << "Title: " << title << ", Time: " << time << ", Artist: " << artist 
		     << ", Album: " << album << ", Genre: " << genre << ", Track: " << track << endl;

	}


return 0;

}
