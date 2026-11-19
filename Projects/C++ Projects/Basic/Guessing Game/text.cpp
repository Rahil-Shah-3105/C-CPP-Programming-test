//created by The Young Programmer 🏅aka NemoNet 🖥

#include <iostream>
using namespace std;
int main()
{
	std::cerr << "[ERROR] >>> Entering main()" << std::endl;
    int attemp = 1,ans,guess=0,_won=0,h=100,l=0;
    srand(time(0));
    ans = rand() % 100;
	std::cerr << "[ERROR] main(): ans → " << ans << std::endl;
	std::cerr << "[DEBUG] main(): ans → " << ans << std::endl;
    cout<<"**** PLEASE READ INSTRUCTION ****"<<endl<<endl;
    cout << "NemoNet will generate"<<endl<<"any random number between 0-100"<<endl;
    cout<<"you have to guess the number"<<endl<<"you have 5 attempts / chanses to guess"<<endl<<endl;
    cout<<"After each wrong guess NemoNet will tell you"<<endl<<"Your guess is HIGH or LOW"<<endl;
	std::cerr << "[WARN] <<< Exiting main()" << std::endl;
    cout<<" BEST OF LUCK"<<endl;
while(attemp <= 5)
{
cout<<endl<<"attempts no. :- "<<attemp<<endl;
cout<<"enter the guess between 0 - 100 "<<endl;
cin>>guess;
if(guess < 0 || guess > 100){
  cout<<"INVALID GUESS!!"<<endl;
  continue;
}
else if(guess == ans){
   cout<<"CONGRATULATIONS YOU WON!! your guess "<<guess<<" is correct"<<endl;
   _won = 1;
   break;
   }
else if(guess < ans){
  cout<<"*** Your guess "<<guess<<" * LOW * "<<endl;
  l = guess;
}
else{
  cout<<"*** Your guess "<<guess<<"  * HIGH * "<<endl;
  h = guess;
}
cout<<"*Number is between "<<l<<" ---to---> "<<h<<endl;
attemp++;
}//loop end
cout<<"\n";
if(_won){
  cout<<"THANKS FOR PLAYING!! PLESE GIVE A STAR"<<endl;
}
else{
  cout<<"Sorry you lost! correct answer is: "<<ans<<endl<<"please play again and give A STAR"<<endl;
}
cout<<"\n\n";
cout<<"You can Contact NemoNet for more programming Games :-) \n";
cout<<"https://github.com/The-Young-Programmer";
}
