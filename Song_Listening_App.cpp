#include <iostream>
#include <string>
#include <iomanip>
#include <cctype>
#include <algorithm>
#include <limits>
#include <fstream>

using namespace std;

struct Song {
    string title;
    string singer;
    float duration;
    string genre;
};

const int MAX_SONGS = 100;

string to_lower(string s) {
    transform(s.begin(), s.end(), s.begin(), ::tolower);
    return s;
}

bool is_all_digit(string s) {
    if (s.empty()) return false;

    for (int i = 0; i < s.length(); i++) {
        if (!isdigit(s[i])) {
            return false;
        }
    }
    return true;
}

bool is_duplicate(Song array[], int count, string title, string singer) {
    for (int i = 0; i < count; i++) {
        if (to_lower(array[i].title) == to_lower(title) && 
            to_lower(array[i].singer) == to_lower(singer)) {
            return true;
        }
    }
    return false;
}

void save_songs(Song array[], int *count) {
    ofstream fout("songs.txt");
    if (!fout) {
        cout << "Error! Failed to save data." << endl;
        return;
    }

    fout << *count << endl;
    for (int i = 0; i < *count; i++) {
        fout << array[i].title << endl;
        fout << array[i].singer << endl;
        fout << array[i].duration << endl;
        fout << array[i].genre << endl;
    }
    fout.close();
    cout << "Data saved successfully." << endl;
}

void load_songs(Song array[], int *count) {
    ifstream fin("songs.txt");
    if (!fin) {
        cout << "No save data found." << endl;
        return;
    }

    fin >> *count;
    fin.ignore(); 
    for (int i = 0; i < *count; i++) {
        getline(fin, array[i].title);
        getline(fin, array[i].singer);
        fin >> array[i].duration;
        fin.ignore(); 
        getline(fin, array[i].genre);
    }
    fin.close();
    cout << "Data loaded: " << *count << " songs." << endl;
    cout << endl;
}

enum User { Guest, Admin };

User select_user() {
    int pick;
    do {
        cout << "=== Welcome User! ===" << endl;
        cout << "Select User: " << endl;
        cout << "1. Admin" << endl;
        cout << "2. Guest" << endl;
        cout << "Choose: ";
        
        if (!(cin >> pick)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nInvalid input. Please enter a number." << endl;
            cout << endl;
            continue;
        }
        cin.ignore();

        if (pick == 1) return Admin;
        if (pick == 2) return Guest;

        cout << "\nMenu is unavailable." << endl;
        cout << endl;
    } while(true);
}

bool login() {
    string username, password;
    int attempts = 5;
    cout << endl;
    while (attempts > 0) {
        cout << "=== Login ===" << endl;
        cout << "Username: ";
        getline(cin, username);
        cout << "Password: ";
        getline(cin, password);

        if (username == "admin" && password == "admin123") {
            cout << "\nLogin successful. Welcome, " << username << "!" << endl;
            cout << endl;
            return true;
        }

        attempts--;
        if (attempts > 0) {
            cout << "\nInvalid username or password." << endl;
            cout << "Attempts remaining: " << attempts << endl;
            cout << endl;
        }
    }
    cout << "\nToo many failed attempts. Exiting..." << endl;
    cout << endl;
    return false;
}

void add_songs(Song array[], int *count) {
    int addition;
    cout << endl;
    do {
        cout << "=== Add New Songs ===" << endl;
        cout << "Number of songs: ";
        if (!(cin >> addition)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            addition = -1;
            cout << "\nInvalid input. Please enter a number." << endl;
            cout << endl;
            continue;
        }

        if (addition <= 0) {
            cout << "\nMust be more than 0." << endl;
            cout << endl;
        } else if (*count + addition > MAX_SONGS) {
            cout << "\nCannot add more than " << MAX_SONGS << " songs." << endl;
            cout << endl;
        } else {
            break; 
        }
    } while(true);

    cin.ignore();
    for (int i = 0; i < addition; i++) {
        string t_title, t_singer;
        while (true) {
            cout << "\nSong " << *count + 1 << ":" << endl;
            cout << "=> Title   : ";
            getline(cin, t_title);
            cout << "=> Singer  : ";
            getline(cin, t_singer);

            if (is_duplicate(array, *count, t_title, t_singer)) {
                cout << "\n[Error] Song already exists in library!" << endl;
                cout << "Please input a different song." << endl;
            } else {
                break;
            }
        }

        array[*count].title = t_title;
        array[*count].singer = t_singer;

        while (true) {
            cout << "=> Duration: ";
            if (!(cin >> array[*count].duration)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << endl;
                cout << "Invalid input. Enter a number for duration." << endl;
                cout << endl;
                continue;
            }
            if (array[*count].duration <= 0) {
                cout << endl;
                cout << "Duration must be more than 0." << endl;
                cout << endl;
                continue;
            }
            break;
        }
        cin.ignore();
        cout << "=> Genre   : ";
        getline(cin, array[*count].genre);
        
        (*count)++;
    }
    cout << "---------------------" << endl;;
    cout << "\nSuccess! " << addition << " songs added." << endl;
    save_songs(array, count);
}

void display_songs(Song array[], int *count, int index) {
    if (index == *count) return;
    
    cout << "\n=========================================================================================" << endl;
    string text = "SONGS LIBRARY";
    cout << string((90 - text.length()) / 2, ' ') << text << endl;
    cout << "=========================================================================================" << endl;
    cout << left << setw(5) << "#" << setw(30) << "Title" << setw(25) << "Singer" 
         << setw(20) << "Duration(min)" << setw(20) << "Genre" << endl;
    cout << "-----------------------------------------------------------------------------------------" << endl;
    
    for (int i = index; i < *count; i++) {
        cout << left << setw(5) << i + 1 
             << setw(30) << array[i].title 
             << setw(25) << array[i].singer 
             << setw(20) << array[i].duration 
             << setw(20) << array[i].genre << endl;
    }
    cout << "-----------------------------------------------------------------------------------------" << endl;
}

void sorting_title(Song array[], int *count) {
    for (int gap = *count / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < *count; i++) {
            Song temp = array[i];
            string t1 = to_lower(temp.title);
            int j;
            for (j = i; j >= gap; j -= gap) {
                string t2 = to_lower(array[j - gap].title);
                if (t2 <= t1) break;
                array[j] = array[j - gap];
            }
            array[j] = temp;
        }
    }
}

void sorting_duration(Song array[], int *count) {
    for (int gap = *count / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < *count; i++) {
            Song temp = array[i];
            int j;
            for (j = i; j >= gap && array[j - gap].duration < temp.duration; j -= gap) {
                array[j] = array[j - gap];
            }
            array[j] = temp;
        }
    }
}

void sorting_singer(Song array[], int *count) {
    for (int gap = *count / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < *count; i++) {
            Song temp = array[i];
            string s1 = to_lower(temp.singer);
            int j;
            for (j = i; j >= gap; j -= gap) {
                string s2 = to_lower(array[j - gap].singer);
                if (s2 <= s1) break;
                array[j] = array[j - gap];
            }
            array[j] = temp;
        }
    }
}

int search_title(Song array[], int l, int r, string target) { 
    if (l > r) return -1;
    int mid = (l + r) / 2;
    string mid_t = to_lower(array[mid].title);
    string target_t = to_lower(target);

    if (mid_t == target_t) return mid;
    if (mid_t > target_t) return search_title(array, l, mid - 1, target);
    return search_title(array, mid + 1, r, target);
}

int search_singer(Song array[], int l, int r, string target) { 
    if (l > r) return -1;
    int mid = (l + r) / 2;
    string mid_s = to_lower(array[mid].singer);
    string target_s = to_lower(target);

    if (mid_s == target_s) return mid;
    if (mid_s > target_s) return search_singer(array, l, mid - 1, target);
    return search_singer(array, mid + 1, r, target);
}

int main() {
    Song s[MAX_SONGS];
    int count = 0;
    int choice;

    load_songs(s, &count);
    User user = select_user();
    
    if (user == Admin && !login()) return 0;
    cout << endl;
    do {
        cout << "== Song Listening App ==" << endl;
        cout << "User: " << (user == Admin ? "Admin" : "Guest") << endl;
        cout << "Library: " << count << " songs" << endl << endl;
        
        cout << "1. " << (user == Admin ? "Add songs" : "Add songs (Admin Only)") << endl;
        cout << "2. Display songs" << endl;
        cout << "3. Search songs" << endl;
        cout << "4. Exit" << endl;
        cout << "Choose: ";
        
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nInvalid input. Enter a number." << endl;
            cout << endl;
            continue;
        }
        cin.ignore();
        
        if ((choice == 2 || choice == 3) && count == 0) {
            cout << "\nNo songs available. Please add songs first." << endl;
            cout << endl;
            continue;
        }

        switch (choice) {
            case 1:
                if (user == Admin) add_songs(s, &count);
                else cout << "\nAccess denied! Admin only." << endl;
                cout << endl;
                break;

            case 2: {
                display_songs(s, &count, 0);
                string sort_choice;
                do {
                    cout << "\nSort by:\n1. Title (A-Z)\n2. Duration (Longest)\n0. Back\nChoose: ";
                    cin >> sort_choice;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                
                    if (sort_choice == "1") {
                        sorting_title(s, &count);
                        display_songs(s, &count, 0);
                        cout << "Song sorted: A-Z" << endl;
                    } else if (sort_choice == "2") {
                        sorting_duration(s, &count);
                        display_songs(s, &count, 0);
                        cout << "Song sorted: Longest to Shortest" << endl;
                    } else if (sort_choice == "0") {
                        cout << endl;
                        cout << "Returning to main menu..." << endl;
                        cout << endl;
                        break;
                    } else {
                       if (is_all_digit(sort_choice)) {
                            cout << "\nMenu is unavailable." << endl;
                            cout << endl;
                        } else {
                            cout << "\nInvalid input. Please enter a number." << endl;
                            cout << endl;
                        }
                    }
                } while(sort_choice != "0");
                break;
            }

            case 3: {
                string sc;
                do {
                    cout << "\nSearch by:\n1. Title\n2. Singer\n0. Back\nChoose: ";
                    cin >> sc;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                    if (sc == "1") {
                        sorting_title(s, &count);
                        string t; 
                        cout << endl;
                        cout << "Title: "; getline(cin, t);
                        cout << endl;
                        int res = search_title(s, 0, count-1, t);
                        if (res != -1) {
                            cout << "Found at index -> " << res+1 << endl;
                            cout << endl;
                            cout << "=========================================================================================" << endl;
                            cout << left << setw(5) << "#" << setw(30) << "Title" << setw(25) << "Singer" 
                                 << setw(20) << "Duration(min)" << setw(20) << "Genre" << endl;
                            cout << "-----------------------------------------------------------------------------------------" << endl;
                            cout << left << setw(5) << res + 1 
                                 << setw(30) << s[res].title 
                                 << setw(25) << s[res].singer 
                                 << setw(20) << s[res].duration 
                                 << setw(20) << s[res].genre << endl;
                            cout << "-----------------------------------------------------------------------------------------" << endl;
                        } else {
                            cout << "[x] Not found." << endl;
                            cout << endl; 
                            cout << "Search another title." << endl;
                        }
                    } else if (sc == "2") {
                        sorting_singer(s, &count);
                        string sg; 
                        cout << endl;
                        cout << "Singer: "; getline(cin, sg);
                        cout << endl;
                        int res = search_singer(s, 0, count-1, sg);
                        if (res != -1) {
                            cout << "Found at index -> " << res+1 << endl;
                            cout << endl;
                            cout << "=========================================================================================" << endl;
                            cout << left << setw(5) << "#" << setw(30) << "Title" << setw(25) << "Singer" 
                                 << setw(20) << "Duration(min)" << setw(20) << "Genre" << endl;
                            cout << "-----------------------------------------------------------------------------------------" << endl;
                            cout << left << setw(5) << res + 1 
                                 << setw(30) << s[res].title 
                                 << setw(25) << s[res].singer 
                                 << setw(20) << s[res].duration 
                                 << setw(20) << s[res].genre << endl;
                            cout << "-----------------------------------------------------------------------------------------" << endl;
                        } else {
                            cout << "[x] Not found." << endl;
                            cout << endl; 
                            cout << "Search another singer." << endl;
                        }
                    } else if (sc == "0") {
                        cout << endl;
                        cout << "Returning to main menu..." << endl;
                        cout << endl;
                        break;
                    } else {
                        if (is_all_digit(sc)) {
                            cout << "\nMenu is unavailable." << endl;
                            cout << endl;
                        } else {
                            cout << "\nInvalid input. Please enter a number." << endl;
                            cout << endl;
                        }
                    }
                } while(sc != "0");
                break;
            }

            case 4: {
                string ex;
                do {
                    cout << "\nAre you sure you want to exit? (Y/N): ";
                    cin >> ex; 
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                    if (ex == "y" || ex == "Y") {
                        cout << endl;
                        cout << "Goodbye!" << endl;
                        cout << endl;
                        return 0;
                    } else if (ex == "n" || ex == "N") {
                        cout << endl;
                        cout << "Returning to main menu..." << endl;
                        cout << endl;
                        break;
                    } else {
                        if (is_all_digit(ex)) {
                            cout << "\nInvalid input. Please enter a letter(alphabet)." << endl;
                            cout << endl;
                        } else {
                            cout << "\n(Y/y) or (N/n) only." << endl;
                            cout << endl;
                        }
                    }
                } while(true);
                cout << endl;
                break;
            }

            default:
                cout << "\nMenu is unavailable." << endl;
                cout << endl;
        }
    } while(true);

    return 0;
}