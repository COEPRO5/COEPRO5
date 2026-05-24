#include <iostream>
using namespace std;

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    // Arrays to store process data
    int pid[100];        // Process ID
    int arrival[100];    // Arrival time
    int burst[100];      // Burst time
    int completion[100]; // Completion time
    int waiting[100];    // Waiting time
    int turnaround[100]; // Turnaround time
    bool completed[100]; // Track if process is done

    // Input process details
    cout << "\nEnter arrival time and burst time for each process:\n";
    for (int i = 0; i < n; i++) {
        pid[i] = i + 1;
        cout << "Process " << pid[i] << " - Arrival time: ";
        cin >> arrival[i];
        cout << "Process " << pid[i] << " - Burst time: ";
        cin >> burst[i];
        completed[i] = false;
    }

    // =====================
    // FCFS SCHEDULING
    // =====================
    cout << "\n========== FCFS SCHEDULING ==========\n";

    // Sort by arrival time using simple bubble sort
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arrival[j] > arrival[j + 1]) {
                // Swap all related arrays
                int temp;
                
                temp = arrival[j];
                arrival[j] = arrival[j + 1];
                arrival[j + 1] = temp;

                temp = burst[j];
                burst[j] = burst[j + 1];
                burst[j + 1] = temp;

                temp = pid[j];
                pid[j] = pid[j + 1];
                pid[j + 1] = temp;
            }
        }
    }

    // Calculate completion, turnaround, and waiting times for FCFS
    int currentTime = 0;
    
    for (int i = 0; i < n; i++) {
        // If CPU is idle, jump to next arrival
        if (currentTime < arrival[i]) {
            currentTime = arrival[i];
        }
        
        // Process executes
        currentTime = currentTime + burst[i];
        completion[i] = currentTime;
        
        // Calculate times
        turnaround[i] = completion[i] - arrival[i];
        waiting[i] = turnaround[i] - burst[i];
    }

    // Display FCFS results
    cout << "\nPID\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n";
    
    float totalWait = 0, totalTAT = 0;
    for (int i = 0; i < n; i++) {
        cout << "P" << pid[i] << "\t" << arrival[i] << "\t" << burst[i] << "\t" 
             << completion[i] << "\t\t" << turnaround[i] << "\t\t" << waiting[i] << "\n";
        totalWait += waiting[i];
        totalTAT += turnaround[i];
    }
    
    cout << "\nAverage Waiting Time (FCFS): " << totalWait / n;
    cout << "\nAverage Turnaround Time (FCFS): " << totalTAT / n;

    // =====================
    // SJF SCHEDULING (Non-Preemptive)
    // =====================
    cout << "\n\n========== SJF SCHEDULING ==========\n";

    // Reset completed array
    for (int i = 0; i < n; i++) {
        completed[i] = false;
    }

    currentTime = 0;
    int completedCount = 0;

    while (completedCount < n) {
        // Find process with shortest burst among arrived processes
        int shortest = -1;
        int minBurst = 99999;

        for (int i = 0; i < n; i++) {
            if (completed[i] == false && arrival[i] <= currentTime) {
                if (burst[i] < minBurst) {
                    minBurst = burst[i];
                    shortest = i;
                }
                // Tie-breaker: earlier arrival wins
                else if (burst[i] == minBurst && shortest != -1) {
                    if (arrival[i] < arrival[shortest]) {
                        shortest = i;
                    }
                }
            }
        }

        // If no process is ready, advance time to next arrival
        if (shortest == -1) {
            int nextArrival = 99999;
            for (int i = 0; i < n; i++) {
                if (completed[i] == false && arrival[i] < nextArrival) {
                    nextArrival = arrival[i];
                }
            }
            currentTime = nextArrival;
        } 
        else {
            // Execute the shortest job
            currentTime = currentTime + burst[shortest];
            completion[shortest] = currentTime;
            turnaround[shortest] = completion[shortest] - arrival[shortest];
            waiting[shortest] = turnaround[shortest] - burst[shortest];
            completed[shortest] = true;
            completedCount++;
        }
    }

    // Display SJF results
    cout << "\nPID\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n";
    
    totalWait = 0;
    totalTAT = 0;
    for (int i = 0; i < n; i++) {
        cout << "P" << pid[i] << "\t" << arrival[i] << "\t" << burst[i] << "\t" 
             << completion[i] << "\t\t" << turnaround[i] << "\t\t" << waiting[i] << "\n";
        totalWait += waiting[i];
        totalTAT += turnaround[i];
    }
    
    cout << "\nAverage Waiting Time (SJF): " << totalWait / n;
    cout << "\nAverage Turnaround Time (SJF): " << totalTAT / n;
    cout << "\n";

    return 0;
}
