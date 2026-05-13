//CREDIT:

//Idea and Concept : 
//M DAFA JAUHAR HAQ M DAFA JAUHAR HAQ (123250019)
//Developer :
//VINCENTIUS ARNOLD ADRA (123250022)

// ====================== LIBRARY ======================
#include <iostream>
#include <string>
#include <iomanip>
#include <cctype>
#include <algorithm>
#include <limits>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;
// -----------------------------------------------------
// ==================== DATA STRUCT ====================
struct Movie {
    string title;
    string genre;
    int duration;
    int releaseYear;
    int stock;
    float price;
};

struct Account {
    string username;
    string password;
    string role;
};

struct Member {
    string memberID;
    string name;
    string phone;
};
// -----------------------------------------------------
// ======================= UI/UX =======================
void clear_screen() {
    system("clear || cls");
}

void wait_for_user() {
    cin.get();
}
// -----------------------------------------------------
// ================== HELPER FUNCTION ==================
string to_lower(string s) {
    transform(s.begin(), s.end(), s.begin(), ::tolower);
    return s;
}

bool is_all_alpha(string s) {
    if (s.empty()) return false;

    for (int i = 0; i < s.length(); i++) {
        if (!isalpha(s[i]) && !isspace(s[i])) {
            return false;
        }
    }
    return true;
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

bool is_alphanum_space(string s) {
    if (s.empty()) return false;

    for (int i = 0; i < s.length(); i++) {
        if (!isalnum(s[i]) && !isspace(s[i])) {
            return false;
        }
    }
    return true;
}

bool is_no_space_not_empty(string s) {
    if (s.empty()) {
        return false;
    }
    for (int i = 0; i < s.length(); i++) {
        if (isspace(s[i])) {
            return false;
        }
    }
    return true;
}
// -----------------------------------------------------
// =================== SEATS COUNTER ===================
int count_total_seats(const vector<Movie> &mv, int index) {
    if (index >= mv.size()) {
        return 0;
    }
    return mv[index].stock + count_total_seats(mv, index + 1);
}
// -----------------------------------------------------
// ================= VALIDATION HELPERS ================
int get_valid_int(string prompt) {
    string input;
    while(true) {
        cout << prompt;
        getline(cin, input);
        if (is_all_digit(input) && !input.empty()) {
            return stoi(input);
        }
        cout << "[!] Number only." << endl;
    }
}

float get_valid_float(string prompt) {
    string input;
    while(true) {
        cout << prompt;
        getline(cin, input);
        try {
            return stof(input);
        } catch (...) {
            cout << "[!] Decimal number only." << endl;
        }
    }
}

string get_valid_alpha(string prompt) {
    string input;
    while(true) {
        cout << prompt;
        getline(cin, input);
        if (is_all_alpha(input)) {
            return input;
        }
        cout << "[!] Letter(alphabet) and space only." << endl;
    }
}

string get_valid_alphanum_space(string prompt) {
    string input;
    while(true) {
        cout << prompt;
        getline(cin, input);
        if (is_alphanum_space(input)) {
            return input;
        }
        cout << "[!] No weird symbol." << endl;
    }
}

string get_valid_no_space(string prompt) {
    string input;
    while(true) {
        cout << prompt;
        getline(cin, input);
        if (input.empty()) {
            cout << "[!] Input cannot be empty." << endl;
        } else if (!is_no_space_not_empty(input)) {
            cout << "[!] Spaces are not allowed." << endl;
        } else {
            return input;
        }

    }
}
// -----------------------------------------------------
// ================== DUPLICATE SEARCH =================
bool is_duplicate(const vector<Movie> &mv, string title, int year) {
    string lower_target = to_lower(title);
    for (const auto& m : mv) {
        if (to_lower(m.title) == lower_target && 
            m.releaseYear == year) {
            return true;
        }
    }
    return false;
}
// -----------------------------------------------------
// ================== DATA MANAGEMENT ================== 
void save_movie(vector<Movie> &mv) {
    ofstream fout("movies.txt");
    if (!fout) {
        cout << "Error! Failed to save data." << endl;
        return;
    }

    fout << mv.size() << endl;
    for (int i = 0; i < mv.size(); i++) {
        fout << mv[i].title << endl;
        fout << mv[i].genre << endl;
        fout << mv[i].duration << endl;
        fout << mv[i].releaseYear << endl;
        fout << mv[i].stock << endl;
        fout << mv[i].price << endl;
    }
    fout.close();
    cout << "Data saved successfully." << endl;
}

void load_movie(vector<Movie> &mv) {
    ifstream fin("movies.txt");
    if (!fin) {
        cout << "Movie library is still empty." << endl;
        mv.clear();
        return;
    }

    int count;
    fin >> count;
    fin.ignore(numeric_limits<streamsize>::max(), '\n');

    mv.clear(); 
    for (int i = 0; i < count; i++) {
        Movie temp;
        getline(fin, temp.title);
        getline(fin, temp.genre);
        fin >> temp.duration;
        fin >> temp.releaseYear;
        fin >> temp.stock;
        fin >> temp.price;
        fin.ignore(numeric_limits<streamsize>::max(), '\n');

        mv.push_back(temp);
    }
    fin.close();
    cout << "Total movie  : " << mv.size() << endl;
}

void save_account(vector<Account> &ac) {
    ofstream fout("users.txt");
    if (!fout) {
        cout << "Error! Failed to save data." << endl;
        return;
    }

    fout << ac.size() << endl;
    for (int i = 0; i < ac.size(); i++) {
        fout << ac[i].username << endl;
        fout << ac[i].password << endl;
        fout << ac[i].role << endl;
    }
    fout.close();
    cout << "Data saved successfully." << endl;
}

void load_account(vector<Account> &ac) {
    ifstream fin("users.txt");
    if (!fin) {
        cout << "No users yet." << endl;
        ac.clear();
        return;
    }

    int count;
    fin >> count;
    fin.ignore(numeric_limits<streamsize>::max(), '\n'); 
    ac.clear();

    for (int i = 0; i < count; i++) {
        Account temp;
        getline(fin, temp.username);
        getline(fin, temp.password);
        getline(fin, temp.role);

        ac.push_back(temp);
    }
    fin.close();
    cout << "Total account: " << ac.size() << endl;
}

void save_member(vector<Member> &mb) {
    ofstream fout("members.txt");
    if (!fout) {
        cout << "Error! Failed to save data." << endl;
        return;
    }

    fout << mb.size() << endl;
    for (int i = 0; i < mb.size(); i++) {
        fout << mb[i].memberID << endl;
        fout << mb[i].name << endl;
        fout << mb[i].phone << endl;
    }
    fout.close();
    cout << "Data saved successfully." << endl;
}

void load_member(vector<Member> &mb) {
    ifstream fin("members.txt");
    if (!fin) {
        cout << "No members yet." << endl;
        mb.clear();
        return;
    }

    int count;
    fin >> count;
    fin.ignore(numeric_limits<streamsize>::max(), '\n'); 
    mb.clear();

    for (int i = 0; i < count; i++) {
        Member temp;
        getline(fin, temp.memberID);
        getline(fin, temp.name);
        getline(fin, temp.phone);

        mb.push_back(temp);
    }
    fin.close();
    cout << "Total member : " << mb.size() << endl;
}
 
void rec_sale(string buyer, string movieTitle, int qty, float total) {
    ofstream fout("sales_report.txt", ios::app);

    if (fout.is_open()) {
        fout << "Buyer: " << buyer << endl;
        fout << "Movie: " << movieTitle << endl;
        fout << "Qty  : " << qty << endl;
        fout << "Total: Rp" << total << endl;
        fout << "---------------------------" << endl;
        fout.close();
    }
}
// -----------------------------------------------------
// ============= TITLE & RELEASE YEAR SORT =============
void sorting_title(vector<Movie> &mv) {
    for (int gap = mv.size() / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < mv.size(); i++) {
            Movie temp = mv[i];
            string t1 = to_lower(temp.title);
            int j;
            for (j = i; j >= gap; j -= gap) {
                string t2 = to_lower(mv[j - gap].title);
                if (t2 <= t1) break;
                mv[j] = mv[j - gap];
            }
            mv[j] = temp;
        }
    }
}

void sorting_releaseYear(vector<Movie> &mv) {
    for (int gap = mv.size() / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < mv.size(); i++) {
            Movie temp = mv[i];
            int j;
            for (j = i; j >= gap && mv[j - gap].releaseYear < temp.releaseYear; j -= gap) {
                mv[j] = mv[j - gap];
            }
            mv[j] = temp;
        }
    }
}
// -----------------------------------------------------
// ==================== MAIN FEATURE ===================
void view_sales_report(const vector<Movie> &mv) {
    ifstream fin("sales_report.txt");
    string line;
    clear_screen();
    int totalRemainingSeats = count_total_seats(mv, 0);
    cout << "===========================================" << endl;
    cout << "       CINEMA INVENTORY & SALES REPORT     " << endl;
    cout << "===========================================" << endl;
    cout << "Total Movies in Library    : " << mv.size() << endl;
    cout << "Total Remaining Seats      : " << totalRemainingSeats << " seats" << endl;
    cout << "===========================================" << endl << endl;
    
    cout << "--- Transaction History ---" << endl;
    if (!fin) {
        cout << "No sales yet." << endl;
    } else {
        while (getline(fin, line)) {
            cout << line << endl;
        }
        fin.close();
    }
    cout << "\n===========================================" << endl;
    wait_for_user();
}

void add_movie(vector<Movie> &mv) {
    clear_screen();
    cout << "=== Add New Movies ===" << endl;

    int addition = get_valid_int("Number of movies: ");

    for (int i = 0; i < addition; i++) {
        Movie temp;
        cout << "\nData Movie #" << mv.size() + 1 << ":" << endl;

        while(true) {
            temp.title = get_valid_alphanum_space("=> Title        : ");
            temp.releaseYear = get_valid_int("=> Release Year : ");
            if (is_duplicate(mv, temp.title, temp.releaseYear)) {
                cout << "\n[!] Error: Movie already exists." << endl;
                cout << "Please input a different movie." << endl;
            } else {
                break;
            }
        }
        
        temp.genre = get_valid_alpha("=> Genre        : ");
        temp.duration = get_valid_int("=> Duration(min): ");
        temp.stock = get_valid_int("=> Stock (Seats): ");
        temp.price = get_valid_float("=> Ticket Price : ");
        mv.push_back(temp);
        cout << "----------------------------------" << endl;
    }
    save_movie(mv);
    cout << "\nSuccess! " << addition << " movies added." << endl;
    wait_for_user();
}

void delete_movie(vector<Movie> &mv) {
    clear_screen();
    cout << "=== Delete Movie ===" << endl;
    if (mv.empty()) {
        cout << "[!] Movie library is empty. Nothing to delete." << endl;
        wait_for_user();
        return;
    }
    string targetTitle = get_valid_alphanum_space("Enter Movie Title to delete: ");
    int targetYear = get_valid_int("Enter Release Year: ");

    bool found = false;
    for (int i = 0; i < mv.size(); i++) {
        if (to_lower(mv[i].title) == to_lower(targetTitle) && mv[i].releaseYear == targetYear) {
            cout << "\nFound: " << mv[i].title << " (" << mv[i].releaseYear << ")" << endl;
            cout << "Are you sure you want to delete this movie? (Y/N): ";
            string confirm;
            getline(cin, confirm);

            if (to_lower(confirm) == "y") {
                mv.erase(mv.begin() + i);
                save_movie(mv);
                cout << "\n[v] Movie deleted successfully." << endl;
            } else if (to_lower(confirm) == "n") {
                cout << "\n[!] Deletion cancelled." << endl;
            } else {
                cout << "\n[!] Invalid input. Please enter 'Y' or 'N' only." << endl;
            }
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "\n[x] Movie not found." << endl;
     
    }
    wait_for_user();
}

void display_movie(const vector<Movie> &mv) {
    if (mv.empty()) {
        cout << "\n[!] Movie library is empty." << endl;
        return;
    }
    auto print_line = []() {
        cout << "+" << string(4, '-') << "+" << string(32, '-') << "+" << string(17, '-') 
             << "+" << string(8, '-') << "+" << string(12, '-') << "+" << string(9, '-')
             << "+" << string(14, '-') << "+" << endl; 
    };
    int totalSeats = count_total_seats(mv, 0);
    cout << "\n" << string(40, ' ') << "MOVIE LIST" << endl;
    cout << "Total Cinema Capacity (All Movies): " << totalSeats << " seats available." << endl;
    print_line();

    cout << "| " << left << setw(2) << "No"
         << " | " << setw(30) << "Title"
         << " | " << setw(15) << "Genre"
         << " | " << setw(6)  << "Year"
         << " | " << setw(10) << "Duration"
         << " | " << setw(7)  << "Stock"
         << " | " << setw(12) << "Price" << " |" << endl;
    print_line();
    
    for (int i = 0; i < mv.size(); i++) {
        string dur = to_string(mv[i].duration) + "m";
        ostringstream stream;
        stream << "Rp" << fixed << setprecision(2) << mv[i].price;
        string prc = stream.str();

        cout << "| " << left << setw(2) << i + 1
         << " | " << setw(30) << mv[i].title
         << " | " << setw(15) << mv[i].genre
         << " | " << setw(6)  << mv[i].releaseYear
         << " | " << setw(10) << dur
         << " | " << setw(7)  << mv[i].stock
         << " | " << setw(12) << prc << " |" << endl;
    }
    print_line();
}

void search_movie(const vector<Movie> &mv) {
    clear_screen();
    cout << "=== Search Movie (Title or Genre) ===" << endl;
    string query = get_valid_alphanum_space("Enter keyword: ");
    string l_query = to_lower(query);

    bool found = false;
    int matchCount = 0;

    cout << "\nShowing result for: '" << query << "'" << endl;

    cout << string(80, '-') << endl;
    cout << left << setw(30) << "Title" << setw(15) << "Genre" << setw(10) << "Year"
         << "Price" << endl;
    cout << string(80, '-') << endl;

    for (int i = 0; i < mv.size(); i++) {
        string l_title = to_lower(mv[i].title);
        string l_genre = to_lower(mv[i].genre);
        if (l_title.find(l_query) != string::npos || l_genre.find(l_query) != string::npos ) {
            cout << left << setw(30) << mv[i].title
                 << setw(15) << mv[i].genre
                 << setw(10) << mv[i].releaseYear
                 << "Rp" << (int)mv[i].price << endl;
            found = true;
            matchCount++;
        }
    }
    if (!found) {
        cout << "[x] No movies found with keyword '" << query << "'" << endl;
    } else {
        cout << string(80, '-') << endl;
        cout << "[v] Found " << matchCount << " movie(s)." << endl;
    }
    wait_for_user();
}

void transaction(vector<Movie> &mv, vector<Member> &mb, string buyerName, string role) {
    clear_screen();
    display_movie(mv);
    if (mv.empty()) { wait_for_user(); return; }

    int idx = get_valid_int("\nEnter Movie Number to buy: ") - 1;

    if (idx >= 0 && idx < mv.size()) {
        int qty = get_valid_int("Quantity: ");
        if (qty > 0 && qty <= mv[idx].stock) {
            bool isMember = false;
            for (int i = 0; i < mb.size(); i++) {
                if (to_lower(mb[i].name) == to_lower(buyerName)) {
                    isMember = true;
                    break;
                }
            }
            float subtotal = qty * mv[idx].price;
            float discount = 0;

            if (isMember) {
                discount = subtotal * 0.10;
            }
            float total = subtotal - discount;
            mv[idx].stock -= qty;

            save_movie(mv);
            rec_sale(buyerName, mv[idx].title, qty, total);

            cout << "\n" << string(30, '=') << endl;
            cout << "   TRANSACTION SUCCESS" << endl;
            cout << string(30, '=') << endl;
            cout << "Movie    : " << mv[idx].title << endl;
            cout << "Quantity : " << qty << endl;
            cout << "Subtotal : Rp" << fixed << setprecision(2) << subtotal << endl;

            if (isMember) {
                cout << "Discount : Rp" << discount << " (Member 10%)" << endl;
            }
            cout << "TOTAL    : Rp" << total << endl;
            cout << string(30, '=') << endl;
        } else {
            cout << "\n[!] Not enough stock or invalid quantity." << endl;
        }
    } else {
        cout << "\n[!] Invalid movie number." << endl;
    }
    wait_for_user();
}

void add_member(vector<Member> &mb) {
    clear_screen();
    cout << "=== Member Registration ===" << endl;
    Member temp;
    while(true) {
        temp.memberID = get_valid_no_space("Enter Member ID (e.g., M001): ");
        bool idExists = false;
        for (const auto& m : mb) {
            if (to_lower(m.memberID) == to_lower(temp.memberID)) {
                idExists = true;
                break;
            }
        }
        if (idExists) {
            cout << "[!] Error: Member ID already exists. Use another ID." << endl;
        } else {
            break;
        }
    }
    temp.name = get_valid_alpha("Enter Full Name: ");
    while (true) {
        cout << "Enter Phone Number: ";
        getline(cin, temp.phone);
        if (is_all_digit(temp.phone) && !temp.phone.empty()) {
            break;
        }
        cout << "[!] Invalid phone number. Digits only!" << endl;
    }
    mb.push_back(temp);
    save_member(mb);
    cout << "\n[v] Member '" << temp.name << "' registered successfully!" << endl;
    cout << "Now this user can get a 10% discount on ticket purchase." << endl;
    wait_for_user();
}

void display_members(const vector<Member> &mb) {
    clear_screen();
    cout << "=== REGISTERED MEMBERS ===" << endl;
    if (mb.empty()) {
        cout << "No members registered yet." << endl;
    } else {
        cout << string(60, '-') << endl;
        cout << left << setw(10) << "ID" << setw(30) << "Full Name" << "Phone Number" << endl;
        cout << string(60, '-') << endl;
        
        for (const auto& m : mb) {
            cout << left << setw(10) << m.memberID
                 << setw(30) << m.name
                 << m.phone << endl;
        }
        cout << string(60, '-') << endl;
        cout << "Total Members: " << mb.size() << endl;
    }
    wait_for_user();
}

bool logout_confirm(string name) {
    string confirm;
    while (true) {
        cout << "\nAre you sure want to logout and exit, " << name << "? (Y/N): ";
        getline(cin, confirm);
        string res = to_lower(confirm);
        if (res == "y") {
            cout << "\nThank you for using Heliopolis Cinema System." << endl;
            cout << "Goodbye, " << name << "!" << endl;
            wait_for_user();
            return true;
        } else if (res == "n") {
            cout << "\nLogout cancelled. Returning to dashboard..." << endl;
            wait_for_user();
            return false;
        } else {
            cout << "\n[!] Invalid input. Please enter 'Y' or 'N' only." << endl;
            wait_for_user();
            clear_screen();
            cout << "=== Logout Confirmation ===" << endl;
        }
    }
}
// -----------------------------------------------------
// ==================== LANDING PAGE =================== 
void signUp(vector<Account> &ac) {
    clear_screen();
    cout << "=== Sign Up / Register ===" << endl;

    Account newUser;
    string secret;

    newUser.username = get_valid_no_space("Create username: ");

    for (int i = 0; i < ac.size(); i++) {
        if (ac[i].username == newUser.username) {
            cout << "\n[Error] Username already taken! Use another name." << endl;
            wait_for_user();
            return;
        }
    }

    newUser.password = get_valid_no_space("Create password: ");

    cout << "Enter Admin Code(Optional): ";
    getline(cin, secret);

    if (secret == "C1N30P0L15") {
        newUser.role = "admin";
    } else {
        newUser.role = "guest";
    }

    ac.push_back(newUser);
    save_account(ac);
    cout << newUser.role << " Registration Success!" << endl;
    wait_for_user();
}

bool login(vector<Account> &ac, string &Uname, string &Urole) {
    string username, password;
    int attempts = 5;
    cout << endl;
    while (attempts > 0) {
        clear_screen();
        cout << "=== Login ===" << endl;
        username = get_valid_no_space("Username: ");
        password = get_valid_no_space("Password: ");

        for (int i = 0; i < ac.size(); i++) {
            if (ac[i].username == username && ac[i].password == password) {
                Uname = ac[i].username;
                Urole = ac[i].role;
                cout << "\nLogged in as: " << Uname << " [" << Urole << "]" << endl;
                wait_for_user();
                return true;
            }
        }

        attempts--;
        if (attempts > 0) {
            cout << "\nInvalid username or password." << endl;
            cout << "Attempts remaining: " << attempts << endl;
            wait_for_user();
        }
    }
    cout << "\nToo many failed attempts. Exiting..." << endl;
    wait_for_user();
    return false;
}

bool landing_page(vector<Account> &ac, string &Uname, string &Urole) {
    string choice;
    while(true) {
        clear_screen();
        cout << "=== WELCOME TO HELIOPOLIS CINEMA ===" << endl;
        cout << "Do you already have an account?" << endl;
        cout << "1. Yes, Login" << endl;
        cout << "2. No, Sign Up (Register)" << endl;
        cout << "3. Exit Application" << endl;
        cout << "\nChoose: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choice == "1") {
            if (login(ac, Uname, Urole)) {
                return true;
            }
        } else if (choice == "2") {
            signUp(ac);
        } else if (choice == "3") {
            return false;
        } else {
            cout << "\n[Error] Invalid input. Please enter 1, 2, or 3." << endl;
            wait_for_user();
        }
    }

}
// -----------------------------------------------------
// ===================== DASHBOARD =====================
int main() {
    vector<Movie> mv;
    vector<Account> ac;
    vector<Member> mb;
    
    load_movie(mv);
    load_account(ac);
    load_member(mb);
    
    string Uname, Urole;

    if (!landing_page(ac, Uname, Urole)) {
        return 0;
    }

    string choice;
    while (true) {
        clear_screen();
        cout << "== HELIOPOLIS CINEMA DASHBOARD ==" << endl;
        cout << "User: " << Uname << " | Role: " << Urole << endl << endl;

        cout << (Urole == "admin" ? "1. Add Movie" : "[A] 1. Add Movie") << endl;
        cout << (Urole == "admin" ? "2. Delete Movie" : "[A] 2. Delete Movie") << endl;
        cout << "3. Display All Movies" << endl;
        cout << "4. Search Movie" << endl;
        cout << "5. " << (Urole == "admin" ? "Sell Ticket" : "Buy Ticket") << endl;
        cout << "6. " << (Urole == "admin" ? "Member Menu" : "Member Registration") << endl;
        cout << (Urole == "admin" ? "7. View Sales Report" : "[A] 7. View Sales Report") << endl;
        cout << "8. Logout & Exit" << endl;
        cout << "\nChoose: ";
        getline(cin, choice);

        if (choice == "1") {
            if (Urole == "admin") {
                add_movie(mv);
            } else {
                cout << "\n[!] Access Denied." << endl;
                wait_for_user();
            } 
        } else if (choice == "2") {
            if (Urole == "admin") {
                delete_movie(mv);
            } else {
                cout << "\n[!] Access Denied." << endl;
                wait_for_user();
            } 
        } else if (choice == "3") {
            string s_choice;
            do {
                clear_screen();

                display_movie(mv);
                cout << "\n[ Sorting Option ]" << endl;
                cout << "1. Sort by Title (A-Z)" << endl;
                cout << "2. Sort by Year (Newest to Oldest)" << endl;
                cout << "0. Back to Main Menu" << endl;
                s_choice = get_valid_no_space("Choose: ");
                if (s_choice == "1") {
                    sorting_title(mv);
                } else if (s_choice == "2") {
                    sorting_releaseYear(mv);
                } else if (s_choice == "0") {
                    break;
                } else {
                    cout << "\n[!] Invalid input." << endl;
                    wait_for_user();
                }
            } while(true);
        } else if (choice == "4") {
            search_movie(mv);
        } else if (choice == "5") {
            transaction(mv, mb, Uname, Urole);
        } else if (choice == "6") {
            if (Urole == "admin") {
                string mb_choice;
                do {
                    clear_screen();
                    cout << "\n[ Member Menu ]" << endl;
                    cout << "1. Member Registration" << endl;
                    cout << "2. View All Registered Members" << endl;
                    cout << "0. Back to Main Menu" << endl;
                    mb_choice = get_valid_no_space("Choose: ");
                    if (mb_choice == "1") {
                        add_member(mb);
                    } else if (mb_choice == "2") {
                        display_members(mb);
                    } else if (mb_choice == "0") {
                        break;
                    } else {
                        cout << "\n[!] Invalid input." << endl;
                        wait_for_user();
                    }
                } while(true);
            } else {
                add_member(mb);
            } 
        } else if (choice == "7") {
             if (Urole == "admin") {
                view_sales_report(mv);
            } else {
                cout << "\n[!] Access Denied." << endl;
                wait_for_user();
            } 
        } else if (choice == "8") {
            if (logout_confirm(Uname)) {
                break;
            }
        } else {
            cout << "\n[!] Invalid choice." << endl;
            wait_for_user();
        }
    }
    return 0;
}
// -----------------------------------------------------