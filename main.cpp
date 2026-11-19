// ======= Variable definitions =======

// sus - susceptible at the beginning of the day
// inf - infected at the beginning of the day
// rec - recovered at the beginning of the day
//
// newInf - new infected during the day
// newRec - new recovered during the day
//
// infRate - infection rate
// recRate - recovery rate
//
// newInfRate - new infection rate
// newRecRate - new recovery rate

#include <iostream>
#include <cmath>

using namespace std;

const int MAX_DAYS = 100;

int populationHistory[MAX_DAYS][3];
int dailyNewInfections[MAX_DAYS]={};
int dailyRecoveries[MAX_DAYS]={};


void showPopulation(int &day, int &susceptible, int &infected, int &recovered);
void simulateDay(int &day, int &sus, int &inf, int &rec, double &infRate, double &recRate, const int &sum);
void changeParameters(double &infRate, double &recRate);
bool checkPopulation(int &sus, int &inf, int &rec);
void menu(int &day, int &sus, int &inf, int &rec, double &infRate, double &recRate, const int &sum);
void showPopulationHistory(int &day);

int main() {
    int susceptible = 80;  // podatni
    int infected = 10;     // aktualnie zarażeni
    int recovered = 10;    // uzdrowieńcy
    int day = 0;
    const int sumOfPeople = susceptible + infected + recovered;

    double infectionRate = 0.2;  // współczynnik zakażeń
    double recoveryRate = 0.1;   // współczynnik wyzdrowień

    populationHistory[0][0] = susceptible;
    populationHistory[0][1] = infected;
    populationHistory[0][2] = recovered;

    menu(day, susceptible, infected, recovered, infectionRate, recoveryRate, sumOfPeople);

    return 0;
}

void showPopulation(int &day, int &susceptible, int &infected, int &recovered) {
    cout<<"Day: "<<day<<endl;
    cout<<"Susceptible: "<<susceptible<<endl;
    cout<<"Infection: "<<infected<<endl;
    cout<<"Recovery: "<<recovered<<endl;
    cout<<"Total: "<<susceptible+infected+recovered<<endl;
}

void simulateDay(int &day, int &sus, int &inf, int &rec, double &infRate, double &recRate, const int &sum) {
    int newInf = floor(inf * infRate);
    int newRec = floor(rec * recRate);
    if (newInf<0 || newRec < 0) {
        cout<<"Error: newInf or newRec is less than 0"<<endl;
    }
    if (newInf>sus) newInf = sus;
    if (newRec>inf) newRec = inf;

    // check if every number of person is not greater than 100
    if (newInf> sus) sus=0;
    else sus -=newInf;
    if (inf + newInf - newRec >sum) inf = sum - sus - rec;
    else inf += newInf - newRec;
    if (rec + newRec >sum) rec = sum - sus - inf;
    else rec += newRec;


    day++;

    // adding to history
    populationHistory[day][0] = sus;
    populationHistory[day][1] = inf;
    populationHistory[day][2] = rec;
    dailyNewInfections[day] = newInf;
    dailyRecoveries[day] = newRec;

}

void changeParameters(double &infRate, double &recRate) {
    double newInfRate;
    double newRecRate;
    cout<<"Enter infection rate (0-1): ";
    cin>>newInfRate;
    cout<<"Enter recovery rate (0-1): ";
    cin>>newRecRate;
    if (newInfRate >=0 && newInfRate<=1 && newRecRate >=0 && newRecRate<=1) {
        infRate = newInfRate;
        recRate = newRecRate;
        cout<<"Parameters updated"<<endl;
    } else {
        cout<<"Parameters not updated"<<endl;
        cout<<"Check parameters and try again"<<endl;
    }
}

bool checkPopulation(int &sus, int &inf, int &rec) {
    if (sus<0 || inf<0 || rec<0 || sus+inf+rec!=100) {
        return false;
    } else {
        return true;
    }
}

void menu(int &day, int &sus, int &inf, int &rec, double &infRate, double &recRate, const int &sum) {
    bool running = true;
    while (running) {
        int choice;
        showPopulation(day, sus, inf,rec);
        cout<<"=== Epidemic Simulation ==="<<endl;
        cout<<"1. Simulate next day"<<endl;
        cout<<"2. Change model parameters"<<endl;
        cout<<"3. Show history"<<endl;
        cout<<"4. Exit"<<endl;
        cout<<"Your choice: ";
        cin>>choice;
        switch (choice) {
            case 1:
                simulateDay(day, sus, inf, rec, infRate, recRate, sum);
                break;
            case 2:
                changeParameters(infRate, recRate);
                break;
            case 3:
                showPopulationHistory(day);
                break;
            case 4:
                running = false;
                break;
            default:
                cout<<"Wrong choice. Type number betwenn 1 and 3."<<endl;

        }
        if (day>MAX_DAYS) {
            cout<<"Achieved limit of simulation"<<endl;
            running = false;
        }
        if (!checkPopulation(sus,inf,rec)) {
            cout<<"Error: Population was changed. Expected - 100, got - "<<sus+inf+rec<<endl;
            // cout<<sus<<" "<<inf<<" "<<rec<<endl;
            running = false;
        }
    }
}

void showPopulationHistory(int &day) {
    cout<<"Day: ";
    for (int i=0; i<=day;i++) {
        cout<<i<<" ";
    }
    cout<<endl;
    cout<<"Susceptible: ";

    for (int i=0; i<=day;i++) {
        cout<<populationHistory[i][0]<<" ";
    }
    cout<<endl;
    cout<<"Infected: ";

    for (int i=0; i<=day;i++) {
        cout<<populationHistory[i][1]<<" ";
    }
    cout<<endl;
    cout<<"Recoveries: ";
    for (int i=0; i<=day;i++) {
        cout<<populationHistory[i][2]<<" ";
    }
    cout<<endl;

    cout<<"New Infections: ";
    for (int i=0; i<=day;i++) {
        if (i!=0) {
            cout<<dailyNewInfections[i]<<" ";
        } else {
            cout<<"- ";
        }
    }
    cout<<endl;

    cout<<"New Recoveries: ";
    for (int i=0; i<=day;i++) {
        if (i!=0) {
            cout<<dailyRecoveries[i]<<" ";
        } else {
            cout<<"- ";
        }
    }
    cout<<endl;
}
