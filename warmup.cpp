// =====================================================================
//  C++ WARM-UP  ·  African Olympiad Academy
//
//  The question descriptions are in README.md. Read them there.
//  This file holds the data, one worked example, and your answers.
//
//  BUILD AND RUN:   g++ -std=c++17 -Wall -o run warmup.cpp && ./run
//            or:    ./run.sh
//
//  Work on ONE question at a time. Write it, run it, check the output
//  against the README, commit it, move on.
// =====================================================================

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
using namespace std;


bool is_integer(const std::string& s) {
    return !s.empty() && std::all_of(s.begin(), s.end(), [](unsigned char c) {
        return std::isdigit(c);
    });
}


/**
 * THE RECORD
 * One delivery: who brought it, how much, and what grade it was given.
 */
struct Delivery {
    string farmer;
    double kg;
    char   grade;
};


/**
 * THE DATA
 * Do not change these. Every expected answer in the README comes from exactly this data.
 */

// Q1 — one morning's weights, in the order they were weighed
vector<double> morningWeights = {
    45.5, 80.0, 12.0, -3.0, 66.5, 20.0, 31.0, 95.0, 50.0, 18.5, 0.0, 72.0
};

// Q2, Q3, Q4, Q7, Q8 — the day's logbook
vector<Delivery> logbook = {
    {"Keza",    45.5, 'A'},
    {"Bonu",    80.0, 'B'},
    {"Isanda",  20.0, 'A'},
    {"Keza",    12.0, 'C'},
    {"Onyinye", 66.5, 'B'},
    {"Karimi",  31.0, 'A'},
    {"Karimi",  31.0, 'A'},
    {"Keza",    18.5, 'B'},
    {"Bonu",    50.0, 'C'},
    {"Isanda",  20.0, 'A'},
    {"Onyinye", 72.0, 'A'}
};   // yes, one of these rows is in here twice. Q8 is about that.

// Q5 — records as the volunteers typed them, before any checking. Several of these are wrong. That is the point.
struct RawRecord {
    string id;
    string kg;        // text, because a volunteer can type anything
    char   grade;
};

vector<RawRecord> rawRecords = {
    {"F012", "45.5",  'A'},
    {"F7",   "20",    'A'},
    {"F033", "heavy", 'B'},
    {"F021", "0",     'C'},
    {"F044", "80",    'b'},
    {"F055", "",      'A'},
    {"F066", "31.5",  'D'},
    {"F077", "92",    'B'}
};

// Q6 — an Igisoro board. 16 pits, in sowing order.
//      Position 0 is unused so that board[1] really is pit 1.
vector<int> board = {0, 0, 0, 1, 0, 0, 4, 1, 0, 0, 2, 2, 0, 1, 5, 0, 0};


// ---------------------------------------------------------------------
//  A HELPER YOU MAY FIND USEFUL
// ---------------------------------------------------------------------
void printBoard(const vector<int> &b) {
    for (int i = 1; i <= 16; i++) cout << b[i] << " ";
    cout << "\n";
}


int main() {

    // =================================================================
    //  WORKED EXAMPLE  ·  not a question
    //
    //  This is the house style: walk the data once, keep what you need
    //  as you go, print at the end. Read it before you start Q1.
    //
    //  It answers: how many deliveries were grade A, and what was the
    //  heaviest single delivery in the whole logbook?
    // =================================================================

    int gradeACount = 0;
    Delivery heaviest = logbook[0];        // start from a REAL entry,
                                           // never from a made-up 0
    for (Delivery d : logbook) {
        if (d.grade == 'A') {
            gradeACount++;
        }
        if (d.kg > heaviest.kg) {
            heaviest = d;                  // keep the WHOLE record,
        }                                  // not just the number
    }

    cout << "=== Worked example ===\n";
    cout << "Grade A deliveries: " << gradeACount << "\n";
    cout << "Heaviest: " << heaviest.farmer << " with "
         << heaviest.kg << " kg\n\n";


    // =================================================================
    //  Q1  ·  THE WEIGHING SESSION          (see README)
    //  Uses: morningWeights
    // =================================================================
    int total = 0;
    int valid = 0;
    int valid_run = 0;
    int max_run = 0;
    pair<int,int> heavy = {0,0};
    for(int i = 0; i < morningWeights.size(); i++){
        total += morningWeights[i];
        if(heavy.first < morningWeights[i]){
            heavy.first = morningWeights[i];
            heavy.second = i;
        }
        if((morningWeights[i] > 0) && (morningWeights[i] <= 80)){
            valid_run += 1;
            valid += 1;
        }
        else{
            if(valid_run > max_run){
                max_run = valid_run;
            }
            valid_run = 0;
        }
        if(i == morningWeights.size()-1){
            if(valid_run > max_run){
                max_run = valid_run;
            }
            valid_run = 0;
        }
    }
    cout << "=== Q1 ===\n";
    cout << "Total: " << total << "\n";
    cout << "Valid Weights: " << valid << "\n";
    cout << "Heaviest Weight: " << heavy.first << "\n";
    cout << "Position of Heaviest Weight: " << heavy.second << "\n";
    cout << "Longest run of valid weights: " << max_run << "\n";




    cout << "\n";


    // =================================================================
    //  Q2  ·  GRADE SUMMARY                 (see README)
    //  Uses: logbook
    // =================================================================


    vector<int> A = {0,0};
    vector<int> B = {0,0};
    vector<int> C = {0,0};
    for(Delivery i : logbook){
        if(i.grade == 'A'){
            A[0] += 1;
            A[1] += i.kg;
        }
        else if(i.grade == 'B'){
            B[0] += 1;
            B[1] += i.kg;
        }
        else if(i.grade == 'C'){
            C[0] += 1;
            C[1] += i.kg;
        }
    }
    char best;
    if(A[0] == 0 || B[0] == 0 || C[0] == 0){
        cout << "Zero encountered";
    }
    else{
        if(A[1]/A[0] == max(max(C[1]/C[0],A[1]/A[0]),B[1]/B[0])){
            best = 'A';
        }
        if(B[1]/B[0] == max(max(C[1]/C[0],A[1]/A[0]),B[1]/B[0])){
            best = 'B';
        }
        if(C[1]/C[0] == max(max(C[1]/C[0],A[1]/A[0]),B[1]/B[0])){
            best = 'C';
        }
        
        cout << "=== Q2 ===\n";
        cout << "Grade A: " << A[0] << " deliveries. " <<  "Total: " << A[1] << " Average: " << A[1]/A[0] << "\n";
        cout << "Grade B: " << B[0] << " deliveries. " <<  "Total: " << B[1] << " Average: " << B[1]/B[0] << "\n";
        cout << "Grade C: " << C[0] << " deliveries. " <<  "Total: " << C[1] << " Average: " << C[1]/C[0] << "\n";
        cout << "Best Average: " << best<< "\n";
    }

    cout << "\n";


    // =================================================================
    //  Q3  ·  WHO IS WHO                    (see README)
    //  Uses: logbook, and the findFarmer function you write below main
    // =================================================================

    cout << "=== Q3 ===\n";





    cout << "\n";


    // =================================================================
    //  Q4  ·  PAYMENT RUN WITH A DAILY CAP  (see README)
    //  Uses: logbook, and the payment function you write below main
    // =================================================================

    cout << "=== Q4 ===\n";





    cout << "\n";


    // =================================================================
    //  Q5  ·  THE VALIDATION REPORT         (see README)
    //  Uses: rawRecords
    // =================================================================

    cout << "=== Q5 ===\n";
    //     struct RawRecord {
    //     string id;
    //     string kg;        // text, because a volunteer can type anything
    //     char   grade;
    // };

    // vector<RawRecord> rawRecords = {
    //     {"F012", "45.5",  'A'},
    //     {"F7",   "20",    'A'},
    //     {"F033", "heavy", 'B'},
    //     {"F021", "0",     'C'},
    //     {"F044", "80",    'b'},
    //     {"F055", "",      'A'},
    //     {"F066", "31.5",  'D'},
    //     {"F077", "92",    'B'}
    // };
    for(RawRecord r: rawRecords){
        if(r.id.size() != 4){
            cout << r.id << " Reject : Invalid id" << "\n";
            continue;
        }
        if(is_integer(r.kg) == true){
            if(stof(r.kg) <= 0 || stof(r.kg) > 80){
                cout << r.id << " Reject : Weight out of Range" << "\n";
                continue;
            }
        }
        else{
            if(r.kg.size() == 0){
            cout << r.id << " Reject : Weight Missing" << "\n";
            continue;   
            }
            cout << r.id << " Reject : Weight is not a number" << "\n";
            continue;
        }
        if(tolower(r.grade) != 'a' && tolower(r.grade) != 'b' && tolower(r.grade) != 'c'){
            cout << r.id << " Reject : Unknown grade" << "\n";
            continue;
        }
        else{
            cout << r.id << " Accepted" << "\n";
        }
    }




    cout << "\n";

    // =================================================================
    //  Q6  ·  IGISORO: A FULL TURN          (see README)
    //  Uses: board
    // =================================================================

    cout << "=== Q6 ===\n";



    
    // =================================================================
    //  STRETCH  ·  optional
    // =================================================================

    // =================================================================
    //  Q7  ·  SORT THE LOGBOOK              (see README)
    //  Uses: logbook
    // =================================================================

    // cout << "=== Q7 ===\n";





    // =================================================================
    //  Q8  ·  SPOTTING DOUBLE-ENTRIES       (see README)
    //  Uses: logbook
    // =================================================================

    // cout << "=== Q8 ===\n";

    return 0;
}


// =====================================================================
//  FUNCTIONS YOU WRITE
//
//  C++ reads a file top to bottom, so a function must be DECLARED above
//  the place that calls it. These two are declared here at the bottom,
//  which main() cannot see — so move them ABOVE main(), or leave a
//  one-line declaration up there. Working that out is part of Q3.
// =====================================================================

// Q3:  return the position of the first delivery by this farmer,
//      or -1 if the farmer is not in the log at all.
//
int findFarmer(const vector<Delivery> &log, string name) {
    int count = 0;
    bool out = false;
    for(Delivery d : log){
        count += 1;
        if(d.farmer == name){
            return count;
        }
    }
    return -1;

}


// Q4:  what one delivery earns, before any cap is applied.
//      Grade A pays 10% above the rate, B pays the rate,
//      anything else pays 20% below it. The rate is 450.
double payment(double kg, char grade) {
    int maxi = 100000;
    int given_out = 0;
    double price = 0;
    for(Delivery d : logbook){
        if(given_out < maxi){
            if(d.grade == 'A'){
                price = 450*1.2*d.kg;
            }
            if(d.grade == 'B'){
                price = d.kg*450;
            }
            else{
                price = d.kg*450*0.8;
            }
            given_out += price;
            cout << d.farmer << " Grade: " << d.grade << " "<< price << "\n"; 
        }
        else{
            if(d.grade == 'A'){
                price = 450*1.2*d.kg/2;
            }
            if(d.grade == 'B'){
                price = d.kg*450/2;
            }
            else{
                price = d.kg*450*0.8/2;
            }
            given_out += price;
            cout << d.farmer << " Grade: " << d.grade << " "<< price << " (halved)" <<"\n"; 
        }
    }
    return given_out;

}