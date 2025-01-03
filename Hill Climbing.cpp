#include <iostream>
#include <vector>

using namespace std;

class HillClimbing {
public:
    HillClimbing(const vector<int>& values);
    void search();
    int getCurrentState() const;
    int getGoalState() const;
private:
    vector<int> values;
    int current_state;
    int goal_state;
};

HillClimbing::HillClimbing(const vector<int>& values) {
    this->values = values;
    this->current_state = 0;
    this->goal_state = 0;
    for (int i = 1; i < values.size(); ++i) {
        if (values[i] > values[goal_state]) {
            goal_state = i;
        }
    }
}

void HillClimbing::search() {
    while (true) {
        int next_state = current_state + 1;
        int prev_state = current_state - 1;
        if (next_state < values.size() && values[next_state] > values[current_state]) {
            current_state = next_state;
        }
        else if (prev_state >= 0 && values[prev_state] > values[current_state]) {
            current_state = prev_state;
        }
        else {
            break;
        }
    }
}

int HillClimbing::getCurrentState() const {
    return current_state;
}

int HillClimbing::getGoalState() const {
    return goal_state;
}

int main() {
    vector<int> values = {1, 3, 5, 2, 4, 7, 6};
    HillClimbing hc(values);
    hc.search();
    cout << "The current state (local maximum) is at index: " << hc.getCurrentState() << endl;
    cout << "The global maximum is at index: " << hc.getGoalState() << endl;
    cout << "Local maximum value: " << values[hc.getCurrentState()] << endl;
    cout << "Global maximum value: " << values[hc.getGoalState()] << endl;
    return 0;
}