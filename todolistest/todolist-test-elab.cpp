#include <iostream>
#include "../todolist.h"
using namespace std;

void printPriorityList(const DailyTodoList& t)
{
    cout << "Priority items: " << t.numPriorityItems() << endl;
    for (size_t i = 0; i < t.numPriorityItems(); i++)
    {
        cout << t.getPriorityVal(i) << " ";
    }
    cout << endl;

}
void printDailyList(const DailyTodoList& t, size_t day)
{
    size_t num = t.numItemsOnDay(day);
    cout << "Items on day #" << day << ": " << num << endl;
    for (size_t i = 0; i < num; i++)
    {
        cout << t.getNormalVal(day,i) << " ";
    }
    cout << endl;

}
int main()
{
    DailyTodoList t1;
    // Default size: 5, Priority: 0
    cout << "numDays = " << t1.numDays() << endl;
    cout << "numPriority = " << t1.numPriorityItems() << endl;
    
    // Resize
    cout << "RESIZE" << endl;
    cout << "numDays = " << t1.numDays() << endl; // 12
    t1.insert(6, 0, "6b", false);
    printDailyList(t1, 6); // 6b -> NULL (cout: 6b)
    printPriorityList(t1); // Priorty : NULL (cout:)

    t1.push_back(6, "6c", true);
    printDailyList(t1, 6); // 6b -> 6c -> NULL (cout: 6b -> 6c)
    printPriorityList(t1); // Priority: 6c -> NULL (cout: 6c)

    t1.insert(6, 0, "6a", false); 
    printDailyList(t1, 6); // 6a -> 6b -> 6c -> NULL
    printPriorityList(t1); // Priority: 6c -> NULL

    t1.insert(6, 3, "6d", false); 
    printDailyList(t1, 6); // 6a -> 6b -> 6c -> 6d
    printPriorityList(t1); // Priority: 6c -> NULL

    t1.insert(2, 0, "2a", true); 
    printDailyList(t1, 2); // 2a -> NULL
    printPriorityList(t1); // Priority: 6c -> 2a -> NULL

    t1.insert(14, 0, "14a", true); 
    printDailyList(t1, 2); // 14a -> NULL
    printPriorityList(t1); // Priority: 6c -> 2a -> 14a -> NULL

    t1.push_back(30, "30a", true); 
    printDailyList(t1, 2); // 30a -> NULL
    printPriorityList(t1); // Priority: 6c -> 2a -> 14a -> 30a -> NULL

    // Remove priority from middle
    cout << "Remove items" << endl;
    t1.remove(14, 0);
    printDailyList(t1, 14); // NULL
    printPriorityList(t1); // Priority: 6c -> 2a -> 30a -> NULL

    /*printDailyList(t1, 2);
    printDailyList(t1, 6);
    printDailyList(t1, 14);
    printDailyList(t1, 30);

    cout << "numDays = " << t1.numDays() << endl;
    cout << "numDays = " << t1.numItemsOnDay(6) << endl;
    cout << "numPriority = " << t1.numPriorityItems() << endl;

    // Remove from front
    cout << "Removed from front in Day 6" << endl;
    // 6b -> 6c -> 6d
    t1.remove(6, 0);
    printDailyList(t1, 6);
    // Remove from middle
    t1.remove(6, 1);
    // 6b -> 6d
    cout << "Remove form end" << endl;
    // 6b
    t1.remove(6, t1.numItemsOnDay(6) - 1);
    printDailyList(t1, 6);
    // Remove from end
    printDailyList(t1,6);
    


    //printDailyList(t1, 6U);
    printPriorityList(t1);
    t1.remove(2, 0);
    printPriorityList(t1);
    t1.remove(14, 0);
    printPriorityList(t1);
    t1.remove(6, 2);
    printPriorityList(t1);
    */

    {
        DailyTodoList t2;
    }
    return 0;
}

