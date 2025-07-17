# ENGR 101 Project 3

## Autonomous Vehicle Challenge Progress Report

### Analysis
On the Hardware side, building the robot chassis from Meccano was a good idea in the sense that it allows for a more modular robot design should anything need be changed. Meccano also being made of steel means that the robot is fairly robust which means that if the robot were to fall off of the table by mistake it is unlikely to cause any significant damage. Cohen did have to 3d print a mount to attach the servo to the front of the robot and this piece fit well to both the robot chassis and the servo.

It took a good bit of finesse to attach the drive motors to the robot chassis due to the Meccano not being matched to the size of the motors. However we were able to engineer a solution that holds the motors securely to the robot chassis using only one screw per motor. We also had find a way to mount the Pi to the robot chassis rigidly so that it would not move when attaching / removing cables. To do this two angled pieces of Meccano were added at the back of the Pi and a locking tab was also added at the rear to secure the Pi in place. The Pi is now held extremely securely adding further rigidity to the robot. Currently, there are no bottlenecks on the hardware side of the robot and the robot is in a place where it is now just up to the software to complete the course.

We have had a few issues with version control and communication within the team as well as having working code that gets modified and then no longer works. This has been a fairly substantial bottleneck for us as when we come into the lab we have to spend a significant portion of our time going back through the code to isolate the sections of code that are not working and then work out how to fix them. This slowed down a lot of our work on quad 3 and 4 due to the robot no longer being able to detect the line and going backwards a lot of the time.

They best way for us to advance the project has been taking advantage of PID. Initially we were not using PID to control the robots movement, this worked but was very slow and the robot struggles to go around sharp corners. So we have begun to implement PID to the robot. Implementing PID will take some time as we will have to modify many of our functions and in some cases re-engineer the way the code works. But making this change will ulitimatly optimise our code and the results from the changes will be significant.

The PID controller was successfully implemented into the code within a short timeframe, resolving the previous issues. Development has now progressed to working on Quadrants 3 and 4.

### Roadmap
#### Planning
|START DATE|STATUS|TASK DESCRIPTION|RESPONSIBILITY|DEADLINE|OUTCOME|ACTUAL PROGRESS 23 may|
|----------|------|----------------|--------------|--------|-------|----------------------|
|1/5/25    |Completed |Project Plan    |All |12/5/25 ||Completed|
|13/5/25   |Completed |Progress Report |All		   |23/5/25 ||Completed|
|1/5/25    |Completed |Software design |Helene and Oshane|8/5/25 |Each phase has a detailed explantion of what the bot needs to do|Completed|
|1/5/25    |Completed |Pseudo code |Helene|12/5/25 |Pre-code pseudo code written|Completed|
|1/5/25    |Completed |Base code plan and functions |Oshane |8/5/25||Completed|

#### Software
|START DATE|STATUS|TASK DESCRIPTION|RESPONSIBILITY|DEADLINE|OUTCOME|ACTUAL PROGRESS 23 may|
|----------|------|----------------|--------------|--------|-------|----------------------|
|1/5/25    |Completed |Phase 0 - Initialization |Oshane |8/5/25 |Robot resets all variables and gets ready to make its way through the track|Completed|
|1/5/25    |Completed |Phase 1 - Open door |Oshane |8/5/25 |Robot can make its way through quad 1|Robot is able to connect to door - open it and move through|
|1/5/25    |Completed |Phase 2 - Follow line|Oshane |8/5/25 |Robot can make its way through quad 2|Robot is able to follow the line all the way to the red marker|
|1/5/25    |In progress |Phase 3 - Maze |Jessica and Oshane |15/5/25 ||Currently in progress working on logic instead of hard code but managed to complete with hardcode. Logic now makes sense and we are looking at a solution to be able to move the camera closer to the body|
|15/5/25   |In progress |Phase 4 - Pillars and ball |Oshane and Jessica |22/5/25||Running into an issue of not being able to detect the blue pillar|
|15/5/25   |In progress |Phase 5 - Victory |Oshane |22/5/25||Currently in progress|
|1/5/25    |Completed |Motor functions - forwards, back, stop, left, right|Oshane |8/5/25|Robot has the ability to complete a series of movements|Completed|
|1/5/25    |Completed |Door function |Oshane |8/5/25|Robot can connect to server and open the door|Completed|
|8/5/25    |Completed |Camera - Look up and down |Jessica and Oshane|15/5/25|Camera can look up and down when needed|Adjustments have been made to make sure the camera is at the correct angle when needed due to the small range of movement we have|
|14/5/25    |Completed |Optimisation of color functions |Jessica |15/5/25|We had duplicates of the same function taking up a lot of space so they have become 1 function with parameters passed to make the code more effciant|Completed|

#### Hardware
|START DATE|STATUS|TASK DESCRIPTION|RESPONSIBILITY|DEADLINE|OUTCOME|ACTUAL PROGRESS 23 may|
|----------|------|----------------|--------------|--------|-------|----------------------|
|1/5/25    |Completed|Moving Bot|Cam|6/5/25|Bot moves and chasis is rigid and reliable|Completed|
|1/5/25    |In progress|Motor optimizing - Wheels|Cam|15/5/25||Implementing PID to the robot|
|1/5/25    |Completed|Motor optimizing - Camera|Cam|25/5/25|The camera initializes at the start and sets to a consistent positions across runs|Camera position is set for the first three quadrants but is not set in the 'up' position for the final quadrant|
|1/5/25    |In progress|Bot body - 3d printed|Cohen|15/5/25||Needs to be checked to ensure no wires are going to be in the way of the robots movement|
|7/5/25    |Complete|Camera motor mount|Cohen|8/5/25|Mounts great - stable|Completed|
|22/5/25    |Complete|Switch wheels to front|Cam|22/5/25|Wheels swapped to front to make the camera closer to the wheel motors|Completed|

#### Testing
|START DATE|STATUS|TASK DESCRIPTION|RESPONSIBILITY|DEADLINE|OUTCOME|
|----------|------|----------------|--------------|--------|-------|
|6/5/25    |Completed |Line detection test 1|All|8/5/25|First test for the lines work but the motors were set to the incorret motor numbers|
|6/5/25    |Completed |Gate open test 1|All|8/5/25|We were able to comunicate with the door but unable to send the password back to the gate so the gate did not open|
|6/5/25    |Completed|Forward test 1|All|6/5/25|Robot went backwards|
|6/5/25    |Completed|Line dection test 2|All|6/5/25|Robot was able to see line - once the robot lost line the robot stopped|
|7/5/25    |Completed |Camera test 1 |Jessica and Cohen |7/5/25 |The motor on the robot was faulty - we tested and switched the motor out.|
|7/5/25   |Completed |Phase 2 - test 1 |Osahne and Helene|15/5/25|Robot followed the line-stoped when it saw red.camra was manualy adjusted downward to prevent the possiblity of seeing two lines|
|8/5/25   |Completed |Phase 2 - test 2 |All|15/5/25|Robot would lose line on some turns and shoot off|
|8/5/25   |Completed |Phase 1 - test 3 |All|15/5/25|An update to the git has broken phase 1 - robot moves to fast and loses line - door now shuts on robot|
|15/5/25   |Completed |Phase 3 - test 1 |Jessica and Oshane|15/5/25|Robot is able to navigate its way through the maze, but due to the postion of the camera it isn't able to make desicions on directions soon enough. To fix this we are looking at moving the camera closer to the body of the bot|
|22/5/25   |Completed |Phase 3 - test 2 |All|2/5/25|Robot is unable to detect line ahead of it and therefore kept turning left.|
|22/5/25   |Completed |Phase 4 - test 1 |Cam and Oshane|22/5/25|Bot was able to find and go to Red and Green cylinder and not hit them. Working on detecting Blue pillar|
|22/5/25   |Not started |Phase 5 - First test ||22/5/25||


---
