#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>
#include <cstdlib>

using namespace std;

class Pupils {
public:
    string id;
    string name;
    string surName;
    string age;
    string qclass;
};

class Grades {
public:
    string id;
    string idPupil;
    string idCourse;
    string grade;
};

class Courses {
public:
    string id;
    string couresName;
};

class Table{
public:
    vector < vector <string> > data;
    vector < string > names;

    Table(){


    }

    void preLoadData(string way) {

        data.clear();
        names.clear();

        ifstream inputStream(way.c_str());

        string inputStr;
        getline(inputStream, inputStr);

        string bufer = "";
        for (int i = 0; i < inputStr.size(); i++){
            if (inputStr[i] == ' '){
                names.push_back(bufer);
                bufer = "";
            }
            else {
                bufer = bufer + inputStr[i];
            }
        }
        if (bufer != "") names.push_back(bufer);

        while (!inputStream.eof()) {
            bufer = "";

            getline(inputStream, inputStr);
            // cout << inputStr << endl;
            vector <string> bufV;

            for (int i = 0; i < inputStr.size(); i++){
                if (inputStr[i] == ' '){
                    // cout << bufer << endl;
                    bufV.push_back(bufer);
                    bufer = "";
                }
                else {
                    bufer = bufer + inputStr[i];
                }
            }
            if (bufer != "")bufV.push_back(bufer);

            data.push_back(bufV);

        }
    }

    void coutData(){
        for (string currentName : names)
            cout << setw(15) << currentName;

        cout << endl;

        for (vector <string> currentLine : data){
            for (int i = 0; i < currentLine.size(); i++)
                cout << setw(15) << currentLine[i];
            cout << endl;
        }
    }

    void reWriteTxt(string path) {
        ofstream outputStream;
        outputStream.open(path);

        for (string currentName : names)
            outputStream << currentName << " ";

        outputStream << endl;

        int counter = 0;
        for (vector <string> currentLine : data){
            for (int i = 0; i < currentLine.size(); i++)
                outputStream << currentLine[i] << " ";
            if ((data.size() - 1) != counter ) outputStream << endl;
            counter += 1;
        }

    }

    void deleteString(string id) {

        vector < vector < string > > vectWithOutId;
        bool wasDeleted = 0;
        for (int i = 0; i < data.size(); i++){
            if (data[i][0] != id){
                vectWithOutId.push_back(data[i]);
            }
            else {
                wasDeleted = 1;
            }
        }

        data = vectWithOutId;

    }
};

void printAvaivlbleCommands() {

    cout << "Main commands: " << endl;
    cout << "1 - Show Tables" << endl;
    cout << "2 - Add String" << endl;
    cout << "3 - Delete String with OUT Dependences" << endl;
    cout << "4 - Delete String with Dependences" << endl;
    cout << "5 - Clear Console" << endl;
    cout << "6 - Close Programm" << endl;
}

int chooseTable() {
    int output;
    cout << "Choose table: " << endl;
    cout << "1 - Grades" << endl;
    cout << "2 - Pupils" << endl;
    cout << "3 - Coureses" << endl;
    cin >> output;
    return output;
}

int main(void) {

    int a;

    Table tableGrades;
    Table tableCourses;
    Table tablePupils;

    while (true) {

        printAvaivlbleCommands();

        tableGrades.preLoadData("dbGrades.txt");
        tablePupils.preLoadData("dbPupils.txt");
        tableCourses.preLoadData("dbCourses.txt");

        cin >> a;

        switch (a) {

        case 1:{
            int userChoose = chooseTable();

            switch (userChoose) {
            case 1:{
                tableGrades.coutData();
                break;
            }
            case 2:{
                tablePupils.coutData();
                break;
            }
            case 3:{
                tableCourses.coutData();
                break;
            }
            }

            break;
        }

        case 6:{
            cout << endl << "You've come a long way, hero, go to your well-deserved rest" << endl;
            return 0;
            break;
        }

        case 2:{
            int userChoose = chooseTable();

            switch (userChoose) {

            case 1:{
                Grades myGrades;
                cout << "input pupil id - ";
                cin >> myGrades.idPupil;
                cout << "input course id - ";
                cin >> myGrades.idCourse;
                cout << "input grade - ";
                cin >> myGrades.grade;

                int tableSize = tableGrades.data.size();
                int da = atoi(tableGrades.data
                              [tableSize-1]
                        [0].c_str()
                        );

                vector <string> vect;
                vect.push_back(to_string(da + 1));
                vect.push_back(myGrades.idPupil);
                vect.push_back(myGrades.idCourse);
                vect.push_back(myGrades.grade);

                tableGrades.data.push_back(vect);
                tableGrades.reWriteTxt("dbGrades.txt");

                tableGrades.coutData();
                break;
            }
            case 2:{
                Pupils myPupiles;
                cout << "input name - ";
                cin >> myPupiles.name;
                cout << "input course surName - ";
                cin >> myPupiles.surName;
                cout << "input age - ";
                cin >> myPupiles.age;
                cout << "input class - ";
                cin >> myPupiles.qclass;

                int tableSize = tablePupils.data.size();
                int da = atoi(tablePupils.data
                              [tableSize-1]
                        [0].c_str()
                        );

                vector <string> vect;
                vect.push_back(to_string(da + 1));
                vect.push_back(myPupiles.name);
                vect.push_back(myPupiles.surName);
                vect.push_back(myPupiles.age);
                vect.push_back(myPupiles.qclass);

                tablePupils.data.push_back(vect);
                tablePupils.reWriteTxt("dbPupils.txt");

                tablePupils.coutData();
                break;
            }
            case 3:{
                Courses myCourses;

                cout << "input pupil name of course - ";
                cin >> myCourses.couresName;

                int tableSize = tableCourses.data.size();
                int da = atoi(tableCourses.data
                              [tableSize-1]
                        [0].c_str()
                        );

                vector <string> vect;
                vect.push_back(to_string(da + 1));
                vect.push_back(myCourses.couresName);

                tableCourses.data.push_back(vect);
                tableCourses.reWriteTxt("dbCourses.txt");

                tableCourses.coutData();
                break;
            }

            }

            break;
        }

        case 3:{

            int userChoose = chooseTable();
            string deletingId;

            cout << "input deleting id - ";
            cin >> deletingId;

            switch (userChoose) {
            case 1:{
                tableGrades.deleteString(deletingId);
                tableGrades.reWriteTxt("dbGrades.txt");
                tableGrades.coutData();
                break;
            }
            case 2:{
                tablePupils.deleteString(deletingId);
                tablePupils.reWriteTxt("dbPupils.txt");
                tablePupils.coutData();
                break;
            }
            case 3:{
                tableCourses.deleteString(deletingId);
                tableCourses.reWriteTxt("dbCourses.txt");
                tableCourses.coutData();
                break;
            }
            }
            break;

        }

        case 4:{
            int userChoose = chooseTable();
            string deletingId;

            cout << "input deleting id - ";
            cin >> deletingId;

            switch (userChoose) {
            case 1:{
                tableGrades.deleteString(deletingId);
                tableGrades.reWriteTxt("dbGrades.txt");
                tableGrades.coutData();
                break;
            }
            case 2:{
                tablePupils.deleteString(deletingId);
                tablePupils.reWriteTxt("dbPupils.txt");
                tablePupils.coutData();
                cout << endl;

                vector < vector < string > > vectWithOutId;
                for (int i = 0; i < tableGrades.data.size(); i++){
                    if (tableGrades.data[i][1] != deletingId){
                        vectWithOutId.push_back(tableGrades.data[i]);
                    }
                }

                tableGrades.data = vectWithOutId;
                tableGrades.reWriteTxt("dbGrades.txt");
                tableGrades.coutData();

                break;
            }
            case 3:{
                tableCourses.deleteString(deletingId);
                tableCourses.reWriteTxt("dbCourses.txt");
                tableCourses.coutData();

                cout << endl;

                vector < vector < string > > vectWithOutId;
                for (int i = 0; i < tableGrades.data.size(); i++){
                    if (tableGrades.data[i][2] != deletingId){
                        vectWithOutId.push_back(tableGrades.data[i]);
                    }
                }

                tableGrades.data = vectWithOutId;
                tableGrades.reWriteTxt("dbGrades.txt");
                tableGrades.coutData();

                break;
            }
            }
            break;

            break;
        }

        case 5:{
            if (system("CLS")) system("clear");
            break;
        }

        }

    }

}
