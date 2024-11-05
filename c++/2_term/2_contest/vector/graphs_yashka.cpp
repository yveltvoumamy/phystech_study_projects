#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct VerticalLine {
    int x, y1, y2;
    bool type;
    int idx;

    VerticalLine(int x, int y1, int y2, bool type, int idx) 
        : x(x), y1(y1), y2(y2), type(type), idx(idx) {}
};

vector<vector<int> > input_list() {
    int n;
    cin >> n;
    vector<vector<int> > squares(n, vector<int>(4));
    for (int i = 0; i < n; ++i) {
        cin >> squares[i][0] >> squares[i][1] >> squares[i][2] >> squares[i][3];
    }
    return squares;
}

vector<int> solution(const vector<vector<int> >& rectangles) {
    vector<VerticalLine> events;
    int n = rectangles.size();
    vector<int> intersection_counts(n, 0);

    for (int i = 0; i < n; ++i) {
        int x1 = rectangles[i][0], y1 = rectangles[i][1];
        int x2 = rectangles[i][2], y2 = rectangles[i][3];
        events.push_back(x1, y1, y2, true, i);
        events.push_back(x2, y1, y2, false, i);
    }

    sort(events.begin(), events.end(), [](const VerticalLine& a, const VerticalLine& b) {
        return a.x < b.x || (a.x == b.x && a.type < b.type);
    });

    vector<tuple<int, int, int>> active_segments;

    for (const auto& event : events) {
        if (event.type) {
            for (const auto& [y1, y2, idx] : active_segments) {
                if (event.y2 > y1 && event.y1 < y2) {  // Проверка на пересечение по y
                    intersection_counts[event.idx]++;
                    intersection_counts[idx]++;
                }
            }
            active_segments.emplace_back(event.y1, event.y2, event.idx);
        } else {
            active_segments.erase(remove_if(active_segments.begin(), active_segments.end(),
                [&](const auto& seg) {
                    return get<0>(seg) == event.y1 && get<1>(seg) == event.y2 && get<2>(seg) == event.idx;
                }), active_segments.end());
        }
    }

    return intersection_counts;
}

int main() {
    vector<vector<int>> rectangles = input_list();
    vector<int> result = solution(rectangles);

    for (int count : result) {
        cout << count << " ";
    }
    cout << endl;

    return 0;
}

