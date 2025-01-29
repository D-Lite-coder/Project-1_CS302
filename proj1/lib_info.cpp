//Student Names: David Carpenter and Michael Batchelor
//David NetID:
//David StudentID:
//Michael NetID: mbatche1
//Michael StudentID: 000663958

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

// Structure to hold song information
struct Song {
    string title;
    string time;
    int track;
};

// Structure to hold album information
struct Album {
    map<int, Song> songs; // Track number as key
    int total_songs = 0;
    int total_seconds = 0;
};

// Structure to hold artist information
struct Artist {
    map<string, Album> albums; // Album name as key
    int total_songs = 0;
    int total_seconds = 0;
};

// Function to convert time format mm:ss to total seconds
int timeToSeconds(const string &time) {
    int minutes, seconds;
    char colon;
    stringstream ss(time);
    ss >> minutes >> colon >> seconds;
    return minutes * 60 + seconds;
}

// Function to convert seconds to mm:ss format
string secondsToTime(int total_seconds) {
    int minutes = total_seconds / 60;
    int seconds = total_seconds % 60;
    return to_string(minutes) + ":" + (seconds < 10 ? "0" : "") + to_string(seconds);
}

// Function to replace underscores with spaces
string formatString(const string &input) {
    string formatted = input;
    replace(formatted.begin(), formatted.end(), '_', ' ');
    return formatted;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <filename>" << endl;
        return 1;
    }

    ifstream file(argv[1]);
    if (!file) {
        cerr << "Error opening file: " << argv[1] << endl;
        return 1;
    }

    map<string, Artist> library;
    string title, time, artist, album, genre, track;

    while (file >> title >> time >> artist >> album >> genre >> track) {
        string formattedTitle = formatString(title);
        string formattedArtist = formatString(artist);
        string formattedAlbum = formatString(album);
        int trackNum = stoi(track);
        int songSeconds = timeToSeconds(time);
        
        library[formattedArtist].total_songs++;
        library[formattedArtist].total_seconds += songSeconds;
        library[formattedArtist].albums[formattedAlbum].total_songs++;
        library[formattedArtist].albums[formattedAlbum].total_seconds += songSeconds;
        library[formattedArtist].albums[formattedAlbum].songs[trackNum] = {formattedTitle, time, trackNum};
    }
    
    // Output the sorted data
    for (map<string, Artist>::iterator artistIt = library.begin(); artistIt != library.end(); ++artistIt) {
        const string &artistName = artistIt->first;
        const Artist &artist = artistIt->second;
        cout << artistName << ": " << artist.total_songs << ", " << secondsToTime(artist.total_seconds) << endl;
        
        for (map<string, Album>::const_iterator albumIt = artist.albums.begin(); albumIt != artist.albums.end(); ++albumIt) {
            const string &albumName = albumIt->first;
            const Album &album = albumIt->second;
            cout << "        " << albumName << ": " << album.total_songs << ", " << secondsToTime(album.total_seconds) << endl;
            
            for (map<int, Song>::const_iterator songIt = album.songs.begin(); songIt != album.songs.end(); ++songIt) {
                const Song &song = songIt->second;
                cout << "                " << song.track << ". " << song.title << ": " << song.time << endl;
            }
        }
    }
    
    return 0;
}
