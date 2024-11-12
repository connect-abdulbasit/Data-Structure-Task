#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <chrono>
#include <fstream>
using namespace std;

string getCurrentTimestamp()
{
    auto now = chrono::system_clock::now();
    time_t now_time = chrono::system_clock::to_time_t(now);
    string timeStr = ctime(&now_time);
    timeStr.pop_back();
    return timeStr;
}
class Ticket
{
public:
    int ticketID;
    string customerName;
    int priority;
    string serviceRequestDescription;
    string creationTime;
    bool status;
    string ticketCloseTime;

    Ticket() {}
    Ticket(int ticketID, string customerName, int priority, string serviceRequestDescription, string creationTime, bool status, string ticketCloseTime)
        : ticketID(ticketID), customerName(customerName), priority(priority),
          serviceRequestDescription(serviceRequestDescription), creationTime(creationTime), status(status), ticketCloseTime(ticketCloseTime) {}
    void display() const
    {
        cout << "Ticket ID: " << ticketID << endl;
        cout << "Customer Name: " << customerName << endl;
        cout << "Priority: " << priority << endl;
        cout << "Status: " << (status ? "Open" : "Closed") << endl;
        cout << "Service Request: " << serviceRequestDescription << endl;
        cout << "Creation Time: " << creationTime << endl;
        if (!status)
        {
            cout << "Ticket Close Time: " << ticketCloseTime << endl;
        }
    }

    void closeTicket()
    {
        ticketCloseTime = getCurrentTimestamp();
        status = false;
    }
};

class Node
{
public:
    Ticket data;
    Node *next;
    Node *prev;

    Node(Ticket data) : data(data), next(nullptr), prev(nullptr) {}
};

class Stack
{
    Node *top;

public:
    Stack() : top(nullptr) {}

    void push(Ticket data)
    {
        Node *newNode = new Node(data);
        newNode->next = top;
        top = newNode;
    }

    Ticket pop()
    {
        if (top == nullptr)
            throw runtime_error("Stack is empty");
        Ticket data = top->data;
        Node *temp = top;
        top = top->next;
        delete temp;
        return data;
    }

    bool isEmpty() const { return top == nullptr; }
};

class LinkedList
{
    Node *head;
    Node *tail;
    string sortingAlgorithm;
    string searchAlgorithm;
    int thresholdSize;

public:
    LinkedList() : head(nullptr), tail(nullptr)
    {
        loadConfig("config.txt");
    }
    void loadConfig(const string &filename)
    {
        ifstream configFile(filename);
        string line;

        if (!configFile.is_open())
        {
            cout << "Error opening configuration file!" << endl;
            return;
        }

        while (getline(configFile, line))
        {
            if (line.find("sorting_algorithm") != string::npos)
            {
                sortingAlgorithm = parseConfigValue(line);
            }
            else if (line.find("search_algorithm") != string::npos)
            {
                searchAlgorithm = parseConfigValue(line);
            }
            else if (line.find("threshold_size") != string::npos)
            {
                thresholdSize = stoi(parseConfigValue(line));
            }
        }

        configFile.close();
    }
    string parseConfigValue(const string &line)
    {
        size_t pos = line.find("=");
        if (pos != string::npos)
        {
            return line.substr(pos + 1);
        }
        return "";
    }
    int getListSize()
    {
        int size = 0;
        Node *temp = head;
        while (temp)
        {
            size++;
            temp = temp->next;
        }
        return size;
    }
    void insert(Ticket data)
    {
        Node *newNode = new Node(data);
        if (!head)
            head = tail = newNode;
        else
        {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void remove(int ticketID)
    {
        Node *temp = head;
        while (temp)
        {
            if (temp->data.ticketID == ticketID)
            {
                if (temp->prev)
                    temp->prev->next = temp->next;
                if (temp->next)
                    temp->next->prev = temp->prev;
                if (temp == head)
                    head = temp->next;
                if (temp == tail)
                    tail = temp->prev;
                delete temp;
                return;
            }
            temp = temp->next;
        }
        cout << "Ticket ID not found\n";
    }

    int interpolationSearch(Node *head, int ticketID)
    {
        Node *low = head, *high = nullptr;
        while (low && high)
        {
            int pos = low->data.ticketID + ((ticketID - low->data.ticketID) * (high->data.ticketID - low->data.ticketID)) / (high->data.ticketID - low->data.ticketID);
            if (low->data.ticketID == ticketID)
                return low->data.ticketID;
            else if (ticketID < low->data.ticketID)
                low = low->next;
            else
                high = high->prev;
        }
        return -1; // Ticket not found
    }

    void bubbleSort(Node *&head)
    {
        if (!head || !head->next)
            return;

        bool swapped;
        do
        {
            swapped = false;
            Node *temp = head;
            while (temp && temp->next)
            {
                if (temp->data.priority > temp->next->data.priority)
                {
                    swap(temp->data, temp->next->data);
                    swapped = true;
                }
                temp = temp->next;
            }
        } while (swapped);
    }

    void insertionSort(Node *&head)
    {
        if (!head || !head->next)
            return;

        Node *sorted = nullptr;
        Node *current = head;
        while (current)
        {
            Node *next = current->next;
            if (!sorted || sorted->data.priority >= current->data.priority)
            {
                current->next = sorted;
                sorted = current;
            }
            else
            {
                Node *temp = sorted;
                while (temp->next && temp->next->data.priority < current->data.priority)
                {
                    temp = temp->next;
                }
                current->next = temp->next;
                temp->next = current;
            }
            current = next;
        }
        head = sorted;
    }

    void selectionSort(Node *&head)
    {
        if (!head || !head->next)
            return;

        Node *temp1 = head;
        while (temp1)
        {
            Node *temp2 = temp1->next;
            Node *min = temp1;
            while (temp2)
            {
                if (temp2->data.priority < min->data.priority)
                {
                    min = temp2;
                }
                temp2 = temp2->next;
            }
            if (min != temp1)
            {
                swap(temp1->data, min->data);
            }
            temp1 = temp1->next;
        }
    }

    void mergeSort(Node *&head)
    {
        if (!head || !head->next)
            return;

        Node *mid = getMiddle(head);
        Node *left = head;
        Node *right = mid->next;
        mid->next = nullptr;

        mergeSort(left);
        mergeSort(right);

        head = merge(left, right);
    }

    Node *getMiddle(Node *head)
    {
        if (!head)
            return head;
        Node *slow = head;
        Node *fast = head;
        while (fast->next && fast->next->next)
        {
            slow = slow->next;
            fast = fast->next->next;
        }
        return slow;
    }

    Node *merge(Node *left, Node *right)
    {
        if (!left)
            return right;
        if (!right)
            return left;

        if (left->data.priority <= right->data.priority)
        {
            left->next = merge(left->next, right);
            return left;
        }
        else
        {
            right->next = merge(left, right->next);
            return right;
        }
    }

    void quickSort(Node *&head)
    {
        if (!head || !head->next)
            return;

        Node *pivot = head;
        Node *left = nullptr, *right = nullptr, *temp = head->next;

        while (temp)
        {
            if (temp->data.priority < pivot->data.priority)
            {
                if (!left)
                    left = temp;
                else
                    left->next = temp;
            }
            else
            {
                if (!right)
                    right = temp;
                else
                    right->next = temp;
            }
            temp = temp->next;
        }

        quickSort(left);
        quickSort(right);

        head = merge(left, right);
    }
    void sort(int choice)
    {
        if (!head)
            return;

        int threshold = 50;
        bool useMergeSort = true;

        int listSize = getListSize();

        if (listSize < threshold)
        {
            if (sortingAlgorithm == "bubble_sort")
            {
                bubbleSort(head);
            }
            else if (sortingAlgorithm == "insertion_sort")
            {
                insertionSort(head);
            }
            else if (sortingAlgorithm == "selection_sort")
            {
                selectionSort(head);
            }
            else if (sortingAlgorithm == "quick_sort")
            {
                quickSort(head);
            }
            else if (sortingAlgorithm == "merge_sort")
            {
                mergeSort(head);
            }
            else
            {
                cout << "Invalid sorting algorithm" << endl;
            }
        }
        else
        {
            if (useMergeSort)
            {
                mergeSort(head);
            }
            else
            {
                quickSort(head);
            }
        }
    }

    void search(int ticketID)
    {

        if (searchAlgorithm == "interpolation_search")
        {
            int result = interpolationSearch(head, ticketID);
            if (result == -1)
            {
                cout << "Ticket not found" << endl;
            }
            else
            {
                cout << "Ticket found: " << result << endl;
            }
        }
        else
        {
            Node *temp = head;
            while (temp)
            {
                if (temp->data.ticketID == ticketID)
                {
                    temp->data.display();
                    return;
                }
                temp = temp->next;
            }
            cout << "Ticket not found\n";
        }
    }

    void display()
    {
        Node *temp = head;
        while (temp)
        {
            temp->data.display();
            temp = temp->next;
        }
    }
    friend class AgentManager;
};

class Queue
{
    vector<Ticket> tickets;

public:
    void enqueue(const Ticket &ticket)
    {
        tickets.push_back(ticket);
    }

    Ticket dequeue()
    {
        if (tickets.empty())
            throw runtime_error("Queue is empty");
        Ticket frontTicket = tickets.front();
        tickets.erase(tickets.begin());
        return frontTicket;
    }

    bool isEmpty() const { return tickets.empty(); }

    void display() const
    {
        if (tickets.empty())
        {
            cout << "The queue is empty.\n";
            return;
        }
        cout << "Tickets in the queue:\n";
        for (const auto &ticket : tickets)
        {
            ticket.display();
            cout << "------------------------\n";
        }
    }
};

class Agent
{
public:
    int agentID;
    string name;
    vector<int> assignedTickets; // List of assigned ticket IDs
    int maxCapacity = 5;         // Maximum number of tickets an agent can handle
    string status = "Available"; // Status can be "Available" or "Unavailable"

    Agent() {}

    Agent(int id, const string &n) : agentID(id), name(n) {}

    bool isAvailable() const
    {
        return status == "Available";
    }

    void assignTicket(int ticketID)
    {
        assignedTickets.push_back(ticketID);
        if (assignedTickets.size() >= maxCapacity)
        {
            status = "Unavailable";
        }
    }

    void display() const
    {
        cout << "Agent ID: " << agentID << endl
             << "Name: " << name << endl
             << "Status: " << status << endl;
        cout << "Assigned Tickets: ";
        for (const auto &ticketID : assignedTickets)
        {
            cout << ticketID << " ";
        }
        cout << endl;
    }
};

class AgentManager
{
    Agent *agents;
    int size;

public:
    AgentManager()
    {
        agents = NULL;
        size = 0;
    }
    void addAgent(const Agent &agent)
    {
        Agent *temp = new Agent[size];
        for (int i = 0; i < size; i++)
        {
            temp[i] = agents[i];
        }
        delete[] agents;
        agents = new Agent[size + 1];
        for (int i = 0; i < size; i++)
        {
            agents[i] = temp[i];
        }
        agents[size] = agent;
        size++;
    }
    void sortAgentsByTicketCount()
    {
        for (int i = 0; i < size; i++)
        {
            int key = i;
            for (int j = i + 1; j < size; j++)
            {
                if (agents[j].assignedTickets.size() < agents[key].assignedTickets.size())
                {
                    key = j;
                }
            }
            if (key != i)
            {
                Agent temp = agents[i];
                agents[i] = agents[key];
                agents[key] = temp;
            }
        }
    }

    void assignTicketToAgent(LinkedList &openTickets)
    {
        openTickets.sort(1);
        Node *temp = openTickets.head;
        for (int i = 0; i < size; i++)
        {
            if (agents[i].isAvailable())
            {
                int ticketID = temp->data.ticketID;
                temp = temp->next;
                agents[i].assignedTickets.push_back(ticketID);
                cout << "Assigned Ticket " << ticketID << " to Agent " << agents[i].name << endl;
            }
        }
    }
    void displayAgents() const
    {
        for (int i = 0; i < size; i++)
        {
            agents[i].display();
            cout << endl;
        }
    }
};

class TicketResolutionLog
{
    Stack ticketStack;

public:
    void logClosedTicket(const Ticket &ticket)
    {
        ticketStack.push(ticket);
    }

    void viewLogs()
    {
        cout << "Recent ticket resolution logs:\n";
        while (!ticketStack.isEmpty())
        {
            Ticket ticket = ticketStack.pop();
            cout << "Ticket ID: " << ticket.ticketID << endl;
        }
    }
};

int main()
{
    LinkedList ticketList;
    LinkedList openTickets;
    AgentManager agentManager;
    TicketResolutionLog resolutionLog;
    Queue ticketQueue;

    int choice;
    while (choice != 0)
    {
        cout << "\n--- One-Stop Management System ---\n";
        cout << "1. Add Ticket\n2. Remove Ticket\n3. Search Ticket\n4. Display Tickets\n";
        cout << "5. Add Agent\n6. Assign Ticket\n7. View Logs\n8. Process Ticket Queue\n9. Display Ticket Queue\n0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            int id, priority, creationTime;
            string customerName, description, timeStr;
            cout << "Enter Ticket ID: ";
            cin >> id;
            cout << "Enter Customer Name: ";
            cin >> customerName;
            cout << "Enter Priority (1-High, 2-Medium, 3-Low): ";
            cin >> priority;
            cout << "Enter Description: ";
            cin.ignore();
            getline(cin, description);
            timeStr = getCurrentTimestamp();
            Ticket newTicket(id, customerName, priority, description, timeStr, true, "");
            ticketList.insert(newTicket);
            openTickets.insert(newTicket);
            ticketQueue.enqueue(newTicket);
            break;
        }
        case 2:
        {
            int id;
            cout << "Enter Ticket ID to remove: ";
            cin >> id;
            ticketList.remove(id);
            break;
        }
        case 3:
        {
            int id;
            cout << "Enter Ticket ID to search: ";
            cin >> id;
            ticketList.search(id);
            break;
        }
        case 4:
            ticketList.display();
            break;
        case 5:
        {
            int id;
            string name;
            cout << "Enter Agent ID: ";
            cin >> id;
            cin.ignore();
            cout << "Enter Agent Name: ";
            cin >> name;
            agentManager.addAgent(Agent(id, name));
            break;
        }
        case 6:
        {
            agentManager.assignTicketToAgent(openTickets);
            agentManager.displayAgents();
            break;
        }
        case 7:
            resolutionLog.viewLogs();
            break;
        case 8:
            if (!ticketQueue.isEmpty())
            {
                Ticket ticketToProcess = ticketQueue.dequeue();
                openTickets.remove(ticketToProcess.ticketID);
                cout << "Processing Ticket:\n";
                ticketToProcess.display();
                ticketToProcess.closeTicket();
                resolutionLog.logClosedTicket(ticketToProcess);
            }
            else
            {
                cout << "No tickets in the queue to process.\n";
            }
            break;
        case 9:
            ticketQueue.display();
            break;
        case 10:
            return 0;
        }
    }
    return 0;
}
