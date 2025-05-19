#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <algorithm>
#include <fstream>
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;
using cell = pair<double, double>;

void solver(cell** field, cell** result, int STEPSX, int STEPSY, double deltaX, double deltaY, double dt, int ts){
    for(int time = 0; time < ts; time++){
        for(int i = 1; i < STEPSY+1; i++){
            for(int j = 1; j < STEPSX+1; j++){
                double J_r = 2*field[i][j].first*field[i][j+1].first/(field[i][j].first+field[i][j+1].first) * (field[i][j+1].second-field[i][j].second) / deltaX;
                double J_l = 2*field[i][j].first*field[i][j-1].first/(field[i][j].first+field[i][j-1].first) * (field[i][j-1].second-field[i][j].second) / deltaX;
                double J_u = 2*field[i][j].first*field[i+1][j].first/(field[i][j].first+field[i+1][j].first) * (field[i+1][j].second-field[i][j].second) / deltaY;
                double J_d = 2*field[i][j].first*field[i-1][j].first/(field[i][j].first+field[i-1][j].first) * (field[i-1][j].second-field[i][j].second) / deltaY;
                double divJ = (J_r + J_l)/deltaX + (J_u + J_d)/deltaY;
                result[i][j].first = field[i][j].first;
                result[i][j].second = field[i][j].second + divJ*dt;
            }
        }
        for(int j = 1; j < STEPSX+1; j++){
            result[0][j] = result[1][j];
            result[STEPSY+1][j] = result[STEPSY][j]; //memcpi
        }
        for(int i = 1; i < STEPSY+1; i++){
            result[i][0] = field[i][0];
            result[i][STEPSX+1] = field[i][STEPSX+1];
        }
        for(int i = 0; i < STEPSY+2; i++){
            for(int j = 0; j < STEPSX+2; j++){
                field[i][j] = result[i][j]; //swap
            }
        }
        // swap(result, field);
    }
    return;
}

void print(cell** field, int STXR, int STYR){
    static int n = 0;
    ofstream f("data/"+to_string(n)+".csv");
    for(int i = 0; i < STYR; i++){
        for(int j = 0; j < STXR; j++){
            if (j!=STXR-1) f << field[i][j].second << ' ';
            else f << field[i][j].second;
        }
        f << '\n';
    }
    n++;
}



int main (int argc, char* argv[]){
    ifstream f(argv[1]);  // read config
    json data = json::parse(f); 
    int STEPSX = data["STEPSX"];
    int STEPSY = data["STEPSY"];
    int STXR = STEPSX + 2;
    int STYR = STEPSY + 2;
    int WIDTH = data["WIDTH"];
    int LENGTH = data["LENGTH"];
    double dt = data["dt"];
    int ts = data["timesteps"];
    cell** field = new cell*[STYR];
    cell** result = new cell*[STYR];

    for(int i = 0; i < STYR; i++){
        field[i] = new cell[STXR];
        result[i] = new cell[STXR]{pair<double, double>(0,0)};
        if(data["type"]=="manual"){
            if(i==0){
                for(int j = 0; j < STEPSX; j++){
                    field[i][j+1].first = data["sgm"][i][j];
                    field[i][j+1].second = static_cast<double>(data["phi"][i][j])+static_cast<double>(data["BC"]["U"]["j"]);
                }
                continue;
            }
            if(i==STYR-1){
                for(int j = 0; j < STEPSX; j++){
                    field[i][j+1].first = data["sgm"][i-2][j];
                    field[i][j+1].second = static_cast<double>(data["phi"][i-2][j])+static_cast<double>(data["BC"]["D"]["j"]);
                }
                continue;
            }

            for(int j = 0; j < STXR; j++){
                if(j==0){
                    field[i][j].first = data["sgm"][i-1][j];
                    field[i][j].second = data["BC"]["L"]["Phi"];
                    continue;
                }
                if(j==STXR-1){
                    field[i][j].first = data["sgm"][i-1][j-2];
                    field[i][j].second = data["BC"]["R"]["Phi"];
                    continue;
                }
                field[i][j].first = data["sgm"][i-1][j-1];
                field[i][j].second = data["phi"][i-1][j-1];
            }
        }
        else if(data["type"]=="auto"){
            if(i==0){
                for(int j = 0; j < STEPSX; j++){
                    field[i][j+1].first = 1;
                    field[i][j+1].second = 0+static_cast<double>(data["BC"]["U"]["j"]);
                }
                continue;
            }
            if(i==STYR-1){
                for(int j = 0; j < STEPSX; j++){
                    field[i][j+1].first = 1;
                    field[i][j+1].second = 0+static_cast<double>(data["BC"]["D"]["j"]);
                }
                continue;
            }

            for(int j = 0; j < STXR; j++){
                if(j==0){
                    field[i][j].first = 1;
                    field[i][j].second = data["BC"]["L"]["Phi"];
                    continue;
                }
                if(j==STXR-1){
                    field[i][j].first = 1;
                    field[i][j].second = data["BC"]["R"]["Phi"];
                    continue;
                }
                field[i][j].first = 1;
                field[i][j].second = 0;
            }
        }
        else if(data["type"]=="auto_linear"){
            if(i==0){
                for(int j = 0; j < STEPSX; j++){
                    field[i][j+1].first = (1.+i+j)/(STEPSY+STEPSX);
                    field[i][j+1].second = 0+static_cast<double>(data["BC"]["U"]["j"]);
                }
                continue;
            }
            if(i==STYR-1){
                for(int j = 0; j < STEPSX; j++){
                    field[i][j+1].first = (1.+i+j)/(STEPSY+STEPSX);
                    field[i][j+1].second = 0+static_cast<double>(data["BC"]["D"]["j"]);
                }
                continue;
            }

            for(int j = 0; j < STXR; j++){
                if(j==0){
                    field[i][j].first = (1.+i+j)/(STEPSY+STEPSX);
                    field[i][j].second = data["BC"]["L"]["Phi"];
                    continue;
                }
                if(j==STXR-1){
                    field[i][j].first = (1.+i+j)/(STEPSY+STEPSX);
                    field[i][j].second = data["BC"]["R"]["Phi"];
                    continue;
                }
                field[i][j].first = (1.+i+j)/(STEPSY+STEPSX);
                field[i][j].second = 0;
            }
        }
    }
    print(field, STXR, STYR);
    solver(field, result, STEPSX, STEPSY, static_cast<double>(WIDTH)/STEPSX, static_cast<double>(LENGTH)/STEPSY, dt, ts);
    print(field, STXR, STYR);



    for (int i = 0; i < STYR; i++) delete[] field[i];
    delete[] field;
    return 0;
}
