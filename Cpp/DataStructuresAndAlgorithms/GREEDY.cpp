#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <string>
#include <map>

using namespace std;

class GreedyMaster {
public:
    // ==========================================================
    // PATTERN 1: INTERVAL SCHEDULING (Activity Selection)
    // Problem: Maximize the number of non-overlapping activities.
    // THE GREEDY CHOICE: Always pick the activity that FINISHES EARLIEST.
    // Why? It leaves the maximum amount of time for the remaining activities.
    // ==========================================================
    struct Activity {
        int start, end, id;
    };

    // Custom Comparator: Sort by End Time
    static bool compareActivities(Activity a, Activity b) {
        return a.end < b.end;
    }

    void solveActivitySelection(vector<Activity>& activities) {
        // 1. Sort based on finish time
        sort(activities.begin(), activities.end(), compareActivities);

        cout << "--- 1. Activity Selection ---" << endl;
        cout << "Selected Activities (IDs): ";

        // 2. Select the first activity always
        int last_end_time = activities[0].end;
        cout << activities[0].id << " ";
        int count = 1;

        // 3. Iterate through the rest
        for (int i = 1; i < activities.size(); i++) {
            // If this activity starts AFTER the last one finished, take it.
            if (activities[i].start >= last_end_time) {
                cout << activities[i].id << " ";
                last_end_time = activities[i].end;
                count++;
            }
        }
        cout << "\nTotal Activities: " << count << endl;
    }

    // ==========================================================
    // PATTERN 2: FRACTIONAL KNAPSACK
    // Problem: Fill a bag to maximize value. You CAN break items.
    // THE GREEDY CHOICE: Always pick the item with highest VALUE PER UNIT WEIGHT.
    // Note: This fails for 0/1 Knapsack (where you can't break items), but works here.
    // ==========================================================
    struct Item {
        int id;
        double weight;
        double value;
    };

    static bool compareRatio(Item a, Item b) {
        double r1 = a.value / a.weight;
        double r2 = b.value / b.weight;
        return r1 > r2; // Descending order of ratio
    }

    void solveFractionalKnapsack(vector<Item>& items, double capacity) {
        sort(items.begin(), items.end(), compareRatio);

        double totalValue = 0.0;
        double currentWeight = 0.0;

        cout << "\n--- 2. Fractional Knapsack ---" << endl;
        
        for (const auto& item : items) {
            // Option A: Take the whole item
            if (currentWeight + item.weight <= capacity) {
                currentWeight += item.weight;
                totalValue += item.value;
                cout << "Took full Item " << item.id << endl;
            } 
            // Option B: Take a fraction of the item to fill remaining space
            else {
                double remaining = capacity - currentWeight;
                double fractionValue = item.value * (remaining / item.weight);
                totalValue += fractionValue;
                cout << "Took " << remaining << "kg of Item " << item.id << endl;
                break; // Bag is full
            }
        }
        cout << "Max Value: " << totalValue << endl;
    }

    // ==========================================================
    // PATTERN 3: HUFFMAN CODING (Lossless Compression)
    // Problem: Assign shorter binary codes to more frequent characters.
    // THE GREEDY CHOICE: Merge the two LEAST frequent nodes first.
    // This pushes rare characters deeper into the tree (longer codes).
    // ==========================================================
    struct MinHeapNode {
        char data;
        unsigned freq;
        MinHeapNode *left, *right;

        MinHeapNode(char data, unsigned freq) {
            this->left = this->right = nullptr;
            this->data = data;
            this->freq = freq;
        }
    };

    struct CompareNode {
        bool operator()(MinHeapNode* l, MinHeapNode* r) {
            return (l->freq > r->freq); // Min Heap
        }
    };

    void printCodes(struct MinHeapNode* root, string str) {
        if (!root) return;
        if (root->data != '$') // '$' is our internal node marker
            cout << root->data << ": " << str << "\n";
        printCodes(root->left, str + "0");
        printCodes(root->right, str + "1");
    }

    void solveHuffmanCoding(vector<char>& data, vector<int>& freq) {
        priority_queue<MinHeapNode*, vector<MinHeapNode*>, CompareNode> minHeap;

        // 1. Create a leaf node for each character and add to heap
        for (size_t i = 0; i < data.size(); ++i)
            minHeap.push(new MinHeapNode(data[i], freq[i]));

        // 2. Iterate while heap size > 1
        while (minHeap.size() != 1) {
            // Extract two smallest freq items
            MinHeapNode* left = minHeap.top(); minHeap.pop();
            MinHeapNode* right = minHeap.top(); minHeap.pop();

            // Create a new internal node with sum of frequencies
            // '$' is a special character for internal nodes
            MinHeapNode* top = new MinHeapNode('$', left->freq + right->freq);
            top->left = left;
            top->right = right;

            minHeap.push(top);
        }

        cout << "\n--- 3. Huffman Codes ---" << endl;
        printCodes(minHeap.top(), "");
    }
};

int main() {
    GreedyMaster solver;

    // 1. Activity Selection
    // {Start, End, ID}
    vector<GreedyMaster::Activity> acts = {
        {1, 2, 1}, {3, 4, 2}, {0, 6, 3}, {5, 7, 4}, {8, 9, 5}, {5, 9, 6}
    };
    solver.solveActivitySelection(acts); 
    // Logic: {1,2} finishes first. Then {3,4}. Then {5,7}. Then {8,9}.
    // Result: 1, 2, 4, 5 (4 activities)

    // 2. Fractional Knapsack
    // {ID, Weight, Value}
    vector<GreedyMaster::Item> items = {
        {1, 10, 60}, {2, 20, 100}, {3, 30, 120}
    };
    // Ratios: Item1 (6.0), Item2 (5.0), Item3 (4.0)
    solver.solveFractionalKnapsack(items, 50);

    // 3. Huffman Coding
    vector<char> chars = {'a', 'b', 'c', 'd', 'e', 'f'};
    vector<int> freqs = {5, 9, 12, 13, 16, 45};
    solver.solveHuffmanCoding(chars, freqs);

    return 0;
}