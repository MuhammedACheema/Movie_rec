#ifndef MAIN_H
#define MAIN_H
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <curl/curl.h> // Install libcurl to use this

// // Replace with your actual Gemini API key

// // URL for Google Generative Language API
// const std::string API_URL = "https://generativelanguage.googleapis.com/v1beta/models/gemini-pro:generateContent?key=" + API_KEY;

// // Callback function to capture response data
// static size_t WriteCallback(void *contents, size_t size, size_t nmemb, std::string *output) {
//     size_t total_size = size * nmemb;
//     output->append((char *)contents, total_size);
//     return total_size;
// }

// // Function to send a request to the Gemini API
// std::string sendRequest(const std::string &prompt) {
//     CURL *curl;
//     CURLcode res;
//     std::string response_data;

//     curl_global_init(CURL_GLOBAL_ALL);
//     curl = curl_easy_init();

//     if (curl) {
//         std::string json_payload = R"({
//             "contents": [{"parts": [{"text": ")" + prompt + R"("}]}]
//         })";

//         struct curl_slist *headers = NULL;
//         headers = curl_slist_append(headers, "Content-Type: application/json");

//         curl_easy_setopt(curl, CURLOPT_URL, API_URL.c_str());
//         curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
//         curl_easy_setopt(curl, CURLOPT_POST, 1);
//         curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json_payload.c_str());
//         curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
//         curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_data);

//         res = curl_easy_perform(curl);

//         if (res != CURLE_OK) {
//             std::cerr << "Request failed: " << curl_easy_strerror(res) << std::endl;
//         }

//         curl_slist_free_all(headers);
//         curl_easy_cleanup(curl);
//     }

//     curl_global_cleanup();
//     return response_data;
// }

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

    void getRecs(){
        for (size_t i = 0; i < watched.size(); i++){
            std::stringstream ss;
            ss << "give me 3 movie recommendations, I watched this movie " << watched[i].movie << "it is a " << watched[i].genre <<  "and I rated it a " << watched[i].rating;
        }
    }
};


#endif