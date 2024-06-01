#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <random>
using namespace std;

const int QUEUE_SIZE = 10;
const int MIN_PAGES = 10;
const int MAX_PAGES = 30;

mutex mtx;
condition_variable cv;
queue<int> printer1Queue;
queue<int> printer2Queue;
int papersInPrinter1 = 0;
int papersInPrinter2 = 0;
bool allJobsPrinted = false;

void laborThread() {
    while (true) {
        this_thread::sleep_for(chrono::seconds(1));
        
        unique_lock<mutex> lock(mtx);
        if (allJobsPrinted) {
            break;
        }
        
        papersInPrinter1 += 5;
        papersInPrinter2 += 5;
        cout << "Added 5 A4 papers to both printers." << endl;
        
        cv.notify_all();
    }
}

void printDocument(int printerId, int documentId, int numPages) {
    this_thread::sleep_for(chrono::seconds(1));
    
    unique_lock<mutex> lock(mtx);
    
    if (printerId == 1) {
        while (papersInPrinter1 < numPages) {
            cout << "Printer 1 is out of paper. Waiting..." << endl;
            cv.wait(lock);
        }
        
        papersInPrinter1 -= numPages;
        printer1Queue.pop();
    } else if (printerId == 2) {
        while (papersInPrinter2 < numPages) {
            cout << "Printer 2 is out of paper. Waiting..." << endl;
            cv.wait(lock);
        }
        
        papersInPrinter2 -= numPages;
        printer2Queue.pop();
    }
    
    cout << "Printer " << printerId << " printed document " << documentId << " with " << numPages << " pages." << endl;
}

void printerThread(int printerId) {
    while (true) {
        this_thread::sleep_for(chrono::seconds(1));
        
        unique_lock<mutex> lock(mtx);
        if (allJobsPrinted) {
            break;
        }
        
        if (printerId == 1 && !printer1Queue.empty()) {
            int documentId = printer1Queue.front();
            int numPages = printer1Queue.front();
            printDocument(printerId, documentId, numPages);
        } else if (printerId == 2 && !printer2Queue.empty()) {
            int documentId = printer2Queue.front();
            int numPages = printer2Queue.front();
            printDocument(printerId, documentId, numPages);
        }
        
        if (printer1Queue.empty() && printer2Queue.empty() && allJobsPrinted) {
            break;
        }
    }
}

int main() {
    thread labor(laborThread);
    thread printer1(printerThread, 1);
    thread printer2(printerThread, 2);
    
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(MIN_PAGES, MAX_PAGES);
    
    for (int i = 1; i <= QUEUE_SIZE; i++) {
        int numPages = dis(gen);
        printer1Queue.push(i);
        printer2Queue.push(i);
        cout << "Added document " << i << " with " << numPages << " pages to both printers." << endl;
    }
    
    printer1.join();
    printer2.join();
    labor.join();
    
    cout << "All jobs printed. Simulation completed." << endl;
    
    return 0;
}