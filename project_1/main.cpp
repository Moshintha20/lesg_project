#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <list>

using namespace std;

bool compare_p(const vector<string> v1, const vector<string> v2){
    return (stoi(v1[4]) < stoi(v2[4]));
}

bool compare_pr(const vector<string> v1, const vector<string> v2){
    return (stoi(v1[4]) > stoi(v2[4]));
}


void classify_data(const string &filename)
{
    ifstream fin(filename);  // filecontains:   client, name,side, quantity, price, orderid

    if (!fin.is_open())
        return;

    string line;
    if (!getline(fin, line))
        return;

    list<vector<string>> lotus_s,lotus_b;
    list<vector<string>> lavender_s,lavender_b;
    list<vector<string>> tulip_s,tulip_b;
    list<vector<string>> orchid_s, orchid_b;
    list<vector<string>> rose_s, rose_b;

    while (getline(fin, line))
    {
        stringstream s(line);
        vector<string> fields;
        string field;

        while (getline(s, field, ','))
        {
            fields.push_back(field);
        }
        if (fields[1]=="Rose"){
            if (fields[2]=="2"){    // for buyer side ascending order
                if (rose_s.size()==0){
                    rose_s.push_back(fields);
                } else {
                    rose_s.push_back(fields);
                    sort(rose_s.begin(), rose_s.end(), compare_p);
                }
                cout<< "size of the seller_rose= "<<rose_s.size()<<endl;

            }else if (fields[2]=="1"){
                if (rose_b.size()==0){
                    rose_b.push_back(fields);
                } else {
                    rose_b.push_back(fields);
                    sort(rose_b.begin(), rose_b.end(), compare_pr);
                }
                cout<< "size of the buyer_rose= "<<rose_b.size()<<endl;

            }

        } else if (fields[1]=="Lavender"){
            if (fields[2]=="2"){    // for buyer side ascending order
                if (lavender_s.size()==0){
                    lavender_s.push_back(fields);
                } else {
                    lavender_s.push_back(fields);
                    sort(lavender_s.begin(), lavender_s.end(), compare_p);

                }
            } else if (fields[1]=="1"){
                if (lavender_b.size()==0){
                    lavender_b.push_back(fields);
                } else {
                    lavender_b.push_back(fields);
                    sort(lavender_b.begin(), lavender_b.end(), compare_pr);

                }
            }


        } else if (fields[1]=="Lotus"){
            if (fields[2]=="2"){    // for buyer side ascending order
                if (lotus_s.size()==0){
                    lotus_s.push_back(fields);
                } else {
                    lotus_s.push_back(fields);
                    sort(lotus_s.begin(), lotus_s.end(), compare_p);

                }
            }else if (fields[2]=="1"){
                if (lotus_b.size()==0){
                    lotus_b.push_back(fields);
                } else {
                    lotus_b.push_back(fields);
                    sort(lotus_b.begin(), lotus_b.end(), compare_pr);

                }
            }


        } else if (fields[1]=="Tulip"){
            if (fields[2]=="2"){    // for buyer side ascending order
                if (tulip_s.size()==0){
                    tulip_s.push_back(fields);
                } else {
                    tulip_s.push_back(fields);
                    sort(tulip_s.begin(), tulip_s.end(), compare_p);
                }
            } else if (fields[2]=="1"){
                if (tulip_b.size()==0){
                    tulip_b.push_back(fields);
                } else {
                    tulip_b.push_back(fields);
                    sort(tulip_b.begin(), tulip_b.end(), compare_pr);

                }
            }


        } else if (fields[1]=="Orchid"){
            if (fields[2]=="2"){    // for buyer side ascending order
                if (orchid_s.size()==0){
                    orchid_s.push_back(fields);
                } else {
                    orchid_s.push_back(fields);
                    sort(orchid_s.begin(), orchid_s.end(), compare_p);
                }
            }else if (fields[2]=="1"){
                if (orchid_b.size()==0){
                    orchid_b.push_back(fields);
                } else {
                    orchid_b.push_back(fields);
                    sort(orchid_b.begin(), orchid_b.end(), compare_pr);;
                }
            }
        }

    }
}



int main()
{

    classify_data("reportcard.csv");



    return 0;
}