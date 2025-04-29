#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
struct match
{
    int my_goals, their_goals, my_points;
};
struct team
{
    string name;
    map<int, match> opponents;
    int all_points, goals_scored, goals_conceded, goal_difference;
};
bool compare(const map<int, team>::iterator& a, const map<int, team>::iterator& b)
{
    const team& ta = a->second;
    const team& tb = b->second;
    if(ta.all_points != tb.all_points) return ta.all_points > tb.all_points;
    if(ta.goal_difference != tb.goal_difference) return ta.goal_difference > tb.goal_difference;
    return ta.goals_scored > tb.goals_scored;
}
map<int, team> teams;
vector<map<int, team>::iterator> order;
int main()
{
    ifstream teams_file("teams.csv"), results_file("results.csv");
    ofstream table_file("table.csv");
    string line;
    while(getline(teams_file, line))
    {
        int comma = line.find(',');
        if(comma==string::npos) continue;
        string id = line.substr(0, comma);
        string name = line.substr(comma+1);
        if(id.empty() || name.empty()) continue;
        teams[stoi(id)].name = name;
    }
    for(auto i=teams.begin(); i!=teams.end(); i++)
    {
        for(auto j=teams.begin(); j!=teams.end(); j++) i -> second.opponents[j->first] = match{0,0,0};
    }
    while(getline(results_file, line))
    {
        int c1 = line.find(',');
        if(c1==string::npos) continue;
        int c2 = line.find(',', c1+1);
        if(c2==string::npos) continue;
        int c3 = line.find(',', c2+1);
        if(c3==string::npos) continue;
        if(line.find(',', c3+1) != string::npos) continue;
        int home = stoi(line.substr(0, c1));
        int away = stoi(line.substr(c1+1, c2-c1-1));
        int home_goals = stoi(line.substr(c2+1, c3-c2-1));
        int away_goals = stoi(line.substr(c3+1));
        if(!teams.count(home) || !teams.count(away)) continue;
        teams[home].opponents[away].my_goals += home_goals;
        teams[home].opponents[away].their_goals += away_goals;
        teams[away].opponents[home].my_goals += away_goals;
        teams[away].opponents[home].their_goals += home_goals;
    }
    for(auto i=teams.begin(); i!=teams.end(); i++)
    {
        for(auto j=teams.begin(); j!=teams.end(); j++)
        {
            if(i==j) continue;
            if(i->second.opponents[j->first].my_goals>i->second.opponents[j->first].their_goals) i -> second.opponents[j->first].my_points = 3;
            else if(i->second.opponents[j->first].my_goals==i->second.opponents[j->first].their_goals) i -> second.opponents[j->first].my_points = 1;
            i -> second.all_points += i -> second.opponents[j->first].my_points;
            i -> second.goals_scored += i -> second.opponents[j->first].my_goals;
            i -> second.goals_conceded += i -> second.opponents[j->first].their_goals;
        }
        i -> second.goal_difference = i -> second.goals_scored - i -> second.goals_conceded;
    }
    for(auto i=teams.begin(); i!=teams.end(); i++) order.push_back(i);
    sort(order.begin(), order.end(), compare);
    for(auto i : order)
    {
        const team& t = i -> second;
        table_file << t.name << "," << t.all_points << "," << t.goals_scored << "," << t.goals_conceded << "," << t.goal_difference << endl;
    }
}