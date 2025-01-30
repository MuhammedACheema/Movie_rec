#ifndef MAIN_H
#define MAIN_H
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <curl/curl.h> 

class Movie {
    public:
    
    std::string movie;
    std::string genre;
    int rating;

    Movie(std::string movie, std::string genre, int rating){
        this -> movie = movie;
        this -> genre = genre;
        this -> rating = rating;
    }
};

class Watched{
    public:

    std::vector <Movie> watched;
    std::vector <int> movie_id;

    void add_movie(Movie movie){
        if (movie.rating > 100){
            std::cout << "Movie rating is invalid, reput in a rating between 0-100";
            return;
        }

        watched.push_back(movie);
    }

    // this will sort the movies by rating
    void sortMovies(){
        std::sort(watched.begin(), watched.end(), [](const Movie &a, const Movie &b) {
            return a.rating < b.rating;
        });
    }  

    void searchMovies(){
        
    }

    void getRecs(){
        for (size_t i = 0; i < watched.size(); i++){
            std::stringstream ss;
            ss << "give me 3 movie recommendations, I watched this movie " << watched[i].movie << "it is a " << watched[i].genre <<  "and I rated it a " << watched[i].rating;
        }
    }
};


#endif