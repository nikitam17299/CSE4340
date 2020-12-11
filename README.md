# CSE4340

Eating Habit Monitoring using IMU

INTRODUCTION

In this project, we designed a system that can track and identify, using a neck wearable, if a user is eating, drinking, or speaking. This system utilizes a basic machine learning model that has been given data in order to train itself. 
To monitor eating habits is to monitor calorie intake and water intake. In this project, we aim to identify when someone is eating, drinking or speaking, and hope to use this technology for more detailed research in the future. 
This system can be used for a variety of use, for a variety of peoples that need it. This includes medical patients, including those with diabetes or the elderly, who may need their food intake recorded, or average users that simply want to track what they consume. We hope to develop this system even further to not just identify if the user is simply eating/drinking, but to even identify what exactly they are eating. 


SYSTEM IMPLEMENTATION (View Demo here: https://youtu.be/8F2CKhA6wp4)

For hardware, we utilize the following. (Note that we were to initially use a microphone (MAX4466) to implement speaking identification software, however, this was omitted because of privacy concerns, that for the fact that there was no need for it):
-Arduino Nano 33 IOT
-MPU-6050/GY-521

We utilize 3 modes of software for the entire system:
-Arduino IDE
This IDE will be utilized to program the microcontroller board, collect data, and identify consistencies for Activity Recognition
-Jupyter Notebook
Supervised machine learning is performed on jupyter notebook, as well as evaluating the system performance.
-Kaggle
Used for the SVM algorithm for activity recognition, and to import the micromlgen library for adapting machine learning techniques

SOLUTION

The first step was to piece together all of the hardware components as shown in the architectural section. 

We can then begin the first tests, which were our data collection. For instruction to run the code all instructions can be found on the read.me file at the git repository: https://github.com/nikitam17299/CSE4340

The data collection software for the first solution (Supervised ML) is performed in the Arduino IDE environment, where we perform initialization on the board, and record gyroscope and accelerometer values. 

A trial is conducted by performing the following(View data collection process here: https://youtu.be/qhOYamJciGM) 
1.Get food and drink ready to be consumed. 
2.Place the IMU on the throat, making sure the system is stable. Orientation should be with the x-axis label visible on the board pointing upwards. 
3.Open up the serial monitor and observe the raw data coming in. Eat or drink as needed, and once finished, simply copy all the values from the monitor and paste it into a .txt file. Then save the file in .csv format.
4.Duplicate the file and create graphical forms in the x-, y-, and z- axes of the gyroscope. This is so that we can have a better understanding of which action impacts what axes, and understand the differences in the peaks of the signal that is formed.

We performed eating and drinking trials a total of 10 times, with a variety of demographics, including age and gender. This can assure a more accurate model, as there may be a variety of difference in the way a throat appears. The full set of trials and its data values for each axis can be found on the github repository, but the most important axes to consider is the y- and z- axes of the gyroscope, and the y-axis of the accelerometer:

After analyzing the 10 trials we chose the signal function to be part of the feature extraction process. We observed that eating had more peaks than drinking, so that became a classification factor. 
This feature was then fed into a SVM machine learning model with mircomlgen library to achieve machine learning on microcontrollers. 
	
SYSTEM EVALUATION

This supervised machine learning technique is currently at 100% accuracy. This is because of the limited data we had, it was extremely fitted. Due to the pandemic we were not able to gather a lot of data as required to get a diverse dataset. 


LESSONS LEARNED

This project helped us to review embedded/microcontroller techniques, and implement machine learning skills previously learned. We were able to complete the tasks at hand and identify, on both solutions, with some degree of accuracy, whether or not a user was eating or drinking. 


