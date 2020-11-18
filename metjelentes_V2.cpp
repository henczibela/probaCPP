#include <iostream>
#include <fstream>
#include <cmath>
#include "string.h"
#include <cstdlib>

using namespace std;

struct tavirat {
    string telepules, ido, szel;
    int homerseklet;
};

string idoForma(string szo)
{
    string valami = szo.substr(0,2) + ":" + szo.substr(2,2);
    return valami;
}

int ora(string szo)
{
    string o = szo.substr(0,2);
    char oo[3];
    strcpy(oo,o.c_str());
    int ooo = atoi(oo);
    return ooo;
}
int szelEro(string szo)
{
    string o = szo.substr(3,2);
    char oo[3];
    strcpy(oo,o.c_str());
    int ooo = atoi(oo);
    return ooo;
}

int main()
{
    tavirat adatok[501];
    ifstream bemenetiFajl;
    bemenetiFajl.open("tavirathu13.txt");
    int db=0;
    while (!bemenetiFajl.eof())
    {
        bemenetiFajl >> adatok[db].telepules >> adatok[db].ido >> adatok[db].szel >> adatok[db].homerseklet;
        if (!bemenetiFajl.fail())
        {
            db++;
        }
    }
    bemenetiFajl.close();
    //cout << adatok[db-1].homerseklet;
    // -------------------------------------------
    cout << "2. feladat" << endl;
    string telepulesKod;
    cout << "Adja meg egy telepules kodjat! Telepules: ";
    cin >> telepulesKod;
    int i = db-1;
    while (i>=0 && adatok[i].telepules != telepulesKod)
    {
        i--;
    }
    if (i>=0)
    {
        string idopont = idoForma(adatok[i].ido);
        cout << "Az utolso meresi adat a telepulesrol " << idopont << "-kor erkezett" << endl;
    }
    else
    {
        cout << "Nincs ilyen telepuleskod az adatok kozott" << endl;
    }
    // -------------------------------------------
    cout << "3. feladat" << endl;
    int mini=0, maxi=0;
    for (int j=1;j<db;j++)
    {
        if (adatok[j].homerseklet < adatok[mini].homerseklet)
        {
            mini = j;
        }
        if (adatok[j].homerseklet > adatok[maxi].homerseklet)
        {
            maxi = j;
        }
    }
    string minIdopont = idoForma(adatok[mini].ido);
    cout << "A legalacsonyabb homerseklet: " << adatok[mini].telepules << " " << minIdopont << " " << adatok[mini].homerseklet << " fok" << endl;
    string maxIdopont = idoForma(adatok[maxi].ido);
    cout << "A legmagasabb homerseklet: " << adatok[maxi].telepules << " " << maxIdopont << " " << adatok[maxi].homerseklet << " fok" << endl;
    // -------------------------------------------
    cout << "4. feladat" << endl;
    int szelcsendDb = 0;
    for (int j=0;j<db;j++)
    {
        if (adatok[j].szel=="00000")
        {
            string idopont = idoForma(adatok[j].ido);
            cout << adatok[j].telepules << " " << idopont << endl;
            szelcsendDb++;
        }
    }
    if (szelcsendDb==0)
    {
        cout << "Nem volt szelcsend a meresek idejen." << endl;
    }
    // -------------------------------------------
    cout << "5. feladat" << endl;
    tavirat adatok2[501];
    for (int j=0;j<db;j++)
    {
        adatok2[j] = adatok[j];
    }
    // adatok2 tömb rendezése település szerint
    for (int j=0;j<db;j++)
    {
        int mini = j;
        for (int k=j+1;k<db;k++)
        {
            if (adatok2[k].telepules<adatok2[mini].telepules)
            {
                mini = k;
            }
        }
        tavirat doboz=adatok2[j];
        adatok2[j]=adatok2[mini];
        adatok2[mini]=doboz;
    }
    //cout << adatok2[0].telepules << endl;
    int dbOrankent[24], osszegOrankent[24];
    i=0;
    int minHomerseklet, maxHomerseklet, osszeg=0, darab=0;
    string telepules;
    while (i<db)
    {
        for (int j=0;j<24;j++)
        {
            dbOrankent[j] = 0;
            osszegOrankent[j] = 0;
        }
        telepules=adatok2[i].telepules;
        minHomerseklet=adatok2[i].homerseklet; maxHomerseklet=adatok2[i].homerseklet;
        dbOrankent[ora(adatok2[i].ido)]++;
        osszegOrankent[ora(adatok2[i].ido)] = osszegOrankent[ora(adatok2[i].ido)] + adatok2[i].homerseklet;
        i++;
        while (i<db && adatok2[i].telepules==telepules)
        {
            dbOrankent[ora(adatok2[i].ido)]++;
            osszegOrankent[ora(adatok2[i].ido)] = osszegOrankent[ora(adatok2[i].ido)] + adatok2[i].homerseklet;
            if (adatok2[i].homerseklet<minHomerseklet)
            {
                minHomerseklet=adatok2[i].homerseklet;
            }
            if (adatok2[i].homerseklet>maxHomerseklet)
            {
                maxHomerseklet=adatok2[i].homerseklet;
            }
            i++;
        }
        cout << telepules << " Kozephomerseklet: ";
        if (dbOrankent[1]*dbOrankent[7]*dbOrankent[13]*dbOrankent[19] == 0)
        {
            cout << "NA;";
            //cout << osszegDb;
        }
        else
        {
            osszeg = osszegOrankent[1]+osszegOrankent[7]+osszegOrankent[13]+osszegOrankent[19];
            darab = dbOrankent[1]+dbOrankent[7]+dbOrankent[13]+dbOrankent[19];
            cout << (int)round(osszeg/darab)<< ";";
        }
        cout << " Homerseklet-ingadozas: " << maxHomerseklet-minHomerseklet << endl;
    }
    // -------------------------------------------
    cout << "6. feladat" << endl;
    i=0;
    while (i<db)
    {
        string telepules = adatok2[i].telepules;
        string fajlnev = telepules + ".txt";
        char fajlnev2[7];
        strcpy(fajlnev2,fajlnev.c_str());
        ofstream kimenet;
        kimenet.open(fajlnev2);
        kimenet << adatok2[i].telepules << endl;
        while (i<db && telepules==adatok2[i].telepules)
        {
            kimenet << idoForma(adatok2[i].ido) << " ";
            for (int j=1;j<=szelEro(adatok2[i].szel);j++)
            {
                kimenet << "#";
            }
            kimenet << endl;
            i++;
        }
        kimenet.close();
    }
	// Itt a vége
    return 0;
}
