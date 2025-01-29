#include "main.h"

int main() {
    Watched myMovies;

    // Add movies
    myMovies.add_movie(Movie("Inception", "Sci-Fi", 95));
    myMovies.add_movie(Movie("The Godfather", "Crime", 98));
    myMovies.add_movie(Movie("The Dark Knight", "Action", 92));

    // Sort movies by rating
    myMovies.sortMovies();

    // Get AI recommendations
    myMovies.getRecs();

    return 0;
}
