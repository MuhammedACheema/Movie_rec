#ifndef MAIN_H
#define MAIN_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <unordered_map>



class Movie {
    public:
    
    std::string movie;
    std::string genre;
    float rating;

    Movie(std::string movie, std::string genre, float rating){
        this -> movie = movie;
        this -> genre = genre;
        this -> rating = rating;
    }
};

// Function to load movies from CSV into a vector
std::vector<Movie> loadMoviesFromCSV(const std::string &filename) {
    std::vector<Movie> movies;
    std::ifstream file(filename);
    std::string line;

    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return movies;
    }

    // Skip the header row
    std::getline(file, line);

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string title, genre, rating, year;

        std::getline(ss, title, ',');
        std::getline(ss, genre, ',');
        std::getline(ss, rating, ',');
        std::getline(ss, year, ',');  // Still reading but not storing

        try {
            int ratingValue = std::stoi(rating);  // Convert safely
            movies.emplace_back(title, genre, ratingValue);
        } catch (const std::invalid_argument &e) {
            std::cerr << "Skipping invalid row (non-numeric rating): " << line << std::endl;
        } catch (const std::out_of_range &e) {
            std::cerr << "Skipping row (rating out of range): " << line << std::endl;
        }
    }

    file.close();
    return movies;
}



void filterByGenre(const std::vector<Movie> &movies, const std::string &genre) {
    std::cout << "\nMovies in Genre: " << genre << "\n";
    for (const auto &movie : movies) {
        if (movie.genre == genre) {
            std::cout << "- " << movie.movie <<  " Rating: " << movie.rating << "/10\n";
        }
    }
}

void filterByRating(const std::vector<Movie> &movies, float minRating) {
    std::cout << "\nMovies with rating >= " << minRating << "\n";
    for (const auto &movie : movies) {
        if (movie.rating >= minRating) {
            std::cout << "- " << movie.movie << " - Rating: " << movie.rating << "/10\n";
        }
    }
}



class Watched{
    public:
    // csv file that will provide recs;
    std::vector<Movie> all = loadMoviesFromCSV("movies.csv");
    std::vector <Movie> watched;
    std::vector <int> movie_recs;
    std::string most_watched_genre;



    // and count most
    void count_most() {
        if (watched.empty()) {
            std::cout << "No movies in watchlist.\n";
            most_watched_genre = "None";  
            return;
        }

        std::unordered_map<std::string, int> genreCount;

        for (const auto &movie : watched) {
            genreCount[movie.genre]++;
        }

        int maxCount = 0;
        std::string genreWithMax;

        for (const auto &pair : genreCount) {
            if (pair.second > maxCount) {
                maxCount = pair.second;
                genreWithMax = pair.first;
            }
        }

        most_watched_genre = genreWithMax;  // ✅ Set the genre with max count
        std::cout << "Most watched genre: " << most_watched_genre << " (" << maxCount << " times)\n";
    }


    void add_movie(Movie movie) {
        if (movie.rating > 100) {
            std::cout << "Movie rating is invalid, enter a rating between 0-100\n";
            return;
        }

        watched.push_back(movie);
        count_most();  
        std::cout << "Movie added successfully!\n";
    }


    // this will sort the movies by rating
    void sortMovies(){
        std::sort(watched.begin(), watched.end(), [](const Movie &a, const Movie &b) {
            return a.rating < b.rating;
        });
    }  

    // implemented get recs
    void getRecs() {
        if (most_watched_genre.empty() || most_watched_genre == "None") {
            std::cout << "No watched genre found. Add more movies first!\n";
            return;
        }

        std::cout << "\nRecommended movies in your most-watched genre (" << most_watched_genre << "):\n";
        filterByGenre(all, most_watched_genre);

        std::cout << "\nMovies in this genre that you haven't watched yet:\n";

        for (const auto &movie : all) {
            bool alreadyWatched = std::any_of(watched.begin(), watched.end(), [&](const Movie &m) {
                return m.movie == movie.movie;
            });

            if (!alreadyWatched && movie.genre == most_watched_genre) {
                std::cout << "- " << movie.movie << " - Rating: " << movie.rating << "/10\n";
            }
        }
    }

};


#endif