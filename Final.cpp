#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <fstream>
#include <map>
using namespace std;

string getCurrentDate()
{
    time_t now = time(0);
    tm *ltm = localtime(&now);
    char buffer[11];
    sprintf(buffer, "%04d-%02d-%02d", 1900 + ltm->tm_year, 1 + ltm->tm_mon, ltm->tm_mday);
    return string(buffer);
}

class StudyLog
{
private:
    string Date;
    string Subject;
    double Duration;
    string Description;

public:
    StudyLog(string A, string B, double C, string D)
    {
        this->Date = A;
        this->Subject = B;
        this->Duration = C;
        this->Description = D;
    }

    string getDate() const { return Date; }
    string getSubject() const { return Subject; }
    double getDuration() const { return Duration; }
    string getDescription() const { return Description; }

    friend ostream &operator<<(ostream &out, const StudyLog &obj)
    {
        out << obj.Date << " | "
            << obj.Subject << " | "
            << obj.Duration << " | "
            << obj.Description;
        return out;
    }
};

class StudyTracker
{
private:
    vector<StudyLog> Database;

public:
    void InsertLog()
    {
        cout << "----------------------------------------------------\n";
        cout << "--- Please enter the valid details of your study ---\n";
        cout << "----------------------------------------------------\n";

        string date = getCurrentDate();

        cout << "Please provide the name of subject like C/C++/Java/OS/DS: ";
        string sub;
        cin.ignore();
        getline(cin, sub);

        cout << "Enter the time period of your study in hours: ";
        double dur;
        cin >> dur;
        cin.ignore();

        cout << "Please provide the description about the study for future reference: ";
        string desc;
        getline(cin, desc);

        StudyLog sobj(date, sub, dur, desc);
        Database.push_back(sobj);

        cout << "Study Log stored successfully\n";
        cout << "----------------------------------------------------\n";
    }

    void DisplayLog()
    {
        cout << "----------------------------------------------------\n";
        if (Database.empty())
        {
            cout << "Nothing to display as database is empty\n";
            cout << "----------------------------------------------------\n";
            return;
        }

        cout << "---- Log report from Study Tracker ------\n";
        for (const auto &sobj : Database)
        {
            cout << sobj << endl;
        }
        cout << "----------------------------------------------------\n";
    }

    void ExportCSV()
    {
        if (Database.empty())
        {
            cout << "----------------------------------------------------\n";
            cout << "Nothing to export as database is empty\n";
            cout << "----------------------------------------------------\n";
            return;
        }

        string FileName = "Study.csv";
        ofstream fwobj(FileName);

        if (!fwobj)
        {
            cout << "Error creating file.\n";
            return;
        }

        fwobj << "Date,Subject,Duration,Description\n";

        for (const auto &sobj : Database)
        {
            fwobj << sobj.getDate() << ","
                  << sobj.getSubject() << ","
                  << sobj.getDuration() << ","
                  << sobj.getDescription() << "\n";
        }

        fwobj.close();
        cout << "Log exported successfully to " << FileName << "\n";
    }

    void SummaryByDate()
    {
        cout << "----------------------------------------------------\n";
        if (Database.empty())
        {
            cout << "Nothing to display as database is empty\n";
            cout << "----------------------------------------------------\n";
            return;
        }

        cout << "-- Summary By Date from  Study Tracker ---\n";
        map<string, double> tobj;

        for (const auto &sobj : Database)
        {
            tobj[sobj.getDate()] += sobj.getDuration();
        }

        for (auto &entry : tobj)
        {
            cout << "Date: " << entry.first
                 << " | Total Study: " << entry.second << " hrs\n";
        }
        cout << "----------------------------------------------------\n";
    }

    void SummaryBySubject()
    {
        cout << "----------------------------------------------------\n";
        if (Database.empty())
        {
            cout << "Nothing to display as database is empty\n";
            cout << "----------------------------------------------------\n";
            return;
        }

        cout << "-- Summary By Subject from Study Tracker --\n";
        map<string, double> tobj;

        for (const auto &sobj : Database)
        {
            tobj[sobj.getSubject()] += sobj.getDuration();
        }

        for (auto &entry : tobj)
        {
            cout << "Subject: " << entry.first
                 << " | Total Study: " << entry.second << " hrs\n";
        }
        cout << "----------------------------------------------------\n";
    }
};

int main()
{
    StudyTracker stobj;
    int iChoice = 0;

    cout << "----------------------------------------------------\n";
    cout << "-- Welcome to Study Tracker Application --\n";
    cout << "----------------------------------------------------\n";

    do
    {
        cout << "Please select the appropriate option\n";
        cout << "1 : Insert new Study Log into Database\n";
        cout << "2 : View All Study Logs\n";
        cout << "3 : Summary of Study Log by Date\n";
        cout << "4 : Summary of Study Log by Subject\n";
        cout << "5 : Export Study Log to CSV file\n";
        cout << "6 : Exit the application\n";

        cin >> iChoice;

        switch (iChoice)
        {
        case 1:
            stobj.InsertLog();
            break;

        case 2:
            stobj.DisplayLog();
            break;

        case 3:
            stobj.SummaryByDate();
            break;

        case 4:
            stobj.SummaryBySubject();
            break;

        case 5:
            stobj.ExportCSV();
            break;

        case 6:
            cout << "----------------------------------------------------\n";
            cout << "Thank you for using Study Log application\n";
            cout << "----------------------------------------------------\n";
            break;

        default:
            cout << "Please enter a valid option\n";
        }

    } while (iChoice != 6);

    return 0;
}
