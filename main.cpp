#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>
using namespace std;
int vStari[100];
int dfa(string a[100][100], int stareInitiala, int n, char litera)
{
    int stareCurenta = stareInitiala;

    for(int j=0; j<n + stareInitiala; j++)
        if(a[stareCurenta][j].find(litera) != string:: npos){
                stareCurenta = j;
                return stareCurenta;
        }
}

int main()
{
    ifstream f("date.in");
    ofstream g("date.out");
    int n, stareInitiala, e[100][100];
    f>>n;
    f>>stareInitiala;
    string a[100][100], stariFinale, alfabet;
    f>>stariFinale;
    f>>alfabet;

    for(int i=0; i<100 ; i++)
        for(int j=0; j<100 ; j++)
            a[i][j] = "-";

    for(int i=0; i<n; i++){
        int x;
        f>>x;
        for(int j=0; j<alfabet.length(); j++){
            int y;
            f>>y;
            if(a[x][y] != "-")
                a[x][y]+=alfabet[j];
            else {
                a[x][y].pop_back();
                a[x][y]+=alfabet[j];
            }
        }
    }

    for(int i=stareInitiala; i<stareInitiala+n; i++)
        for(int j=stareInitiala; j<stareInitiala+n; j++){
            e[i][j] = 1;
            if(i != j){
                if((stariFinale.find('0' + i) == string :: npos && stariFinale.find('0' + j) != string :: npos) ||
                   (stariFinale.find('0' + i) != string :: npos && stariFinale.find('0' + j) == string :: npos))
                    e[i][j] = 0;}
            else e[i][j] = -1;

    }



    int ok = 1;
    while(ok){
        ok = 0;
        for(int i=stareInitiala+1; i<n; i++)
            for(int j=stareInitiala; j < i; j++)
                for(int k=0; k<alfabet.length(); k++){
                    int i2 = dfa(a, i, n, alfabet[k]);
                    int j2 = dfa(a, j, n, alfabet[k]);
                    if(i2 < j2)
                        swap(i2, j2);
                    if(e[i2][j2] == 0 && e[i][j] != 0 && i2 != j2){
                        e[i][j] = 0;
                        ok = 1;
                        break;
                    }
                }
        }
/*
    for(int i=stareInitiala; i<stareInitiala+n; i++){
        for(int j=stareInitiala; j<stareInitiala+n; j++)
            cout<<e[i][j]<<" ";
        cout<<endl;
    }
*/
    vector <string> stariNoi;
    int n2=0;
    for(int j=stareInitiala; j<stareInitiala+n; j++){
        if(!vStari[j]){
            string aux = ""; aux += ('0' + j);
            stariNoi.push_back(aux);
            n2++;
            vStari[j]++;

        for(int i=j+1; i<stareInitiala + n; i++)
            if(e[i][j] == 1){
                stariNoi.back() += ('0' + i);
                vStari[i]++;
            }
        }
    }
    g<<"Nr. stari: "<<n2<<endl<<"Stare initiala: "<<stariNoi.at(0)<<endl;
    g<<"Stari finale: ";
    for(int i=0; i<stariNoi.size(); i++)
        for(int k=0; k<stariNoi.at(i).length(); k++)
                if(stariFinale.find(stariNoi.at(i)[k]) != string::npos){
                    g<<stariNoi.at(i)<<" ";
                    break;
            }
    g<<endl;
    g<<"Alfabet: "<<alfabet<<endl;
    g<<"Tabel de tranzitii: "<<endl;
    for(int i=0; i<stariNoi.size(); i++){
        g<<stariNoi.at(i)<<" ";
        for(int j=0; j<alfabet.length(); j++){
            int x = dfa(a, (stariNoi.at(i)[0] - '0'), n, alfabet[j]);
            for(int k=0; k<stariNoi.size(); k++)
                if(stariNoi.at(k).find('0' + x) != string::npos){
                    g<<stariNoi.at(k);
                    break;
            }
            g<<" ";
        }
        g<<endl;
    }
    return 0;
}
