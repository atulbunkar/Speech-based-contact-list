
===========================  SP Final Project - Speech Based Contact List   =============================
Submitted By : 
Atul Bunkar - 214101011 :  Back-end , Connecting Back end to front end.
Allam Eswar - 214101004 : Creating Form design.

To run : Load the Project , Build and Run . 

If by chance you get this error : " error C2440: '=' : cannot convert from 'const wchar_t [8]' to 'System::Windows::Forms::Label ^'  "
Comment out the line of error which is :    this->Name = L"myform1";
And the program will work fine. This error cant be fixed as I have tried everything. 

Files:
-> The "live demo.mp4" video shows the working of application.
-> " Final report.pdf " is the report work of the project.
-> Rest all is same as the HMM assignment.


Things to Note:-

To live Train : 
I have Created a folder "live_train" where user can put own word samples of 25 utterance or more. The program is designed to take 25 utterance , so make sure  to put 25 samples if you want to and rename them as I have used . Else I have already put 2 names in live Training "Rohan" And "Kirti" which will be live trained from the application, rest all names are trained and models stored in folder "model" . After live training , the name can be live tested.

To live test: 
On recording , the console opens up , after saying the name , user has to press a button to close the console and  proceed further. 




