#include <iostream>   
#include <string>
using namespace std;

class Song {
protected:
    string name;
    int length;
    string artist;
public:
    Song(string n = "unknown", int l = 0, string a = "unknown") {
        name = n;
        length = l;
        artist = a;
    }

    virtual void play() = 0;

    virtual void display() {
        cout << "Name: " << name << endl;
        cout << "Length: " << length << " seconds" << endl;
        cout << "Artist: " << artist << endl;
    }

    string getArtist() { return artist; }

    virtual ~Song() {}
};

// ---------------- Live Song ----------------
class LiveSong : virtual public Song {
protected:
    string venue;
public:
    LiveSong(string n = "unknown", int l = 0, string a = "unknown", string v = "unknown")
        : Song(n, l, a) {
        venue = v;
    }

    void play() override {
        cout << "Playing live song at: " << venue << endl;
    }

    void display() override {
        Song::display();
        cout << "Venue: " << venue << endl;
    }

    string getVenue() { return venue; }   
};

// ---------------- Remix Song ----------------
class RemixSong : virtual public Song {
protected:
    string remixer;
public:
    RemixSong(string n = "unknown", int l = 0, string a = "unknown", string r = "unknown")
        : Song(n, l, a) {
        remixer = r;
    }

    void play() override {
        cout << "Playing remix by: " << remixer << endl;
    }

    void display() override {
        Song::display();
        cout << "Remixer: " << remixer << endl;
    }
};

// ---------------- Special Song ----------------
class SpecialSong : public LiveSong, public RemixSong {
protected:
    string specialNote;
public:
    SpecialSong(string n = "unknown", int l = 0, string a = "unknown",
                string v = "unknown", string r = "unknown", string s = "unknown")
        : Song(n, l, a), LiveSong(n, l, a, v), RemixSong(n, l, a, r) {
        specialNote = s;
    }

    void play() override {
        cout << "Playing live song at: " << venue
             << " | Remix by: " << remixer
             << " | Special note: " << specialNote << endl;
    }

    void display() override {
        Song::display();
        cout << "Venue: " << venue
             << " | Remixer: " << remixer
             << " | Note: " << specialNote << endl;
    }
    
    string getSpecialVenue() { return venue; }   
};

// ================= Playlist =================
class Playlist {
public:
    Song* liveSongs[100];
    Song* remixSongs[100];
    Song* specialSongs[100];
    int liveCount, remixCount, specialCount;

    Playlist() {
        liveCount = remixCount = specialCount = 0;
        for(int i = 0; i < 100; i++) {
            liveSongs[i] = NULL; 
            remixSongs[i] = NULL;
            specialSongs[i] = NULL;
        }
    }

    bool isDuplicate(Song* s, Song** arr, int count) {
        for (int i = 0; i < count; i++)
            if (arr[i] == s) return true;
        return false;
    }

    void addLiveSong(LiveSong* s) {
        if (liveCount >= 100) throw 1;
        liveSongs[liveCount++] = s;
    }

    void addRemixSong(RemixSong* s) {
        if (remixCount >= 100) throw 1;
        remixSongs[remixCount++] = s;
    }

    void addSpecialSong(SpecialSong* s) {
        if (specialCount >= 100) throw 1;
        specialSongs[specialCount++] = s;
    }

    void playAll() {
        if (liveCount + remixCount + specialCount == 0) throw 2;

        cout << "\n--- Live Songs ---\n";
        for (int i = 0; i < liveCount; i++) if(liveSongs[i]) liveSongs[i]->play();

        cout << "\n--- Remix Songs ---\n";
        for (int i = 0; i < remixCount; i++) if(remixSongs[i]) remixSongs[i]->play();

        cout << "\n--- Special Songs ---\n";
        for (int i = 0; i < specialCount; i++) if(specialSongs[i]) specialSongs[i]->play();
    }

    void showPlaylist() {
        if (liveCount + remixCount + specialCount == 0) throw 3;

        cout << "\n--- Live Songs ---\n";
        for (int i = 0; i < liveCount; i++) {
            if(liveSongs[i]) {
                liveSongs[i]->display();
                cout << "--------------------\n";
            }
        }

        cout << "\n--- Remix Songs ---\n";
        for (int i = 0; i < remixCount; i++) {
            if(remixSongs[i]) {
                remixSongs[i]->display();
                cout << "--------------------\n";
            }
        }

        cout << "\n--- Special Songs ---\n";
        for (int i = 0; i < specialCount; i++) {
            if(specialSongs[i]) {
                specialSongs[i]->display();
                cout << "--------------------\n";
            }
        }
    }

    void deleteLiveSongs() {
        for (int i = 0; i < liveCount; i++) {
            if (liveSongs[i]) {
                delete liveSongs[i];
                liveSongs[i] = NULL;
            }
        }
        liveCount = 0;
        cout << "Live songs deleted from memory.\n";
    }

    void deleteRemixSongs() {
        for (int i = 0; i < remixCount; i++) {
            if (remixSongs[i]) {
                delete remixSongs[i];
                remixSongs[i] = NULL;
            }
        }
        remixCount = 0;
        cout << "Remix songs deleted from memory.\n";
    }

    void deleteSpecialSongs() {
        for (int i = 0; i < specialCount; i++) {
            if (specialSongs[i]) {
                delete specialSongs[i];
                specialSongs[i] = NULL;
            }
        }
        specialCount = 0;
        cout << "Special songs deleted from memory.\n";
    }

    void showSongsByArtist(const string& artistName) {
        bool found = false;

        for (int i = 0; i < liveCount; i++)
            if (liveSongs[i] && liveSongs[i]->getArtist() == artistName) {
                liveSongs[i]->display(); found = true;
            }

        for (int i = 0; i < remixCount; i++)
            if (remixSongs[i] && remixSongs[i]->getArtist() == artistName) {
                remixSongs[i]->display(); found = true;
            }

        for (int i = 0; i < specialCount; i++)
            if (specialSongs[i] && specialSongs[i]->getArtist() == artistName) {
                specialSongs[i]->display(); found = true;
            }

        if (!found) cout << "No songs found by this artist.\n";
    }

    void showArtistVenueRelation() {
        bool found = false;
        cout << "\n--- Artist - Venue Relation (R -> A x V) ---\n";

        for (int i = 0; i < liveCount; i++) {
            if (!liveSongs[i]) continue;
            LiveSong* ls = dynamic_cast<LiveSong*>(liveSongs[i]);
            if (ls) {
                cout << "Artist: " << ls->getArtist() << " -> Venue: " << ls->getVenue() << endl;
                found = true;
            }
        }

        for (int i = 0; i < specialCount; i++) {
            if (!specialSongs[i]) continue;
            SpecialSong* ss = dynamic_cast<SpecialSong*>(specialSongs[i]);
            if (ss) {
                cout << "Artist: " << ss->getArtist() << " -> Venue: " << ss->getSpecialVenue() << endl;
                found = true;
            }
        }

        if (!found) cout << "No track logs to form a relation set.\n";
    }

    ~Playlist() {
        deleteLiveSongs();
        deleteRemixSongs();
        deleteSpecialSongs();
    }
};

// ================= Main =================
int main() {
    Playlist playlist;
    int choice;

    do {
        cout << "\n--------- Playlist Menu ---------\n";
        cout << "1. Add Live song\n";
        cout << "2. Add Remix song\n";
        cout << "3. Add Special song\n";
        cout << "4. Play all songs\n";
        cout << "5. Show all playlists\n";
        cout << "6. Delete Live songs\n";
        cout << "7. Delete Remix songs\n";
        cout << "8. Delete Special songs\n";
        cout << "9. Show songs by artist\n";
        cout << "10. Show performer-venue relation\n";
        cout << "11. Exit\n";
        cout << "---------------------------------\nEnter choice: ";
        cin >> choice;
        cin.ignore();

        try {
            switch (choice) {
            case 1: {
                string n, a, v; int l;
                cout << "Enter name: "; getline(cin, n);
                cout << "Enter length (sec): "; cin >> l; cin.ignore();
                cout << "Enter artist: "; getline(cin, a);
                cout << "Enter venue: "; getline(cin, v);
                playlist.addLiveSong(new LiveSong(n, l, a, v));
                cout << "Live song added successfully.\n";
                break;
            }
            case 2: {
                string n, a, r; int l;
                cout << "Enter name: "; getline(cin, n);
                cout << "Enter length (sec): "; cin >> l; cin.ignore();
                cout << "Enter artist: "; getline(cin, a);
                cout << "Enter remixer: "; getline(cin, r);
                playlist.addRemixSong(new RemixSong(n, l, a, r));
                cout << "Remix song added successfully.\n";
                break;
            }
            case 3: {
                string n, a, v, r, s; int l;
                cout << "Enter name: "; getline(cin, n);
                cout << "Enter length (sec): "; cin >> l; cin.ignore();
                cout << "Enter artist: "; getline(cin, a);
                cout << "Enter venue: "; getline(cin, v);
                cout << "Enter remixer: "; getline(cin, r);
                cout << "Enter special note: "; getline(cin, s);
                playlist.addSpecialSong(new SpecialSong(n, l, a, v, r, s));
                cout << "Special song added successfully.\n";
                break;
            }
            case 4:
                playlist.playAll();
                break;
            case 5:
                playlist.showPlaylist();
                break;
            case 6:
                playlist.deleteLiveSongs();
                break;
            case 7:
                playlist.deleteRemixSongs();
                break;
            case 8:
        playlist.deleteSpecialSongs();
        break;

    case 9: 
        {
            string a;
            cout << "Enter artist name: ";
            getline(cin, a);
            playlist.showSongsByArtist(a);
            break;
        }

    case 10:
        playlist.showArtistVenueRelation();
        break;

    case 11:
        cout << "Exiting system.\n";
        break;

    default:
        cout << "Invalid choice!\n";
    }
}
catch (int err) 
{
    if (err == 1) 
        cout << "Error: Playlist storage array limit reached!\n";
    if (err == 2) 
        cout << "Error: No tracks available to play!\n";
    if (err == 3) 
        cout << "Error: Playlist is completely empty!\n";
}
} while (choice != 11);

return 0;
}
























