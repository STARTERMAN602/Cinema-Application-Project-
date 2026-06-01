//CREDIT:

//Idea and Concept : 
//M DAFA JAUHAR HAQ (123250018)
//Developer :
//VINCENTIUS ARNOLD ADRA (123250022)
//M DAFA JAUHAR HAQ (123250018)

// ====================== LIBRARY ======================
#include <iostream> 
#include <iomanip> //untuk UI (setw, fixed, setprecision)
#include <cctype> //untuk error handling (huruf, angka, simbol, spasi)
#include <algorithm> //untuk fungsi bantuan (to lower, swap)
#include <fstream> //untuk implementasi file (ifstream, ofstream)
#include <string> //untuk penggunaan string

using namespace std;
// -----------------------------------------------------
// ==================== DATA STRUCT & ARRAY ====================
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


Movie mv[100];
Account ac[100];
int mvCount = 0;
int acCount = 0;

//----------------------------------------------------
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

    int length = s.length();
    for (int i = 0; i < length; i++) {
        if (!isalpha(s[i]) && !isspace(s[i])) {
            return false;
        }
    }
    return true;
}

bool is_all_digit(string s) {
    if (s.empty()) return false;

    int length = s.length();
    for (int i = 0; i < length; i++) {
        if (!isdigit(s[i])) {
            return false;
        }
    }
    return true;
}

bool is_alphanum_space(string s) {
    if (s.empty()) return false;

    int length = s.length();
    for (int i = 0; i < length; i++) {
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
    int length = s.length();
    for (int i = 0; i < length; i++) {
        if (isspace(s[i])) {
            return false;
        }
    }
    return true;
}

float total_revenue(float arr[], int n) {
    if (n == 0) {
        return 0;
    }
    return arr[n - 1] + total_revenue(arr, n - 1);
}
// -----------------------------------------------------
// =================== SEATS COUNTER ===================
int count_total_seats(int index) {
    if (index >= mvCount) {
        return 0;
    }
    return mv[index].stock + count_total_seats(index + 1);
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
bool is_duplicate(string title, int year) {
    string lower_target = to_lower(title);
    for (int i = 0; i < mvCount; i++) {
        if (to_lower(mv[i].title) == lower_target && 
            mv[i].releaseYear == year) {
            return true;
        }
    }
    return false;
}
// -----------------------------------------------------
// ================== DATA MANAGEMENT ================== 
void save_movie() {
    ofstream file("movies.txt");
    if (!file) {
        cout << "Error! Failed to save data." << endl;
        return;
    }

    file << mvCount << endl;
    for (int i = 0; i < mvCount; i++) {
        file << mv[i].title << endl;
        file << mv[i].genre << endl;
        file << mv[i].duration << endl;
        file << mv[i].releaseYear << endl;
        file << mv[i].stock << endl;
        file << mv[i].price << endl;
    }
    file.close();
    cout << "Data saved successfully." << endl;
}

void load_movie() {
    ifstream file("movies.txt");
    if (!file) {
        cout << "Movie library is still empty." << endl;
        mvCount = 0;
        return;
    }

    int count;
    file >> count;
    if (count > 100){
		count = 100;
    }
    
    file.ignore(numeric_limits<streamsize>::max(), '\n');

    mvCount = 0; 
    for (int i = 0; i < count; i++) {
        getline(file, mv[i].title);
        getline(file, mv[i].genre);
        file >> mv[i].duration;
        file >> mv[i].releaseYear;
        file >> mv[i].stock;
        file >> mv[i].price;
        file.ignore(1000 ,'\n');

        mvCount++;
    }
    file.close();
    cout << "Total movie  : " << mvCount << endl;
}

void save_account() {
    ofstream file("users.txt");
    if (!file) {
        cout << "Error! Failed to save data." << endl;
        return;
    }

    file << acCount << endl;
    for (int i = 0; i < acCount; i++) {
        file << ac[i].username << endl;
        file << ac[i].password << endl;
        file << ac[i].role << endl;
    }
    file.close();
    cout << "Data saved successfully." << endl;
}

void load_account() {
    ifstream file("users.txt");
    if (!file) {
        cout << "No users yet." << endl;
        acCount = 0;
        return;
    }

    int count;
    file >> count;
    if (count > 100){
		count = 100;
    }
    
    file.ignore(1000, '\n'); 
    acCount = 0;

    for (int i = 0; i < count; i++) {
        getline(file, ac[i].username);
        getline(file, ac[i].password);
        getline(file, ac[i].role);

        acCount++;
    }
    file.close();
    cout << "Total account: " << acCount << endl;
}
 
void rec_sale(string buyer, string movieTitle, int qty, float total) {
    ofstream file("sales_report.txt", ios::app);
    if (file.is_open()) {

        file << "Buyer: " << buyer << endl;
        file << "Movie: " << movieTitle << endl;
        file << "Qty  : " << qty << endl;
        file << "Total: Rp" << total << endl;
        file << "---------------------------" << endl;

        file.close();
    }
}
// -----------------------------------------------------
// ============= TITLE & RELEASE YEAR SORT =============
void sorting_title() {
    for (int gap = mvCount / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < mvCount; i++) {
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

int partition(Movie mv[], int low, int high) {
    int pivot = mv[high].releaseYear; 
    int i = (low - 1); 

    for (int j = low; j <= high - 1; j++) {
        if (mv[j].releaseYear > pivot) { 
            i++;
            swap(mv[i], mv[j]);
        }
    }
    swap(mv[i + 1], mv[high]);
    return (i + 1);
}

void quickSort(Movie mv[], int low, int high) {
    if (low < high) {
        int pi = partition(mv, low, high);

        quickSort(mv, low, pi - 1);
        quickSort(mv, pi + 1, high);
    }
}

void sorting_releaseYear() {
    if (mvCount == 0) return;
    
    quickSort(mv, 0, mvCount - 1);
}

// -----------------------------------------------------
// ==================== MAIN FEATURE ===================

float get_total_revenue() {
    ifstream file("sales_report.txt");
    if (!file) {
        return 0;
    }
    float revenues[1000];
    int count = 0;
    string line;
    while (getline(file, line)) {

        if (line.find("Total: Rp") != string::npos) {
            string angka = line.substr(9);
            revenues[count] = stof(angka);
            count++;
        }
    }

    file.close();
    return total_revenue(revenues, count);
}

void view_sales_report() {
    ifstream file("sales_report.txt");
    string line;
    float revenue = get_total_revenue();
    clear_screen();
    int totalRemainingSeats = count_total_seats(0);
    cout << "===========================================" << endl;
    cout << "       CINEMA INVENTORY & SALES REPORT     " << endl;
    cout << "===========================================" << endl;
    
    cout << "--- Transaction History ---" << endl;
    if (!file) {
        cout << "No sales yet." << endl;
    } else {
        while (getline(file, line)) {
            cout << line << endl;
        }
        file.close();
    }
    cout << "\n===========================================" << endl;
    cout << "Total Movies in Library    : " << mvCount << endl;
    cout << "Total Remaining Seats      : " << totalRemainingSeats << " seats" << endl;
    cout << "Total Revenue              : Rp" << revenue << fixed << setprecision(2) << endl;
    cout << "===========================================" << endl << endl;
    wait_for_user();
}

void add_movie() {
    clear_screen();
    cout << "=== Add New Movies ===" << endl;

    int addition = get_valid_int("Number of movies: ");
    
    if (mvCount + addition > 100) {
		cout << "[!] Storage full. Maximum movie capacity is 100." << endl;
		wait_for_user();
		return;
	}

    for (int i = 0; i < addition; i++) {

    int idx = mvCount;

    cout << "\nData Movie #" << idx + 1 << ":" << endl;

    while(true) {
        mv[idx].title = get_valid_alphanum_space("=> Title        : ");
        mv[idx].releaseYear = get_valid_int("=> Release Year : ");

        if (is_duplicate(mv[idx].title, mv[idx].releaseYear)) {
            cout << "\n[!] Error: Movie already exists." << endl;
        } else {
            break;
        }
    }

    mv[idx].genre = get_valid_alpha("=> Genre        : ");
    mv[idx].duration = get_valid_int("=> Duration(min): ");
    mv[idx].stock = get_valid_int("=> Stock (Seats): ");
    mv[idx].price = get_valid_float("=> Ticket Price : ");

    mvCount++;
    cout << "----------------------------------" << endl;
	}
	
    save_movie();
    cout << "\nSuccess! " << addition << " movies added." << endl;
    wait_for_user();
}

void display_movie() {
    if (mvCount == 0){
        cout << "\n[!] Movie library is empty." << endl;
        return;
    }
    auto print_line = []() {
        cout << "+" << string(4, '-') << "+" << string(32, '-') << "+" << string(17, '-') 
             << "+" << string(8, '-') << "+" << string(12, '-') << "+" << string(9, '-')
             << "+" << string(14, '-') << "+" << endl; 
    };
    int totalSeats = count_total_seats(0);
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
    
    for (int i = 0; i < mvCount; i++) {
        string dur = to_string(mv[i].duration) + "m";

        cout << "| " << left << setw(2) << i + 1
         << " | " << setw(30) << mv[i].title
         << " | " << setw(15) << mv[i].genre
         << " | " << setw(6)  << mv[i].releaseYear
         << " | " << setw(10) << dur
         << " | " << setw(7)  << mv[i].stock
         << " | Rp" << setw(10) << fixed << setprecision(2) <<  mv[i].price << " |" << endl;
    }
    print_line();
}

void delete_movie() {
    clear_screen();
    cout << "=== Delete Movie ===" << endl;
    if (mvCount == 0) {
        cout << "[!] Movie library is empty. Nothing to delete." << endl;
        wait_for_user();
        return;
    }
    display_movie();
    string targetTitle = get_valid_alphanum_space("Enter Movie Title to delete: ");

    bool found = false;
    for (int i = 0; i < mvCount; i++) {
        if (to_lower(mv[i].title) == to_lower(targetTitle)) {
            cout << "\nFound: " << mv[i].title << " (" << mv[i].releaseYear << ")" << endl;
            while (true) {
				cout << "Are you sure you want to delete this movie? (Y/N): ";

				string confirm;
				getline(cin, confirm);

				if (to_lower(confirm) == "y") {

					for (int j = i; j < mvCount - 1; j++) {
						mv[j] = mv[j + 1];
					}
					mvCount--;
					save_movie();
					cout << "\n[v] Movie deleted successfully." << endl;
					break;
				} else if (to_lower(confirm) == "n") {
					cout << "\n[!] Deletion cancelled." << endl;
					break;
				} else {
					cout << "\n[!] Invalid input. Please enter 'Y' or 'N' only." << endl;
				}
			}
			found = true;
		}
    }
    if (!found) {
        cout << "\n[x] Movie not found." << endl;
     
    }
    wait_for_user();
}

void search_movie() {
    clear_screen();
    cout << "=== Search Movie (Title or Genre) ===" << endl;
    string query = get_valid_alphanum_space("Enter keyword: ");
    string l_query = to_lower(query);

    bool found = false;
    int matchCount = 0;

    cout << "\nShowing result for: '" << query << "'" << endl;

    cout << string(80, '-') << endl;
    cout << left << setw(40) << "Title" << setw(15) << "Genre" << setw(10) << "Year"
         << "Price" << endl;
    cout << string(80, '-') << endl;

    for (int i = 0; i < mvCount; i++) {
        string l_title = to_lower(mv[i].title);
        string l_genre = to_lower(mv[i].genre);
        if (l_title.find(l_query) != string::npos || l_genre.find(l_query) != string::npos ) {
            cout << left << setw(40) << mv[i].title
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

float calculate_discount(float subtotal) {
    if (subtotal >= 500000) {
        return subtotal * 0.15f;
    }
    if (subtotal >= 250000) {
        return subtotal * 0.10f;
    }
    if (subtotal >= 150000) {
        return subtotal * 0.05f;
    }
    return 0;
}

void transaction(string buyerName, string role) {
    clear_screen();
    string buyer;

    if (role == "admin") {
		buyer = get_valid_alpha("Enter Buyer Name: ");
	} else {
		buyer = buyerName;
	}

    if (mvCount == 0) {
        wait_for_user();
        return;
    }
    
    display_movie();
	cout << "\n=== DISCOUNT PROMO ===" << endl;
	cout << "Total >= Rp150.000 : 5% discount" << endl;
	cout << "Total >= Rp250.000 : 10% discount" << endl;
	cout << "Total >= Rp500.000 : 15% discount" << endl;
	cout << "======================" << endl;

    int idx = get_valid_int("\nEnter Movie Number to buy: ") - 1;

    if (idx < 0 || idx >= mvCount) {
        cout << "\n[!] Invalid movie number." << endl;
        wait_for_user();
        return;
    }
	Movie* m = &mv[idx];
    int qty = get_valid_int("Quantity: ");

    if (qty <= 0 || qty > m->stock) {
        cout << "\n[!] Not enough stock or invalid quantity." << endl;
        wait_for_user();
        return;
    }

	float subtotal = qty * m->price;
	float discount = calculate_discount(subtotal);
	float total = subtotal - discount;
	
	cout << string(30, '=') << endl;
	cout << "   TRANSACTION SUMMARY" << endl;
    cout << string(30, '=') << endl;
    cout << "Buyer    : " << buyer << endl;
    cout << "Movie    : " << m->title << endl;
    cout << "Quantity : " << qty << endl;
    cout << "Subtotal : Rp" << fixed << setprecision(2) << subtotal << endl;
    if (discount > 0) {
		cout << "Discount : Rp" << fixed << setprecision(2) << discount;
		if (subtotal >= 500000) {
			cout << " (15%)";
		} else if (subtotal >= 250000) {
			cout << " (10%)";
		} else if (subtotal >= 150000) {
			cout << " (5%)";
		}
		cout << endl;
	}
    cout << "TOTAL    : Rp" << total << endl;
    cout << string(30, '=') << endl;
	while (true) {
		cout << "Are you sure you want to proceed this transaction? (Y/N): ";
		string confirm;
		getline(cin, confirm);

		if (to_lower(confirm) == "y") {
			m->stock -= qty;
			save_movie();
			rec_sale(buyer, m->title, qty, total);

			cout << "\n" << string(30, '=') << endl;
			cout << "   TRANSACTION SUCCESS" << endl;
			cout << string(30, '=') << endl;
			wait_for_user();
			break;
		} else if (to_lower(confirm) == "n") {
			cout << "\n[!] Transaction cancelled." << endl;
			wait_for_user();
			return;
		} else {
			cout << "\n[!] Invalid input. Please enter 'Y' or 'N' only." << endl;
		}
	}
}

bool only_logout(string name) {
    string confirm;
    while (true) {
        cout << "\nAre you sure want to logout, " << name << "? (Y/N): ";
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
void signUp() {
    clear_screen();
    cout << "=== Sign Up / Register ===" << endl;
	
	if (acCount >= 100) {
		cout << "[!] Account storage is full." << endl;
		wait_for_user();
		return;
	}
	
    Account newUser;
    string secret;

    newUser.username = get_valid_no_space("Create username: ");

    for (int i = 0; i < acCount; i++) {
        if (ac[i].username == newUser.username) {
            cout << "\n[Error] Username already taken! Use another name." << endl;
            wait_for_user();
            return;
        }
    }

    newUser.password = get_valid_no_space("Create password: ");

    cout << "Enter Admin Code(Optional): ";
    getline(cin, secret);

    if (secret == "admin123") {
        newUser.role = "admin";
    } else {
        newUser.role = "guest";
    }

	ac[acCount] = newUser;  
	acCount++;
	
    save_account();
    cout << newUser.role << " Registration Success!" << endl;
    wait_for_user();
}

bool login(string &Uname, string &Urole) {
    string username, password;
    int attempts = 5;
    cout << endl;
    while (attempts > 0) {
        clear_screen();
        cout << "=== Login ===" << endl;
        username = get_valid_no_space("Username: ");
        password = get_valid_no_space("Password: ");

        for (int i = 0; i < acCount; i++) {
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

bool landing_page(string &Uname, string &Urole) {
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
        cin.ignore(1000, '\n');

        if (choice == "1") {
            if (login(Uname, Urole)) {
                return true;
            } else {
				return 0;
			}
        } else if (choice == "2") {
            signUp();
        } else if (choice == "3") {
			cout << "\n=== Exiting...";
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
    
    load_movie();
    load_account();
    
    string Uname, Urole;

    if (!landing_page(Uname, Urole)) {
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
        cout << (Urole == "admin" ? "6. View Sales Report" : "[A] 6. View Sales Report") << endl;
        cout << "7. Logout" << endl;
        cout << "8. Logout & Exit" << endl;
        cout << "\nChoose: ";
        getline(cin, choice);

        if (choice == "1") {
            if (Urole == "admin") {
                add_movie();
            } else {
                cout << "\n[!] Access Denied." << endl;
                wait_for_user();
            } 
        } else if (choice == "2") {
            if (Urole == "admin") {
                delete_movie();
            } else {
                cout << "\n[!] Access Denied." << endl;
                wait_for_user();
            } 
        } else if (choice == "3") {
            string s_choice;
            do {
                clear_screen();

                display_movie();
                cout << "\n[ Sorting Option ]" << endl;
                cout << "1. Sort by Title (A-Z)" << endl;
                cout << "2. Sort by Year (Newest to Oldest)" << endl;
                cout << "0. Back to Main Menu" << endl;
                s_choice = get_valid_no_space("Choose: ");
                if (s_choice == "1") {
                    sorting_title();
                } else if (s_choice == "2") {
                    sorting_releaseYear();
                } else if (s_choice == "0") {
                    break;
                } else {
                    cout << "\n[!] Invalid input." << endl;
                    wait_for_user();
                }
            } while(true);
        } else if (choice == "4") {
            search_movie();
        } else if (choice == "5") {
            transaction(Uname, Urole);
        } else if (choice == "6") {
             if (Urole == "admin") {
                view_sales_report();
            } else {
                cout << "\n[!] Access Denied." << endl;
                wait_for_user();
            } 
        } else if (choice == "7") {
            if (only_logout(Uname)) {
                if(!landing_page(Uname, Urole)){
					break;
				} else{
					continue;
				}
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
