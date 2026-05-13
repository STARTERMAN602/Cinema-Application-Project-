#include <iostream>
#include <string>
using namespace std;

int main()
{
    // ==========================
    // LOGIN SYSTEM SECTION
    // ==========================
    string username, password;
    int loginAttempt = 0;

    while (loginAttempt < 2)
    {
        cout << "Username: ";
        cin >> username;
        cout << "Password (4 Digit): ";
        cin >> password;

        if (username == "Jikiwoi" && password == "1234")
        {
            cout << "\nLogin successful!\n\n";
            system("pause");
            system("cls");
            break;
        }
        else
        {
            cout << "Invalid username or password.\n";
            loginAttempt++;

            if (loginAttempt == 2)
            {
                cout << "Too many failed attempts. Program terminated.\n";
                return 0;
            }

            cout << "Please try again.\n\n";
        }
    }

    // ==========================
    // SONG DATA VARIABLES
    // ==========================
    string title[1000], singer[1000];
    int songCount = 0;
    bool menuUse = true;

    // ==========================
    // MAIN MENU SECTION
    // ==========================
    while (menuUse)
    {
        cout << "\n===== MAIN MENU =====\n";
        cout << "1. Add a new song\n";
        cout << "2. View all songs\n";
        cout << "3. Search for a song by title\n";
        cout << "4. Exit\n";
        cout << "Choose (1-3): ";

        int choice;
        cin >> choice;
        cin.ignore();
        cout << endl;
        system("cls");

        switch (choice)
        {
        // ==========================
        // OPTION 1: Add a New Song
        // ==========================
        case 1:
        {
            string tempTitle, tempSinger;
            cout << "Enter song title: ";
            getline(cin>>ws, tempTitle);
            cout << "Enter singer name: ";
            getline(cin>>ws, tempSinger);

            title[songCount] = tempTitle; //0, 1, 2
            singer[songCount] = tempSinger; //0, 1, 2
            songCount++; //1, 2
            cout << "Song successfully added to the playlist.\n";
            break;
        }

        // ==========================
        // OPTION 2: View All Songs
        // ==========================
        case 2:
        {
            cout << "===== PLAYLIST =====\n";
            if (songCount == 0)
            {
                cout << "No songs available.\n";
            }
            else
            {
                for (int i = 0; i < songCount; i++)
                {
                    cout << i+1 << ". Title : " << title[i] <<endl;
                    cout << "Singer : " << singer[i] << endl << endl; 
                }
                
            }
            break;
        }

        // ==========================
        // OPTION 3: Search for a Song
        // ==========================
        case 3:
        {
            string search;
            cout << "Enter song title to search: ";
            getline(cin, search);

            // if (search == title1)
            //     cout << "Singer: " << singer1 << endl;
            // else if (search == title2)
            //     cout << "Singer: " << singer2 << endl;
            // else
            //     cout << "Song not found.\n";
            // break;
        }
        case 4: 
            menuUse = false;
            cout << "Good Bye";
            break;
        // ==========================
        // INVALID INPUT HANDLER
        // ==========================
        default:
        {
            cout << "Invalid option. Please choose 1-4.\n";
            break;
        }
        }
        cout << "\n";
        system("pause");
        system("cls");
    }

    return 0;
}