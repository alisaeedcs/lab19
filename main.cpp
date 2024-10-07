// COMSC-210 | Lab 19 | Ali Saeed
// IDE used: nvim / vscode
// comments: wished there was more specifics in assignment as well as some examples of class functions
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
using namespace std;

const int NUM_MOVIES = 2;
const int NUM_REVIEWS = 2;

struct comNode {
    string comment;
    comNode *next;
};

struct ratNode {
    float rating;
    ratNode *next;
};

class Movie {
private:
    string title;
    ratNode *ratings;
    comNode *comments;
public:
    //movie class constructor
    Movie(string name) : title(name), ratings(nullptr), comments(nullptr) {} //initialzie these values using the title as well as the null initial linked lists
    
    void output();
    void addRating();
    void addComment(ifstream& file);
    void delComments();
    void delRatings();  

    //destructor
    ~Movie() {
        delRatings();
        delComments();
    }
};


int main() {
    srand(time(0));
    vector<Movie> movies;

    ifstream file("data.txt");
    movies.push_back(Movie("Good Will Hunting"));
    movies.push_back(Movie("The Shawshank Redemption"));

    //loop thru movies
    for (int j = 0; j < NUM_MOVIES; j++) {
        //loop thru reviews
        for (int i = 0; i < NUM_REVIEWS; i++) {
            movies[j].addRating();
            movies[j].addComment(file);
        }
    }

    for (int j = 0; j < NUM_MOVIES; j++) {
        movies[j].output();
    }

    file.close();
    return 0;
}

void Movie::output() {
    cout << "Movie Title: " << title << endl;
    ratNode * current = ratings;
    comNode * com = comments;
    int count = 1;
    float total = 0;
    while (current) {
        cout << "\t>" << " Review #" << count++ << ": " << current->rating << ": " << com->comment << endl;;
        total += current->rating;
        current = current->next;
        com = com->next;
    }
    cout << "\t> Average: " << total / (count - 1) << endl << endl;
    
}

void Movie::addRating() {
    ratNode *tempRat = new ratNode;
    float rating = float((rand() % 50)) / 10;
   // adds node at head
        if (!ratings) { // if this is the first node, it's the new head
            tempRat->next = nullptr;
            tempRat->rating = rating;
            ratings = tempRat;

        }
        else { // its a second or subsequent node; place at the head
            tempRat->next = ratings;
            tempRat->rating = rating;
            ratings = tempRat;
        }
}

void Movie::addComment(ifstream& file) {
    comNode *tempCom = new comNode;
    string inputcomment;
   // adds node at head
        if (!comments) { // if this is the first node, it's the new head
            comments = tempCom;
            getline(file, inputcomment);
            tempCom->next = nullptr;
            tempCom->comment = inputcomment;
        }
        else { // its a second or subsequent node; place at the head
            tempCom->next = comments;
            getline(file, inputcomment);
            tempCom->comment = inputcomment;
            comments = tempCom;
        }
}

void Movie::delComments() {
    comNode * current = comments;
    while (current) {
        comments = current->next;
        delete current;
        current = comments;
    }
    comments = nullptr;
}


void Movie::delRatings() {
    ratNode * current = ratings;
    while (current) {
        ratings = current->next;
        delete current;
        current = ratings;
    }
    ratings = nullptr;
}