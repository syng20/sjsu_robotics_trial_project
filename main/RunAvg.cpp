#include"RunAvg.h" 

// constructor
RunAvg::RunAvg() {
  for (int i=0; i<10; i++) {
      rec_ten[i] = 0; 
  }
  curr_avg = 0; 
  index = 0; 
} 

// get
int RunAvg::get_avg() { return curr_avg; }

// update 
void RunAvg::update_avg(int next) {
  rec_ten[index] = next; 
  int t = 0; 
  for (int i=0; i<10; i++) t += rec_ten[i]; 
  curr_avg = t/10; 
  if (index == 9) index = 0; 
  else index++; 
}
