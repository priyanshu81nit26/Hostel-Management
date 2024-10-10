#include<bits/stdc++.h>
#include<iostream>
#include<fstream>
#include<windows.h> // to access the Sleep method:
#include<sstream>
using namespace std;

class hostel {
    private:
    string name;
    int fee;
    int bed;

    public:
    // Constructor:
    hostel(string name, int bed, int fee) {
        this->name = name;
        this->bed = bed;
        this->fee = fee;
    }

    // Getter functions:
    string getname() {
        return name;
    }

    int getbed() {
        return bed;
    }

    int getfee() {
        return fee;
    }

    void reserve() {
        ifstream in("hostel.txt");
        ofstream out("hostel_temp.txt");

        string line;
        while (getline(in, line)) {
            int pos = line.find("block A");
            if (pos != string::npos) {
                int temp = bed - 1;
                bed = temp;

                stringstream ss;
                ss << bed;
                string strbed = ss.str();
                int bedpos = line.find_last_of(':');
                line.replace(bedpos + 1, string::npos, strbed);
            }
            out << line << endl;
        }

        out.close();
        in.close();

        remove("hostel.txt");
        rename("hostel_temp.txt", "hostel.txt"); // Update hostel.txt with temp file:
        cout << "\tBed reserved successfully" << endl;
    }
};

class student {
    private:
    string name, address, rollno;

    public:
    student(): name(" "), address(" "), rollno(" ") {}

    // Setter functions:
    void setname(string name) {
        this->name = name;
    }

    void setrollno(string roll) {
        rollno = roll;
    }

    void setaddress(string add) {
        address = add;
    }

    // Getter functions:
    string getname() {
        return name;
    }

    string getroll() {
        return rollno;
    }

    string getaddress() {
        return address;
    }
};

int main() {
    hostel h("block A", 30, 10000);

    // Save hostel data
    ofstream out("hostel.txt");
    if (!out) {
        cerr << "Error opening hostel.txt" << endl;
        return 1;
    }
    out << "\t" << h.getname() << ":" << h.getbed() << ":" << h.getfee() << endl;
    cout << "Hostel data saved" << endl;
    out.close();

    student s;
    bool exit = false;

    while (!exit) {
        system("cls");
        int val;
        cout << "Welcome to Student Management System" << endl;
        cout << "Type 1 : Reserve a bed" << endl;
        cout << "Type 2 : Exit" << endl;
        cout << "Enter your choice" << endl;
        cin >> val;

        if (val == 1) {
            system("cls");
            string name, rollno, address;

            cout << "Enter the name of the student" << endl;
            cin >> name;
            s.setname(name);

            cout << "Enter the address of the student" << endl;
            cin >> address;
            s.setaddress(address);

            cout << "Enter the roll number of the student" << endl;
            cin >> rollno;
            s.setrollno(rollno);

            if (h.getbed() > 0) {
                h.reserve();
                Sleep(3000);
            } else if (h.getbed() == 0) {
                cout << "Beds are not available" << endl;
                Sleep(3000);
            }

            ofstream outfile("student.txt", ios::app);
            if (!outfile) {
                cerr << "Error opening student.txt" << endl;
                return 1;
            }
            outfile << "\t" << s.getname() << ":" << s.getroll() << ":" << s.getaddress() << endl;
            cout << "Student details saved" << endl;
        } else if (val == 2) {
            exit = true;
            cout << "Exiting..." << endl;
            Sleep(3000);
        }
    }
}
