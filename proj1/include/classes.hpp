#pragma once 
#include <vector>
#include <string>

class Song {

	    protected:

	     std::string name
		 std::string time;
	     int trackNum;

		 public:

	     Song(string n, string t, int track)
	     {
		     name = n;
			 time = t;
			 trackNum = track;
	     }

		 string getName() const { return name; }
	     string getTime() const { return time; }
		 string getTrackNum() const { return trackNum; }




};

class Album {

	  protected:

	    string name;
	    map<int, Song> songs;

	  public:

		Album(string n)
	    {
		  name = n;	
		}

	 string getName() const { return name; }

};
