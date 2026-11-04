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

    if (newInf> sus) sus=0;
    else sus -=newInf;
    if (inf + newInf - newRec >sum) inf = sum - sus - rec;
    else inf += newInf - newRec;
    if (rec + newRec >sum) rec = sum - sus - inf;
    else rec += newRec;

    day++;

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
        cout<<"3. Exit"<<endl;
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
                running = false;
                break;
            default:
                cout<<"Wrong choice. Type number betwenn 1 and 3."<<endl;

        }
        // if (!checkPopulation(sus,inf,rec)) {
        //     cout<<"Error: Population was changed. Expected - 100, got - "<<sus+inf+rec<<endl;
        //     running = false;
        // }
    }
}

int main() {
    int susceptible = 80;  // podatni
    int infected = 10;     // aktualnie zarażeni
    int recovered = 10;    // uzdrowieńcy
    int day = 0;
    const int sumOfPeople = susceptible + infected + recovered;

    double infectionRate = 0.2;  // współczynnik zakażeń
    double recoveryRate = 0.1;   // współczynnik wyzdrowień

    menu(day, susceptible, infected, recovered, infectionRate, recoveryRate, sumOfPeople);

    return 0;
}