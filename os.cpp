#include<fstream>
#include<iostream>
#include<vector>

static int total=0,counter=0;

void rr_gantz(std::vector<int> a,std::vector<int>b,std::vector<int>c,int x){
  std::cout<<"\nRR Gantt"<<std::endl;
  std::cout<<"Start: ";
  int sum=0,count=0,temp=0;
  std::vector<int> temp_=c;
  for(auto x:c)
    sum+=x;
  while(count<sum){
    for(int i=0;i<a.size();i++){
      if(temp_[i]<=x){
        if(temp_[i]==0){
          count+=0;
        }
        else{
          while(temp<temp_[i]){
            std::cout<<a[i]<<", ";
            temp++;
          }
          count+=temp_[i];
          temp_[i]=0;
          temp=0;
        }
      }
      else{
        temp=x;
        temp_[i]-=x;
        while(counter<temp){
          std::cout<<a[i]<<", ";
          counter++;
        }
        count+=x;
        counter=0;
        temp=0;
      }
    }
  }
  counter=0;
  std::cout<<"End.\n";
}


void fcfs_gantz(std::vector<int> a,std::vector<int>b,std::vector<int>c){
  std::cout<<"\nFCFS Gantt"<<std::endl;
  int sum=0;
  std::cout<<"Start: ";
  for(int j=0;j<a.size();j++){
    while(counter<c[j]){
      while(b[j]>sum){
        std::cout<<"Idle, ";
        sum++;
      }
      std::cout<<a[j]<<", ";
      counter++;
      sum++;
    }
    counter=0;
  }
  counter=0;
  std::cout<<"End.\n\n";
}

void rr_waitingtime(std::vector<int> a,std::vector<int>b, std::vector<int> c,int x){
  std::cout<<"\nRR Waiting Time. Time quantum: "<<x<<std::endl;
  std::vector<int> waitingtime_;
  for(int i=0;i<a.size();i++){
    std::cout<<"Processor: "<<a[i]<<" Waiting Time: "<<c[i]-b[i]<<std::endl;
    waitingtime_.push_back(c[i]-b[i]);
  }
  for(auto x:waitingtime_)
    total+=x;
  std::cout<<"Average Waiting Time: "<<(float)total/a.size()<<std::endl;
  total=0;
}

void rr_responsetime(std::vector<int> a,std::vector<int>b, std::vector<int>c,int x){
  std::cout<<"\nRR Response Time. Time quantum: "<<x<<std::endl;
  std::vector<int> responsetime_;
  for(int i=0;i<a.size();i++){
    if(i==0){
      std::cout<<"Processor: "<<a[i]<<" Response Time: "<<0<<std::endl;
      responsetime_.push_back(0);
      if(c[i]>x)
        counter+=x;
      else
        counter+=c[i];
    }
    else{
      if(b[i]>counter){
        counter+=b[i]-counter;
        if(c[i]>x){
          std::cout<<"Processor: "<<a[i]<<" Response Time: "<<counter-b[i]<<std::endl;
          responsetime_.push_back(counter-b[i]);
          counter+=x;
        }
        else{
          std::cout<<"Processor: "<<a[i]<<" Response Time: "<<counter-b[i]<<std::endl;
          responsetime_.push_back(counter-b[i]);
          counter+=c[i];
        }
      }
      else{
        if(c[i]>x){
          std::cout<<"Processor: "<<a[i]<<" Response Time: "<<counter-b[i]<<std::endl;
          responsetime_.push_back(counter-b[i]);
          counter+=x;
        }
        else{
          std::cout<<"Processor: "<<a[i]<<" Response Time: "<<counter-b[i]<<std::endl;
          responsetime_.push_back(counter-b[i]);
          counter+=c[i];
        }
      }
    }
  }
  for(auto x:responsetime_)
    total+=x;
  std::cout<<"Avergae Response Time: "<<(float)total/a.size()<<std::endl;
  total=0;
  counter=0;
}

void rr_turnaroundtime(std::vector<int> a,std::vector<int>b, std::vector<int>c,int x){
  std::cout<<"\nRR Turnaround Time. Time quantum: "<<x<<std::endl;
  std::vector<int> temp=c,another_temp,turnaround_;
  another_temp.resize(a.size());
  int sum=0;
  for(auto x:c)
    sum+=x;
  while(counter<sum){
    for(int i=0;i<a.size();i++){
      if(temp[i]>x){
        counter+=x;
        another_temp[i]=counter;
        temp[i]-=x;
      }
      else{
        if(temp[i]!=0){
          counter+=temp[i];
          another_temp[i]=counter;
          temp[i]=0;
        }
      }
    }
  }
  for(int i=0;i<another_temp.size();i++){
    std::cout<<"Processor: "<<a[i]<<" Turnaround Time: "<<another_temp[i]-b[i]<<std::endl;
    turnaround_.push_back(another_temp[i]-b[i]);
  }
  for(auto x:turnaround_)
    total+=x;
  std::cout<<"Average Turnaround Time: "<<(float)total/a.size()<<std::endl;
  total=0;
  counter=0;
  rr_waitingtime(a,c,turnaround_,x);
}

int find_time_quantum(int & x){
  do{
    std::cout<<"\nEnter time quantum: ";
    std::cin>>x;
    try{
      if(x<=0)
        throw 1;
    }
    catch(int){
      std::cout<<"Enter positive integer."<<std::endl;
    }
  }while(x<=0);
  return x;
}

void fcfs_response_time(std::vector<int>a,std::vector<int>b,std::vector<int>c){
  std::cout<<"\nFCFS Response Time"<<std::endl;
  std::vector<int> response_,arrival,burst;
  for(int i=0;i<a.size();i++){
    if(i==0){
      arrival.push_back(b[i]);
      burst.push_back(c[i]);
      int response=counter-arrival[i];
      counter=burst[i];
      response_.push_back(response);
      arrival.pop_back();
      burst.pop_back();
      std::cout<<"Processor: "<<a[i]<<" Response Time: "<<response<<std::endl;
    }
    else{
      arrival.push_back(b[i]);
      burst.push_back(c[i]);
      if(arrival[0]>counter){
        counter+=arrival[0]-counter;
        int response=counter-arrival[0];
        counter+=burst[0];
        response_.push_back(response);
        arrival.pop_back();
        burst.pop_back();
        std::cout<<"Processor: "<<a[i]<<" Response Time: "<<response<<std::endl;
      }
      else{
        int response=counter-arrival[0];
        counter+=burst[0];
        response_.push_back(response);
        arrival.pop_back();
        burst.pop_back();
        std::cout<<"Processor: "<<a[i]<<" Response Time: "<<response<<std::endl;
      }
    }
  }
  for(auto x:response_)
    total+=x;
  std::cout<<"Average Response Time: "<<(float)total/a.size()<<std::endl;
  total=0;
  counter=0;
}

void fcfs_waitingtime(std::vector<int> a, std::vector<int> b,std::vector<int> c){
  std::cout<<"\nFCFS Waiting Time"<<std::endl;
  std::vector<int> waiting_;
  for(int i=0;i<a.size();i++){
    std::cout<<"Processor: "<<a[i]<<" Waiting Time: "<<b[i]-c[i]<<std::endl;
    waiting_.push_back(b[i]-c[i]);
  }
  for(auto x:waiting_)
    total+=x;
  std::cout<<"Average Waiting Time: "<<(float)total/a.size()<<std::endl;
  total=0;
}

void fcfs_turnaroundtime(std::vector<int>a,std::vector<int>b,std::vector<int>c){
  std::cout<<"FCFS Turnaround Time"<<std::endl;
  std::vector<int> arrival,burst,turnaround_;
  for(int i=0;i<a.size();i++){
    if(i==0){
      arrival.push_back(b[i]);
      burst.push_back(c[i]);
      int turnaround = burst[0]-arrival[0];
      turnaround_.push_back(turnaround);
      counter=turnaround;
      std::cout<<"Processor: "<<a[i]<<" Turnaround Time: "<<turnaround<<std::endl;
      arrival.pop_back();
      burst.pop_back();
    }
    else{
      arrival.push_back(b[i]);
      burst.push_back(c[i]);
      if(arrival[0]>counter){
        counter+=arrival[0]-counter;
        int turnaround = counter+burst[0]-arrival[0];
        turnaround_.push_back(turnaround);
        counter+=burst[0];
        burst.pop_back();
        arrival.pop_back();
        std::cout<<"Processor: "<<a[i]<<" Turnaround Time: "<<turnaround<<std::endl;
      }
      else{
        counter+=burst[0];
        int turnaround = counter-arrival[0];
        turnaround_.push_back(turnaround);
        arrival.pop_back();
        burst.pop_back();
        std::cout<<"Processor: "<<a[i]<<" Turnaround Time: "<<turnaround<<std::endl;
      }
    }
  }
  for(auto x:turnaround_)
    total+=x;
  std::cout<<"Avergae Turnaround time: "<<(float)total/a.size()<<std::endl;
  total=0;
  counter=0;
  fcfs_waitingtime(a,turnaround_,c);
}

int main(){
  std::vector<int> pid,arrival_time,burst_time,temp_;
  std::vector<std::vector<int>> temp;
  std::ifstream file("test.txt"); //"C:\\Users\\Andrew\\Documents\\test.txt" 
  if(file.is_open()){
    int value;
    while(file>>value){
      if(counter!=3){
        A:temp_.push_back(value);
        counter++;
      }
      else{
        temp.push_back(temp_);
        temp_.clear();
        counter=0;
        goto A;
      }
    }
    temp.push_back(temp_);
  }
  else{
    std::cout<<"File not open."<<std::endl;
    exit(0);
  }
  file.close();
  counter=0;
  for(int i=0;i<temp.size();i++){
    pid.push_back(temp[i][0]);
    arrival_time.push_back(temp[i][1]);
    burst_time.push_back(temp[i][2]);
  }
  fcfs_turnaroundtime(pid,arrival_time,burst_time);
  fcfs_response_time(pid,arrival_time,burst_time);
  fcfs_gantz(pid,arrival_time,burst_time);
  int x;
  find_time_quantum(x);
  rr_turnaroundtime(pid,arrival_time,burst_time,x);
  rr_responsetime(pid,arrival_time,burst_time,x);
  rr_gantz(pid,arrival_time,burst_time,x);
  return 0;
}