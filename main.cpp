#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>
#include <algorithm>
using namespace std;
int vStari[100];
int dfa(string a[100][100], int stareInitiala, int n, char litera)
{
    int stareCurenta = stareInitiala;

    for(int j=0; j<100; j++)
        if(a[stareCurenta][j].find(litera) != string:: npos){
                stareCurenta = j;
                return stareCurenta;
        }
}

int main()
{
    ifstream f("date.in");
    ofstream g("date.out");
    int n, stareInitiala, e[100][100], nrFin, aux;
    f>>n;
    f>>stareInitiala;
    f>>nrFin;
    string a[100][100], alfabet;
    vector <int> stariFinale;
    for(int i=0; i<nrFin; i++){
        f>>aux;
        stariFinale.push_back(aux);
    }
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
                if((find(stariFinale.begin(), stariFinale.end(), i) != stariFinale.end() &&
                    find(stariFinale.begin(), stariFinale.end(), j) == stariFinale.end()) ||
                   (find(stariFinale.begin(), stariFinale.end(), j) != stariFinale.end() &&
                    find(stariFinale.begin(), stariFinale.end(), i) == stariFinale.end()))
                        e[i][j] = 0;}
            else e[i][j] = -1;

    }

    int ok = 1;
    while(ok){
        ok = 0;
        for(int i=stareInitiala+1; i<stareInitiala + n; i++)
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
            stariNoi.push_back(to_string(j));
            n2++;
            vStari[j]++;

        for(int i=j+1; i<stareInitiala + n; i++)
            if(e[i][j] == 1){
                stariNoi.back() += (to_string(i));
                vStari[i]++;
            }
        }
    }
    g<<"Nr. stari: "<<n2<<endl<<"Stare initiala: "<<stariNoi.at(0)<<endl;
    g<<"Stari finale: ";
    for(int i=0; i<stariNoi.size(); i++)
        for(int k=0; k<stariFinale.size(); k++)
                if(stariNoi.at(i).find(to_string(stariFinale.at(k))) != string::npos){
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
            if(x < 0)
                x = dfa(a, stoi(stariNoi.at(i).substr(0, 2)), n, alfabet[j]);
            for(int k=0; k<stariNoi.size(); k++)
                if(stariNoi.at(k).find(to_string(x)) != string::npos){
                    g<<stariNoi.at(k);
                    break;
            }
            g<<" ";
        }
        g<<endl;
    }
    return 0;
}
