#include<iostream>
#include<vector>
#include<string>

#define RED_COLOR "\x1b[31m"
#define GREEN_COLOR "\x1b[32m"
#define RESET_COLOR "\x1b[0m"

bool isLeapYear(int year){
 return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

std::vector<int> getEndOfMonthDays(int year){
 std::vector<int> days_in_month = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

 if(isLeapYear(year))
  days_in_month[1] = 29;

 return days_in_month;
}

std::vector<std::string> getMonthNames(){
 return {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
}

std::vector<std::string> getWeekDays(){
 return {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
}

int getDayOfWeek(int day, int month, int year){
 if(month < 3){
  month += 12; // jan & feb will treated at 13th and 14th of the month of the previous year
  year -= 1; // back to previous year
 }

 int K = year % 100; // year within the century. e.g: 2024 will be `24`
 int J = year / 100; // zero-based centure. e.g: 2024 will be `20`
 int h = (day + (13 * (month + 1))/5 + K + (K/4) + (J/4) + 5 * J) % 7; // Zeller's Congruence Formula

 return (h + 6) % 7; // adjustment for mapping 0 = Sun, 1 = Mon, ... , 6 = Sat
}

void generateMonthCalendar(int month, int year){
 std::vector<int> months_days = getEndOfMonthDays(year);
 std::vector<std::string> month_names = getMonthNames();
 std::vector<std::string> week_days = getWeekDays();
 int first_day_index = getDayOfWeek(1, month, year);
 int padding_counter = 0, counter = 0;
 int days = months_days[month - 1];

 // print the day headers: Sun Mon Tue Wed Thur Fri Sat
 std::cout << "\n" << GREEN_COLOR << month_names[month - 1] << RESET_COLOR << "\n";
 
 for(int i = 0; i < week_days.size(); i++)
  std::cout << week_days[i] << "\t";

 std::cout << "\n";
 
 // print padding before the first day of the month
 for(int i = 0; i < week_days.size(); i++){
  if(i == first_day_index)
   break;
  
  std::cout << "\t";
  padding_counter++;
 } 

 counter = 1 + padding_counter;
 for(int j = 1; j <= days; j++) {
  
  std::string day_name = week_days[getDayOfWeek(j, month, year)]; 
  if(day_name == "Sun"){
   std::cout << RED_COLOR << j << RESET_COLOR << "\t";
  }else{
   std::cout << j << "\t";
  }
  
  if(counter == 7){
   std::cout << "\n";
   counter = 1;
  }else{
   counter++;
  }
 }

 // compute that padding that will be added at the last day of the month
 if(counter > 1)
  counter = 7 - counter;
 
 // print the padding added to the last day of the month
 for(int i = 1; i < counter; i++)
  std::cout << "\t";
 
 std::cout << "\n";
}

void generateFullCalendar(int year){
 for(int i = 1; i <= 12; i++){
  generateMonthCalendar(i, year);
 }
}

int main(){
 int year;
 
 std::cout << "Enter a year: ";
 std::cin >> year;
 
 generateFullCalendar(year);

 return 0;
}
