//Student Names: David Carpenter and Michael Batchelor
//David NetID:
//David StudentID:
//Michael NetID: mbatche1
//Michael StudentID: 000663958

#include <iostream>
#include <string>
#include <map>
#include <sstream>
#include <fstream>
#include <vector>


using namespace std;

string replaceUnderscores(string str) {

  for (size_t i = 0; i < str.length(); ++i) {
	          if (str[i] == '_') str[i] = ' ';
	
  }
      return str;
}

int timeToSec(string timeStr) {

	int min, sec;

	char colon;//ignored, used to simplify the stringstream

	istringstream ss(timeStr);

	if (!(ss >> min >> colon >> sec) || colon != ':' || sec < 0 || sec >= 60) {
		throw std::invalid_argument("Invalid time format: " + timeStr);
	}

	return min * 60 + sec;
}

string secToTime(int time)
{
	int min, sec;
	
	min = time / 60;
	sec = time % 60;

	return to_string(min) + ":" + (sec < 10 ? "0" : "") + to_string(sec);
}


	
	// Define Song struct
	 struct Song {

	     string title;
	     int duration;
	     int track;

	     Song(string t, int d, int tr) : title(t), duration(d), track(tr) {}

	 };
	
	 // Define Album struct
	 struct Album {

	     string name;
	     map<int, Song> songs;
	     int songCount;
		 int totalDuration;
		 
		  Album() : name(""), totalDuration(0), songCount(0) {}  // Default constructor
		  Album(string n) : name(n), totalDuration(0), songCount(0) {}  // Parameterized constructor
	                                         
	    //Add song to album
         void addSong(const Song &song) {

			songs[song.track] = song;
			songCount++;
			totalDuration += song.duration;

	     }

	 };
	
	 // Define Artist struct
	 struct Artist {

	     string name;
	     map<string, Album> albums;
	     int totalDuration;
	     int songCount;
	
		 Artist() : name(""), totalDuration(0), songCount(0) {}  // Default constructor
	     Artist(string n) : name(n), totalDuration(0), songCount(0) {}
	
	     // Add album to artist
	     void addAlbum(const Album &album) {
	     albums[album.name] = album;
	     songCount += album.songCount;
	     totalDuration += album.totalDuration;
		 
		 } 
	};


int main(int argc, char *argv[]) {

    if(argc != 2) {
        cerr << "Usage: " << argv[0] << " <filename>" << endl;
        return 0;
    }

    ifstream file(argv[1]);

    if (!file) {
        cerr << "Error opening file: " << argv[1] << endl;
        return 0;
    }

    string title, time, artist, album, genre;
    int track;
    int timeInSec;

    // Map to store Artist -> Artist
    map<string, Artist> artists;

    // Process each line in the file
    while (file >> title >> time >> artist >> album >> genre >> track) {
        title = replaceUnderscores(title);
        artist = replaceUnderscores(artist);
        album = replaceUnderscores(album);

        // Convert time to seconds
        timeInSec = timeToSec(time);

        // Create a new Song object
        Song newSong(title, timeInSec, track);

        // Check if the artist exists in the map, otherwise create it
        if (artists.find(artist) == artists.end()) {
            artists[artist] = Artist(artist);
        }

        // Check if the album exists under the artist, otherwise create it
        if (artists[artist].albums.find(album) == artists[artist].albums.end()) {
            artists[artist].albums[album] = Album(album);
        }

        // Add the song to the album
        artists[artist].albums[album].addSong(newSong);

        // Add the album to the artist
        artists[artist].addAlbum(artists[artist].albums[album]);
    }

    // Output the data in the required format
    for (map<string, Artist>::iterator artistIt = artists.begin(); artistIt != artists.end(); ++artistIt) {
        // Print artist info
        cout << artistIt->first << ": " << artistIt->second.songCount << ", " 
             << artistIt->second.totalDuration / 60 << ":" << setw(2) << setfill('0') 
             << artistIt->second.totalDuration % 60 << endl;

        // Print albums for each artist
        for (map<string, Album>::iterator albumIt = artistIt->second.albums.begin(); albumIt != artistIt->second.albums.end(); ++albumIt) {
            cout << "        " << albumIt->first << ": " << albumIt->second.songCount << ", " 
                 << albumIt->second.totalDuration / 60 << ":" << setw(2) << setfill('0') 
                 << albumIt->second.totalDuration % 60 << endl;

            // Print songs for each album
            for (map<int, Song>::iterator songIt = albumIt->second.songs.begin(); songIt != albumIt->second.songs.end(); ++songIt) {
                cout << "                " << songIt->first << ". " << songIt->second.title << ": " 
                     << songIt->second.duration / 60 << ":" << setw(2) << setfill('0') 
                     << songIt->second.duration % 60 << endl;
            }
        }
    }

    return 0;
}
